/*
**
** Copyright (C) 2008, The Android Open Source Project
** Copyright (C) 2008 HTC Inc.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

//#define LOG_NDEBUG 0
#define LOG_TAG "CameraService"
#include <utils/Log.h>

#include <utils/IServiceManager.h>
#include <utils/IPCThreadState.h>
#include <utils/String16.h>
#include <utils/Errors.h>
#include <utils/MemoryBase.h>
#include <utils/MemoryHeapBase.h>
#include <ui/ICameraService.h>

#include <media/mediaplayer.h>
#include <media/AudioSystem.h>
#include "CameraService.h"

#include <cutils/properties.h>

namespace android {

extern "C" {
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
}

// When you enable this, as well as DEBUG_REFS=1 and
// DEBUG_REFS_ENABLED_BY_DEFAULT=0 in libutils/RefBase.cpp, this will track all
// references to the CameraService::Client in order to catch the case where the
// client is being destroyed while a callback from the CameraHardwareInterface
// is outstanding.  This is a serious bug because if we make another call into
// CameraHardwreInterface that itself triggers a callback, we will deadlock.

#define DEBUG_CLIENT_REFERENCES 0

#define PICTURE_TIMEOUT seconds(5)

#define DEBUG_DUMP_PREVIEW_FRAME_TO_FILE 0 /* n-th frame to write */
#define DEBUG_DUMP_JPEG_SNAPSHOT_TO_FILE 0
#define DEBUG_DUMP_YUV_SNAPSHOT_TO_FILE 0

#if DEBUG_DUMP_PREVIEW_FRAME_TO_FILE
static int debug_frame_cnt;
#endif

// ----------------------------------------------------------------------------

void CameraService::instantiate() {
    defaultServiceManager()->addService(
            String16("media.camera"), new CameraService());
}

// ----------------------------------------------------------------------------

CameraService::CameraService() :
    BnCameraService()
{
    LOGI("CameraService started: pid=%d", getpid());
}

CameraService::~CameraService()
{
    if (mClient != 0) {
        LOGE("mClient was still connected in destructor!");
    }
}

sp<ICamera> CameraService::connect(const sp<ICameraClient>& cameraClient)
{
    LOGD("Connect E from ICameraClient %p", cameraClient->asBinder().get());

    Mutex::Autolock lock(mLock);
    sp<Client> client;
    if (mClient != 0) {
        sp<Client> currentClient = mClient.promote();
        if (currentClient != 0) {
            sp<ICameraClient> currentCameraClient(currentClient->getCameraClient());
            if (cameraClient->asBinder() == currentCameraClient->asBinder()) {
                // this is the same client reconnecting...
                LOGD("Connect X same client (%p) is reconnecting...", cameraClient->asBinder().get());
                return currentClient;
            } else {
                // it's another client... reject it
                LOGD("new client (%p) attempting to connect - rejected", cameraClient->asBinder().get());
                return client;
            }
        } else {
            // can't promote, the previous client has died...
            LOGD("new client connecting, old reference was dangling...");
            mClient.clear();
        }
    }

    // create a new Client object
    client = new Client(this, cameraClient, IPCThreadState::self()->getCallingPid());
    mClient = client;
#if DEBUG_CLIENT_REFERENCES
    // Enable tracking for this object, and track increments and decrements of
    // the refcount.
    client->trackMe(true, true);
#endif
    LOGD("Connect X");
    return client;
}

void CameraService::removeClient(const sp<ICameraClient>& cameraClient)
{
    // declar this outside the lock to make absolutely sure the
    // destructor won't be called with the lock held.
    sp<Client> client;

    Mutex::Autolock lock(mLock);

    if (mClient == 0) {
        // This happens when we have already disconnected.
        LOGV("mClient is null.");
        return;
    }

    // Promote mClient. It should never fail because we're called from
    // a binder call, so someone has to have a strong reference.
    client = mClient.promote();
    if (client == 0) {
        LOGW("can't get a strong reference on mClient!");
        mClient.clear();
        return;
    }

    if (cameraClient->asBinder() != client->getCameraClient()->asBinder()) {
        // ugh! that's not our client!!
        LOGW("removeClient() called, but mClient doesn't match!");
    } else {
        // okay, good, forget about mClient
        mClient.clear();
    }
}

