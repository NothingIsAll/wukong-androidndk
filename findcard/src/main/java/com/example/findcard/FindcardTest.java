package com.example.findcard;

public class FindcardTest {

    static {
        System.loadLibrary("sofindcard");
    }

    public native void init();
    public native void loopgetcard();
    public native void stop();
}
