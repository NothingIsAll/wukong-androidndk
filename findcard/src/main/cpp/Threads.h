//
// Created by TLKG-014 on 2020-03-24.
//

#ifndef MICSERVERJNIDEMO_THREADS_H
#define MICSERVERJNIDEMO_THREADS_H


#include <pthread.h>

//void * directrun(void *param);
class Threads {
public:
    friend void * directrun(void *param);
    Threads();
    void start();
    int isrunning();
    int join();
    virtual void* run(void*);

private:
    pthread_t m_tid ;

};



#endif //MICSERVERJNIDEMO_THREADS_H
