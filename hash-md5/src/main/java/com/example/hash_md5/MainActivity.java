package com.example.hash_md5;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    public Button bt_md5sum;
    public MD5Check md5Check;
    public TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt_md5sum = findViewById(R.id.bt_md5sum);
        textView = findViewById(R.id.tv_show);
        bt_md5sum.setOnClickListener(this);
        md5Check = new MD5Check();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.bt_md5sum:
                //需要有文件读写权限
//                String md5 = md5Check.getMD5FromFile("/sdcard/testupfile.mp4");
                String md5 = md5Check.getMD5FromString("A/5sXAq+3Rb5MMbFc1l/7KRkR9otdror9ZY640gKUkRagPVeyaK9cZg6B8aAqP5mvNLQv4840di/W7Py1DhMRLQhKK6/hO/XuekNqcl11oYvQRnkIoyYGeLvcD4KmHRDJLuXDWfAtJfIDiQKcq1okXq6QFPMfC+4oOTjMnTAFVc=");
                textView.setText(md5);
                break;
        }

    }
}
