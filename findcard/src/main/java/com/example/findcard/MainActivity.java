package com.example.findcard;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.NumberPicker;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    public Button bt_init,bt_start,bt_stop;
    FindcardTest findcard;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt_init = findViewById(R.id.bt_init);
        bt_init.setOnClickListener(this);
        bt_start = findViewById(R.id.bt_starttest);
        bt_start.setOnClickListener(this);
        bt_stop = findViewById(R.id.bt_teststop);
        bt_stop.setOnClickListener(this);
        findcard = new FindcardTest();
    }
    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.bt_init:
                findcard.init();
                break;
            case R.id.bt_starttest:
                findcard.loopgetcard();
                break;
            case R.id.bt_teststop:
                findcard.stop();
                break;
        }
    }
}