static sp<MediaPlayer> newMediaPlayer(const char *file)
{
    sp<MediaPlayer> mp = new MediaPlayer();
    if (mp->setDataSource(file) == NO_ERROR) {
        char value[PROPERTY_VALUE_MAX];
        property_get("ro.camera.sound.forced", value, "0");
        if (atoi(value)) {
            mp->setAudioStreamType(AudioSystem::ENFORCED_AUDIBLE);
        } else {
            mp->setAudioStreamType(AudioSystem::SYSTEM);
        }
        mp->prepare();
    } else {
        mp.clear();
        LOGE("Failed to load CameraService sounds.");
    }
    return mp;
}

CameraService::Client::Client(const sp<CameraService>& cameraService,
        const sp<ICameraClient>& cameraClient, pid_t clientPid)
{
    LOGD("Client E constructor");
    mCameraService = cameraService;
    mCameraClient = cameraClient;
    mClientPid = clientPid;
    mHardware = openCameraHardware();
    mUseOverlay = mHardware->useOverlay();

    mMediaPlayerClick = newMediaPlayer("/system/media/audio/ui/camera_click.ogg");
    mMediaPlayerBeep = newMediaPlayer("/system/media/audio/ui/VideoRecord.ogg");

    // Callback is disabled by default
    mPreviewCallbackFlag = FRAME_CALLBACK_FLAG_NOOP;
    LOGD("Client X constructor");
}

status_t CameraService::Client::checkPid()
{
    if (mClientPid == IPCThreadState::self()->getCallingPid()) return NO_ERROR;
    LOGW("Attempt to use locked camera (%p) from different process", getCameraClient()->asBinder().get());
    return -EBUSY;
}

status_t CameraService::Client::lock()
{
    Mutex::Autolock _l(mLock);
    // lock camera to this client if the the camera is unlocked
    if (mClientPid == 0) {
        mClientPid = IPCThreadState::self()->getCallingPid();
        return NO_ERROR;
    }
    // returns NO_ERROR if the client already owns the camera, -EBUSY otherwise
    return checkPid();
}

status_t CameraService::Client::unlock()
{
    Mutex::Autolock _l(mLock);
    // allow anyone to use camera
    LOGV("unlock (%p)", getCameraClient()->asBinder().get());
    status_t result = checkPid();
    if (result == NO_ERROR) mClientPid = 0;
    return result;
}

status_t CameraService::Client::connect(const sp<ICameraClient>& client)
{
    // connect a new process to the camera
    LOGV("connect (%p)", client->asBinder().get());

    // I hate this hack, but things get really ugly when the media recorder
    // service is handing back the camera to the app. The ICameraClient
    // destructor will be called during the same IPC, making it look like
    // the remote client is trying to disconnect. This hack temporarily
    // sets the mClientPid to an invalid pid to prevent the hardware from
    //  being torn down.
    {

        // hold a reference to the old client or we will deadlock if the client is
        // in the same process and we hold the lock when we remove the reference
        sp<ICameraClient> oldClient;
        {
            Mutex::Autolock _l(mLock);
            if (mClientPid != 0) {
                LOGW("Tried to connect to locked camera");
                return -EBUSY;
            }
            oldClient = mCameraClient;

            // did the client actually change?
            if (client->asBinder() == mCameraClient->asBinder()) return NO_ERROR;

            mCameraClient = client;
            mClientPid = -1;
            mPreviewCallbackFlag = FRAME_CALLBACK_FLAG_NOOP;
            LOGV("connect new process (%d) to existing camera client", mClientPid);
        }

    }
    // the old client destructor is called when oldClient goes out of scope
    // now we set the new PID to lock the interface again
    mClientPid = IPCThreadState::self()->getCallingPid();

    return NO_ERROR;
}

#if HAVE_ANDROID_OS
static void *unregister_surface(void *arg)
{
    ISurface *surface = (ISurface *)arg;
    surface->unregisterBuffers();
    IPCThreadState::self()->flushCommands();
    return NULL;
}
#endif

