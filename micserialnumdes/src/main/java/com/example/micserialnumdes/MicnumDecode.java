package com.example.micserialnumdes;

public class MicnumDecode {
    static {
        System.loadLibrary("micdecodejni");
    }
    public native int setSerialnum(String num);
    public native String getdecode();
    public native boolean isHIDdmic();
    public native int hidkeyID();
}
