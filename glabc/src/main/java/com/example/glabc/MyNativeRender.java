package com.example.glabc;

public class MyNativeRender {

    static {
        System.loadLibrary("glabc");
    }

    public native void native_OnInit();
    public native void native_OnUnInit();
    public native void native_SetImageData(int format,int width,int height,byte[] bytes);
    public native void native_onSurfaceCreated();
    public native void native_OnSurfaceChanged(int width,int height);
    public native void native_OnDrawFrame();

}
