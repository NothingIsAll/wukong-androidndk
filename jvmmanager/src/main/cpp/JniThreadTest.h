//
// Created by TLKG-014 on 2020/9/7.
//

#ifndef WUKONG_DEMO_LOWVERSION_JNITHREADTEST_H
#define WUKONG_DEMO_LOWVERSION_JNITHREADTEST_H

#include <thread>
#include <list>
#include "JniThreadCallJavaCallBack.h"

class JniThreadTest {

private:
    JniThreadCallJavaCallBack* callJavaCallBack;
    bool iscancell;
    std::list<std::thread*> list_t;
    void run(void);
public:
    void syncrun();
    void setCallBack(JniThreadCallJavaCallBack* callBack);
    void runThreadCount(int count);
    void cancellThread();

};


#endif //WUKONG_DEMO_LOWVERSION_JNITHREADTEST_H
