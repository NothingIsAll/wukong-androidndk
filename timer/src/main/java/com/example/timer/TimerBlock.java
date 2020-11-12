package com.example.timer;

import android.os.ParcelUuid;
import android.os.SystemClock;

import java.util.Random;

public class TimerBlock {

    static {
        System.loadLibrary("flltimer");
    }

    public native void blockTimer(int maxtime);

    public boolean cancell =false;
    public Random r;
    public void audioIOSimulate(){
        r = new Random(1);
        new Thread(new Runnable() {
            @Override
            public void run() {
                cancell = true;
                while (cancell){
                    int usems = r.nextInt(100);
                    SystemClock.sleep(usems);
                    blockTimer(50);

                }
            }
        }).start();


    }

    public void cancelRuning(){
        cancell = false;
    }

}
