//
// Created by TLKG-014 on 2020/9/8.
//

#ifndef WUKONG_DEMO_LOWVERSION_WKTIMER_H
#define WUKONG_DEMO_LOWVERSION_WKTIMER_H
#include <time.h>

class wktimer {
private:
    timeval blocktimestart={};
    timeval blocktimeend={};
public:
    void pcmblock(int channel,int rate,int bytepersample,int bytesize);
    void block(int tms);

};


#endif //WUKONG_DEMO_LOWVERSION_WKTIMER_H
