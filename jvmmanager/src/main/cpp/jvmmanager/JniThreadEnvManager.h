//
// Created by TLKG-014 on 2020/9/5.
//

#ifndef KARAOKE_TV_SDK_JNITHREADNAMESET_H
#define KARAOKE_TV_SDK_JNITHREADNAMESET_H
#include <jni.h>
#include <map>
#include <mutex>

class JniThreadEnvManager {
public:
    JniThreadEnvManager();
    JniThreadEnvManager(char* tname);
    ~JniThreadEnvManager();


public:
    static JNIEnv* getCurrentEnv();
    /**
     * DefaultEnv 都是new JniThreadEnvManager() 申请的堆内存
     * 需要再线程退出后，或者不再使用线程env后de
     * @return
     */
    static int cleanDefaultEnv();
    JNIEnv *pEnv;
private:
    static std::mutex m_mutex;
    static JNIEnv* findCurrentEnv();
    static JavaVM* jvm;
    bool jvmAttachWithName(char* name);
    void jvmDetachCurrent();
    bool isattached;
    bool isdefaultCreate;
    static std::map<int, JniThreadEnvManager*> threadinfolist;
    static std::map<int , JniThreadEnvManager*>::iterator threadinfolist_iter;

};


#endif //KARAOKE_TV_SDK_JNITHREADNAMESET_H
