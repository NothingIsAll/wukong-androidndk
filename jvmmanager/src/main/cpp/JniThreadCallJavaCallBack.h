//
// Created by TLKG-014 on 2020/9/7.
//

#ifndef WUKONG_DEMO_LOWVERSION_JNITHREADCALLJAVACALLBACK_H
#define WUKONG_DEMO_LOWVERSION_JNITHREADCALLJAVACALLBACK_H

#include <jni.h>
#include <mutex>

class JniThreadCallJavaCallBack {
private:
    jobject javacallbackobj;
    std::mutex m_mutex;
public:
    JniThreadCallJavaCallBack(jobject jobj);
    int javaAdd(int a,int b);
    int javaSub(int a,int b);

};


#endif //WUKONG_DEMO_LOWVERSION_JNITHREADCALLJAVACALLBACK_H
