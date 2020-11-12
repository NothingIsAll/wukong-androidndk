package com.example.oboe_channelresampler;

import android.provider.Settings;

public class ResamplerTest {
    static {
        System.loadLibrary("resamplerjni");
    }
    public native void init(int inrate,int outrate,int channel,String infile,String outfile);
    public native void resamplerProcess();
    public native void destory();

}
