//
// Created by TLKG-014 on 2020/11/24.
//

#ifndef WUKONG_DEMO_LOWVERSION_TEXTUREUNITSYUVOBJ_H
#define WUKONG_DEMO_LOWVERSION_TEXTUREUNITSYUVOBJ_H

#define LOG_TAG "TextureUnitsYUVObj"
#include <GLES2/gl2.h>
#include "ShapeObj.h"
#include "../FreeImage/ImageLoad.h"
#include "GLShaderToProgram.h"

class TextureUnitsYUVObj : public ShapeObj{
private:
    GLuint texture[2],ytexture,uvtexture;
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
                                 "uniform sampler2D y_texture;                        \n"
                                 "uniform sampler2D uv_texture;                        \n"
                                 "void main()\n"
                                 "{\n"
                                 "	vec3 yuv;										\n"
                                 "   yuv.x = texture(y_texture, TexCoord).a;  	\n"
                                 "   yuv.y = texture(uv_texture, TexCoord).a-0.5;	\n"
                                 "   yuv.z = texture(uv_texture, TexCoord).r-0.5;	\n"
                                 "	highp vec3 rgb = mat3( 1,       1,       	1,					\n"
                                 "               0, 		-0.344, 	1.770,					\n"
                                 "               1.403,  -0.714,       0) * yuv; 			\n"
                                 "	color = vec4(rgb, 1);						\n"
                                 "}\n";

public:
    void init();
    void draw();
    void release();

private:
    GLuint VBO,EBO;
    GLuint vertexshader,fragmentshader,program;
    GLint m_ySamplerLocation,m_uvSamplerLocation;
    GLShaderToProgram shaderToProgram;
    char* yuvbuf = nullptr;
    void VBOinit();
    void EBOinit();
    void initTexture2D();
    void ShaderSrctoProgram();
    void LinkVAtoLocation();

};


#endif //WUKONG_DEMO_LOWVERSION_TEXTUREUNITSYUVOBJ_H
