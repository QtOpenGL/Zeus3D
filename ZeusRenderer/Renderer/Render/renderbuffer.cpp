#include "RenderBuffer.h"
#include "Renderer/Context.h"
#include <QDebug>

/*******************************************
 * RenderData
 *******************************************/

RenderData::RenderData(uint loc,GLenum type,uint count,uint channel,uint row,
                        const OpenGLBuffer &vbo,bool normalize,GLenum draw,int divisor, void *data
                       )
{
    switch(type){
    case GL_FLOAT:
        bitSize = sizeof(GLfloat);break;
    case GL_INT:
        bitSize = sizeof(GLint);break;
    case GL_UNSIGNED_INT:
        bitSize = sizeof(GLuint);break;
    case GL_UNSIGNED_SHORT:
        bitSize = sizeof(GLushort);break;
    case GL_UNSIGNED_BYTE:
        bitSize = sizeof(GLubyte);
    }
    channelCount = channel;
    rowCount = row;
    dataSize = count * channelCount * rowCount;
    bufferid = vbo;
    drawType = draw;
    streamData = data;

    //get current ogl context
    GlobalContext::contextFunc->glBindBuffer(GL_ARRAY_BUFFER, bufferid.bufferId());
    GlobalContext::contextFunc->glBufferData(GL_ARRAY_BUFFER, dataSize * bitSize, streamData, drawType);
    for (uint i = 0; i < row; i++) {
        uint attrloc = loc + i;
        GlobalContext::contextFunc->glVertexAttribPointer(attrloc, channel, type, normalize,
                                   bitSize * row * channel, (void*)(bitSize * i * channel));
        if (divisor >= 0)
            GlobalContext::contextFunc->glVertexAttribDivisor(attrloc, divisor);
        GlobalContext::contextFunc->glEnableVertexAttribArray(attrloc);
    }
    bufferid.release();
}

RenderData::RenderData(GLenum type, uint size, const OpenGLBuffer &vbo, GLenum draw, void *data)
{
    switch (type) {
    case GL_UNSIGNED_INT:
        bitSize = sizeof(GLuint);break;
    case GL_UNSIGNED_SHORT:
        bitSize = sizeof(GLushort);break;
    case GL_UNSIGNED_BYTE:
        bitSize = sizeof(GLubyte);break;
    }
    dataSize = size;
    bufferid = vbo;
    drawType = draw;
    streamData = data;
    GlobalContext::contextFunc->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferid.bufferId());
    GlobalContext::contextFunc->glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize * bitSize, streamData, drawType);
}

void RenderData::updateAttrBuf(uint count, void *data, GLenum draw)
{
    dataSize = count * channelCount * rowCount;
    drawType = draw;
    streamData = data;
    GlobalContext::contextFunc->glBindBuffer(GL_ARRAY_BUFFER, bufferid.bufferId());
    GlobalContext::contextFunc->glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize * bitSize, streamData);
}

/*******************************************
 * RenderBuffer
 *******************************************/

RenderBuffer::RenderBuffer(uint size)
{
    //bind size buffer vbos
    bufferSize = size;
    vbos.resize(bufferSize);
    streamDatas.resize(bufferSize);
    for (uint i = 0; i < bufferSize; i++)
        pushData(i, nullptr);
    vao.create();
    vao.bind();
    for(auto &vbo:vbos){
        vbo.create();
    }
}

void RenderBuffer::release()
{
    GlobalContext::contextFunc->glBindVertexArray(0);
    GlobalContext::contextFunc->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GlobalContext::contextFunc->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

RenderBuffer::~RenderBuffer()
{
    for(auto &vbo:vbos)vbo.destroy();
    vao.destroy();
    for(auto &elem:streamDatas){
        if(elem){
            delete elem;
        }
    }
}
