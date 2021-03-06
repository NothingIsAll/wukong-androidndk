/* DO NOT EDIT THIS FILE - it is machine generated */
#define LOG_TAG "JNI"

#include <jni.h>
#include <cstring>
#include <cstdlib>
#include <MultiChannelResampler.h>
#include <pthread.h>
#include <OboeResampler.h>
#include <libs/include/wktimer.h>
/* Header for class com_example_oboe_channelresampler_ResamplerTest */
#include "TLMicLog.h"
#ifndef _Included_com_example_oboe_channelresampler_ResamplerTest
#define _Included_com_example_oboe_channelresampler_ResamplerTest
#ifdef __cplusplus
extern "C" {
#endif
using namespace resampler;

char* jstring2string(JNIEnv* env, jstring jstr){
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0){
        rtn = (char*)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

/*
 * Class:     com_example_oboe_channelresampler_ResamplerTest
 * Method:    init
 * Signature: (IIILjava/lang/String;Ljava/lang/String;)V
 */
MultiChannelResampler* resamplers;
FILE* infp;
FILE* outfp;
int inrateglobal = 0;
int32_t channelCount = 2;
OboeResampler* oboeResampler = nullptr;
JNIEXPORT void JNICALL Java_com_example_oboe_1channelresampler_ResamplerTest_init
  (JNIEnv * env, jobject obj, jint inrate, jint outrate, jint channel , jstring infile, jstring outfile){
    char* finfile = jstring2string(env,infile);
    char* foutfile = jstring2string(env,outfile);
    DLOG("FILE OPEN infile=%s ",finfile);
    DLOG("FILE OPEN foutfile=%s ",foutfile);
    channelCount = channel;
    inrateglobal = inrate;
//    resamplers= MultiChannelResampler::make(channelCount,inrate,outrate,MultiChannelResampler::Quality::Fastest);
    if(oboeResampler == nullptr){
        oboeResampler = new OboeResampler();
    }
    oboeResampler->init(inrate,outrate,channelCount);
    infp = fopen(finfile,"r");
    outfp = fopen(foutfile,"wb+");
    if(infp == nullptr || outfp == nullptr){
        DLOG("FILE OPEN FAILED!!!");
    }

}

/**
 * 固定输入的数量，输出数量根据返回值来算
 * 量入为出
 * 这个可以根据使用环境来变化，
 * oboe的使用环境 固定输出，变化输入。
 * @param inputBuffer
 * @param numFrames
 * @param outputBuffer
 * @return
 */
//int32_t onProcess(float * inputBuffer,int32_t numFrames,float *outputBuffer) {
//    int framesLeft = numFrames;
//    int framesUse = 0;
//    while (true) {
//        // Gather input samples as needed.
//        if(resamplers->isWriteNeeded()) {
//            //是否还有可用数据
//            if (framesUse<=numFrames) {
//                const float *frame = &inputBuffer[framesUse++ * channelCount];
//                resamplers->writeNextFrame(frame);
//            } else {
//                break;
//            }
//        } else {
//            // Output frame is interpolated from input samples.
//            resamplers->readNextFrame(outputBuffer);
//            outputBuffer += channelCount;
//            framesLeft--;
//        }
//    }
//    return numFrames - framesLeft;
//}
float* inputBuffer= nullptr;
float* outputbuffercache = nullptr;
float* outputBuffer = nullptr;
int32_t onProcess(short * sinputBuffer,int32_t numFrames,short *soutputBuffer) {
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



wktimer timer;
bool isrunable;
void* threadrun(void* ){
    DLOG("thread begin...");
    isrunable = true;
    short buffer[10240]={};
    short bufferout[10240]={};
    int bytesize = 1024;
    if(infp == nullptr || outfp == nullptr)
        return nullptr;
    while(isrunable){

        if(fread(buffer,1,bytesize,infp) > 0){
            timer.pcmblock(channelCount,inrateglobal, sizeof(short),bytesize);
//            resamplers->writeNextFrame()
//            int rescout = onProcess((short*)buffer,bytesize/4,(short*)bufferout);
            int rescout = oboeResampler->onProcess((short*)buffer,bytesize/4,(short*)bufferout);
            DLOG("processing...");
            fwrite(bufferout,1,rescout*4,outfp);
        }else{
            DLOG("read failed ...");
            break;
        }


    }
    DLOG("process end ...");
    return 0;
}

/*
 * Class:     com_example_oboe_channelresampler_ResamplerTest
 * Method:    resamplerProcess
 * Signature: ()V
 */
pthread_t tid = 0;
pthread_attr_t attr;
JNIEXPORT void JNICALL Java_com_example_oboe_1channelresampler_ResamplerTest_resamplerProcess
  (JNIEnv *, jobject){
    pthread_create(&tid,nullptr,threadrun, nullptr);
}


JNIEXPORT void JNICALL Java_com_example_oboe_1channelresampler_ResamplerTest_destory
        (JNIEnv *, jobject){
    isrunable = false;
    if(tid != 0){
        pthread_join(tid, nullptr);
        tid = 0;
    }
    if(oboeResampler){
        delete oboeResampler;
        oboeResampler = nullptr;
    }

}

#ifdef __cplusplus
}
#endif
#endif
