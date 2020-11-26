//
// Created by TLKG-014 on 2020/11/23.
//

#include "GLABC_config.h"
#include "ShapeObj/TextureObj.h"
#include "ShapeObj/VertexObj.h"
#include "ShapeObj/TextureUnitsYUVObj.h"

char* GLABC_config::ShapeObj_Texture_ImageName = "/sdcard/DCIM/Camera/IMG_20200607_074239.jpg";//"/sdcard/DCIM/Camera/IMG_20200605_002041.jpg" ;//"/sdcard/pngdemo.png";"/sdcard/DCIM/Camera/IMG_20200607_074239.jpg"
char* GLABC_config::ShapeObj_TextureUnitsSaveImageName = "/sdcard/DCIM/Camera/freeimagesave.JPEG";
ShapeObj* GLABC_config::drawEngIns = 0;

ShapeObj *GLABC_config::getDrawEng() {
    if(drawEngIns == 0){
//        drawEngIns = new VertexObj();
//        drawEngIns = new TextureObj();
        drawEngIns = new TextureUnitsYUVObj();
    }
    return drawEngIns;
}
