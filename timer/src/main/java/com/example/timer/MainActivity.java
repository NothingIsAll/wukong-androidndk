package com.example.timer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    public Button bt_blocktimerstart,bt_blocktimercancell;
    public TimerBlock timerBlock;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt_blocktimerstart = findViewById(R.id.blocktimerstart);
        bt_blocktimercancell = findViewById(R.id.blocktimercancel);
        bt_blocktimerstart.setOnClickListener(this);
        bt_blocktimercancell.setOnClickListener(this);

        timerBlock = new TimerBlock();
    }

    @Override
    public void onClick(View v) {
    switch (v.getId()){
        case  R.id.blocktimerstart:
            timerBlock.audioIOSimulate();
            break;
        case R.id.blocktimercancel:
            timerBlock.cancelRuning();
            break;
    }
    }
}
