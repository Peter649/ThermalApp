package com.example.thermalapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatImageView;

import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.thermalapp.databinding.ActivityMainBinding;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Set;

public class MainActivity extends AppCompatActivity {
    private final String TAG = "hola main";
    private static String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
    private final int DRAW_PREVIEW = 0;

    UsbManager mUsbManager;
    UsbDeviceConnection mConnection;

    // Used to load the 'thermalapp' library on application startup.
    static {
        System.loadLibrary("thermalapp");
    }

    private ActivityMainBinding binding;
    byte[] buffer = new byte[160 * 120 * 4];
    AppCompatImageView imgView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        init(buffer);
        imgView = binding.imgPreview;

        mUsbManager = (UsbManager) this.getSystemService(Context.USB_SERVICE);
        PendingIntent mPermissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(
                ACTION_USB_PERMISSION), 0);

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());

        Button btn_permission = binding.btnUsbPermission;
        btn_permission.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final HashMap<String, UsbDevice> deviceList = mUsbManager.getDeviceList();
                Set<String> ss = deviceList.keySet();
                final List<UsbDevice> result = new ArrayList<UsbDevice>();
                Collection<UsbDevice> aa = deviceList.values();
                result.addAll(aa);
                if (result.size() > 0) {
                    Log.i(TAG, "onClick:  deviceList.keySet() " + mUsbManager.hasPermission(result.get(0)));
                }
                for (UsbDevice usb : deviceList.values()) {
                    mUsbManager.requestPermission(usb, mPermissionIntent);
                }
            }
        });

        Button btn_start = binding.btnStartCamara;
        btn_start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {


                //====
                final HashMap<String, UsbDevice> deviceList = mUsbManager.getDeviceList();
                Log.i(TAG, "onClick:  deviceList.size() " + deviceList.size());
                Log.i(TAG, "onClick:  deviceList.keySet() " + deviceList.keySet());
//                Log.i(TAG, "onClick:  deviceList.values() " + deviceList.values());
//                deviceList.keySet();
                Set<String> ss = deviceList.keySet();
                Collection<UsbDevice> aa = deviceList.values();
                final List<UsbDevice> result = new ArrayList<UsbDevice>(aa);

                for (UsbDevice usb : deviceList.values()) {
                    Log.i(TAG, "onClick:   mUsbManager.hasPermission(usb) " + mUsbManager.hasPermission(usb));
                    mConnection = mUsbManager.openDevice(usb);
                    Log.i(TAG, "onClick:  mUsbManager.openDevice(usb) " + mUsbManager.openDevice(usb));
                    if (mConnection != null) {
                        Log.i(TAG, "onClick:   mConnection.getFileDescriptor() " + mConnection.getFileDescriptor());
                        final String name = usb.getDeviceName();
                        final String[] strings = !TextUtils.isEmpty(name) ? name.split("/") : null;
                        int busnum = 0;
                        int devnum = 0;
                        if (strings != null) {
                            busnum = Integer.parseInt(strings[strings.length - 2]);
                            devnum = Integer.parseInt(strings[strings.length - 1]);
                        }
                        int mBusNum = busnum;
                        int mDevNum = devnum;
                        int mFileDescriptor = mConnection.getFileDescriptor();
                        startCamera(usb.getVendorId(), usb.getProductId(), mConnection.getFileDescriptor(), mBusNum, mDevNum);
//                        Log.i(TAG, "onClick: usb.getVendorId() -> " + usb.getVendorId());
                        Log.i(TAG, "onClick: usb.getProductId() -> " + usb.getProductId());


                    }
                }
                //====


            }
        });


        Button btn_stop = binding.btnStopCamara;
        btn_stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopCamera();

            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        term();
    }

    /**
     * A native method that is implemented by the 'thermalapp' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int startCamera(int vid, int pid, int fd, int bus_num, int dev_num);

    public native int stopCamera();

    public native void init(byte[] buffer);

    public native void term();

    public void callback() {
        mHandler.sendEmptyMessage(DRAW_PREVIEW);
    }
    public native byte[] takeBuffer();

    Handler mHandler = new Handler(Looper.getMainLooper()) {
        @Override
        public void handleMessage(@NonNull Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case DRAW_PREVIEW:
                    Bitmap bitmap;
                    bitmap = Bitmap.createBitmap(160, 120, Bitmap.Config.ARGB_8888);
                    bitmap.copyPixelsFromBuffer(ByteBuffer.wrap(takeBuffer()));

                    imgView.setImageBitmap(bitmap);
                    break;
            }
        }
    };


}