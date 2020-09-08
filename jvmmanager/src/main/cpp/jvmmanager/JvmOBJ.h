//
// Created by TLKG-014 on 2020/9/5.
//

#ifndef KARAOKE_TV_SDK_JVMOBJ_H
#define KARAOKE_TV_SDK_JVMOBJ_H


#include <jni.h>



class JvmOBJ {
private:
    static JavaVM* javaVmobj;
public:
    static JavaVM* getJvm();
    static void setJvm(JavaVM* javaVm1);

};


#endif //KARAOKE_TV_SDK_JVMOBJ_H
