#ifndef OPENGLVERTEXARRAYOBJECT_H
#define OPENGLVERTEXARRAYOBJECT_H

#include "OpenGLCommon.h"
#include <QOpenGLVertexArrayObject>
/*******************************************************************************
 * OpenGLVertexArrayObjectChecked，继承自QOpenGLVertexArrayObject,套上错误检查宏定义
 * 和性能监测宏定义
 ******************************************************************************/
// Register to check OpenGLVertexArrayObject
class OpenGLVertexArrayObjectChecked : public QOpenGLVertexArrayObject
{
public:
    explicit OpenGLVertexArrayObjectChecked(QObject *parent = 0) : QOpenGLVertexArrayObject(parent) {}
    GL_CHECK(QOpenGLVertexArrayObject,create);
};

// Register to profile OpenGLVertexArrayObject
class OpenGLVertexArrayObjectProfiled : public OpenGLVertexArrayObjectChecked
{
public:
    explicit OpenGLVertexArrayObjectProfiled(QObject *parent = 0) : OpenGLVertexArrayObjectChecked(parent) {}
    GL_PROFILE(OpenGLVertexArrayObjectChecked,bind);
    GL_PROFILE(OpenGLVertexArrayObjectChecked,create);
    GL_PROFILE(OpenGLVertexArrayObjectChecked,destroy);
    GL_PROFILE(OpenGLVertexArrayObjectChecked,isCreated);
    GL_PROFILE(OpenGLVertexArrayObjectChecked,objectId);
    GL_PROFILE(OpenGLVertexArrayObjectChecked,release);
};

// Final class
class OpenGLVertexArrayObject : public OpenGLVertexArrayObjectProfiled
{
public:
    explicit OpenGLVertexArrayObject(QObject *parent = 0) : OpenGLVertexArrayObjectProfiled(parent) {}
};

#endif // OPENGLVERTEXARRAYOBJECT_H