CameraService::Client::~Client()
{
    // tear down client
    LOGD("Client (%p)  E destructor", getCameraClient()->asBinder().get());
    if (mSurface != 0 && !mUseOverlay) {
#if HAVE_ANDROID_OS
        pthread_t thr;
        // We unregister the buffers in a different thread because binder does
        // not let us make sychronous transactions in a binder destructor (that
        // is, upon our reaching a refcount of zero.)
        pthread_create(&thr, NULL,
                       unregister_surface,
                       mSurface.get());
        pthread_join(thr, NULL);
#else
        mSurface->unregisterBuffers();
#endif
    }

    if (mMediaPlayerBeep.get() != NULL) {
        mMediaPlayerBeep->disconnect();
        mMediaPlayerBeep.clear();
    }
    if (mMediaPlayerClick.get() != NULL) {
        mMediaPlayerClick->disconnect();
        mMediaPlayerClick.clear();
    }

    // make sure we tear down the hardware
    mClientPid = IPCThreadState::self()->getCallingPid();
    disconnect();
    LOGD("Client X destructor");
}

void CameraService::Client::disconnect()
{
    LOGD("Client (%p) E disconnect from (%d)",
            getCameraClient()->asBinder().get(),
            IPCThreadState::self()->getCallingPid());
    Mutex::Autolock lock(mLock);
    if (mClientPid <= 0) {
        LOGV("camera is unlocked, don't tear down hardware");
        return;
    }
    if (checkPid() != NO_ERROR) {
        LOGV("Different client - don't disconnect");
        return;
    }

    mCameraService->removeClient(mCameraClient);
    if (mHardware != 0) {
        LOGV("hardware teardown");
        // Before destroying mHardware, we must make sure it's in the
        // idle state.
        mHardware->stopPreview();
        // Cancel all picture callbacks.
        mHardware->cancelPicture(true, true, true);
        // Release the hardware resources.
        mHardware->release();
    }
    mHardware.clear();
    LOGD("Client X disconnect");
}

// pass the buffered ISurface to the camera service
status_t CameraService::Client::setPreviewDisplay(const sp<ISurface>& surface)
{
    LOGD("setPreviewDisplay(%p)", surface.get());
    Mutex::Autolock lock(mLock);
    status_t result = checkPid();
    if (result != NO_ERROR) return result;
    Mutex::Autolock surfaceLock(mSurfaceLock);
    // asBinder() is safe on NULL (returns NULL)
    if (surface->asBinder() != mSurface->asBinder()) {
        if (mSurface != 0 && !mUseOverlay) {
            LOGD("clearing old preview surface %p", mSurface.get());
            mSurface->unregisterBuffers();
        }
        mSurface = surface;
    }
    return NO_ERROR;
}

// set the preview callback flag to affect how the received frames from
// preview are handled.
void CameraService::Client::setPreviewCallbackFlag(int callback_flag)
{
    LOGV("setPreviewCallbackFlag");
    Mutex::Autolock lock(mLock);
    if (checkPid() != NO_ERROR) return;
    mPreviewCallbackFlag = callback_flag;
}

// start preview mode, must call setPreviewDisplay first
status_t CameraService::Client::startCameraMode(camera_mode mode)
{
    LOGD("startCameraMode(%d)", mode);

    /* we cannot call into mHardware with mLock held because
     * mHardware has callbacks onto us which acquire this lock
     */

    Mutex::Autolock lock(mLock);
    status_t result = checkPid();
    if (result != NO_ERROR) return result;

    if (mHardware == 0) {
        LOGE("mHardware is NULL, returning.");
        return INVALID_OPERATION;
    }

    if (mSurface == 0) {
        LOGE("setPreviewDisplay must be called before startCameraMode!");
        return INVALID_OPERATION;
    }

    switch(mode) {
    case CAMERA_RECORDING_MODE:
        return startRecordingMode();

    default: // CAMERA_PREVIEW_MODE
        return startPreviewMode();
    }
}

status_t CameraService::Client::startRecordingMode()
{
    LOGV("startRecordingMode");

    status_t ret = UNKNOWN_ERROR;

    // if preview has not been started, start preview first
    if (!mHardware->previewEnabled()) {
        ret = startPreviewMode();
        if (ret != NO_ERROR) {
            return ret;
        }
    }

    // if recording has been enabled, nothing needs to be done
    if (mHardware->recordingEnabled()) {
        return NO_ERROR;
    }

    // start recording mode
    ret = mHardware->startRecording(recordingCallback,
                                    mCameraService.get());
    if (ret != NO_ERROR) {
        LOGE("mHardware->startRecording() failed with status %d", ret);
    }
    return ret;
}

