//
// Created by TLKG-014 on 2020/11/18.
//

#ifndef WUKONG_DEMO_LOWVERSION_SHAPEOBJ_H
#define WUKONG_DEMO_LOWVERSION_SHAPEOBJ_H

class ShapeObj{
public:
    virtual void init()=0;
    virtual void draw()=0;
    virtual void release()=0;
};

#endif //WUKONG_DEMO_LOWVERSION_SHAPEOBJ_H
