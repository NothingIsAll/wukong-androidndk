//
// Created by TLKG-014 on 2020/11/19.
//
#define LOG_TAG "TextureObj"
#include <GLES2/gl2.h>
#include "TextureObj.h"
#include "../GLABC_config.h"
#include "../FreeImage/ImageLoad.h"
#include "../TLMicLog.h"

void TextureObj::init() {
    VBOinit();
    EBOinit();
    initTexture2D();
    ShaderSrctoProgram();
}

void TextureObj::draw() {
    glBindTexture(GL_TEXTURE_2D,texture);
    glUseProgram(program);
    LinkVAtoLocation();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void TextureObj::release() {

}


void TextureObj::VBOinit() {
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
void TextureObj::EBOinit() {
    /**
        * 生成一个顶点索引对象
        */
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
void TextureObj::initTexture2D() {
    /**
        * 第一个参数纹理数量
        * 也就是一个纹理对象可以对应 多个纹理数量
        * 这个以后怎么通过一个对象 使用多个纹理
        * 还会再讲解
        */
    glGenTextures(1,&texture);
    /**
     * 设置纹理类型 为 GL_TEXTURE_2D
     */
    glBindTexture(GL_TEXTURE_2D,texture);

    /**
     * 纹理环绕方式
     * 设置环绕方式 S/T/R 对应坐标的 X/Y/Z
     * 纹理坐标不同于gl的渲染顶点坐标
     * 纹理坐标是（0，0）~（1，1）
     * 渲染坐标是（-1,-1,-1）~(1,1,1)
     * 两种坐标的顺序对应关系，决定图像的旋转情况
     *
     * 什么情况下需要环绕
     * 如果纹理坐标设置的值大于了(0,0)~(1,1)的范围
     * 则真实纹理 到 纹理坐标之间 填充方式需要设置
     * GL_REPEAT ：纹理的默认行为，重复纹理图像
     * GL_MIRRORED_REPEAET：和   一样，除了重复的图片是镜像放置的
     * GL_CLAMP_TO_EDGE：纹理坐标会在0到1之间，超出的部分会重复纹理坐标的 边缘，就是边缘被拉伸
     * GL_CLAMP_TO_BORDER：超出的部分是用户指定的边缘的颜色，颜色设置需要如下代码：
     * float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
     * glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
     * 现在使用的2D纹理 需要 设置 S/T两个轴的 空余空间 环绕方式
     *
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    /**
     * 纹理过滤方式：
     * 纹理坐标是不依赖纹理的清晰度的，纹理坐标可以是任意的浮点数值，
     * 但纹理的分辨率（解析度）是固定的。
     * 两种过滤情景：放大和缩小 GL_TEXTURE_MAG_FILTER/GL_TEXTURE_MIN_FILTER
     * 在纹理放大或者缩小过程中，纹理坐标可以无限放大或缩小
     * 缩小纹理(渐远纹理)：GL_TEXTURE_MIN_FILTER 物体逐渐远去，看上去越来越小。一个纹理坐标可能对应多个纹理像素点，
     * 放大纹理：GL_TEXTURE_MAG_FILTER 纹理被放大，如果用GL_NEAREST 则出现马赛克式像素点，GL_LINEAR 差值方式则会进行模糊处理
     *
     * 如果是缩小纹理，需要开启多级渐远创建 多级渐远纹理用如下方法：
     * glGenerateMipmap(GL_TEXTURE_2D);
     *
     *过滤情景对应的过滤模式：
     * 基本过滤模式(试用放大情景，和基本的缩小情景(不包括多级渐远))：
     * GL_NEAREST：返回离坐标最近的一个像素值(放大情境下会有马赛克效果)
     * GL_LINEAR：返回坐标 周围像素值得平均值(放大情境下不会有马赛克，会有模糊效果)
     *多级渐远情景(打开了多级渐远创建)过滤模式：
     * GL_NEAREST_MIPMAP_NEAREST：使用NEAREST进行多级渐远纹理创建，并使用NEAREST进行显示时纹理采样
     * GL_LINEAR_MIPMAP_NEAREST：使用LINEAR进行多级渐远纹理创建，并使用NEAREST进行显示时纹理采样
     *GL_NEAREST_MIPMAP_LINEAR：使用NEAREST进行多级渐远纹理创建，并使用LINEAR进行显示时纹理采样
     * GL_LINEAR_MIPMAP_LINEAR：使用LINEAR进行多级渐远纹理创建，并使用LINEAR进行显示时纹理采样
     *
     * 还有一点要注意
     * 如果 GL_TEXTURE_MIN_FILTER 情景 设置了 多级渐远的过滤模式 GL_NEAREST_MIPMAP_NEAREST/GL_LINEAR_MIPMAP_NEAREST/GL_NEAREST_MIPMAP_LINEAR/GL_LINEAR_MIPMAP_LINEAR
     * 则一定要打开 glGenerateMipmap(GL_TEXTURE_2D) 创建多级渐远纹理自动生成，否则 在缩小的情况下可能会黑屏。
     * 并且 glGenerateMipmap(GL_TEXTURE_2D) 一定在glTexImage2D（）绑定纹理数据后再进行自动生成。
     * 可见 glGenerateMipmap/glTexImage2D两个方法应该是状态执行方法，执行后立即生效。
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    /**
     * 获取图像数据
     */
    bool isload = imageLoad.load_from_file(GLABC_config::ShapeObj_Texture_ImageName);
    DLOG("isload =%d imageLoad width=%d height=%d",isload,imageLoad.width,imageLoad.height);
    /**
     *将图像数据 绑定到 当前纹理对象
     * 第一个参数指定纹理目标(环境);设置为 GL_TEXTURE_2D 意味着会生成与当前绑定的纹理 对象在同一个目标(Target)上的纹理(任何绑定到 GL_TEXTURE_1D 和 GL_TEXTURE_3D 的纹理 不会受到影响)
     * 第二个参数为我们打算创建的纹理指定多级渐远纹理的层级，如果你希望单独手工设置 每个多级渐远纹理的层级的话。这里我们填0基本级。
     * 第三个参数告诉OpenGL，我们希望把纹理储存为何种格式。我们的图像只有RGB值， 因此我们把纹理储存为 GL_RGB 值
     * 第四个和第五个参数设置最终的纹理的宽度和高度。我们加载图像的时候提前储存它们 这样我们就能使用相应变量了。下个参数应该一直被设为 0 (遗留问题)。
     * 第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它 们储存在char(byte)，我们将会传入相应值。
     * 最后一个参数是真实的图像数据。
     */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageLoad.width, imageLoad.height, 0, GL_RGB, GL_UNSIGNED_BYTE,imageLoad.imgdata);
    /**
     * 这个自动创建多级渐远纹理
     * 如果没有设置多级渐远的过滤模式，则无需设置。
     * 而且必须在 glTexImage2D 纹理绑定 图像后 设置执行。
     * 否则会黑屏 不生效，而且在程序对象绑定shader对象的时候 会报错502
     * 就记住 这个方法和多级渐远的过滤设置一定是成对出现。
    */
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,0);
}

void TextureObj::ShaderSrctoProgram() {
    program = shaderToProgram.CreateProgram(vertexShaderSource,fragmentShaderSource,vertexshader,fragmentshader);
}

void TextureObj::LinkVAtoLocation() {
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
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8* sizeof(GLfloat),(void*)0);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,vertices);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
}