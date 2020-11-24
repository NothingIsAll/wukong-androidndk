//
// Created by TLKG-014 on 2020/11/19.
//

#ifndef WUKONG_DEMO_LOWVERSION_TEXTUREOBJ_H
#define WUKONG_DEMO_LOWVERSION_TEXTUREOBJ_H


#include "ShapeObj.h"
#include "../FreeImage/ImageLoad.h"
#include "GLShaderToProgram.h"

class TextureObj : public ShapeObj{
private:
    GLuint texture;
    ImageLoad imageLoad;
    GLfloat vertices[32] = {
// ----顶点坐标----   ---- 颜色 ----   ---- 纹理坐标 ----
    0.5f, 0.5f,0.0f, 1.0f, 0.0f,0.0f, 1.0f, 1.0f, // 右上
    0.5f,-0.5f,0.0f, 0.0f, 1.0f,0.0f, 1.0f, 0.0f, // 右下
    -0.5f,-0.5f,0.0f,0.0f, 0.0f,1.0f, 0.0f, 0.0f, // 左下
    -0.5f,0.5f,0.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f  // 左上
    };
    const int indices[6]={
            0,1,2,
            2,3,0};

    char* vertexShaderSource = "#version 300 es\n"
                   "layout (location = 0) in vec3 position;\n"
                   "layout (location = 1) in vec3 color;\n"
                   "layout (location = 2) in vec2 texCoord;\n"
                   "out vec3 ourColor;\n"
                   "out vec2 TexCoord;\n"
                   "void main()\n"
                   "{\n"
                   "gl_Position = vec4(position, 1.0f); \n"
                   "ourColor = color;\n"
                   "TexCoord = texCoord;\n"
                   "}\n";


    char* fragmentShaderSource = "#version 300 es\n"
                     "in vec3 ourColor;\n"
                     "in vec2 TexCoord;\n"
                     "out vec4 color;\n"
                     "uniform sampler2D ourTexture;\n"
                     "void main()\n"
                     "{\n"
                     "    color = texture(ourTexture, TexCoord);\n"
                     "}\n";

public:
    void init();
    void draw();
    void release();

private:
    GLuint VBO,EBO;
    GLuint vertexshader,fragmentshader,program;
    GLShaderToProgram shaderToProgram;
    void VBOinit();
    void EBOinit();
    void initTexture2D();
    void ShaderSrctoProgram();
    void LinkVAtoLocation();

};


#endif //WUKONG_DEMO_LOWVERSION_TEXTUREOBJ_H
