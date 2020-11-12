package com.example.oboe_channelresampler;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    public ResamplerTest resamplerTest;
    public Button bt_destory;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        resamplerTest = new ResamplerTest();
        resamplerTest.init(8000,48000,2,"/sdcard/record.pcm","/sdcard/resample_record.pcm");
        resamplerTest.resamplerProcess();
        bt_destory = findViewById(R.id.destory);
        bt_destory.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.destory:
                resamplerTest.destory();
                break;
        }
    }
}
