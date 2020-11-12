//
// Created by TLKG-014 on 2020/9/10.
//



#include <cstdint>
#include <cstring>
#include <cstdlib>
#include "OboeResampler.h"
#include "MultiChannelResampler.h"
#ifdef __cplusplus
extern "C"{
#endif

using namespace resampler;
void OboeResampler::init(int inrate, int outrate, int channel){
    channelCount = channel;
    resamplersptr= resampler::MultiChannelResampler::make(channelCount,inrate,outrate,resampler::MultiChannelResampler::Quality::Fastest);
    this->inrate = inrate;
    this->outrate = outrate;
}


int OboeResampler::onProcess(short * sinputBuffer, int numFrames,short *soutputBuffer) {
    MultiChannelResampler* resamplers = (MultiChannelResampler*)resamplersptr;
    if(inputBuffer == nullptr){
        inputBuffer = (float*)malloc(numFrames*channelCount* sizeof(float));
        memset(inputBuffer,0,numFrames*channelCount* sizeof(float));
    }
    if(outputbuffercache == nullptr){
        outputbuffercache = (float*)malloc(numFrames*channelCount* sizeof(float)*10);
        memset(outputbuffercache,0,numFrames*channelCount* sizeof(float)*10);
    }

    outputBuffer = outputbuffercache;
    int framesLeft = numFrames;
    int framesUse = 0;
    while (true) {
        // Gather input samples as needed.
        if(resamplers->isWriteNeeded()) {
            //是否还有可用数据
            if (framesUse< numFrames) {
                for (int i=0;i<channelCount;i++){
                    inputBuffer[(channelCount*framesUse)+i] = sinputBuffer[(channelCount*framesUse)+i]/ 32768.0f;
                }
                const float *frame = &inputBuffer[framesUse++ * channelCount];
                resamplers->writeNextFrame(frame);
            } else {
                break;
            }
        } else {
            // Output frame is interpolated from input samples.
            resamplers->readNextFrame(outputBuffer);
            for (int i=0;i<channelCount;i++){
                soutputBuffer[(channelCount*(numFrames - framesLeft))+i] = outputBuffer[i]* 32768;
            }
            outputBuffer += channelCount;
            framesLeft--;
        }
    }
    return numFrames - framesLeft;
}

OboeResampler::~OboeResampler() {
    MultiChannelResampler* resamplers = (MultiChannelResampler*)resamplersptr;
    if(resamplers){
        delete resamplers;
        resamplers = nullptr;
    }
    if(inputBuffer){
        free(inputBuffer);
        inputBuffer = nullptr;
    }
    if(outputbuffercache){
        free(outputbuffercache);
        outputbuffercache = nullptr;
    }
}

#ifdef __cplusplus
}
#endif