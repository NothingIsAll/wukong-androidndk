//
// Created by TLKG-014 on 2020/9/10.
//

#ifndef WUKONG_DEMO_LOWVERSION_OBOERESAMPLER_HH
#define WUKONG_DEMO_LOWVERSION_OBOERESAMPLER_HH

//#include "MultiChannelResampler.h"
#ifdef __cplusplus
extern "C"{
#endif
//using namespace resampler;
//class MultiChannelResampler;
class OboeResampler {
private:
    float* inputBuffer= nullptr;
    float* outputbuffercache = nullptr;
    float* outputBuffer = nullptr;
    void* resamplersptr = nullptr;
    int channelCount = 2;
    int inrate;
    int outrate;

public:
    void init(int inrate, int outrate, int channel);
//    void init(int inrate, int outrate, int channel , char* infile, char* outfile);
    int onProcess(short * sinputBuffer, int numFrames,short *soutputBuffer);
    ~OboeResampler();

};

#ifdef __cplusplus
}
#endif
#endif //WUKONG_DEMO_LOWVERSION_OBOERESAMPLER_HH
