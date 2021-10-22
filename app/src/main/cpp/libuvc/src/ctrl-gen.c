/* This is an AUTO-GENERATED file! Update it with the output of `ctrl-gen.py def`. */
#include "libuvc/libuvc.h"
#include "libuvc/libuvc_internal.h"

static const int REQ_TYPE_SET = 0x21;
static const int REQ_TYPE_GET = 0xa1;

/** @ingroup ctrl
 * @brief Reads the SCANNING_MODE control.
 * @param devh UVC device handle
 * @param[out] mode 0: interlaced, 1: progressive
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_scanning_mode(uvc_device_handle_t *devh, uint8_t* mode, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_SCANNING_MODE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *mode = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the SCANNING_MODE control.
 * @param devh UVC device handle
 * @param mode 0: interlaced, 1: progressive
 */
uvc_error_t uvc_set_scanning_mode(uvc_device_handle_t *devh, uint8_t mode) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = mode;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_SCANNING_MODE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads camera's auto-exposure mode.
 * 
 * See uvc_set_ae_mode() for a description of the available modes.
 * @param devh UVC device handle
 * @param[out] mode 1: manual mode; 2: auto mode; 4: shutter priority mode; 8: aperture priority mode
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_ae_mode(uvc_device_handle_t *devh, uint8_t* mode, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_AE_MODE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *mode = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets camera's auto-exposure mode.
 * 
 * Cameras may support any of the following AE modes:
 *  * UVC_AUTO_EXPOSURE_MODE_MANUAL (1) - manual exposure time, manual iris
 *  * UVC_AUTO_EXPOSURE_MODE_AUTO (2) - auto exposure time, auto iris
 *  * UVC_AUTO_EXPOSURE_MODE_SHUTTER_PRIORITY (4) - manual exposure time, auto iris
 *  * UVC_AUTO_EXPOSURE_MODE_APERTURE_PRIORITY (8) - auto exposure time, manual iris
 * 
 * Most cameras provide manual mode and aperture priority mode.
 * @param devh UVC device handle
 * @param mode 1: manual mode; 2: auto mode; 4: shutter priority mode; 8: aperture priority mode
 */
uvc_error_t uvc_set_ae_mode(uvc_device_handle_t *devh, uint8_t mode) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = mode;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_AE_MODE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Checks whether the camera may vary the frame rate for exposure control reasons.
 * See uvc_set_ae_priority() for a description of the `priority` field.
 * @param devh UVC device handle
 * @param[out] priority 0: frame rate must remain constant; 1: frame rate may be varied for AE purposes
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_ae_priority(uvc_device_handle_t *devh, uint8_t* priority, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_AE_PRIORITY_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *priority = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Chooses whether the camera may vary the frame rate for exposure control reasons.
 * A `priority` value of zero means the camera may not vary its frame rate. A value of 1
 * means the frame rate is variable. This setting has no effect outside of the `auto` and
 * `shutter_priority` auto-exposure modes.
 * @param devh UVC device handle
 * @param priority 0: frame rate must remain constant; 1: frame rate may be varied for AE purposes
 */
uvc_error_t uvc_set_ae_priority(uvc_device_handle_t *devh, uint8_t priority) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = priority;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_AE_PRIORITY_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Gets the absolute exposure time.
 * 
 * See uvc_set_exposure_abs() for a description of the `time` field.
 * @param devh UVC device handle
 * @param[out] time 
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_exposure_abs(uvc_device_handle_t *devh, uint32_t* time, enum uvc_req_code req_code) {
  uint8_t data[4];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *time = DW_TO_INT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the absolute exposure time.
 * 
 * The `time` parameter should be provided in units of 0.0001 seconds (e.g., use the value 100
 * for a 10ms exposure period). Auto exposure should be set to `manual` or `shutter_priority`
 * before attempting to change this setting.
 * @param devh UVC device handle
 * @param time 
 */
uvc_error_t uvc_set_exposure_abs(uvc_device_handle_t *devh, uint32_t time) {
  uint8_t data[4];
  uvc_error_t ret;

  INT_TO_DW(time, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the exposure time relative to the current setting.
 * @param devh UVC device handle
 * @param[out] step number of steps by which to change the exposure time, or zero to set the default exposure time
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_exposure_rel(uvc_device_handle_t *devh, int8_t* step, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_EXPOSURE_TIME_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *step = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the exposure time relative to the current setting.
 * @param devh UVC device handle
 * @param step number of steps by which to change the exposure time, or zero to set the default exposure time
 */
uvc_error_t uvc_set_exposure_rel(uvc_device_handle_t *devh, int8_t step) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = step;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_EXPOSURE_TIME_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the distance at which an object is optimally focused.
 * @param devh UVC device handle
 * @param[out] focus focal target distance in millimeters
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_focus_abs(uvc_device_handle_t *devh, uint16_t* focus, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_FOCUS_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *focus = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the distance at which an object is optimally focused.
 * @param devh UVC device handle
 * @param focus focal target distance in millimeters
 */
uvc_error_t uvc_set_focus_abs(uvc_device_handle_t *devh, uint16_t focus) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(focus, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_FOCUS_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the FOCUS_RELATIVE control.
 * @param devh UVC device handle
 * @param[out] focus_rel TODO
 * @param[out] speed TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_focus_rel(uvc_device_handle_t *devh, int8_t* focus_rel, uint8_t* speed, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_FOCUS_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *focus_rel = data[0];
    *speed = data[1];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the FOCUS_RELATIVE control.
 * @param devh UVC device handle
 * @param focus_rel TODO
 * @param speed TODO
 */
uvc_error_t uvc_set_focus_rel(uvc_device_handle_t *devh, int8_t focus_rel, uint8_t speed) {
  uint8_t data[2];
  uvc_error_t ret;

  data[0] = focus_rel;
  data[1] = speed;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_FOCUS_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the FOCUS_SIMPLE control.
 * @param devh UVC device handle
 * @param[out] focus TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_focus_simple_range(uvc_device_handle_t *devh, uint8_t* focus, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_FOCUS_SIMPLE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *focus = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the FOCUS_SIMPLE control.
 * @param devh UVC device handle
 * @param focus TODO
 */
uvc_error_t uvc_set_focus_simple_range(uvc_device_handle_t *devh, uint8_t focus) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = focus;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_FOCUS_SIMPLE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the FOCUS_AUTO control.
 * @param devh UVC device handle
 * @param[out] state TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_focus_auto(uvc_device_handle_t *devh, uint8_t* state, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_FOCUS_AUTO_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *state = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the FOCUS_AUTO control.
 * @param devh UVC device handle
 * @param state TODO
 */
uvc_error_t uvc_set_focus_auto(uvc_device_handle_t *devh, uint8_t state) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = state;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_FOCUS_AUTO_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the IRIS_ABSOLUTE control.
 * @param devh UVC device handle
 * @param[out] iris TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_iris_abs(uvc_device_handle_t *devh, uint16_t* iris, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_IRIS_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *iris = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the IRIS_ABSOLUTE control.
 * @param devh UVC device handle
 * @param iris TODO
 */
uvc_error_t uvc_set_iris_abs(uvc_device_handle_t *devh, uint16_t iris) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(iris, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_IRIS_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the IRIS_RELATIVE control.
 * @param devh UVC device handle
 * @param[out] iris_rel TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_iris_rel(uvc_device_handle_t *devh, uint8_t* iris_rel, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_IRIS_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *iris_rel = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the IRIS_RELATIVE control.
 * @param devh UVC device handle
 * @param iris_rel TODO
 */
uvc_error_t uvc_set_iris_rel(uvc_device_handle_t *devh, uint8_t iris_rel) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = iris_rel;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_IRIS_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the ZOOM_ABSOLUTE control.
 * @param devh UVC device handle
 * @param[out] focal_length TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_zoom_abs(uvc_device_handle_t *devh, uint16_t* focal_length, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_ZOOM_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *focal_length = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the ZOOM_ABSOLUTE control.
 * @param devh UVC device handle
 * @param focal_length TODO
 */
uvc_error_t uvc_set_zoom_abs(uvc_device_handle_t *devh, uint16_t focal_length) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(focal_length, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_ZOOM_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the ZOOM_RELATIVE control.
 * @param devh UVC device handle
 * @param[out] zoom_rel TODO
 * @param[out] digital_zoom TODO
 * @param[out] speed TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_zoom_rel(uvc_device_handle_t *devh, int8_t* zoom_rel, uint8_t* digital_zoom, uint8_t* speed, enum uvc_req_code req_code) {
  uint8_t data[3];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_ZOOM_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *zoom_rel = data[0];
    *digital_zoom = data[1];
    *speed = data[2];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the ZOOM_RELATIVE control.
 * @param devh UVC device handle
 * @param zoom_rel TODO
 * @param digital_zoom TODO
 * @param speed TODO
 */
uvc_error_t uvc_set_zoom_rel(uvc_device_handle_t *devh, int8_t zoom_rel, uint8_t digital_zoom, uint8_t speed) {
  uint8_t data[3];
  uvc_error_t ret;

  data[0] = zoom_rel;
  data[1] = digital_zoom;
  data[2] = speed;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_ZOOM_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the PANTILT_ABSOLUTE control.
 * @param devh UVC device handle
 * @param[out] pan TODO
 * @param[out] tilt TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_pantilt_abs(uvc_device_handle_t *devh, int32_t* pan, int32_t* tilt, enum uvc_req_code req_code) {
  uint8_t data[8];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_PANTILT_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *pan = DW_TO_INT(data + 0);
    *tilt = DW_TO_INT(data + 4);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the PANTILT_ABSOLUTE control.
 * @param devh UVC device handle
 * @param pan TODO
 * @param tilt TODO
 */
uvc_error_t uvc_set_pantilt_abs(uvc_device_handle_t *devh, int32_t pan, int32_t tilt) {
  uint8_t data[8];
  uvc_error_t ret;

  INT_TO_DW(pan, data + 0);
  INT_TO_DW(tilt, data + 4);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_PANTILT_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the PANTILT_RELATIVE control.
 * @param devh UVC device handle
 * @param[out] pan_rel TODO
 * @param[out] pan_speed TODO
 * @param[out] tilt_rel TODO
 * @param[out] tilt_speed TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_pantilt_rel(uvc_device_handle_t *devh, int8_t* pan_rel, uint8_t* pan_speed, int8_t* tilt_rel, uint8_t* tilt_speed, enum uvc_req_code req_code) {
  uint8_t data[4];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_PANTILT_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *pan_rel = data[0];
    *pan_speed = data[1];
    *tilt_rel = data[2];
    *tilt_speed = data[3];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the PANTILT_RELATIVE control.
 * @param devh UVC device handle
 * @param pan_rel TODO
 * @param pan_speed TODO
 * @param tilt_rel TODO
 * @param tilt_speed TODO
 */
uvc_error_t uvc_set_pantilt_rel(uvc_device_handle_t *devh, int8_t pan_rel, uint8_t pan_speed, int8_t tilt_rel, uint8_t tilt_speed) {
  uint8_t data[4];
  uvc_error_t ret;

  data[0] = pan_rel;
  data[1] = pan_speed;
  data[2] = tilt_rel;
  data[3] = tilt_speed;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_PANTILT_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the ROLL_ABSOLUTE control.
 * @param devh UVC device handle
 * @param[out] roll TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_roll_abs(uvc_device_handle_t *devh, int16_t* roll, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_ROLL_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *roll = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the ROLL_ABSOLUTE control.
 * @param devh UVC device handle
 * @param roll TODO
 */
uvc_error_t uvc_set_roll_abs(uvc_device_handle_t *devh, int16_t roll) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(roll, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_ROLL_ABSOLUTE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the ROLL_RELATIVE control.
 * @param devh UVC device handle
 * @param[out] roll_rel TODO
 * @param[out] speed TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_roll_rel(uvc_device_handle_t *devh, int8_t* roll_rel, uint8_t* speed, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_ROLL_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *roll_rel = data[0];
    *speed = data[1];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the ROLL_RELATIVE control.
 * @param devh UVC device handle
 * @param roll_rel TODO
 * @param speed TODO
 */
uvc_error_t uvc_set_roll_rel(uvc_device_handle_t *devh, int8_t roll_rel, uint8_t speed) {
  uint8_t data[2];
  uvc_error_t ret;

  data[0] = roll_rel;
  data[1] = speed;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_ROLL_RELATIVE_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the PRIVACY control.
 * @param devh UVC device handle
 * @param[out] privacy TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_privacy(uvc_device_handle_t *devh, uint8_t* privacy, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_PRIVACY_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *privacy = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the PRIVACY control.
 * @param devh UVC device handle
 * @param privacy TODO
 */
uvc_error_t uvc_set_privacy(uvc_device_handle_t *devh, uint8_t privacy) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = privacy;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_PRIVACY_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the DIGITAL_WINDOW control.
 * @param devh UVC device handle
 * @param[out] window_top TODO
 * @param[out] window_left TODO
 * @param[out] window_bottom TODO
 * @param[out] window_right TODO
 * @param[out] num_steps TODO
 * @param[out] num_steps_units TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_digital_window(uvc_device_handle_t *devh, uint16_t* window_top, uint16_t* window_left, uint16_t* window_bottom, uint16_t* window_right, uint16_t* num_steps, uint16_t* num_steps_units, enum uvc_req_code req_code) {
  uint8_t data[12];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_DIGITAL_WINDOW_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *window_top = SW_TO_SHORT(data + 0);
    *window_left = SW_TO_SHORT(data + 2);
    *window_bottom = SW_TO_SHORT(data + 4);
    *window_right = SW_TO_SHORT(data + 6);
    *num_steps = SW_TO_SHORT(data + 8);
    *num_steps_units = SW_TO_SHORT(data + 10);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the DIGITAL_WINDOW control.
 * @param devh UVC device handle
 * @param window_top TODO
 * @param window_left TODO
 * @param window_bottom TODO
 * @param window_right TODO
 * @param num_steps TODO
 * @param num_steps_units TODO
 */
uvc_error_t uvc_set_digital_window(uvc_device_handle_t *devh, uint16_t window_top, uint16_t window_left, uint16_t window_bottom, uint16_t window_right, uint16_t num_steps, uint16_t num_steps_units) {
  uint8_t data[12];
  uvc_error_t ret;

  SHORT_TO_SW(window_top, data + 0);
  SHORT_TO_SW(window_left, data + 2);
  SHORT_TO_SW(window_bottom, data + 4);
  SHORT_TO_SW(window_right, data + 6);
  SHORT_TO_SW(num_steps, data + 8);
  SHORT_TO_SW(num_steps_units, data + 10);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_DIGITAL_WINDOW_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the REGION_OF_INTEREST control.
 * @param devh UVC device handle
 * @param[out] roi_top TODO
 * @param[out] roi_left TODO
 * @param[out] roi_bottom TODO
 * @param[out] roi_right TODO
 * @param[out] auto_controls TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_digital_roi(uvc_device_handle_t *devh, uint16_t* roi_top, uint16_t* roi_left, uint16_t* roi_bottom, uint16_t* roi_right, uint16_t* auto_controls, enum uvc_req_code req_code) {
  uint8_t data[10];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_CT_REGION_OF_INTEREST_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *roi_top = SW_TO_SHORT(data + 0);
    *roi_left = SW_TO_SHORT(data + 2);
    *roi_bottom = SW_TO_SHORT(data + 4);
    *roi_right = SW_TO_SHORT(data + 6);
    *auto_controls = SW_TO_SHORT(data + 8);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the REGION_OF_INTEREST control.
 * @param devh UVC device handle
 * @param roi_top TODO
 * @param roi_left TODO
 * @param roi_bottom TODO
 * @param roi_right TODO
 * @param auto_controls TODO
 */
uvc_error_t uvc_set_digital_roi(uvc_device_handle_t *devh, uint16_t roi_top, uint16_t roi_left, uint16_t roi_bottom, uint16_t roi_right, uint16_t auto_controls) {
  uint8_t data[10];
  uvc_error_t ret;

  SHORT_TO_SW(roi_top, data + 0);
  SHORT_TO_SW(roi_left, data + 2);
  SHORT_TO_SW(roi_bottom, data + 4);
  SHORT_TO_SW(roi_right, data + 6);
  SHORT_TO_SW(auto_controls, data + 8);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_CT_REGION_OF_INTEREST_CONTROL << 8,
    uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the BACKLIGHT_COMPENSATION control.
 * @param devh UVC device handle
 * @param[out] backlight_compensation device-dependent backlight compensation mode; zero means backlight compensation is disabled
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_backlight_compensation(uvc_device_handle_t *devh, uint16_t* backlight_compensation, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_BACKLIGHT_COMPENSATION_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *backlight_compensation = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the BACKLIGHT_COMPENSATION control.
 * @param devh UVC device handle
 * @param backlight_compensation device-dependent backlight compensation mode; zero means backlight compensation is disabled
 */
uvc_error_t uvc_set_backlight_compensation(uvc_device_handle_t *devh, uint16_t backlight_compensation) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(backlight_compensation, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_BACKLIGHT_COMPENSATION_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the BRIGHTNESS control.
 * @param devh UVC device handle
 * @param[out] brightness TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_brightness(uvc_device_handle_t *devh, int16_t* brightness, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_BRIGHTNESS_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *brightness = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the BRIGHTNESS control.
 * @param devh UVC device handle
 * @param brightness TODO
 */
uvc_error_t uvc_set_brightness(uvc_device_handle_t *devh, int16_t brightness) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(brightness, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_BRIGHTNESS_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
  {
    printf("Success uvc_set_brightness\n");
    return UVC_SUCCESS;

  } else {

    printf("Fail uvc_set_brightness, errorNo: %d\n", ret);
    return ret;
  }
}

/** @ingroup ctrl
 * @brief Reads the CONTRAST control.
 * @param devh UVC device handle
 * @param[out] contrast TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_contrast(uvc_device_handle_t *devh, uint16_t* contrast, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_CONTRAST_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *contrast = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the CONTRAST control.
 * @param devh UVC device handle
 * @param contrast TODO
 */
uvc_error_t uvc_set_contrast(uvc_device_handle_t *devh, uint16_t contrast) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(contrast, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_CONTRAST_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the CONTRAST_AUTO control.
 * @param devh UVC device handle
 * @param[out] contrast_auto TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_contrast_auto(uvc_device_handle_t *devh, uint8_t* contrast_auto, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_CONTRAST_AUTO_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *contrast_auto = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the CONTRAST_AUTO control.
 * @param devh UVC device handle
 * @param contrast_auto TODO
 */
uvc_error_t uvc_set_contrast_auto(uvc_device_handle_t *devh, uint8_t contrast_auto) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = contrast_auto;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_CONTRAST_AUTO_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the GAIN control.
 * @param devh UVC device handle
 * @param[out] gain TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_gain(uvc_device_handle_t *devh, uint16_t* gain, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_GAIN_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *gain = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the GAIN control.
 * @param devh UVC device handle
 * @param gain TODO
 */
uvc_error_t uvc_set_gain(uvc_device_handle_t *devh, uint16_t gain) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(gain, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_GAIN_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the POWER_LINE_FREQUENCY control.
 * @param devh UVC device handle
 * @param[out] power_line_frequency TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_power_line_frequency(uvc_device_handle_t *devh, uint8_t* power_line_frequency, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_POWER_LINE_FREQUENCY_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *power_line_frequency = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the POWER_LINE_FREQUENCY control.
 * @param devh UVC device handle
 * @param power_line_frequency TODO
 */
uvc_error_t uvc_set_power_line_frequency(uvc_device_handle_t *devh, uint8_t power_line_frequency) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = power_line_frequency;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_POWER_LINE_FREQUENCY_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the HUE control.
 * @param devh UVC device handle
 * @param[out] hue TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_hue(uvc_device_handle_t *devh, int16_t* hue, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_HUE_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *hue = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the HUE control.
 * @param devh UVC device handle
 * @param hue TODO
 */
uvc_error_t uvc_set_hue(uvc_device_handle_t *devh, int16_t hue) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(hue, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_HUE_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the HUE_AUTO control.
 * @param devh UVC device handle
 * @param[out] hue_auto TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_hue_auto(uvc_device_handle_t *devh, uint8_t* hue_auto, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_HUE_AUTO_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *hue_auto = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the HUE_AUTO control.
 * @param devh UVC device handle
 * @param hue_auto TODO
 */
uvc_error_t uvc_set_hue_auto(uvc_device_handle_t *devh, uint8_t hue_auto) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = hue_auto;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_HUE_AUTO_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the SATURATION control.
 * @param devh UVC device handle
 * @param[out] saturation TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_saturation(uvc_device_handle_t *devh, uint16_t* saturation, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_SATURATION_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *saturation = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the SATURATION control.
 * @param devh UVC device handle
 * @param saturation TODO
 */
uvc_error_t uvc_set_saturation(uvc_device_handle_t *devh, uint16_t saturation) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(saturation, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_SATURATION_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
  {
    printf("Success uvc_set_saturation\n");
    return UVC_SUCCESS;

  } else {

    printf("Fail uvc_set_saturation, errorNo: %d\n", ret);
    return ret;
  }
}

/** @ingroup ctrl
 * @brief Reads the SHARPNESS control.
 * @param devh UVC device handle
 * @param[out] sharpness TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_sharpness(uvc_device_handle_t *devh, uint16_t* sharpness, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_SHARPNESS_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *sharpness = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the SHARPNESS control.
 * @param devh UVC device handle
 * @param sharpness TODO
 */
uvc_error_t uvc_set_sharpness(uvc_device_handle_t *devh, uint16_t sharpness) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(sharpness, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_SHARPNESS_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
  {
    printf("Success uvc_set_sharpness\n");
    return UVC_SUCCESS;

  } else {

    printf("Fail uvc_set_sharpness, errorNo: %d\n", ret);
    return ret;
  }
}

/** @ingroup ctrl
 * @brief Reads the GAMMA control.
 * @param devh UVC device handle
 * @param[out] gamma TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_gamma(uvc_device_handle_t *devh, uint16_t* gamma, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_GAMMA_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *gamma = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the GAMMA control.
 * @param devh UVC device handle
 * @param gamma TODO
 */
uvc_error_t uvc_set_gamma(uvc_device_handle_t *devh, uint16_t gamma) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(gamma, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_GAMMA_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the WHITE_BALANCE_TEMPERATURE control.
 * @param devh UVC device handle
 * @param[out] temperature TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_white_balance_temperature(uvc_device_handle_t *devh, uint16_t* temperature, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_WHITE_BALANCE_TEMPERATURE_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *temperature = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the WHITE_BALANCE_TEMPERATURE control.
 * @param devh UVC device handle
 * @param temperature TODO
 */
uvc_error_t uvc_set_white_balance_temperature(uvc_device_handle_t *devh, uint16_t temperature) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(temperature, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_WHITE_BALANCE_TEMPERATURE_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the WHITE_BALANCE_TEMPERATURE_AUTO control.
 * @param devh UVC device handle
 * @param[out] temperature_auto TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_white_balance_temperature_auto(uvc_device_handle_t *devh, uint8_t* temperature_auto, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *temperature_auto = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the WHITE_BALANCE_TEMPERATURE_AUTO control.
 * @param devh UVC device handle
 * @param temperature_auto TODO
 */
uvc_error_t uvc_set_white_balance_temperature_auto(uvc_device_handle_t *devh, uint8_t temperature_auto) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = temperature_auto;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the WHITE_BALANCE_COMPONENT control.
 * @param devh UVC device handle
 * @param[out] blue TODO
 * @param[out] red TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_white_balance_component(uvc_device_handle_t *devh, uint16_t* blue, uint16_t* red, enum uvc_req_code req_code) {
  uint8_t data[4];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_WHITE_BALANCE_COMPONENT_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *blue = SW_TO_SHORT(data + 0);
    *red = SW_TO_SHORT(data + 2);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the WHITE_BALANCE_COMPONENT control.
 * @param devh UVC device handle
 * @param blue TODO
 * @param red TODO
 */
uvc_error_t uvc_set_white_balance_component(uvc_device_handle_t *devh, uint16_t blue, uint16_t red) {
  uint8_t data[4];
  uvc_error_t ret;

  SHORT_TO_SW(blue, data + 0);
  SHORT_TO_SW(red, data + 2);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_WHITE_BALANCE_COMPONENT_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the WHITE_BALANCE_COMPONENT_AUTO control.
 * @param devh UVC device handle
 * @param[out] white_balance_component_auto TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_white_balance_component_auto(uvc_device_handle_t *devh, uint8_t* white_balance_component_auto, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *white_balance_component_auto = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the WHITE_BALANCE_COMPONENT_AUTO control.
 * @param devh UVC device handle
 * @param white_balance_component_auto TODO
 */
uvc_error_t uvc_set_white_balance_component_auto(uvc_device_handle_t *devh, uint8_t white_balance_component_auto) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = white_balance_component_auto;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the DIGITAL_MULTIPLIER control.
 * @param devh UVC device handle
 * @param[out] multiplier_step TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_digital_multiplier(uvc_device_handle_t *devh, uint16_t* multiplier_step, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_DIGITAL_MULTIPLIER_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *multiplier_step = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the DIGITAL_MULTIPLIER control.
 * @param devh UVC device handle
 * @param multiplier_step TODO
 */
uvc_error_t uvc_set_digital_multiplier(uvc_device_handle_t *devh, uint16_t multiplier_step) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(multiplier_step, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_DIGITAL_MULTIPLIER_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the DIGITAL_MULTIPLIER_LIMIT control.
 * @param devh UVC device handle
 * @param[out] multiplier_step TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_digital_multiplier_limit(uvc_device_handle_t *devh, uint16_t* multiplier_step, enum uvc_req_code req_code) {
  uint8_t data[2];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *multiplier_step = SW_TO_SHORT(data + 0);
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the DIGITAL_MULTIPLIER_LIMIT control.
 * @param devh UVC device handle
 * @param multiplier_step TODO
 */
uvc_error_t uvc_set_digital_multiplier_limit(uvc_device_handle_t *devh, uint16_t multiplier_step) {
  uint8_t data[2];
  uvc_error_t ret;

  SHORT_TO_SW(multiplier_step, data + 0);

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the ANALOG_VIDEO_STANDARD control.
 * @param devh UVC device handle
 * @param[out] video_standard TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_analog_video_standard(uvc_device_handle_t *devh, uint8_t* video_standard, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_ANALOG_VIDEO_STANDARD_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *video_standard = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the ANALOG_VIDEO_STANDARD control.
 * @param devh UVC device handle
 * @param video_standard TODO
 */
uvc_error_t uvc_set_analog_video_standard(uvc_device_handle_t *devh, uint8_t video_standard) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = video_standard;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_ANALOG_VIDEO_STANDARD_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the ANALOG_LOCK_STATUS control.
 * @param devh UVC device handle
 * @param[out] status TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_analog_video_lock_status(uvc_device_handle_t *devh, uint8_t* status, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_PU_ANALOG_LOCK_STATUS_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *status = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the ANALOG_LOCK_STATUS control.
 * @param devh UVC device handle
 * @param status TODO
 */
uvc_error_t uvc_set_analog_video_lock_status(uvc_device_handle_t *devh, uint8_t status) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = status;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_PU_ANALOG_LOCK_STATUS_CONTROL << 8,
    uvc_get_processing_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}

/** @ingroup ctrl
 * @brief Reads the INPUT_SELECT control.
 * @param devh UVC device handle
 * @param[out] selector TODO
 * @param req_code UVC_GET_* request to execute
 */
uvc_error_t uvc_get_input_select(uvc_device_handle_t *devh, uint8_t* selector, enum uvc_req_code req_code) {
  uint8_t data[1];
  uvc_error_t ret;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, req_code,
    UVC_SU_INPUT_SELECT_CONTROL << 8,
    uvc_get_selector_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data)) {
    *selector = data[0];
    return UVC_SUCCESS;
  } else {
    return ret;
  }
}


/** @ingroup ctrl
 * @brief Sets the INPUT_SELECT control.
 * @param devh UVC device handle
 * @param selector TODO
 */
uvc_error_t uvc_set_input_select(uvc_device_handle_t *devh, uint8_t selector) {
  uint8_t data[1];
  uvc_error_t ret;

  data[0] = selector;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    UVC_SU_INPUT_SELECT_CONTROL << 8,
    uvc_get_selector_units(devh)->bUnitID << 8 | devh->info->ctrl_if.bInterfaceNumber,
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
    return UVC_SUCCESS;
  else
    return ret;
}


#if 1

uvc_error_t uvc_get_eeprom_register(uvc_device_handle_t *devh, int16_t slaveAddr, int16_t regAddr, int16_t *regDat)
{
  uint8_t data[4];
  uvc_error_t ret;
  uint8_t xuSelector, xuUnit, bRequest;

  xuSelector = 5;  //wValue
  xuUnit = 4;      //wIndex

  data[0] = slaveAddr;
  data[1] = regAddr & 0xFF;
  data[2] = (regAddr>>8) & 0xFF;
  data[3] = 0x00;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_GET, UVC_GET_CUR,
    xuSelector << 8,
//    xuUnit << 8 | devh->info->ctrl_if.bInterfaceNumber,   //for linux
    devh->info->ctrl_if.extension_unit_descs->request,  //for android
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
  {
    *regDat = data[3];
    printf("Success writing Extension unit, slave:0x%x  reg:0x%x, read data:0x%x\n", slaveAddr, regAddr, *regDat);
    return UVC_SUCCESS;
  } else {
    printf("Fail reading Extension unit\n");
    return ret;
  }
}

uvc_error_t uvc_set_eeprom_register(uvc_device_handle_t *devh, int16_t slaveAddr, int16_t regAddr, int16_t regDat)
{
  uint8_t data[4];
  uvc_error_t ret;
  uint8_t xuSelector, xuUnit, bRequest;

  xuSelector = 5;  //wValue
  xuUnit = 4;      //wIndex

  data[0] = slaveAddr;   //for real write it need to be 0xA0 | 0x01,  to set before read 0xA0
  data[1] = regAddr & 0xFF;
  data[2] = (regAddr>>8) & 0xFF;
  data[3] = regDat;

  ret = libusb_control_transfer(
    devh->usb_devh,
    REQ_TYPE_SET, UVC_SET_CUR,
    xuSelector << 8,
//    xuUnit << 8 | devh->info->ctrl_if.bInterfaceNumber,   //for linux
    devh->info->ctrl_if.extension_unit_descs->request,  //for android
    data,
    sizeof(data),
    0);

  if (ret == sizeof(data))
  {
    printf("Success writing Extension unit, slave:0x%x  reg:0x%x, data:0x%x\n", slaveAddr, regAddr, regDat);
    return UVC_SUCCESS;

  } else {

    printf("Fail writing Extension unit\n");
    return ret;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Code for IriUniverseTwo_  20210812

uvc_device_handle_t *g_devh_IriUniverseTwo_=NULL;
uvc_context_t *ctx_IriUniverseTwo_;
uvc_stream_ctrl_t ctrl_IriUniverseTwo_;
uvc_device_t *g_dev_IriUniverseTwo_=NULL;
int g_isStreaming_IriUniverseTwo_ = 0;

/* This callback function runs once per frame. Use it to perform any
 * quick processing you need, or have it put the frame into your application's
 * input queue. If this function takes too long, you'll start losing frames. */


//void cb_IriUniverseTwo(uvc_frame_t *frame, void *ptr);

void cb_IriUniverseTwo(uvc_frame_t *srcFrame, void *ptr)
{
    unsigned char *ptrSrc;
    unsigned char *ptrDst;

    uvc_frame_t *dstFrame;
    uvc_error_t ret;
    unsigned long i, ii;

    enum uvc_frame_format *frame_format = (enum uvc_frame_format *)ptr;
    /* FILE *fp;
     * static int jpeg_count = 0;
     * static const char *H264_FILE = "iOSDevLog.h264";
     * static const char *MJPEG_FILE = ".jpeg";
     * char filename[16]; */

    /* We'll convert the image from YUV to MONO raw, so allocate space */
    dstFrame = uvc_allocate_frame(srcFrame->width * srcFrame->height);
    if (!dstFrame) {
        printf("unable to allocate dstFrame!\n");
        return;
    }

    // printf("callback! frame_format = %d, width = %d, height = %d, length = %lu, ptr = %d\n",
    //   srcFrame->frame_format, srcFrame->width, srcFrame->height, srcFrame->data_bytes, (int) ptr);

    ptrDst = (unsigned char*)dstFrame->data;
    ptrSrc = (unsigned char*)srcFrame->data;

    dstFrame->width = srcFrame->width;
    dstFrame->height = srcFrame->height;

    for( i=0, ii=0; i<2*(srcFrame->width)*(srcFrame->height); i+=2, ii++)
    {
        *(ptrDst+ii) = *(ptrSrc+i);
    }

//    Mat dispimg(dstFrame->height, dstFrame->width , CV_8UC1, dstFrame->data);
//
//    imshow("Universe Video", dispimg);
//    waitKey(1);

    uvc_free_frame(dstFrame);
}

int IriUniverseTwo_UvcInitDevice()
{

     uvc_error_t res;

     /* Initialize a UVC service context. Libuvc will set up its own libusb
      * context. Replace NULL with a libusb_context pointer to run libuvc
      * from an existing libusb context. */
     res = uvc_init(&ctx_IriUniverseTwo_, NULL);

     if (res < 0) {
	    uvc_perror(res, "uvc_init");
	    return -1;
     }

     puts("UVC initialized");

     /* Locates the first attached UVC device, stores in dev */
     res = uvc_find_device(ctx_IriUniverseTwo_, &g_dev_IriUniverseTwo_, 0, 0, NULL); /* filter devices: vendor_id, product_id, "serial_num" */

    if (res < 0)
    {
    	uvc_perror(res, "uvc_find_device"); /* no devices found */
	return -1;
    }
      puts("Device found");
}
//by peter 211020
int IriUniverseTwo_UvcInitDevice_Android(int vid, int pid, int fd, int busNum, int devNum)
{

  uvc_error_t res;

  /* Initialize a UVC service context. Libuvc will set up its own libusb
   * context. Replace NULL with a libusb_context pointer to run libuvc
   * from an existing libusb context. */
  res = uvc_init2(&ctx_IriUniverseTwo_, NULL, "/dev/bus/usb");

  if (res < 0) {
    uvc_perror(res, "uvc_init");
    return -1;
  }

  puts("UVC initialized");

  /* Locates the first attached UVC device, stores in dev */
  res = uvc_get_device_with_fd(ctx_IriUniverseTwo_, &g_dev_IriUniverseTwo_, vid, pid, NULL, fd, busNum, devNum);

  if (res < 0)
  {
    uvc_perror(res, "uvc_find_device"); /* no devices found */
    return -1;
  }
  puts("Device found");
  return 0;
}

void cb_IriUniverseOne(uvc_frame_t *frame, void *ptr);

int IriUniverseTwo_UvcOpenDevice()
{

        uvc_error_t res;

	if(g_dev_IriUniverseTwo_==NULL)
	{
		printf("g_dev_IriUniverseTwo_ is NULL\n");

		return -1;
	}

       /* Try to open the device: requires exclusive access */
      res = uvc_open(g_dev_IriUniverseTwo_, &g_devh_IriUniverseTwo_);

      if (res < 0)
      {
      	uvc_perror(res, "uvc_open"); /* unable to open device */
         return -1;
      }
      /* Print out a message containing all the information that libuvc
       * knows about the device */
      //uvc_print_diag(g_devh_IriUniverseTwo_, stderr);

      const uvc_format_desc_t *format_desc = uvc_get_format_descs(g_devh_IriUniverseTwo_);
      const uvc_frame_desc_t *frame_desc = format_desc->frame_descs;
      enum uvc_frame_format frame_format;
      int width = 640;
      int height = 480;
      int fps = 30;

      switch (format_desc->bDescriptorSubtype)
      {
	      case UVC_VS_FORMAT_MJPEG:
		frame_format = UVC_COLOR_FORMAT_MJPEG;
		break;
	      case UVC_VS_FORMAT_FRAME_BASED:
		frame_format = UVC_FRAME_FORMAT_H264;
		break;
	      default:
		frame_format = UVC_FRAME_FORMAT_YUYV;
		break;
      }

      if (frame_desc)
      {
        width = frame_desc->wWidth;
        height = frame_desc->wHeight;
        fps = 10000000 / frame_desc->dwDefaultFrameInterval;
      }

      printf("\nFirst format: (%4s) %dx%d %dfps\n", format_desc->fourccFormat, width, height, fps);

      /* Try to negotiate first stream profile */
      res = uvc_get_stream_ctrl_format_size(
          g_devh_IriUniverseTwo_, &ctrl_IriUniverseTwo_, /* result stored in ctrl */
          frame_format,
          width, height, fps /* width, height, fps */
      );

      /* Print out the result */
      //uvc_print_stream_ctrl(&ctrl_IriUniverseTwo_, stderr);

      if (res < 0) {
        	uvc_perror(res, "get_mode"); /* device doesn't provide a matching stream */
		return -1;
      }

#if 1
	/* Start the video stream. The library will call user function cb:
		 *   cb(frame, (void *) 12345)
		 */
	res = uvc_start_streaming(g_devh_IriUniverseTwo_, &ctrl_IriUniverseTwo_, cb_IriUniverseOne, (void *) 12345, 0);

	if (res < 0) {
	  	uvc_perror(res, "start_streaming"); /* unable to start stream */
                printf("Error in uvc_start_streaming : %d\n", res);
	  	return -1;
	}

        g_isStreaming_IriUniverseTwo_ = 1;


  	printf("Start streaming...\n");
#endif

	return 0;


}





int IriUniverseTwo_UvcCloseDeivce()
{

	if(g_devh_IriUniverseTwo_==NULL)
	{
		printf("g_devh_IriUniverseTwo_=NULL\n");
		return -1;
	}

	if(g_isStreaming_IriUniverseTwo_==0)
	{
	 	printf("Uvc not streaming, returning\n");
		return -1;
	}

	/* End the stream. Blocks until last callback is serviced */
        uvc_stop_streaming(g_devh_IriUniverseTwo_);
       	printf("Stop streaming\n");

	g_isStreaming_IriUniverseTwo_ = 0;


      /* Release our handle on the device */
       uvc_close(g_devh_IriUniverseTwo_);

       g_devh_IriUniverseTwo_=NULL;

       printf("Device closed\n");


	return 0;
}



int IriUniverseTwo_UvcDeinitDevice()
{

      /* Release the device descriptor */
      uvc_unref_device(g_dev_IriUniverseTwo_);
      printf("uvc_unref_device\n");

      /* Close the UVC context. This closes and cleans up any existing device handles,
       * and it closes the libusb context if one was not provided. */
      uvc_exit(ctx_IriUniverseTwo_);
      printf("UVC exited\n");

     return 0;
}

int g_iDummySharpnessValue = 5;
int IriUniverseTwo_UvcTurnOffLED()
{
	//if same value consecutive, ignored the control
	if(g_iDummySharpnessValue==5) 	g_iDummySharpnessValue = 4;
	else	 			g_iDummySharpnessValue = 5;

	printf("Setting uvc_set_sharpness: vale:%d\n", g_iDummySharpnessValue);
	uvc_set_sharpness(g_devh_IriUniverseTwo_, g_iDummySharpnessValue);

	return 0;
}



int g_iDummySaturationValue = 8;
int IriUniverseTwo_UvcGreenLED()
{
	//if same value consecutive, ignored the control
	if(g_iDummySaturationValue==8) 	g_iDummySaturationValue = 7;
	else	 			g_iDummySaturationValue = 8;

	printf("Setting uvc_set_saturation: value:%d\n", g_iDummySaturationValue);
	uvc_set_saturation(g_devh_IriUniverseTwo_, g_iDummySaturationValue);

	return 0;
}

int g_iDummyBrightnessValue = 8;
int IriUniverseTwo_UvcBlinkLED()
{
	//if same value consecutive, ignored the control
	if(g_iDummyBrightnessValue==8) 	g_iDummyBrightnessValue = 7;
	else	 			g_iDummyBrightnessValue = 8;

	printf("Setting uvc_set_brightness: value:%d\n", g_iDummyBrightnessValue);
	uvc_set_brightness(g_devh_IriUniverseTwo_, g_iDummyBrightnessValue);

	return 0;
}


int IriUniverseTwo_UvcWriteByte(int regAddr, int regDat)
{
	int16_t slaveAddr = 0xA0 | 0x01;

	uvc_set_eeprom_register(g_devh_IriUniverseTwo_, slaveAddr, regAddr, regDat);
	uvc_get_eeprom_register(g_devh_IriUniverseTwo_, slaveAddr, regAddr, &regDat);

	return 0;
}

int IriUniverseTwo_UvcReadByte(int regAddr, int *regDat)
{
	int8_t readData;
	int16_t slaveAddr = 0xA0;

	uvc_set_eeprom_register(g_devh_IriUniverseTwo_, slaveAddr, regAddr, 0x00);
	uvc_get_eeprom_register(g_devh_IriUniverseTwo_, slaveAddr, regAddr, &readData);

	*regDat = (int)readData;

	return 0;
}


//by peter 211020
void IriUniverseTwoUVC_Reset(){
  uvc_set_sharpness(g_devh_IriUniverseTwo_, 0);
  uvc_set_saturation(g_devh_IriUniverseTwo_, 0);
  uvc_set_brightness(g_devh_IriUniverseTwo_, 0);

}

#endif


