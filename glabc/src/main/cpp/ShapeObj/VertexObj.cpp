//
// Created by TLKG-014 on 2020/11/18.
//

#include "VertexObj.h"

void VertexObj::init() {
    VBOinit();
    ShaderSrctoProgram();
}


void VertexObj::release() {

}

char *VertexObj::getShaderSource() {
    return vertexShaderSource;
}



void VertexObj::VBOinit() {
/**
     *生成一个顶点对象
     */
    glGenBuffers(1, &VBO);
    /**
     * 给顶点对象 绑定一个或多个 顶点缓存对象。
     */
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    /**
     * 将顶点数据 传输给 顶点缓存对象。
     * GL_STATIC_DRAW :数据不会或几乎不会改变。
     * GL_DYNAMIC_DRAW :数据会被改变很多。
     * GL_STREAM_DRAW :数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}


void VertexObj::ShaderSrctoProgram() {
   program = shaderToProgram.CreateProgram(vertexShaderSource,fragmentShaderSource,vertexshader,fragmentshader);
}

/**
 * 这个方法作用：
 * 链接顶点数据 与 顶点shader对象中的location属性的关联。
 * 需要每次绘制前 都要调用
 * glVertexAttribPointer()
 * 不与VBO结合，直接单独使用时，需要最后一个参数，传入顶点数据。
 * 如果是在bind VBO 后面使用，则设置VBO 顶点与shader中属性的联系
 * 同时这种方式别忘了VBO的配置初始化 调用 VBOinit()
 * glEnableVertexAttribArray（） 使顶点属性链接生效
 */
void VertexObj::LinkVAtoLocation() {
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(GLfloat),(void*)0);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,vertices);
    glEnableVertexAttribArray(0);
}
/**
 * 这个方法作用：
 * 链接顶点数据 与 顶点shader对象中的location属性的关联。
 * 需要每次绘制前 都要调用
 * glVertexAttribPointer()
 * 直接单独使用需要最后一个参数，顶点数据。
 * 如果是在bind VBO 后面使用，则设置VBO 顶点与shader中属性的联系
 * glEnableVertexAttribArray（） 使顶点属性链接生效
 */
void VertexObj::LinkVAOtoLocationInit() {
//    glGenVertexArrays(1,&VAO);
//    glBindVertexArray(VAO);
    /**
     * bind状态下 所有方法的设置都是对bind对象的设置。
     * 设置完成后 恢复bind 对象 0
     * 当绑定对象在使用的时候重新bind
     */
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(GLfloat),(void*)0);
    glEnableVertexAttribArray(0);
//    glBindVertexArray(0);
}

void VertexObj::LinkVAOtoLocation() {
//    glBindVertexArray(VAO);
}


void VertexObj::draw() {
    /**纯属性方式
     * 或者 VBO 与属性结合的方式
     * 设置顶点数据 与shader对象中location的链接
     */
    LinkVAtoLocation();
    /**
     * VAO的方式
     * 设置顶点数据 与shader对象中location的链接
     * 目前 300 es 版本不支持VAO对象
     */
//    LinkVAOtoLocation();
    /**
     * shader程序对象的激活使用，
     *
     */
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES,0,3);
}




