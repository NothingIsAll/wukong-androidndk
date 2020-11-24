//
// Created by TLKG-014 on 2020/11/23.
//

#ifndef WUKONG_DEMO_LOWVERSION_GLABC_CONFIG_H
#define WUKONG_DEMO_LOWVERSION_GLABC_CONFIG_H


#include "ShapeObj/ShapeObj.h"

class GLABC_config {
private:
    static ShapeObj* drawEngIns;
public:
    static char* ShapeObj_Texture_ImageName;
    static ShapeObj* getDrawEng();

};


#endif //WUKONG_DEMO_LOWVERSION_GLABC_CONFIG_H
