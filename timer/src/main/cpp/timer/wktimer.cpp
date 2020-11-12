//
// Created by TLKG-014 on 2020/9/8.
//

#define LOG_TAG "wktimer"

#include <sys/time.h>
#include <unistd.h>
//#include <mediaframework/avcore/include/AVCommon.h>
#include <linux/prctl.h>
#include <sys/prctl.h>
#include <TLMicLog.h>
#include "wktimer.h"

void wktimer::pcmblock(int channel,int rate,int bytepersample,int bytesize) {
    long perms = (((bytesize/channel*1.0)/(bytepersample)*1.0)/(rate*1.0))*1000.0;
    block(perms);
}

void wktimer::block(int tms) {
    gettimeofday(&blocktimestart, NULL);
    if(blocktimeend.tv_sec > 0){
        long long usetime = (long long)(((blocktimestart.tv_sec - blocktimeend.tv_sec) * 1000) + ((blocktimestart.tv_usec-blocktimeend.tv_usec) / 1000));
        char thread_name[1024] = {};
        prctl(PR_GET_NAME, (char *) (thread_name));
        if(usetime >= 0 && usetime < tms){
            int sleeptime = tms -usetime;
            usleep(sleeptime*1000);
            DLOG("usetime maxtime  =%d ,usetime =%lld thread_name=%s sleeptime = %d",tms,usetime,thread_name,sleeptime);
        } else{
            DLOG("usetime maxtime  =%d ,usetime =%lld thread_name=%s one=%d,two=%d uneedsleep !!",tms,usetime,thread_name,(usetime >= 0),(usetime < tms));
        }
    }
    gettimeofday(&blocktimeend, NULL);
}
