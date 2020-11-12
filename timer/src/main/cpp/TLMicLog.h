//
// Created by TLKG-014 on 2020-03-21.
//

#ifndef MICSERVERJNIDEMO_TLMICLOG_H
#define MICSERVERJNIDEMO_TLMICLOG_H


#include <jni.h>
#include <android/log.h>
#ifdef LOG_TAG
#define DLOG(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,"[flltimerlog]:  " fmt "  [line=%d,fun=%s ]", ##args,__LINE__,__FUNCTION__)
#else
#define DLOG(fmt, args...) //可执行文件中定义printf方法#printf(fmt,##args);
#endif




#endif //MICSERVERJNIDEMO_TLMICLOG_H
