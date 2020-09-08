//
// Created by TLKG-014 on 2020/6/8.
//

#ifndef WUKONG_DEMO_SOFINDCARD_H
#define WUKONG_DEMO_SOFINDCARD_H


#include "Threads.h"
class FindCard;
class SoFindCard : public Threads{
public:
    void init();
    virtual void* run(void*);
    void stop();

private:
    FindCard* findCard = nullptr;
    bool  isplaying = false;
};



#endif //WUKONG_DEMO_SOFINDCARD_H
