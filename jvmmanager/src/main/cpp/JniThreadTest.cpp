//
// Created by TLKG-014 on 2020/9/7.
//
#define LOG_TAG "JniThreadTest"
#include <jvmmanager/JniThreadEnvManager.h>
#include <unistd.h>
#include <linux/prctl.h>
#include <sys/prctl.h>
#include "JniThreadTest.h"
#include "TLMicLog.h"






void JniThreadTest::run(void) {
    iscancell = true;
    int calculateindex;
    char thread_name[100]={};
    sprintf(thread_name, "flltid=%d", gettid());
//    JniThreadEnvManager* testthreadenv = new JniThreadEnvManager(thread_name);

    while (iscancell){
        JniThreadEnvManager testthreadsenv;
        calculateindex ++;
//        usleep(500000);
        int res1 = callJavaCallBack->javaAdd(calculateindex,calculateindex);
        int res2 = callJavaCallBack->javaSub(res1,calculateindex);
        if(res1%100 == 0){
            char thread_name[1024] ={};
            prctl(PR_GET_NAME, (char *)(thread_name));
            DLOG("res1 =%d,res2=%d,tid=%d thread_name=%s",res1,res2,gettid(),thread_name);
        }

    }
//    delete testthreadenv;

}



void JniThreadTest::runThreadCount(int count) {

    for (int i = 0; i < count; ++i) {
        list_t.push_back(new std::thread(&JniThreadTest::run,this));
    }
}

void JniThreadTest::cancellThread() {
    iscancell = false;
}

void JniThreadTest::setCallBack(JniThreadCallJavaCallBack *callBack) {
    callJavaCallBack = callBack;
}

void JniThreadTest::syncrun() {
    run();
}

