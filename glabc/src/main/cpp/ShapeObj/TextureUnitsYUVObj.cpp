//
// Created by TLKG-014 on 2020/11/24.
//
#define LOG_TAG "TextureUnitsYUVObj"
#include "TextureUnitsYUVObj.h"
#include "../TLMicLog.h"
#include "../GLABC_config.h"
#include "../libyuv/include/libyuv.h"

void TextureUnitsYUVObj::init() {
    VBOinit();
    EBOinit();
    initTexture2D();
    ShaderSrctoProgram();
}

void TextureUnitsYUVObj::draw() {
    LinkVAtoLocation();
    glUseProgram(program);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureUnitsYUVObj::release() {

}

void TextureUnitsYUVObj::VBOinit() {
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
void TextureUnitsYUVObj::EBOinit() {
    /**
        * 生成一个顶点索引对象
        */
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
int GetImageStride(int lWidth, int num){
    int tlWidth = 0;
    int tnum = 0;
    int res = 0;
    if (lWidth > 0 && num > 0){
        tlWidth = lWidth;
        tnum = num;
        res = tlWidth % tnum;
        if (res != 0){
            int multiple= tlWidth/tnum;
            tlWidth = tnum*(multiple+1);
        }
    }
    return tlWidth;
}
void TextureUnitsYUVObj::initTexture2D() {
    /**
     * 加载图片数据
     */
    bool isload = imageLoad.load_from_file(GLABC_config::ShapeObj_Texture_ImageName);
    DLOG("isload =%d imageLoad width=%d height=%d",isload,imageLoad.width,imageLoad.height);
    if(isload){
        /**
         * 将图片的RGBA 转为 YUV 格式
         */
         FILE* fpyuv420 = fopen("/sdcard/yuv420.yuv","wb+");
         FILE* fpyuvNV21 = fopen("/sdcard/yuvnv21.yuv","wb+");
        FILE* fprgba = fopen("/sdcard/rgba.rgb","wb+");
        imageLoad.save_to_file(GLABC_config::ShapeObj_TextureUnitsSaveImageName);
        char* yuvframeBuffer = (char*)malloc(imageLoad.width*imageLoad.height*3);
        char* ybuf = yuvframeBuffer;
        char* ubuf = yuvframeBuffer + imageLoad.width*imageLoad.height;
        char* vbuf = yuvframeBuffer + imageLoad.width*imageLoad.height*5/4;
        int mutinum = 4;
        int stride_rgb = GetImageStride(imageLoad.width*3,mutinum);
        int stride_y = GetImageStride(imageLoad.width,mutinum);
        int stride_u = GetImageStride(imageLoad.width/2,4);
        int stride_v = stride_u;
        int stride_uv = stride_y;
        DLOG("stride_rgba = %d stride_y = %d,stride_u = %d stride_v = %d stride_uv = %d",stride_rgb,stride_y,stride_u,stride_v,stride_uv);
        if(fprgba){
            fwrite(imageLoad.imgdata,1,imageLoad.width*imageLoad.height*3,fprgba);
            fclose(fprgba);
        }
        libyuv::RGB24ToI420((uint8*)imageLoad.imgdata,stride_rgb,(uint8*)ybuf,stride_y,(uint8*)ubuf,stride_u,(uint8*)vbuf,stride_v,imageLoad.width,imageLoad.height);
        if(fpyuv420){
            fwrite(yuvframeBuffer,1,imageLoad.width*imageLoad.height*3/2,fpyuv420);
            fclose(fpyuv420);
        }

        if(yuvbuf){
            free(yuvbuf);
        }
        yuvbuf = (char*)malloc(imageLoad.width*imageLoad.height*3);
        char* desybuf = yuvbuf;
        char* desuvbuf = yuvbuf + imageLoad.width*imageLoad.height;
        libyuv::I420ToNV21((uint8*)ybuf,stride_y,(uint8*)ubuf,stride_u,(uint8*)vbuf,stride_v,(uint8*)desybuf,stride_y,(uint8*)desuvbuf,stride_uv,imageLoad.width,imageLoad.height);
        if(fpyuvNV21){
            fwrite(yuvbuf,1,imageLoad.width*imageLoad.height*3/2,fpyuvNV21);
            fclose(fpyuvNV21);
        }

    }

    /**
     * 详细注释请看TextureObj.cpp
     */
    glGenTextures(1,texture);
    ytexture = texture[0];
    uvtexture = texture[1];
    /**
     * 将yuv数据分别绑定 到两个纹理对象
     * 绑定Y纹理 需要 单元素存储格式比如
     * GL_ALPHA / GL_LUMINANCE
     * 如果用 GL_ALPHA shader代码中 中需要使用.a 获取像素y值
     * 如果用 GL_LUMINANCE shader代码中 中需要使用.r 获取像素y值
     *
     *
     */
    glBindTexture(GL_TEXTURE_2D,ytexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, imageLoad.width, imageLoad.height, 0, GL_ALPHA, GL_UNSIGNED_BYTE,yuvbuf);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);


    glBindTexture(GL_TEXTURE_2D,uvtexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, imageLoad.width>>1, imageLoad.height>>1, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,yuvbuf + imageLoad.width*imageLoad.height);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);

}

void TextureUnitsYUVObj::ShaderSrctoProgram() {
    program = shaderToProgram.CreateProgram(vertexShaderSource,fragmentShaderSource,vertexshader,fragmentshader);
    // Get the sampler location
    m_ySamplerLocation = glGetUniformLocation (program, "y_texture" );
    m_uvSamplerLocation = glGetUniformLocation(program, "uv_texture");
}

void TextureUnitsYUVObj::LinkVAtoLocation() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) 0);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,vertices);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    /**
     * 将生成的纹理 对象进行使用
     * 先激活一个纹理单元 glActiveTexture(GL_TEXTURE0);
     * 将纹理对象绑定到这个 纹理单元 glBindTexture(GL_TEXTURE_2D,ytexture);
     * 将 纹理单元和 片段着色器 中的纹理采样器 绑定 location glUniform1i(m_ySamplerLocation, 0);
     * 这里的 0 对应  GL_TEXTURE0 中的 0
     *
     * 采样器的location 获取  m_ySamplerLocation = glGetUniformLocation (program, "y_texture" );
     */
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,ytexture);
    glUniform1i(m_ySamplerLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,uvtexture);
    glUniform1i(m_uvSamplerLocation, 1);

}

