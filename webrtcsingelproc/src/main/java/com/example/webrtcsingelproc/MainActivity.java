package com.example.webrtcsingelproc;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.Toast;

import java.io.FileOutputStream;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MainActivity extends AppCompatActivity {
    public String TAG = "doAgc";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        doAgc();
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP) {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
            } else {
                doAgc();
            }
        }
    }

    /**
     * 开始测试agc
     * 源文件在工程目录raw目录下 test_input.pcm
     * 输入文件位于手机根目录下 /agc_out.pcm
     */
    private void doAgc() {
        Log.e(TAG, "agc doAgc 111  ");
        Toast.makeText(this, "测试开始", Toast.LENGTH_LONG).show();
        try {
            AgcUtils agcUtils = new AgcUtils();
            Log.e(TAG, "agc doAgc 222  ");
            agcUtils.setAgcConfig(0, 20, 1).prepare();
            Log.e(TAG, "agc doAgc 333  ");
            InputStream fInt = getResources().openRawResource(R.raw.record_1);
            FileOutputStream fOut = new FileOutputStream(Environment.getExternalStorageDirectory().getAbsolutePath() + "/agc_outs.pcm");
            byte[] buffer = new byte[4096];
            int bytes;
            int micOutLevel = 0;

            while ((bytes = fInt.read(buffer)) != -1) {
                short[] data = new short[2048];
                short[] outData = new short[204800];
                ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().get(data);
                int status = 0;
//                if ((status = agcUtils.agcProcess(data, 0, 512, outData, 0, micOutLevel, 0, 0))>=0){
                if ((status = agcUtils.agcProcess(data, outData, 2048))>=0){
                    fOut.write(shortArrayToByteArray(outData,status));
                }
                Log.e(TAG, "agc status =  " + status);

            }

            fInt.close();
            fOut.close();

            Toast.makeText(this, "测试结束，输出文件位于手机根目录下/agc_out.pcm", Toast.LENGTH_LONG).show();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //short array to byte array
    public byte[] shortArrayToByteArray(short[] data,int samples) {
        byte[] byteVal = new byte[samples * 2];
        for (int i = 0; i < samples; i++) {
            byteVal[i * 2] = (byte) (data[i] & 0xff);
            byteVal[i * 2 + 1] = (byte) ((data[i] & 0xff00) >> 8);
        }
        return byteVal;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        boolean hasPermissionDismiss = false;
        if (requestCode == 1) {
            for (int i = 0; i < permissions.length; i++) {
                if (grantResults[i] == -1) {
                    hasPermissionDismiss = true;   //发现有未通过权限
                    break;
                }
            }
        }
        if (hasPermissionDismiss) {
        } else {
            doAgc();
        }
    }

}
