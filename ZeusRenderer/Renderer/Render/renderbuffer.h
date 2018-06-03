#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include <vector>
#include "../Debug/OpenGLBuffer.h"
#include "../Debug/OpenGLVertexArrayObject.h"

/*
 * 显卡缓存类，管理各种缓存
 */

class RenderData{
public:
    uint bitSize;
    //数据数量、长度
    uint dataSize, channelCount, rowCount;
    OpenGLBuffer bufferid;
    GLenum drawType;
    void *streamData;

    RenderData(uint loc,GLenum type,uint count,uint channel,uint row,
               const OpenGLBuffer &vbo,bool normalize,GLenum draw,int divisor,void *data
               );
    RenderData(GLenum type, uint size, const OpenGLBuffer &vbo, GLenum draw, void* data);
    void updateAttrBuf(uint count, void* data, GLenum draw);
};

class RenderBuffer
{
public:    
    OpenGLVertexArrayObject vao;
    std::vector<OpenGLBuffer> vbos;
    std::vector<RenderData*> streamDatas;
    uint bufferSize;// quantity of vbo

    RenderBuffer(uint size);

    ~RenderBuffer();

    void pushData(uint index, RenderData *data);

    void use();//like bind

    void release();// like unbind
};

inline void RenderBuffer::pushData(uint index, RenderData *data)
{
    streamDatas[index] = data;
}

inline void RenderBuffer::use()
{
    vao.bind();
}

#endif // RENDERBUFFER_H
