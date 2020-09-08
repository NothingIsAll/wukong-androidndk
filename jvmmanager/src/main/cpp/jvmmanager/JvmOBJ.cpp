//
// Created by TLKG-014 on 2020/9/5.
//
#define LOG_TAG "JvmOBJ"
#include "JvmOBJ.h"

#include "TLMicLog.h"

JavaVM* JvmOBJ::javaVmobj = nullptr;

JavaVM* JvmOBJ::getJvm(){
    return javaVmobj;
}


void JvmOBJ::setJvm(JavaVM* javaVm1){
    javaVmobj = javaVm1;
}