status_t CameraService::Client::startPreviewMode()
{
    LOGV("startPreviewMode");

    // if preview has been enabled, nothing needs to be done
    if (mHardware->previewEnabled()) {
        return NO_ERROR;
    }

    // start preview mode
#if DEBUG_DUMP_PREVIEW_FRAME_TO_FILE
    debug_frame_cnt = 0;
#endif
    status_t ret = UNKNOWN_ERROR;
    int w, h;
    CameraParameters params(mHardware->getParameters());
    params.getPreviewSize(&w, &h);

    if (mUseOverlay) {
        const char *format = params.getPreviewFormat();
        int fmt;
        LOGD("Use Overlays");
        if (!strcmp(format, "yuv422i"))
            fmt = OVERLAY_FORMAT_YCbCr_422_I;
        else if (!strcmp(format, "rgb565"))
            fmt = OVERLAY_FORMAT_RGB_565;
        else {
            LOGE("Invalid preview format for overlays");
            return -EINVAL;
        }
        sp<OverlayRef> ref = mSurface->createOverlay(w, h, fmt);
        ret = mHardware->setOverlay(new Overlay(ref));
        if (ret != NO_ERROR) {
            LOGE("mHardware->setOverlay() failed with status %d\n", ret);
            return ret;
        }
        ret = mHardware->startPreview(NULL, mCameraService.get());
        if (ret != NO_ERROR)
            LOGE("mHardware->startPreview() failed with status %d\n", ret);

    } else {
        ret = mHardware->startPreview(previewCallback,
                                      mCameraService.get());
        if (ret == NO_ERROR) {

            mSurface->unregisterBuffers();

            uint32_t transform = 0;
            if (params.getOrientation() ==
                CameraParameters::CAMERA_ORIENTATION_PORTRAIT) {
              LOGV("portrait mode");
              transform = ISurface::BufferHeap::ROT_90;
            }
            ISurface::BufferHeap buffers(w, h, w, h,
                                         PIXEL_FORMAT_YCbCr_420_SP,
                                         transform,
                                         0,
                                         mHardware->getPreviewHeap());

            mSurface->registerBuffers(buffers);
        } else {
          LOGE("mHardware->startPreview() failed with status %d", ret);
        }
    }
    return ret;
}

status_t CameraService::Client::startPreview()
{
    return startCameraMode(CAMERA_PREVIEW_MODE);
}

status_t CameraService::Client::startRecording()
{
    if (mMediaPlayerBeep.get() != NULL) {
        mMediaPlayerBeep->seekTo(0);
        mMediaPlayerBeep->start();
    }
    return startCameraMode(CAMERA_RECORDING_MODE);
}

// stop preview mode
void CameraService::Client::stopPreview()
{
    LOGD("stopPreview()");

    Mutex::Autolock lock(mLock);
    if (checkPid() != NO_ERROR) return;

    if (mHardware == 0) {
        LOGE("mHardware is NULL, returning.");
        return;
    }

    mHardware->stopPreview();
    LOGD("stopPreview(), hardware stopped OK");

    if (mSurface != 0 && !mUseOverlay) {
        mSurface->unregisterBuffers();
    }
    mPreviewBuffer.clear();
}

// stop recording mode
void CameraService::Client::stopRecording()
{
    LOGV("stopRecording()");

    Mutex::Autolock lock(mLock);
    if (checkPid() != NO_ERROR) return;

    if (mHardware == 0) {
        LOGE("mHardware is NULL, returning.");
        return;
    }

    if (mMediaPlayerBeep.get() != NULL) {
        mMediaPlayerBeep->seekTo(0);
        mMediaPlayerBeep->start();
    }
    mHardware->stopRecording();
    LOGV("stopRecording(), hardware stopped OK");
    mPreviewBuffer.clear();
}

// release a recording frame
void CameraService::Client::releaseRecordingFrame(const sp<IMemory>& mem)
{
    LOGV("releaseRecordingFrame()");

    Mutex::Autolock lock(mLock);
    if (checkPid() != NO_ERROR) return;

    if (mHardware == 0) {
        LOGE("mHardware is NULL, returning.");
        return;
    }

    mHardware->releaseRecordingFrame(mem);
}

bool CameraService::Client::previewEnabled()
{
    Mutex::Autolock lock(mLock);
    if (mHardware == 0) return false;
    return mHardware->previewEnabled();
}

