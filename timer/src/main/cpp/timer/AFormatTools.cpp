//
// Created by TLKG-014 on 2019/2/27.
//
#define LOG_TAG "AFormatTools"
#include "AFormatTools.h"
#include "TLMicLog.h"

AFormatTools::AFormatTools(){
 samplerate = 0;
 channel = 0;
 deepbit = 0;
 bitperbyte =8;
}
long AFormatTools::converTtoF(long time){
  return time*((samplerate*1.0)/1000.0);
}
long AFormatTools::converFtoT(long frames){
  return (frames/(samplerate*1.0))*1000.0;
}
long AFormatTools::converBtoF(long bytesize){
    DLOG("AFormatTools channel = %d, deepbit = %d, bitperbyte = %d",channel,deepbit,bitperbyte);
 long option = (bytesize/channel*1.0)/(deepbit/bitperbyte)*1.0;
  return option;
}
long AFormatTools::converFtoB(long frames){
  return frames*channel*(deepbit/ bitperbyte);
}

long AFormatTools::converTtoB(long time){
 return time*((samplerate*1.0)/1000.0)*channel*(deepbit/ bitperbyte);
} //ms

long AFormatTools::converBtoT(long bytesize){
 return (((bytesize/channel*1.0)/(deepbit/ bitperbyte)*1.0)/(samplerate*1.0))*1000.0;
}

int AFormatTools::getsamplerate(){
  return samplerate;
}
 int AFormatTools::getchannel(){
  return channel;
}
 int AFormatTools::getdeepbit(){
  return deepbit;
}
void AFormatTools::setsamplerate(int rate){
 this->samplerate = rate;
}
void AFormatTools::setchannel(int channel){
 this->channel = channel;
}
void AFormatTools::setdeepbit(int bit){
 this->deepbit = bit;
}