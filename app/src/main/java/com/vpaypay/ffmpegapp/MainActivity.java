package com.vpaypay.ffmpegapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.vpaypay.ffmpegapp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    // Used to load the 'ffmpegapp' library on application startup.
    static {
        System.loadLibrary("ffmpegapp");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Button btn1 =findViewById(R.id.btn_start);
        Button btn2 =findViewById(R.id.btn_stop);
        btn1.setOnClickListener(this);
        btn2.setOnClickListener(this);

        //open("/sdcard/1080.mpr", this);

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());

        //for(int i=0;i<1000;i++) {
            open("/sdcard/in1.mp4", this);
        //}
    }

    /**
     * A native method that is implemented by the 'ffmpegapp' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native boolean open(String url, Object handler);

    public native void start();

    public native void stop();

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_start:
                //btn1按钮点击触发的事件
                Toast.makeText(this, "开始推流点击触发的事件", Toast.LENGTH_SHORT).show();
                start();
                break;
            case R.id.btn_stop:
                //btn2按钮点击触发的事件
                Toast.makeText(this, "停止推流点击触发的事件", Toast.LENGTH_SHORT).show();
                stop();
                break;
        }
    }
}