bool CameraService::Client::recordingEnabled()
{
    Mutex::Autolock lock(mLock);
    if (mHardware == 0) return false;
    return mHardware->recordingEnabled();
}

// Safely retrieves a strong pointer to the client during a hardware callback.
sp<CameraService::Client> CameraService::Client::getClientFromCookie(void* user)
{
    sp<Client> client = 0;
    CameraService *service = static_cast<CameraService*>(user);
    if (service != NULL) {
        Mutex::Autolock ourLock(service->mLock);
        if (service->mClient != 0) {
            client = service->mClient.promote();
            if (client == 0) {
                LOGE("getClientFromCookie: client appears to have died");
                service->mClient.clear();
            }
        } else {
            LOGE("getClientFromCookie: got callback but client was NULL");
        }
    }
    return client;
}


#if DEBUG_DUMP_JPEG_SNAPSHOT_TO_FILE || \
    DEBUG_DUMP_YUV_SNAPSHOT_TO_FILE || \
    DEBUG_DUMP_PREVIEW_FRAME_TO_FILE
static void dump_to_file(const char *fname,
                         uint8_t *buf, uint32_t size)
{
    int nw, cnt = 0;
    uint32_t written = 0;

    LOGD("opening file [%s]\n", fname);
    int fd = open(fname, O_RDWR | O_CREAT);
    if (fd < 0) {
        LOGE("failed to create file [%s]: %s", fname, strerror(errno));
        return;
    }

    LOGD("writing %d bytes to file [%s]\n", size, fname);
    while (written < size) {
        nw = ::write(fd,
                     buf + written,
                     size - written);
        if (nw < 0) {
            LOGE("failed to write to file [%s]: %s",
                 fname, strerror(errno));
            break;
        }
        written += nw;
        cnt++;
    }
    LOGD("done writing %d bytes to file [%s] in %d passes\n",
         size, fname, cnt);
    ::close(fd);
}
#endif

// preview callback - frame buffer update
void CameraService::Client::previewCallback(const sp<IMemory>& mem, void* user)
{
    LOGV("previewCallback()");
    sp<Client> client = getClientFromCookie(user);
    if (client == 0) {
        return;
    }

#if DEBUG_HEAP_LEAKS && 0 // debugging
    if (gWeakHeap == NULL) {
        ssize_t offset;
        size_t size;
        sp<IMemoryHeap> heap = mem->getMemory(&offset, &size);
        if (gWeakHeap != heap) {
            LOGD("SETTING PREVIEW HEAP");
            heap->trackMe(true, true);
            gWeakHeap = heap;
        }
    }
#endif

#if DEBUG_DUMP_PREVIEW_FRAME_TO_FILE
    {
        if (debug_frame_cnt++ == DEBUG_DUMP_PREVIEW_FRAME_TO_FILE) {
            ssize_t offset;
            size_t size;
            sp<IMemoryHeap> heap = mem->getMemory(&offset, &size);
            dump_to_file("/data/preview.yuv",
                         (uint8_t *)heap->base() + offset, size);
        }
    }
#endif

    // The strong pointer guarantees the client will exist, but no lock is held.
    client->postPreviewFrame(mem);

#if DEBUG_CLIENT_REFERENCES
    //**** if the client's refcount is 1, then we are about to destroy it here,
    // which is bad--print all refcounts.
    if (client->getStrongCount() == 1) {
        LOGE("++++++++++++++++ (PREVIEW) THIS WILL CAUSE A LOCKUP!");
        client->printRefs();
    }
#endif
}

// recording callback
void CameraService::Client::recordingCallback(const sp<IMemory>& mem, void* user)
{
    LOGV("recordingCallback");
    sp<Client> client = getClientFromCookie(user);
    if (client == 0) {
        return;
    }
    // The strong pointer guarantees the client will exist, but no lock is held.
    client->postRecordingFrame(mem);
}

// take a picture - image is returned in callback
status_t CameraService::Client::autoFocus()
{
    LOGV("autoFocus");

    Mutex::Autolock lock(mLock);
    status_t result = checkPid();
    if (result != NO_ERROR) return result;

    if (mHardware == 0) {
        LOGE("mHardware is NULL, returning.");
        return INVALID_OPERATION;
    }

    return mHardware->autoFocus(autoFocusCallback,
                                mCameraService.get());
}

