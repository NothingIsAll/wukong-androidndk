//
// Created by TLKG-014 on 2020/9/7.
//

#define LOG_TAG "JniThreadCallJavaCallBack"

#include <jvmmanager/JniThreadEnvManager.h>
#include "JniThreadCallJavaCallBack.h"
#include "TLMicLog.h"


int JniThreadCallJavaCallBack::javaAdd(int a, int b) {
    m_mutex.lock();
    JNIEnv * pEnv = JniThreadEnvManager::getCurrentEnv();
    jclass cbclass = pEnv->GetObjectClass(javacallbackobj);
    jmethodID methodID = pEnv->GetMethodID(cbclass, "num_add", "(II)I");
    int res =pEnv->CallIntMethod(javacallbackobj, methodID, a,b);
    m_mutex.unlock();
    return res;
}

int JniThreadCallJavaCallBack::javaSub(int a, int b) {
    m_mutex.lock();
    JNIEnv * pEnv = JniThreadEnvManager::getCurrentEnv();
    jclass cbclass = pEnv->GetObjectClass(javacallbackobj);
    jmethodID methodID = pEnv->GetMethodID(cbclass, "num_sub", "(II)I");
    int res =pEnv->CallIntMethod(javacallbackobj, methodID, a,b);
    m_mutex.unlock();
    return res;
}

JniThreadCallJavaCallBack::JniThreadCallJavaCallBack(jobject jobj) {
    javacallbackobj = jobj;
}
