//
// Created by TLKG-014 on 2020/6/8.
//
#define LOG_TAG "SoFindCard"

#include <unistd.h>
#include "SoFindCard.h"
#include "findcardtype.h"
#include "findcard1.3.8/findcard/findcard.h"
#include "TLMicLog.h"
#include "findcard1.3.8/tlcurllibmake/FindCardHid.h"

void *SoFindCard::run(void *) {
    isplaying = true;
    while (isplaying){
        usleep(20000);
        cardstrdevice carddevices;
        FindCardHid::getIns()->GetCards(&carddevices);
        MicString sstr;
        int res = FindCardHid::getIns()->GetSerialnum(&sstr);
        MicString deviceinfo;
        int res2 = FindCardHid::getIns()->GetInUseDeviceInfo(&deviceinfo);
        DLOG("res =%d \n res2=%d \n num=%s  \n   devinfo=%s",res,res2,sstr.c_char(),deviceinfo.c_char());



    }
    return nullptr;
}

void SoFindCard::init() {
//    if(findCard == nullptr){
//        findCard = new FindCard();
//        findCard->FindcardInit();
//        findCard->SetMask("MStar");
//        findCard->SetMask("vocsndcard");
//        findCard->SetMicPriority("TLCY-",1);
//        findCard->SetCollectPolicy(2,1);
//    }
}

void SoFindCard::stop() {
    isplaying = false;
}