// take a picture - image is returned in callback
status_t CameraService::Client::takePicture()
{
    LOGD("takePicture");

    Mutex::Autolock lock(mLock);
    status_t result = checkPid();
    if (result != NO_ERROR) return result;

    if (mHardware == 0) {
        LOGE("mHardware is NULL, returning.");
        return INVALID_OPERATION;
    }

    return mHardware->takePicture(shutterCallback,
                                  yuvPictureCallback,
                                  jpegPictureCallback,
                                  mCameraService.get());
}

// picture callback - snapshot taken
void CameraService::Client::shutterCallback(void *user)
{
    sp<Client> client = getClientFromCookie(user);
    if (client == 0) {
        return;
    }

    // Play shutter sound.
    if (client->mMediaPlayerClick.get() != NULL) {
        client->mMediaPlayerClick->seekTo(0);
        client->mMediaPlayerClick->start();
    }

    // Screen goes black after the buffer is unregistered.
    if (client->mSurface != 0 && !client->mUseOverlay) {
        client->mSurface->unregisterBuffers();
    }

    client->postShutter();

    // It takes some time before yuvPicture callback to be called.
    // Register the buffer for raw image here to reduce latency.
    if (client->mSurface != 0 && !client->mUseOverlay) {
        int w, h;
        CameraParameters params(client->mHardware->getParameters());
        params.getPictureSize(&w, &h);
        uint32_t transform = 0;
        if (params.getOrientation() == CameraParameters::CAMERA_ORIENTATION_PORTRAIT) {
            LOGV("portrait mode");
            transform = ISurface::BufferHeap::ROT_90;
        }
        ISurface::BufferHeap buffers(w, h, w, h,
            PIXEL_FORMAT_YCbCr_420_SP, transform, 0, client->mHardware->getRawHeap());

        client->mSurface->registerBuffers(buffers);
    }
}

// picture callback - raw image ready
void CameraService::Client::yuvPictureCallback(const sp<IMemory>& mem,
                                               void *user)
{
    sp<Client> client = getClientFromCookie(user);
    if (client == 0) {
        return;
    }
    if (mem == NULL) {
        client->postRaw(NULL);
        client->postError(UNKNOWN_ERROR);
        return;
    }

    ssize_t offset;
    size_t size;
    sp<IMemoryHeap> heap = mem->getMemory(&offset, &size);
#if DEBUG_HEAP_LEAKS && 0 // debugging
    gWeakHeap = heap; // debugging
#endif

    //LOGV("yuvPictureCallback(%d, %d, %p)", offset, size, user);
#if DEBUG_DUMP_YUV_SNAPSHOT_TO_FILE // for testing pursposes only
    dump_to_file("/data/photo.yuv",
                 (uint8_t *)heap->base() + offset, size);
#endif

    // Put the YUV version of the snapshot in the preview display.
    if (client->mSurface != 0 && !client->mUseOverlay) {
        client->mSurface->postBuffer(offset);
    }

    client->postRaw(mem);

#if DEBUG_CLIENT_REFERENCES
    //**** if the client's refcount is 1, then we are about to destroy it here,
    // which is bad--print all refcounts.
    if (client->getStrongCount() == 1) {
        LOGE("++++++++++++++++ (RAW) THIS WILL CAUSE A LOCKUP!");
        client->printRefs();
    }
#endif
}

// picture callback - jpeg ready
void CameraService::Client::jpegPictureCallback(const sp<IMemory>& mem, void *user)
{
    sp<Client> client = getClientFromCookie(user);
    if (client == 0) {
        return;
    }
    if (mem == NULL) {
        client->postJpeg(NULL);
        client->postError(UNKNOWN_ERROR);
        return;
    }

    /** We absolutely CANNOT call into user code with a lock held **/

#if DEBUG_DUMP_JPEG_SNAPSHOT_TO_FILE // for testing pursposes only
    {
        ssize_t offset;
        size_t size;
        sp<IMemoryHeap> heap = mem->getMemory(&offset, &size);
        dump_to_file("/data/photo.jpg",
                     (uint8_t *)heap->base() + offset, size);
    }
#endif

    client->postJpeg(mem);

#if DEBUG_CLIENT_REFERENCES
    //**** if the client's refcount is 1, then we are about to destroy it here,
    // which is bad--print all refcounts.
    if (client->getStrongCount() == 1) {
        LOGE("++++++++++++++++ (JPEG) THIS WILL CAUSE A LOCKUP!");
        client->printRefs();
    }
#endif
}

