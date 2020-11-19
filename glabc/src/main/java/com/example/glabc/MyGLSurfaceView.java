package com.example.glabc;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLSurfaceView extends GLSurfaceView {

    private static final String TAG = "MyGLSurfaceView";

    private MyGLRender myGLRender;
    private MyNativeRender myNativeRender;

    public MyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        XLog.LogOut("MyGLSurfaceView 2");
        //设置gpengl版本，
        //注意android系统版本对gl的版本限制
        //对应版本详细信息可以查看笔记
        this.setEGLContextClientVersion(3);//这里用的额opengl3.0版本
        myNativeRender = new MyNativeRender();
        myGLRender = new MyGLRender(myNativeRender);
        setRenderer(myGLRender);
        /**
         * 设置绘制模式
         * RENDERMODE_WHEN_DIRTY
         * when the surface is created, or when {@link #requestRender} is called.
         * RENDERMODE_CONTINUOUSLY
         * render不断地被系统调用
         */
        setRenderMode(RENDERMODE_CONTINUOUSLY);

    }
    public MyGLSurfaceView(Context context) {
        super(context);
        XLog.LogOut("MyGLSurfaceView 1");
//        this(context,null); //无论用哪个构造 都会进入带参构造
//        MyGLSurfaceView(Context context, AttributeSet attrs)
    }

    public MyNativeRender getNativeRender(){
        return myNativeRender;
    }

    public class MyGLRender implements GLSurfaceView.Renderer{

        private MyNativeRender myNativeRender;

        public MyGLRender(MyNativeRender myNativeRender){
            this.myNativeRender = myNativeRender;
        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            XLog.LogOut( "onSurfaceCreated() called with: gl = [" + gl + "], config = [" + config + "]");
            myNativeRender.native_onSurfaceCreated();
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            XLog.LogOut("onSurfaceChanged() called with: gl = [" + gl + "], width = [" + width + "], height = [" + height + "]");
            myNativeRender.native_OnSurfaceChanged(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
//            XLog.LogOut( "onDrawFrame() called with: gl = [" + gl + "]");
            myNativeRender.native_OnDrawFrame();
        }
    }

}
