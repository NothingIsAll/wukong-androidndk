package com.example.jvmmanager;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    public Button bt_sync,bt_javathread,bt_jnithread,bt_cancellthread;
    public JavaThreadCallJNITest javaThreadCallJNITest;
    public Handler handler = new Handler(Looper.getMainLooper());

    public Runnable runnable = new Runnable() {
        @Override
        public void run() {
            javaThreadCallJNITest.asyncinit();
            handler.postDelayed(runnable, 50);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt_sync = findViewById(R.id.sync);
        bt_javathread = findViewById(R.id.javathread);
        bt_jnithread = findViewById(R.id.jnithread);
        bt_cancellthread = findViewById(R.id.cancellthread);
        bt_sync.setOnClickListener(this);
        bt_javathread.setOnClickListener(this);
        bt_jnithread.setOnClickListener(this);
        bt_cancellthread.setOnClickListener(this);
        javaThreadCallJNITest = new JavaThreadCallJNITest();
        javaThreadCallJNITest.setjnicalljavaobj(new JniThreadCallJavaCallBack());
    }

    public void handleThreadtest(){
        handler.postDelayed(runnable, 50);
    }
    public void javaThreadtest(){
        for (int i= 0;i<10;i++){
            new Thread(new Runnable() {
                @Override
                public void run() {
                    javaThreadCallJNITest.asyncinit();
                }
            }).start();
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.sync:
                javaThreadCallJNITest.init();
                break;
            case R.id.javathread:
                handleThreadtest();
//                javaThreadtest();
                break;
            case R.id.jnithread:
                javaThreadCallJNITest.createThread(10);
                break;
            case R.id.cancellthread:
                javaThreadCallJNITest.destory();
                break;
        }

    }
}
