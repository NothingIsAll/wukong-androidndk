//
// Created by TLKG-014 on 2020/9/5.
//

#define LOG_TAG "JniThreadEnvManager"
#include <sys/prctl.h>
#include <unistd.h>
//#include <mediaframework/avcore/include/AVCommon.h>
#include "JniThreadEnvManager.h"
#include "JvmOBJ.h"
#include "TLMicLog.h"


std::map<int, JniThreadEnvManager*> JniThreadEnvManager::threadinfolist;
std::map<int , JniThreadEnvManager*>::iterator JniThreadEnvManager::threadinfolist_iter;
std::mutex JniThreadEnvManager::m_mutex;
JavaVM* JniThreadEnvManager::jvm;

bool JniThreadEnvManager::jvmAttachWithName(char *name) {
    char thread_name[128] = {0};
    if (name == nullptr){
        sprintf(thread_name,"flldeftid=%d",gettid());
    }else{
        sprintf(thread_name,"%s",name);
    }
//    prctl(PR_GET_NAME, (char *)(thread_name));
    JavaVMAttachArgs args;
    args.version = JNI_VERSION_1_6;  // version值请参考你的NDK，必须大于JNI_VERSION_1_2
    args.name = (char *)thread_name;
    args.group = NULL;
    DLOG("JniThreadNameSet::CallJavaGMICStream::jvmAttach() thread_name =%s",thread_name);
    int res = 0;
    pEnv = 0;
    if((res=jvm->GetEnv((void**)&pEnv, JNI_VERSION_1_6))<0){
        DLOG("JniThreadNameSet::CallJavaGMICStream::jvmAttach()222 pEnv= %d res= %d",pEnv,res);
        if(jvm->AttachCurrentThread(&pEnv, (void*)&args) != JNI_OK){
//        if(jvm->AttachCurrentThread(&pEnv, nullptr) != JNI_OK){
            DLOG("JniThreadNameSet::CallJavaGMICStream::jvmAttach()333 pEnv =%d",pEnv);
            return false;
        }
        DLOG("JniThreadNameSet::CallJavaGMICStream::jvmAttach()444 pEnv =%d",pEnv);
        return true;
    }
    return false;
}

void JniThreadEnvManager::jvmDetachCurrent() {
    jvm->DetachCurrentThread();
}
JniThreadEnvManager::JniThreadEnvManager() {
//    m_mutex.lock();
    isdefaultCreate = true;
    jvm = JvmOBJ::getJvm();
    isattached = jvmAttachWithName((char*) nullptr);
    DLOG("JniThreadNameSet::insert id = %d,envp=%d,linenum=%d isattached=%d", gettid(), pEnv, __LINE__, isattached);
    threadinfolist.insert(std::make_pair(gettid(),this));
//    m_mutex.unlock();
}
JniThreadEnvManager::JniThreadEnvManager(char *tname) {
    m_mutex.lock();
    isdefaultCreate = false;
    jvm = JvmOBJ::getJvm();
    isattached = jvmAttachWithName(tname);
    if(tname != nullptr)
    DLOG("JniThreadNameSet::insert id = %d,envp=%d,name=%s linenum=%d isattached=%d", gettid(), pEnv, tname, __LINE__, isattached);
    threadinfolist.insert(std::make_pair(gettid(),this));
    m_mutex.unlock();
}

JniThreadEnvManager::~JniThreadEnvManager() {
    m_mutex.lock();
    if(findCurrentEnv()){
        threadinfolist.erase(gettid());
        if(isattached){
            jvmDetachCurrent();
        }
    }
    m_mutex.unlock();
}

JNIEnv* JniThreadEnvManager::getCurrentEnv() {
    m_mutex.lock();
    JNIEnv* env;
    if((env = findCurrentEnv()) != nullptr){
        m_mutex.unlock();
        return env;
    }else{
//        new JniThreadEnvManager();
//        env = findCurrentEnv();
        m_mutex.unlock();
        return nullptr;//env;
    }
    return nullptr;
}

JNIEnv *JniThreadEnvManager::findCurrentEnv() {
    threadinfolist_iter = threadinfolist.find(gettid());
    if(threadinfolist_iter == threadinfolist.end()) {
        return nullptr;
    }else {
        JNIEnv* env = threadinfolist_iter->second->pEnv;
        DLOG("JniThreadNameSet::get id = %d,envp=%d",gettid(),env);
        return env;
    }
    return nullptr;
}

/**
 * 暂时不可用，析构方法中会移除 JniThreadEnvManager 对象
 * cleanDefaultEnv 中也会移除，而且如果不在线程内执行则没办法
 * jvm->DetachCurrentThread();
 * 所以没法选择智能管理，
 * 在线程开始和结束之前 手动attach和deattach是最好的管理方式。
 * @return
 */
int JniThreadEnvManager::cleanDefaultEnv() {
    for ( threadinfolist_iter = threadinfolist.begin();threadinfolist_iter != threadinfolist.end();) {
        if (threadinfolist_iter->second != nullptr) {

            delete threadinfolist_iter->second ;
            threadinfolist.erase( threadinfolist_iter++);
        } else{
            threadinfolist_iter++;
        }
    }
    return 0;
}