void CameraService::Client::autoFocusCallback(bool focused, void *user)
{
    LOGV("autoFocusCallback");

    sp<Client> client = getClientFromCookie(user);
    if (client == 0) {
        return;
    }

    client->postAutoFocus(focused);

#if DEBUG_CLIENT_REFERENCES
    if (client->getStrongCount() == 1) {
        LOGE("++++++++++++++++ (AUTOFOCUS) THIS WILL CAUSE A LOCKUP!");
        client->printRefs();
    }
#endif
}

// set preview/capture parameters - key/value pairs
status_t CameraService::Client::setParameters(const String8& params)
{
    LOGD("setParameters(%s)", params.string());

    Mutex::Autolock lock(mLock);
    status_t result = checkPid();
    if (result != NO_ERROR) return result;

    if (mHardware == 0) {
        LOGE("mHardware is NULL, returning.");
        return INVALID_OPERATION;
    }

    CameraParameters p(params);
    mHardware->setParameters(p);
    return NO_ERROR;
}

// get preview/capture parameters - key/value pairs
String8 CameraService::Client::getParameters() const
{
    LOGD("getParameters");

    Mutex::Autolock lock(mLock);

    if (mHardware == 0) {
        LOGE("mHardware is NULL, returning.");
        return String8();
    }

    return mHardware->getParameters().flatten();
}

void CameraService::Client::postAutoFocus(bool focused)
{
    LOGV("postAutoFocus");
    mCameraClient->autoFocusCallback(focused);
}

void CameraService::Client::postShutter()
{
    mCameraClient->shutterCallback();
}

void CameraService::Client::postRaw(const sp<IMemory>& mem)
{
    LOGD("postRaw");
    mCameraClient->rawCallback(mem);
}

void CameraService::Client::postJpeg(const sp<IMemory>& mem)
{
    LOGD("postJpeg");
    mCameraClient->jpegCallback(mem);
}

void CameraService::Client::copyFrameAndPostCopiedFrame(sp<IMemoryHeap> heap, size_t offset, size_t size)
{
    LOGV("copyFrameAndPostCopiedFrame");
    // It is necessary to copy out of pmem before sending this to
    // the callback. For efficiency, reuse the same MemoryHeapBase
    // provided it's big enough. Don't allocate the memory or
    // perform the copy if there's no callback.
    if (mPreviewBuffer == 0) {
        mPreviewBuffer = new MemoryHeapBase(size, 0, NULL);
    } else if (size > mPreviewBuffer->virtualSize()) {
        mPreviewBuffer.clear();
        mPreviewBuffer = new MemoryHeapBase(size, 0, NULL);
        if (mPreviewBuffer == 0) {
            LOGE("failed to allocate space for preview buffer");
            return;
        }
    }
    memcpy(mPreviewBuffer->base(),
           (uint8_t *)heap->base() + offset, size);

    sp<MemoryBase> frame = new MemoryBase(mPreviewBuffer, 0, size);
    if (frame == 0) {
        LOGE("failed to allocate space for frame callback");
        return;
    }
    mCameraClient->previewCallback(frame);
}

void CameraService::Client::postRecordingFrame(const sp<IMemory>& frame)
{
    LOGV("postRecordingFrame");
    if (frame == 0) {
        LOGW("frame is a null pointer");
        return;
    }
    mCameraClient->recordingCallback(frame);
}

void CameraService::Client::postPreviewFrame(const sp<IMemory>& mem)
{
    LOGV("postPreviewFrame");
    if (mem == 0) {
        LOGW("mem is a null pointer");
        return;
    }

    ssize_t offset;
    size_t size;
    sp<IMemoryHeap> heap = mem->getMemory(&offset, &size);
    {
        Mutex::Autolock surfaceLock(mSurfaceLock);
        if (mSurface != NULL) {
            mSurface->postBuffer(offset);
        }
    }

    // Is the callback enabled or not?
    if (!(mPreviewCallbackFlag & FRAME_CALLBACK_FLAG_ENABLE_MASK)) {
        // If the enable bit is off, the copy-out and one-shot bits are ignored
        LOGV("frame callback is diabled");
        return;
    }

    // Is the received frame copied out or not?
    if (mPreviewCallbackFlag & FRAME_CALLBACK_FLAG_COPY_OUT_MASK) {
        LOGV("frame is copied out");
        copyFrameAndPostCopiedFrame(heap, offset, size);
    } else {
        LOGV("frame is directly sent out without copying");
        mCameraClient->previewCallback(mem);
    }

    // Is this is one-shot only?
    if (mPreviewCallbackFlag & FRAME_CALLBACK_FLAG_ONE_SHOT_MASK) {
        LOGV("One-shot only, thus clear the bits and disable frame callback");
        mPreviewCallbackFlag &= ~(FRAME_CALLBACK_FLAG_ONE_SHOT_MASK |
                                FRAME_CALLBACK_FLAG_COPY_OUT_MASK |
                                FRAME_CALLBACK_FLAG_ENABLE_MASK);
    }
}

