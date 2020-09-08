package com.example.hash_md5;

public class MD5Check {

    static {
        System.loadLibrary("md5checktest");
    }

    public native String getMD5FromString(String str);
    public native String getMD5FromFile(String path);
}
