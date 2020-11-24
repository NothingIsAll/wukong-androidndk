//
// Created by TLKG-014 on 2020/11/23.
//

#include "GLABC_config.h"
#include "ShapeObj/TextureObj.h"
#include "ShapeObj/VertexObj.h"

char* GLABC_config::ShapeObj_Texture_ImageName = "/sdcard/pngdemo.png";//"/sdcard/DCIM/Camera/IMG_20200605_002041.jpg" ;//"/sdcard/pngdemo.png";
ShapeObj* GLABC_config::drawEngIns = 0;

ShapeObj *GLABC_config::getDrawEng() {
    if(drawEngIns == 0){
//        drawEngIns = new VertexObj();
        drawEngIns = new TextureObj();
    }
    return drawEngIns;
}
