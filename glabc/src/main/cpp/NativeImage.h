//
// Created by TLKG-014 on 2020/11/16.
//

#ifndef WUKONG_DEMO_LOWVERSION_NATIVEIMAGE_H
#define WUKONG_DEMO_LOWVERSION_NATIVEIMAGE_H


class NativeImage {
public:
    int format;
    int width;
    int height;
    char* ppPlane[3] = {};
};


#endif //WUKONG_DEMO_LOWVERSION_NATIVEIMAGE_H
