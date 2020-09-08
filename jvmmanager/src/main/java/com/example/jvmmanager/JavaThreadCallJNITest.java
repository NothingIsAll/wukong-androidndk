package com.example.jvmmanager;

public class JavaThreadCallJNITest {

    static {
        System.loadLibrary("javacalljni");
    }

    public native void init();

    public native void setjnicalljavaobj(JniThreadCallJavaCallBack jobj);

    public native void asyncinit();

    public native void createThread(int num);

    public native void destory();


}
