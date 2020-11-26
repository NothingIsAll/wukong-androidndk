//
// Created by TLKG-014 on 2020/11/23.
//
#define LOG_TAG "ImageLoad"
#include <FreeImage.h>
#include <string>
#include "ImageLoad.h"
#include "../TLMicLog.h"

bool ImageLoad::save_to_file(char *filename)
{
    if (FreeImage_Save(FIF_JPEG,bitmap,filename,0) )
        return true;
    else
        return false;
}

bool ImageLoad::load_from_file(char *filename) {
    this->filename = std::string(filename);
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP *dib(0);
    BYTE* bits(0);
    fif = FreeImage_GetFileType(filename, 0);
    if(fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    if(fif == FIF_UNKNOWN){
        DLOG("load false !!! FIF_UNKNOWN 1 filename=%s",filename);
        return false;
    }


    if(FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
    if(!dib){
        DLOG("load false !!! FIF_UNKNOWN 2");
        return false;
    }


    bits = FreeImage_GetBits(dib);
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    DLOG("load success !!! bits=%p,width=%d,height=%d",bits,width,height);
    if((bits == 0) || (width == 0) || (height == 0))
    {
        FreeImage_Unload(dib);
        DLOG("load false !!! bits=%p,width=%d,height=%d",bits,width,height);
        return false;
    }

    FREE_IMAGE_TYPE type;
    type=FreeImage_GetImageType(dib);

    RGBQUAD * pal = FreeImage_GetPalette(dib) ;

    unsigned int bpp;
    bpp= FreeImage_GetBPP( dib ) ;

    // RGBA 每一个颜色的最大值
    unsigned red_mask , green_mask , blue_mask ;

    red_mask = FreeImage_GetRedMask ( dib ) ;
    green_mask = FreeImage_GetGreenMask ( dib ) ;
    blue_mask = FreeImage_GetBlueMask ( dib ) ;
    DLOG("red_mask =%d,green_mask=%d,blue_mask=%d",red_mask,green_mask,blue_mask);

    bitmap = FreeImage_Allocate(width,height,24);
    //转换为 rgba 的图元格式
    //32 = 4*8 每个颜色8bit，是通用的图元格式
    bitmap= FreeImage_ConvertTo24Bits(dib);
    imgdata = (char*)FreeImage_GetBits(bitmap);
    //翻转每个颜色值
    //FreeImage_Invert(bitmap);
    DLOG("load successful !!!");

    red_mask = FreeImage_GetRedMask ( bitmap ) ;
    green_mask = FreeImage_GetGreenMask ( bitmap ) ;
    blue_mask = FreeImage_GetBlueMask ( bitmap ) ;
    DLOG("red_mask =%d,green_mask=%d,blue_mask=%d",red_mask,green_mask,blue_mask);

    return true;
}
