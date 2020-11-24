package com.example.glabc;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Build;

import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;

import java.util.ArrayList;
import java.util.List;

public class AppUtil {
    public static String[] permissions = {"android.permission.RECORD_AUDIO",
            "android.permission.MODIFY_AUDIO_SETTINGS",
            "android.permission.HS_BLUETOOTH",
            "android.permission.MANAGE_VOICE_KEYPHRASES",
            "android.permission.INTERNET",
            "android.permission.CHANGE_NETWORK_STATE",
            "android.permission.WRITE_EXTERNAL_STORAGE",
            "android.permission.ACCESS_NETWORK_STATE" ,
            "android.permission.RECORD_AUDIO",
            "android.permission.ACCESS_WIFI_STATE",
            "android.permission.WAKE_LOCK",
            "android.permission.SYSTEM_ALERT_WINDOW",
            "android.permission.KILL_BACKGROUND_PROCESSES",
            "android.permission.CAMERA",
            "android.permission.ACCESS_FINE_LOCATION",
            "android.permission.ACCESS_COARSE_LOCATION",
            "android.permission.MODIFY_AUDIO_SETTINGS",
            "android.permission.WRITE_SETTINGS",
            "android.permission.RECEIVE_BOOT_COMPLETED",
            "android.permission.MOUNT_UNMOUNT_FILESYSTEMS",
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.READ_MEDIA_STORAGE",
            "android.permission.READ_PHONE_STATE",
            "android.permission.BLUETOOTH",
            "android.permission.HS_BLUETOOTH",
            "android.permission.MANAGE_VOICE_KEYPHRASES",
            "droidlogic.permission.SYSTEM_CONTROL"};


    public static boolean checkAndRequestAppPermission(@NonNull Activity activity, int reqCode) {
        if (Build.VERSION.SDK_INT < 23)
            return true;
        List<String> permissionList = new ArrayList<>();
        for (String permission : permissions) {
            if (ContextCompat.checkSelfPermission(activity, permission) != PackageManager.PERMISSION_GRANTED)
                permissionList.add(permission);
        }
        if (permissionList.size() == 0)
            return true;
        String[] requestPermissions = permissionList.toArray(new String[permissionList.size()]);
        activity.requestPermissions(requestPermissions, reqCode);
        return false;
    }
}
