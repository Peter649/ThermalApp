
#include <include/libuvc/libuvc.h>
//#include <include/libuvc/libuvc_config.h>
#include <include/libuvc/libuvc_internal.h>

#include <android/log.h>

#define APPNAME "hola"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, APPNAME, __VA_ARGS__)

static const int REQ_TYPE_SET = 0x21;
static const int REQ_TYPE_GET = 0xa1;

//uvc_format_desc_t *uvc_get_format_descs(uvc_device_handle_t *devh);

//uvc_error_t uvc_get_eeprom_register(uvc_device_handle_t *devh, int16_t slaveAddr, int16_t regAddr,
//                                    int16_t *regDat) {
//    uint8_t data[4];
//    uvc_error_t ret;
//    uint8_t xuSelector, xuUnit, bRequest;
//
//    xuSelector = 5;  //wValue
//    xuUnit = 4;      //wIndex
//
//    data[0] = slaveAddr;
//    data[1] = regAddr & 0xFF;
//    data[2] = (regAddr >> 8) & 0xFF;
//    data[3] = 0x00;
//
//    ret = libusb_control_transfer(
//            devh->usb_devh,
//            REQ_TYPE_GET, UVC_GET_CUR,
//            xuSelector << 8,
//            //xuUnit << 8 | devh->info->ctrl_if.bInterfaceNumber,   //for linux
//            devh->info->ctrl_if.extension_unit_descs->request,  //for android
//            data,
//            sizeof(data),
//            0);
//
//    if (ret == sizeof(data)) {
//        *regDat = data[3];
//        LOGD("Success writing Extension unit, slave:0x%x  reg:0x%x, read data:0x%x\n", slaveAddr,
//             regAddr, *regDat);
//        return UVC_SUCCESS;
//    } else {
//        LOGD("Fail reading Extension unit\n");
//        return ret;
//    }
//}
//
//
//uvc_error_t uvc_set_eeprom_register(uvc_device_handle_t *devh, int16_t slaveAddr, int16_t regAddr,
//                                    int16_t regDat) {
//    uint8_t data[4];
//    uvc_error_t ret;
//    uint8_t xuSelector, xuUnit, bRequest;
//
//    xuSelector = 5;  //wValue
//    xuUnit = 4;      //wIndex
//
//    data[0] = slaveAddr;   //for real write it need to be 0xA0 | 0x01,  to set before read 0xA0
//    data[1] = regAddr & 0xFF;
//    data[2] = (regAddr >> 8) & 0xFF;
//    data[3] = regDat;
//
//    ret = libusb_control_transfer(
//            devh->usb_devh,
//            REQ_TYPE_SET, UVC_SET_CUR,
//            xuSelector << 8,
////    xuUnit << 8 | devh->info->ctrl_if.bInterfaceNumber,   //for linux
//            devh->info->ctrl_if.extension_unit_descs->request,  //for android
//            data,
//            sizeof(data),
//            0);
//
//    if (ret == sizeof(data)) {
//        LOGD("Success writing Extension unit, slave:0x%x  reg:0x%x, data:0x%x\n", slaveAddr,
//             regAddr, regDat);
//        return UVC_SUCCESS;
//
//    } else {
//
//        LOGD("Fail writing Extension unit\n");
//        return ret;
//    }
//}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Code for IriUniverseOne  20210812

uvc_device_handle_t *g_devh_IriUniverseOne;
uvc_context_t *ctx_IriUniverseOne;
uvc_stream_ctrl_t ctrl_IriUniverseOne;
uvc_device_t *dev_IriUniverseOne;

/* This callback function runs once per frame. Use it to perform any
 * quick processing you need, or have it put the frame into your application's
 * input queue. If this function takes too long, you'll start losing frames. */

void cb_IriUniverseOne(uvc_frame_t *frame, void *ptr);

