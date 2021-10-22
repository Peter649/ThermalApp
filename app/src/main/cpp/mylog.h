//
// Created by Peter on 8/17/2021.
//

#ifndef MYCAM_MYLOG_H
#define MYCAM_MYLOG_H
#include <android/log.h>

#define APPNAME "hola"

#define MYLOGD(...) __android_log_print(ANDROID_LOG_DEBUG, APPNAME, __VA_ARGS__)
#define MYLOGE(...) __android_log_print(ANDROID_LOG_ERROR, APPNAME, __VA_ARGS__)
#define MYLOGW(...) __android_log_print(ANDROID_LOG_WARN, APPNAME, __VA_ARGS__)

#endif //MYCAM_MYLOG_H
