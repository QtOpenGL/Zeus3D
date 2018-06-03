#ifndef CONTEXT_H
#define CONTEXT_H
#include <QOpenGLFunctions_4_3_Core>
#include "Debug/openglfunctions_3_3_core.h"
/*
 * 函数环境
 */
namespace GlobalContext{

extern QOpenGLFunctions_4_3_Core* contextFunc;

//void initialize(QOpenGLContext *context);
}

#endif // CONTEXT_H
