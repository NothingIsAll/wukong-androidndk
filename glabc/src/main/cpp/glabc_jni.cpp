/* DO NOT EDIT THIS FILE - it is machine generated */
#define LOG_TAG "glabc_jni"
#include <jni.h>
#include "TLMicLog.h"
#include "MyGLRenderContext.h"
/* Header for class com_example_glabc_MyNativeRender */

#ifndef _Included_com_example_glabc_MyNativeRender
#define _Included_com_example_glabc_MyNativeRender
#ifdef __cplusplus
extern "C" {
#endif
#include "ShapeObj/GLShaderToProgram.h"

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_OnInit
 * Signature: ()V
 */
//GLShaderToProgram shaderToProgram;
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1OnInit
  (JNIEnv * env, jobject obj){
//    shaderToProgram.LoadShader(nullptr, nullptr);
    DLOG("%s",__FUNCTION__);
    MyGLRenderContext::GetInstance();

}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_OnUnInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1OnUnInit
  (JNIEnv * env, jobject obj){
    DLOG("%s",__FUNCTION__);
    MyGLRenderContext::DestroyInstance();
}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_SetImageData
 * Signature: (III[B)V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1SetImageData
  (JNIEnv * env, jobject obj, jint format, jint width, jint height, jbyteArray imageData){
    DLOG("%s",__FUNCTION__);
    int len = env->GetArrayLength (imageData);
    char* buf = new char[len];
    env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte*>(buf));
    MyGLRenderContext::GetInstance()->SetImageData(format, width, height, buf);
    delete[] buf;
    env->DeleteLocalRef(imageData);
}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_onSurfaceCreated
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1onSurfaceCreated
  (JNIEnv * env, jobject obj){
    DLOG("%s",__FUNCTION__);
    MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_OnSurfaceChanged
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1OnSurfaceChanged
  (JNIEnv*  env, jobject obj, jint width, jint height){
    DLOG("%s",__FUNCTION__);
    MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);
}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_OnDrawFrame
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1OnDrawFrame
  (JNIEnv * env, jobject obj){
//    DLOG("%s",__FUNCTION__);
    MyGLRenderContext::GetInstance()->OnDrawFrame();
}

#ifdef __cplusplus
}
#endif
#endif
