//
// Created by TLKG-014 on 2020/11/10.
//

#ifndef WUKONG_DEMO_LOWVERSION_GLSHADERTOPROGRAM_H
#define WUKONG_DEMO_LOWVERSION_GLSHADERTOPROGRAM_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class GLShaderToProgram {
public:
    GLuint LoadShader(GLenum shaderType, const char *pSource);


};


#endif //WUKONG_DEMO_LOWVERSION_GLSHADERTOPROGRAM_H
