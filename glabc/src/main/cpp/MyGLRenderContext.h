//
// Created by TLKG-014 on 2020/11/16.
//

#ifndef WUKONG_DEMO_LOWVERSION_MYGLRENDERCONTEXT_H
#define WUKONG_DEMO_LOWVERSION_MYGLRENDERCONTEXT_H


#include <cstdint>
#include "ShapeObj/VertexObj.h"

class MyGLRenderContext {
public:
    static MyGLRenderContext* m_pContext;
    static MyGLRenderContext *GetInstance();
    static void DestroyInstance();
    MyGLRenderContext();
    ~MyGLRenderContext();

    void SetImageData(int format, int width, int height, char* pData);
    void OnSurfaceCreated();
    void OnSurfaceChanged(int width, int height);
    void OnDrawFrame();

private:
    VertexObj drawsamples;

};


#endif //WUKONG_DEMO_LOWVERSION_MYGLRENDERCONTEXT_H
