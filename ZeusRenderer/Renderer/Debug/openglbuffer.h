#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "OpenGLCommon.h"
#include <QOpenGLBuffer>
/*******************************************************************************
 * OpenGLBuffer类，继承自QOpenGLBuffer，我们加入了错误检查和性能检测
 ******************************************************************************/
// Register to check OpenGLBuffer
class OpenGLBufferChecked : public QOpenGLBuffer
{
public:
    GL_CHECK(QOpenGLBuffer,bind);
    GL_CHECK(QOpenGLBuffer,create);
    GL_CHECK(QOpenGLBuffer,unmap);
    GL_CHECK(QOpenGLBuffer,read,int,void*,int);
};

// Register to profile OpenGLBuffer
class OpenGLBufferProfiled : public OpenGLBufferChecked
{
public:
    GL_PROFILE(OpenGLBufferChecked,allocate,const void *,int);
    GL_PROFILE(OpenGLBufferChecked,allocate,int);
    GL_PROFILE(OpenGLBufferChecked,bind);
    GL_PROFILE(OpenGLBufferChecked,create);
    GL_PROFILE(OpenGLBufferChecked,destroy);
    GL_PROFILE(OpenGLBufferChecked,map,QOpenGLBuffer::Access);
    GL_PROFILE(OpenGLBufferChecked,mapRange,int,int,QOpenGLBuffer::RangeAccessFlags);
    GL_PROFILE(OpenGLBufferChecked,read,int,void *,int);
    GL_PROFILE(OpenGLBufferChecked,release);
    GL_PROFILE(OpenGLBufferChecked,setUsagePattern,QOpenGLBuffer::UsagePattern);
    GL_PROFILE(OpenGLBufferChecked,unmap);
    GL_PROFILE(OpenGLBufferChecked,write,int,const void *,int);
};

// Final class
class OpenGLBuffer : public OpenGLBufferProfiled
{
    // Intentionally Empty
};

#endif // OPENGLBUFFER_H
