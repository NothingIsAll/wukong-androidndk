//
// Created by TLKG-014 on 2020/11/23.
//

#ifndef WUKONG_DEMO_LOWVERSION_IMAGELOAD_H
#define WUKONG_DEMO_LOWVERSION_IMAGELOAD_H


#include <string>
//#include "FreeImage.h"
class FIBITMAP;
class ImageLoad {
public:
    bool load_from_file(char * filename);
    bool save_to_file(char *filename);
    FIBITMAP* bitmap;
    int width, height;
    char* imgdata;
private:
    std::string filename;
};


#endif //WUKONG_DEMO_LOWVERSION_IMAGELOAD_H
