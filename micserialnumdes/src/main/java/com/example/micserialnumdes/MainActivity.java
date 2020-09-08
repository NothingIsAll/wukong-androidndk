package com.example.micserialnumdes;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    public Button bt_setnum,bt_decode,bt_ishidmic,bt_hidkeyid;
    public TextView tv_textshow;
    public MicnumDecode micnumDecode;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt_setnum = findViewById(R.id.bt_setsnum);
        bt_decode = findViewById(R.id.bt_decode);
        bt_ishidmic = findViewById(R.id.bt_ishidmic);
        bt_hidkeyid = findViewById(R.id.bt_hidkeyid);
        tv_textshow = findViewById(R.id.tv_textshow);
        bt_setnum.setOnClickListener(this);
        bt_decode.setOnClickListener(this);
        bt_ishidmic.setOnClickListener(this);
        bt_hidkeyid.setOnClickListener(this);
        micnumDecode = new MicnumDecode();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.bt_setsnum:
                //"38BF0E8E6B216F78" hid
                //"CDC2AA90BBEBD7A5" 非hid
                int resnum = micnumDecode.setSerialnum("CDC2AA90BBEBD7A");
                if(resnum == 0){
                    tv_textshow.setText("设置成功");
                }else{
                    tv_textshow.setText("设置失败");
                }
                break;
            case R.id.bt_decode:
                String num = micnumDecode.getdecode();
                tv_textshow.setText("decodenum: "+num);
                break;
            case R.id.bt_ishidmic:
                boolean ishid = micnumDecode.isHIDdmic();
                tv_textshow.setText("ishid: "+String.valueOf(ishid));
                break;
            case R.id.bt_hidkeyid:
                int keyid = micnumDecode.hidkeyID();
                tv_textshow.setText("keyid: "+String.valueOf(keyid));
                break;
        }

    }
}