void CameraService::Client::postError(status_t error)
{
    mCameraClient->errorCallback(error);
}

status_t CameraService::dump(int fd, const Vector<String16>& args)
{
    const size_t SIZE = 256;
    char buffer[SIZE];
    String8 result;
    if (checkCallingPermission(String16("android.permission.DUMP")) == false) {
        snprintf(buffer, SIZE, "Permission Denial: "
                "can't dump CameraService from pid=%d, uid=%d\n",
                IPCThreadState::self()->getCallingPid(),
                IPCThreadState::self()->getCallingUid());
        result.append(buffer);
        write(fd, result.string(), result.size());
    } else {
        AutoMutex lock(&mLock);
        if (mClient != 0) {
            sp<Client> currentClient = mClient.promote();
            sprintf(buffer, "Client (%p) PID: %d\n",
                    currentClient->getCameraClient()->asBinder().get(),
                    currentClient->mClientPid);
            result.append(buffer);
            write(fd, result.string(), result.size());
            currentClient->mHardware->dump(fd, args);
        } else {
            result.append("No camera client yet.\n");
            write(fd, result.string(), result.size());
        }
    }
    return NO_ERROR;
}



#define CHECK_INTERFACE(interface, data, reply) \
        do { if (!data.enforceInterface(interface::getInterfaceDescriptor())) { \
            LOGW("Call incorrectly routed to " #interface); \
            return PERMISSION_DENIED; \
        } } while (0)

status_t CameraService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    // permission checks...
    switch (code) {
        case BnCameraService::CONNECT:
            IPCThreadState* ipc = IPCThreadState::self();
            const int pid = ipc->getCallingPid();
            const int self_pid = getpid();
            if (pid != self_pid) {
                // we're called from a different process, do the real check
                if (!checkCallingPermission(
                        String16("android.permission.CAMERA")))
                {
                    const int uid = ipc->getCallingUid();
                    LOGE("Permission Denial: "
                            "can't use the camera pid=%d, uid=%d", pid, uid);
                    return PERMISSION_DENIED;
                }
            }
            break;
    }

    status_t err = BnCameraService::onTransact(code, data, reply, flags);

#if DEBUG_HEAP_LEAKS
    LOGD("+++ onTransact err %d code %d", err, code);

    if (err == UNKNOWN_TRANSACTION || err == PERMISSION_DENIED) {
        // the 'service' command interrogates this binder for its name, and then supplies it
        // even for the debugging commands.  that means we need to check for it here, using
        // ISurfaceComposer (since we delegated the INTERFACE_TRANSACTION handling to
        // BnSurfaceComposer before falling through to this code).

        LOGD("+++ onTransact code %d", code);

        CHECK_INTERFACE(ICameraService, data, reply);

        switch(code) {
        case 1000:
        {
            if (gWeakHeap != 0) {
                sp<IMemoryHeap> h = gWeakHeap.promote();
                IMemoryHeap *p = gWeakHeap.unsafe_get();
                LOGD("CHECKING WEAK REFERENCE %p (%p)", h.get(), p);
                if (h != 0)
                    h->printRefs();
                bool attempt_to_delete = data.readInt32() == 1;
                if (attempt_to_delete) {
                    // NOT SAFE!
                    LOGD("DELETING WEAK REFERENCE %p (%p)", h.get(), p);
                    if (p) delete p;
                }
                return NO_ERROR;
            }
        }
        break;
        default:
            break;
        }
    }
#endif // DEBUG_HEAP_LEAKS

    return err;
}


}; // namespace android