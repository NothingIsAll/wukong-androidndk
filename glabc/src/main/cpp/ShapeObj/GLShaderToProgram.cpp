//
// Created by TLKG-014 on 2020/11/10.
//
#define LOG_TAG "GLShaderToProgram"

#include <cstdlib>
#include "GLShaderToProgram.h"
#include "../TLMicLog.h"


GLuint GLShaderToProgram::LoadShader(GLenum shaderType, const char *pSource)
{
    GLuint shader = 0;
    /*
     * 创建一个shader
     */
    shader = glCreateShader(shaderType);
    if (shader)
    {
        /*
         * 将着色器源码绑定到 着色器
         */
        glShaderSource(shader, 1, &pSource, NULL);
        /*
         * 编译着色器
         */
        glCompileShader(shader);
        GLint compiled = 0;
        /**
         * 获取编译信息，用于检测编译出错。
         * 这一步是非必须的，用于调试。
         */
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* buf = (char*) malloc((size_t)infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    DLOG("GLUtils::LoadShader Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}


GLuint GLShaderToProgram::CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource, GLuint &vertexShaderHandle, GLuint &fragShaderHandle)
{
    GLuint program = 0;
    vertexShaderHandle = LoadShader(GL_VERTEX_SHADER, pVertexShaderSource);
    if (!vertexShaderHandle) return program;

    fragShaderHandle = LoadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
    if (!fragShaderHandle) return program;
    //创建着色器程序对象
    program = glCreateProgram();
    if (program)
    {
        /**
         * 装载顶点shader对象到着色器程序对象
         */
        glAttachShader(program, vertexShaderHandle);
        CheckGLError("glAttachShader");
        /**
         * 装载片段shader对象到着色器程序对象
         */
        glAttachShader(program, fragShaderHandle);
        CheckGLError("glAttachShader");
        /**
         * 生成着色器程序对象过程中，链接各种着色器对象
         */
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        /**
         * 链接成功后，就可以 卸载并删除两个 shader对象了。
         * 完成了shader对象的使命，绘画时直接使用着色器程序对象。
         */
        glDetachShader(program, vertexShaderHandle);
        glDeleteShader(vertexShaderHandle);
        vertexShaderHandle = 0;
        glDetachShader(program, fragShaderHandle);
        glDeleteShader(fragShaderHandle);
        fragShaderHandle = 0;
        if (linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc((size_t)bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    DLOG("GLUtils::CreateProgram Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    DLOG("GLUtils::CreateProgram program = %d", program);
    return program;
}

void GLShaderToProgram::DeleteProgram(GLuint &program)
{
    DLOG("GLUtils::DeleteProgram");
    if (program)
    {
        glUseProgram(0);
        glDeleteProgram(program);
        program = 0;
    }
}

void GLShaderToProgram::CheckGLError(const char *pGLOperation)
{
    for (GLint error = glGetError(); error; error = glGetError())
    {
        DLOG("GLUtils::CheckGLError GL Operation %s() glError (0x%x)\n", pGLOperation, error);
    }

}



