#CVE-2009-2348
>Three different Commits were found here related to the same issue

More details [here] (http://www.cvedetails.com/cve/CVE-2009-2348/)

##Description
Android 1.5 CRBxx allows local users to bypass the (1) Manifest.permission.CAMERA (aka android.permission.CAMERA) and (2) Manifest.permission.AUDIO_RECORD (aka android.permission.RECORD_AUDIO) configuration settings by installing and executing an application that does not make a permission request before using the camera or microphone.		

##Additionnal Information
* Version Impacted : Android 1.5
* Role of the Component : Access Control

##CVSS Score & Vulnerability Types
* Cvss Score : 6.9
* CVSS Access : *Local*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [94] (http://cwe.mitre.org/data/definitions/94.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 5
* **Total Commit**: 3
* **Total modified file**: 4
* **Cloc**: 11


###Patch 1
####Description
 When we moved the media recorder to the media server process, we lost
  the permission check that was done at the process boundary in the
  AudioRecord binder interface because the AudioRecord object is created
  in the same process. This change adds a permission check in the
  MediaRecorderClient:setAudioSource() method.
  BUG=1868334
  
####Origin
* Language : CPP
* Origin of the bug : Design Error -> Unauthorized Access
* Location : [android/platform_frameworks_base] (https://github.com/android/platform_frameworks_base)

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 2
* **Cloc** : 4

You can find here [the corresponding commit] (https://github.com/android/platform_frameworks_base/commit/4d8adefd35efdea849611b8b02d61f9517e47760)  and the different file [in this folder] (patch1/).

###Patch 2
####Description
AI 149135: Add RECORD_AUDIO permission to camera app.
  Due to an oversight, the RECORD_AUDIO permission was not being enforced.
  This change adds the permission to the camera app so that when it is
  enforced, it won't throw an exception.
  BUG=1868334
  
####Origin
* Language : XML
* Origin of the bug : Design Error -> Unauthorized Access
* Location : [android/platform_packages_apps_camera] (https://github.com/android/platform_packages_apps_camera)

#####Patch
  * **Kind of Patch** : Add Authorization permission
  * **Cycc** : 1
  * **Cloc** : 1
  
 You can find [the corresponding commit](https://github.com/android/platform_packages_apps_camera/commit/e655d54160e5a56d4909f2459eeae9012e9f187f) and the different file [here] (patch2/).

###Patch 3
####Description
AI 149135: Add RECORD_AUDIO permission to camera app.
  Due to an oversight, the RECORD_AUDIO permission was not being enforced.
  This change adds the permission to the camera app so that when it is
  enforced, it won't throw an exception.
  BUG=1868334
  
####Origin
* Language : CPP
* Origin of the bug : Debug -> Forget to remove a Debug feature
* Location : [android/platform_frameworks_base] (https://github.com/android/platform_frameworks_base)

#####Patch
  * **Kind of Patch** : Remove debugging condition/ remove Condition
  * **Cycc** : 5
  * **Cloc** : 6
  
 You can find [the corresponding commit](https://github.com/android/platform_frameworks_base/commit/7b7225c8fdbead25235c74811b30ff4ee690dc58) and the different file [here] (patch3/).
