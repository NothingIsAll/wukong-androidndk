//
// Created by TLKG-014 on 2020/7/2.
//

//#define LOG_TAG "FindCardHid"

#include <cstdio>
#include <cstring>
#include "findcard.h"
#include "TLMicLog.h"
#include "FindCardHid.h"
#include "tlmicdes.h"
#include <mutex>


FindCardHid* FindCardHid::findCardHid = nullptr;

FindCardHid::FindCardHid() {
    findcard = new FindCardAdapter();
    micNumDecode = new MicNumDecode();

}

int FindCardHid::FindcardInit() {
    return findcard->FindcardInit();
}

FindCardHid *FindCardHid::getIns() {
    if(findCardHid == nullptr){
        findCardHid = new FindCardHid();
        findCardHid->FindcardInit();
        FindCardHid::getIns()->SetMicPriority("TLCY-",1);
    }
    return findCardHid;
}

int FindCardHid::SetMicPriority(const char *mic, int priority, int device, bool islinein) {
    return findcard->SetMicPriority(mic,priority,device,islinein);
}

int FindCardHid::SetMask(const char *maskmic) {
    return findcard->SetMask(maskmic);
}

void FindCardHid::SetNetPolicy() {
    findcard->SetNetPolicy();
}

void FindCardHid::SetCollectPolicy(int policy, int flag) {
    findcard->SetCollectPolicy(policy,flag);
}

int FindCardHid::FilterInit() {
//    mutex.lock();
     int res = findcard->FilterInit();
//    mutex.unlock();
    return res;
}

int FindCardHid::CollectPolicyFilter(char *buffer, int size) {
    return findcard->CollectPolicyFilter(buffer,size);
}

int FindCardHid::GetSerialnum(MicString *micstr) {
//    mutex.lock();
    int res = findcard->GetSerialnum(micstr);
//    mutex.unlock();
    return res;
}

int FindCardHid::GetInUseDeviceInfo(MicString *micstr) {
//    mutex.lock();
    return findcard->GetInUseDeviceInfo(micstr);
}

int FindCardHid::GetCards(cardstrdevice *rescsd) {
    return findcard->GetCards(rescsd);
}

FindCardHid *FindCardHid::GetAudioInfo(int card_num) {
    char chInfo[256]={};
    char *pTemp = 0;
    char chTemp[128]={};
    memset(chTemp,0,128);
    int nr_ratestmp = 0;
    channels = -1;
    nr_rates = -1;
    sprintf(chInfo,"/proc/asound/card%d/stream0",card_num);
    FILE *fp = fopen(chInfo,"r");
    if(fp==NULL){
        DLOG("%s:Error: No ALSA USB card Found!",__func__);
        return this;
    }
    while (fgets(chInfo,sizeof(chInfo),fp)!=NULL){
        if(strstr(chInfo,"Channels:")){
            pTemp = strstr(chInfo,"Channels:");
            strcpy(chTemp,pTemp + strlen("Channels:"));
            channels = atoi(chTemp);
            DLOG("Channel=%d",channels);
            continue;
        }
        if(strstr(chInfo,"Rates:")){
            pTemp = strstr(chInfo,"Rates:");
            strcpy(chTemp,pTemp + strlen("Rates:"));
            char *pBuff = chTemp;
            char *pCh = strsep(&pBuff, ",");

            while(pCh){
                nr_ratestmp ++;
                rate_table[nr_ratestmp-1] = atoi(pCh);
                pCh = strsep(&pBuff, ",");
            }
            continue;
        }
    }
    fclose(fp);
    nr_rates = nr_ratestmp;
    return this;
}

char *FindCardHid::Getdecode() {
    return micNumDecode->getdecode();
}

int FindCardHid::SetSerialnum(char *num) {
    return micNumDecode->setSerialnum(num);
}

int FindCardHid::IsHIDdmic() {
    MicString micnum;
    findcard->GetSerialnum(&micnum);
    if(SetSerialnum(micnum.c_char())<0){
        return -1;
    }
    return IsHIDdmic_do();
}

int FindCardHid::HidkeyID() {
    MicString micnum;
    findcard->GetSerialnum(&micnum);
    if(SetSerialnum(micnum.c_char())<0){
        return -1;
    }
    return HidkeyID_do();
}

FindCardHid::~FindCardHid() {
    if(findcard){
        delete findcard;
        findcard = nullptr;
    }
    if(micNumDecode){
        delete micNumDecode;
        micNumDecode = nullptr;
    }
}

bool FindCardHid::IsHIDdmic_do() {
    return micNumDecode->isHIDdmic();
}

int FindCardHid::HidkeyID_do() {
    return micNumDecode->hidkeyID();
}
