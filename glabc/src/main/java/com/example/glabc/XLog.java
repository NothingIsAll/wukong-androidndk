package com.example.glabc;

import android.util.Log;

public class XLog {
    private static String TAG = "XLOG";
    private static boolean isdebug = true;

    public static void i(String str){
        if (isdebug) {
            System.out.println(Thread.currentThread().getName() +"   "+ str);
        }
    }
    public static void LogOut(String info) {
        if (isdebug && info != null) {
            StackTraceElement[] stack = (new Throwable()).getStackTrace();
            if (stack.length > 1) {
                StackTraceElement s = stack[1];
                String[] names = s.getClassName().split("\\.");
                Log.e(TAG, names[names.length - 1] + "第" + s.getLineNumber() + "行:---------" + info);
            } else {
                Log.e(TAG, info);
            }
        }

    }

}