//by _YHK_ 210818
int IriUniverseOneUVC_InitDevice(int vid, int pid, int fd, int busNum, int devNum) {

    uvc_error_t res;

    /* Initialize a UVC service context. Libuvc will set up its own libusb
     * context. Replace NULL with a libusb_context pointer to run libuvc
     * from an existing libusb context. */
#ifdef __ANDROID__
    res = uvc_init2(&ctx_IriUniverseOne, NULL, "/dev/bus/usb");
#else
    res = uvc_init(&ctx_IriUniverseOne, NULL);
#endif
    if (res < 0) {
        uvc_perror(res, "uvc_init");
        return -1;
    }

    LOGD("UVC initialized");

    /* Locates the first attached UVC device, stores in dev */
#ifdef __ANDROID__
    res = uvc_get_device_with_fd(ctx_IriUniverseOne, &dev_IriUniverseOne, vid, pid, NULL, fd, busNum, devNum);
#else
    res = uvc_find_device(ctx_IriUniverseOne, &dev_IriUniverseOne, global_vid, global_pid,
                          NULL); /* filter devices: vendor_id, product_id, "serial_num" */
#endif
    if (res < 0) {
        uvc_perror(res, "uvc_find_device"); /* no devices found */
        return -1;
    }
    LOGD("Device found");

    /* Try to open the device: requires exclusive access */
    res = uvc_open(dev_IriUniverseOne, &g_devh_IriUniverseOne);

    if (res < 0) {
        uvc_perror(res, "uvc_open"); /* unable to open device */
        return -1;
    }
    /* Print out a message containing all the information that libuvc
     * knows about the device */
    uvc_print_diag(g_devh_IriUniverseOne, stderr);

    const uvc_format_desc_t *format_desc = uvc_get_format_descs(g_devh_IriUniverseOne);
    const uvc_frame_desc_t *frame_desc = format_desc->frame_descs;
    enum uvc_frame_format frame_format;
    int width = 640;
    int height = 480;
    int fps = 30;

    switch (format_desc->bDescriptorSubtype) {
        case UVC_VS_FORMAT_MJPEG:
            frame_format = UVC_COLOR_FORMAT_MJPEG;
            break;
        case UVC_VS_FORMAT_FRAME_BASED:
            frame_format = UVC_COLOR_FORMAT_YUYV;//;UVC_FRAME_FORMAT_H264;
            break;
        default:
            frame_format = UVC_FRAME_FORMAT_YUYV;
            break;
    }

    if (frame_desc) {
        width = frame_desc->wWidth;
        height = frame_desc->wHeight;
        fps = 10000000 / frame_desc->dwDefaultFrameInterval;
    }

    LOGD("\nFirst format: (%4s) %dx%d %dfps\n", format_desc->fourccFormat, width, height, fps);

    /* Try to negotiate first stream profile */
    res = uvc_get_stream_ctrl_format_size(
            g_devh_IriUniverseOne, &ctrl_IriUniverseOne, /* result stored in ctrl */
            frame_format,
            width, height, fps /* width, height, fps */
    );

    /* Print out the result */
    uvc_print_stream_ctrl(&ctrl_IriUniverseOne, stderr);

    if (res < 0) {
        uvc_perror(res, "get_mode"); /* device doesn't provide a matching stream */
        return -1;
    }

    /* Start the video stream. The library will call user function cb:
         *   cb(frame, (void *) 12345)
         */
    res = uvc_start_streaming(g_devh_IriUniverseOne, &ctrl_IriUniverseOne, cb_IriUniverseOne,
                              (void *) 12345, 0);

    if (res < 0) {
        uvc_perror(res, "start_streaming"); /* unable to start stream */
        return -1;
    }

    LOGD("Streaming...");

    return 0;
}

int IriUniverseOneUVC_StopDevice() {

    /* End the stream. Blocks until last callback is serviced */
    uvc_stop_streaming(g_devh_IriUniverseOne);
    LOGD("Stop streaming.");


    /* Release our handle on the device */
    uvc_close(g_devh_IriUniverseOne);
    LOGD("Device closed\n");

    /* Release the device descriptor */
    uvc_unref_device(dev_IriUniverseOne);
    LOGD("uvc_unref_device\n");

    /* Close the UVC context. This closes and cleans up any existing device handles,
     * and it closes the libusb context if one was not provided. */
    uvc_exit(ctx_IriUniverseOne);

    LOGD("UVC exited\n");

    return 0;
}

int IriUniverseOneUVC_TurnOffLED() {

    LOGD("Setting brightness\n");
    uvc_set_sharpness(g_devh_IriUniverseOne, 5);

    return 0;
}

int IriUniverseOneUVC_GreenLED() {

    LOGD("Setting brightness\n");
    uvc_set_saturation(g_devh_IriUniverseOne, 8);

    return 0;
}

int IriUniverseOneUVC_BlinkLED() {

    LOGD("Setting brightness\n");
    uvc_set_brightness(g_devh_IriUniverseOne, 8);

    return 0;
}

int IriUniverseOneUVC_WriteByte(int regAddr, int regDat) {

    int16_t slaveAddr = 0xA0 | 0x01;

    uvc_set_eeprom_register(g_devh_IriUniverseOne, slaveAddr, regAddr, regDat);
    uvc_get_eeprom_register(g_devh_IriUniverseOne, slaveAddr, regAddr, &regDat);

    return 0;
}

int IriUniverseOneUVC_ReadByte(int regAddr, int *regDat) {
    int8_t readData;
    int16_t slaveAddr = 0xA0;

    uvc_set_eeprom_register(g_devh_IriUniverseOne, slaveAddr, regAddr, 0x00);
    uvc_get_eeprom_register(g_devh_IriUniverseOne, slaveAddr, regAddr, &readData);

    *regDat = (int) readData;

    return 0;
}

void IriUniverseOneUVC_Reset(){
    uvc_set_sharpness(g_devh_IriUniverseOne, 0);
    uvc_set_saturation(g_devh_IriUniverseOne, 0);
    uvc_set_brightness(g_devh_IriUniverseOne, 0);

}


