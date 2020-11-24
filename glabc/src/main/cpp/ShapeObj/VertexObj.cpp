//
// Created by TLKG-014 on 2020/11/18.
//

#include "VertexObj.h"

void VertexObj::init() {
    VBOinit();
    EBOinit();
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

/**
 * EBO 可以和 VBO 顶点链接到shader对象的属性，
 * 都可以绑定到VAO中。
 * 在绘画时 直接bind VAO 即可使用
 */
void VertexObj::EBOinit() {
    /**
        * 生成一个顶点索引对象
        */
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    /**
     * glVertexAttribPointer 函数有很多参数，所以我们仔细来了解它们:
        第一个参数指定我们要配置哪一个顶点属性。记住，我们在顶点着色器中使
        用 layout(location = 0) 定义了顶点属性——位置(Position)的位置值(Location)。
        这样要 把顶点属性的位置值(Location)设置为0，因为我们希望把数据传递到这个顶点属性中， 所以我们在这里填0。
        第二个参数指定顶点属性的大小。顶点属性是 vec3 类型，它由3个数值组成。
        第三个参数指定数据的类型，这里是 GL_FLOAT (GLSL中 vec* 是由浮点数组成的)。
        下个参数定义我们是否希望数据被标准化。如果我们设置为 GL_TRUE ，所有数据都会被 映射到0(对于有符号型signed数据是-1)到1之间。我们把它设置为 GL_FALSE 。
        第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性之间间隔有多少。由于下个 位置数据在3个 GLfloat 后面的位置，我们把步长设置为 3 * sizeof(GLfloat) 。要注意 的是由于我们知道这个数组是紧密排列的(在两个顶点属性之间没有空隙)我们也可以设置 为0来让OpenGL决定具体步长是多少(只有当数值是紧密排列时才可用)。每当我们有更 多的顶点属性，我们就必须小心地定义每个顶点属性之间的空间，我们在后面会看到更 多的例子(译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位 置之间有多少字节)。
        最后一个参数有奇怪的 GLvoid* 的强制类型转换。它表示我们的位置数据在缓冲中起始
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); glEnableVertexAttribArray(0);
        位置的偏移量。由于位置数据是数组的开始，所以这里是0。我们会在后面详细解释这个 参数。
     */
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
     *复制我们的索引数组到一个索引缓冲中，提供给OpenGL使用
     */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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
    /**
     * 绘制VBO
     */
    glDrawArrays(GL_TRIANGLES,0,3);
    /**
     * 绘制EBO
     */
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}






