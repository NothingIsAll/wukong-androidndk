//
// Created by TLKG-014 on 2020/11/16.
//
#define LOG_TAG "MyGLRenderContext"

#include <GLES2/gl2.h>
#include "MyGLRenderContext.h"
#include "TLMicLog.h"
#include "GLCommon.h"
#include "NativeImage.h"
#include "GLABC_config.h"


MyGLRenderContext* MyGLRenderContext::m_pContext = nullptr;

MyGLRenderContext::MyGLRenderContext()
{

}

MyGLRenderContext::~MyGLRenderContext()
{

}

void MyGLRenderContext::SetImageData(int format, int width, int height, char* pData)
{
    DLOG("MyGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width, height, pData);
    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;

    switch (format)
    {
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
            break;
        default:
            break;
    }

    //m_TextureMapSample->LoadImage(&nativeImage);

}

void MyGLRenderContext::OnSurfaceCreated()
{
    DLOG("MyGLRenderContext::OnSurfaceCreated");
    /**
     * 除了 glClear 之外，我们还要调用 glClearColor 来设置要清空缓冲的颜色。
     * 当调用 glClear 函数之后，整个指定清空的缓冲区都被填充为 glClearColor 所设置的颜色。
     * 这两行代码体现了状态机，glClearColor为对clear状态设置，glClear 为真正的清空执行执行，
     */
    glClearColor(1.0f,1.0f,0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    GLABC_config::getDrawEng()->init();
}

void MyGLRenderContext::OnSurfaceChanged(int width, int height)
{
    DLOG("MyGLRenderContext::OnSurfaceChanged [w, h] = [%d, %d]", width, height);
    /**
     * 根据 宽高 在片段着色器之前进行顶点到像素的转换
     */
    glViewport(0, 0, width, height);
}

void MyGLRenderContext::OnDrawFrame()
{
//    DLOG("MyGLRenderContext::OnDrawFrame");
    /**
     * 每次都使用glClearColor 设置的颜色当做底色，进行擦除。
     */
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    GLABC_config::getDrawEng()->draw();


}

MyGLRenderContext *MyGLRenderContext::GetInstance()
{
//    DLOG("MyGLRenderContext::GetInstance");
    if (m_pContext == nullptr)
    {
        m_pContext = new MyGLRenderContext();
    }
    return m_pContext;
}

void MyGLRenderContext::DestroyInstance()
{
    DLOG("MyGLRenderContext::DestroyInstance");
    if (m_pContext)
    {
        delete m_pContext;
        m_pContext = nullptr;
    }

}

