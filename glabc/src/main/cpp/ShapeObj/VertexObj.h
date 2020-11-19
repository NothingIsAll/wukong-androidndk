//
// Created by TLKG-014 on 2020/11/18.
//

#ifndef WUKONG_DEMO_LOWVERSION_VERTEXOBJ_H
#define WUKONG_DEMO_LOWVERSION_VERTEXOBJ_H


#include <GLES2/gl2.h>
#include "ShapeObj.h"
#include "GLShaderToProgram.h"

class VertexObj : public ShapeObj{
public:
    void init();
    void draw();
    void release();

private:
    GLuint VBO,VAO;
    /**
     * 标准化设备坐标，NDC(Normailzed Device Coordinates)
     * xyz 三轴的范围 是 -1 ~ 1
     * 所有超出这个范围的内容都将不被显示
     * 这些坐标 会通过 glViewPort()提供的数据，进行视口变换(Viewport Transform)
     * 视口变换成功后 空间坐标 变成了屏幕的像素，然后输入到片段着色器。
     */
    const GLfloat vertices[9] = { -0.5f, -0.5f, 0.0f,
                           0.5f,  -0.5f, 0.0f,
                           0.0f,  0.5f, 0.0f };
    /**
     *顶点着色器 Vertext shader
     * 第一行：版本生命
     * 第二行：着色器的输入变量 为 三轴向量 position ； location=0描述的变量位置，这一点还不够清楚
     * 第四行：gl_Position 为顶点着色器 输出变量，四轴向量，
     * 输入到输出需要 3轴向量到 4轴向量的转换。
     */
    char* vertexShaderSource = "#version 300 es \n"
                                "layout (location = 0) in vec3 position; \n"
                                "void main() { \n"
                                "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                "} \n";
    /**
     * 片段着色器
     * 处理的是每一个像素的颜色
     * 我们没有定义输入变量
     * 只定义了一个名字 为 color 的输出变量
     * color对象定义的是每一个像素的颜色。
     */
    char* fragmentShaderSource = "#version 300 es \n"
                                    "out vec4 color; \n"
                                    "void main() { \n"
                                    "color = vec4(1.0f, 0.0f, 0.0f, 1.0f); \n"
                                    "}\n";
public:
    char* getShaderSource();

private:
    GLShaderToProgram shaderToProgram;
    GLuint vertexshader,fragmentshader,program;
    void VBOinit();
    void ShaderSrctoProgram();
    void LinkVAtoLocation();

    void LinkVAOtoLocationInit();
    void LinkVAOtoLocation();
};


#endif //WUKONG_DEMO_LOWVERSION_VERTEXOBJ_H
