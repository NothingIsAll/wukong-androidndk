/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_glabc_MyNativeRender */

#ifndef _Included_com_example_glabc_MyNativeRender
#define _Included_com_example_glabc_MyNativeRender
#ifdef __cplusplus
extern "C" {
#endif
#include "GLShaderToProgram.h"
/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_OnInit
 * Signature: ()V
 */
//GLShaderToProgram shaderToProgram;
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1OnInit
  (JNIEnv * env, jobject obj){
//    shaderToProgram.LoadShader(nullptr, nullptr);

}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_OnUnInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1OnUnInit
  (JNIEnv * env, jobject obj){

}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_SetImageData
 * Signature: (III[B)V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1SetImageData
  (JNIEnv * env, jobject obj, jint format, jint width, jint height, jbyteArray bytes){

}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_onSurfaceCreated
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1onSurfaceCreated
  (JNIEnv * env, jobject obj){

}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_OnSurfaceChanged
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1OnSurfaceChanged
  (JNIEnv*  env, jobject obj, jint width, jint height){

}

/*
 * Class:     com_example_glabc_MyNativeRender
 * Method:    native_OnDrawFrame
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_glabc_MyNativeRender_native_1OnDrawFrame
  (JNIEnv * env, jobject obj){

}

#ifdef __cplusplus
}
#endif
#endif
