//
// Created by TLKG-014 on 2020-03-24.
//
#define  LOG_TAG "Threads"
#include <cerrno>
#include "Threads.h"
#include "TLMicLog.h"

void * directrun(void *param){
    DLOG("line=%d,fun=%s",__LINE__,__FUNCTION__);
    Threads * mthis = (Threads*)param ;
    DLOG("line=%d,fun=%s mthis =%p",__LINE__,__FUNCTION__,mthis);
    mthis->run(mthis);
    DLOG("line=%d,fun=%s",__LINE__,__FUNCTION__);
    return 0;
}

void Threads::start() {
    int ret = pthread_create(&(this->m_tid) , NULL , directrun , (void*)this);
}

int Threads::join(){
    if(m_tid)
        pthread_join(m_tid,0);
    return 0;
}

int Threads::isrunning(){
    int pthread_kill_err;
    pthread_kill_err = pthread_kill(m_tid,0);
    if(pthread_kill_err == ESRCH){
        DLOG("ID 为 0x%x 的线程不存在或者已经退出。/n",(unsigned int)m_tid);
        return 0;
    }else if(pthread_kill_err == EINVAL){
        DLOG("发送信号非法。/n");
        return -1;
    }else{
        DLOG("ID 为 0x%x 的线程目前仍然存活。/n",(unsigned int)m_tid);
        return 1;
    }
}

Threads::Threads() {
    m_tid = 0;
}

void *Threads::run(void*) {
    DLOG("line=%d,fun=%s",__LINE__,__FUNCTION__);
    return nullptr;
}
