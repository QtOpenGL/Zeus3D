#ifndef OPENGLFUNCTIONS_3_3_CORE_H
#define OPENGLFUNCTIONS_3_3_CORE_H

#include "OpenGLCommon.h"
#include <QOpenGLFunctions_3_3_Core>

#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)

class OpenGLFunctions_3_3_Core : public QOpenGLFunctions_3_3_Core
{
public:
  inline OpenGLFunctions_3_3_Core() : QOpenGLFunctions_3_3_Core() {}
  inline ~OpenGLFunctions_3_3_Core() {}

  GL_PROFILE(QOpenGLFunctions_3_3_Core,glViewport, GLint, GLint, GLsizei, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDepthRange, GLdouble, GLdouble);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsEnabled, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetTexLevelParameteriv, GLenum, GLint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetTexLevelParameterfv, GLenum, GLint, GLenum, GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetTexParameteriv, GLenum, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetTexParameterfv, GLenum, GLenum, GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetTexImage, GLenum, GLint, GLenum, GLenum, GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetString, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetIntegerv, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetFloatv, GLenum, GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetError);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetDoublev, GLenum, GLdouble *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetBooleanv, GLenum, GLboolean *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glReadPixels, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glReadBuffer, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPixelStorei, GLenum, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPixelStoref, GLenum, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDepthFunc, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glStencilOp, GLenum, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glStencilFunc, GLenum, GLint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glLogicOp, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBlendFunc, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFlush);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFinish);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glEnable, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDisable, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDepthMask, GLboolean);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glColorMask, GLboolean, GLboolean, GLboolean, GLboolean);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glStencilMask, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClearDepth, GLdouble);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClearStencil, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClearColor, GLfloat, GLfloat, GLfloat, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClear, GLbitfield);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawBuffer, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexImage2D, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexImage1D, GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexParameteriv, GLenum, GLenum, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexParameteri, GLenum, GLenum, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexParameterfv, GLenum, GLenum, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexParameterf, GLenum, GLenum, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glScissor, GLint, GLint, GLsizei, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPolygonMode, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPointSize, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glLineWidth, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glHint, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFrontFace, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCullFace, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIndexubv, const GLubyte *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIndexub, GLubyte);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsTexture, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGenTextures, GLsizei, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteTextures, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindTexture, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexSubImage2D, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexSubImage1D, GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCopyTexSubImage2D, GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCopyTexSubImage1D, GLenum, GLint, GLint, GLint, GLint, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCopyTexImage2D, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCopyTexImage1D, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPolygonOffset, GLfloat, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetPointerv, GLenum, GLvoid* *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawElements, GLenum, GLsizei, GLenum, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawArrays, GLenum, GLint, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCopyTexSubImage3D, GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexSubImage3D, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexImage3D, GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawRangeElements, GLenum, GLuint, GLuint, GLsizei, GLenum, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBlendEquation, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBlendColor, GLfloat, GLfloat, GLfloat, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetCompressedTexImage, GLenum, GLint, GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCompressedTexSubImage1D, GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCompressedTexSubImage2D, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCompressedTexSubImage3D, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCompressedTexImage1D, GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCompressedTexImage2D, GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCompressedTexImage3D, GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSampleCoverage, GLfloat, GLboolean);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glActiveTexture, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPointParameteriv, GLenum, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPointParameteri, GLenum, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPointParameterfv, GLenum, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPointParameterf, GLenum, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiDrawElements, GLenum, const GLsizei *, GLenum, const GLvoid* const *, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiDrawArrays, GLenum, const GLint *, const GLsizei *, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBlendFuncSeparate, GLenum, GLenum, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetBufferPointerv, GLenum, GLenum, GLvoid* *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetBufferParameteriv, GLenum, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUnmapBuffer, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMapBuffer, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetBufferSubData, GLenum, GLintptr, GLsizeiptr, GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBufferSubData, GLenum, GLintptr, GLsizeiptr, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBufferData, GLenum, GLsizeiptr, const GLvoid *, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsBuffer, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGenBuffers, GLsizei, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteBuffers, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindBuffer, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetQueryObjectuiv, GLuint, GLenum, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetQueryObjectiv, GLuint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetQueryiv, GLenum, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glEndQuery, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBeginQuery, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsQuery, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteQueries, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGenQueries, GLsizei, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribPointer, GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glValidateProgram, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix4fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix3fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix2fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform4iv, GLint, GLsizei, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform3iv, GLint, GLsizei, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform2iv, GLint, GLsizei, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform1iv, GLint, GLsizei, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform4fv, GLint, GLsizei, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform3fv, GLint, GLsizei, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform2fv, GLint, GLsizei, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform1fv, GLint, GLsizei, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform4i, GLint, GLint, GLint, GLint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform3i, GLint, GLint, GLint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform2i, GLint, GLint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform1i, GLint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform4f, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform3f, GLint, GLfloat, GLfloat, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform2f, GLint, GLfloat, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform1f, GLint, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUseProgram, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glShaderSource, GLuint, GLsizei, const GLchar* const *, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glLinkProgram, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsShader, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsProgram, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetVertexAttribPointerv, GLuint, GLenum, GLvoid* *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetVertexAttribiv, GLuint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetVertexAttribfv, GLuint, GLenum, GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetVertexAttribdv, GLuint, GLenum, GLdouble *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetUniformiv, GLuint, GLint, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetUniformfv, GLuint, GLint, GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetUniformLocation, GLuint, const GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetShaderSource, GLuint, GLsizei, GLsizei *, GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetShaderInfoLog, GLuint, GLsizei, GLsizei *, GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetShaderiv, GLuint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetProgramInfoLog, GLuint, GLsizei, GLsizei *, GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetProgramiv, GLuint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetAttribLocation, GLuint, const GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetAttachedShaders, GLuint, GLsizei, GLsizei *, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetActiveUniform, GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetActiveAttrib, GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glEnableVertexAttribArray, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDisableVertexAttribArray, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDetachShader, GLuint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteShader, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteProgram, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCreateShader, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCreateProgram);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCompileShader, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindAttribLocation, GLuint, GLuint, const GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glAttachShader, GLuint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glStencilMaskSeparate, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glStencilFuncSeparate, GLenum, GLenum, GLint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glStencilOpSeparate, GLenum, GLenum, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawBuffers, GLsizei, const GLenum *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBlendEquationSeparate, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix4x3fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix3x4fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix4x2fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix2x4fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix3x2fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformMatrix2x3fv, GLint, GLsizei, GLboolean, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsVertexArray, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGenVertexArrays, GLsizei, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteVertexArrays, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindVertexArray, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFlushMappedBufferRange, GLenum, GLintptr, GLsizeiptr);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMapBufferRange, GLenum, GLintptr, GLsizeiptr, GLbitfield);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFramebufferTextureLayer, GLenum, GLenum, GLuint, GLint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glRenderbufferStorageMultisample, GLenum, GLsizei, GLenum, GLsizei, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBlitFramebuffer, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGenerateMipmap, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetFramebufferAttachmentParameteriv, GLenum, GLenum, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFramebufferRenderbuffer, GLenum, GLenum, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFramebufferTexture3D, GLenum, GLenum, GLenum, GLuint, GLint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFramebufferTexture2D, GLenum, GLenum, GLenum, GLuint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFramebufferTexture1D, GLenum, GLenum, GLenum, GLuint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCheckFramebufferStatus, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGenFramebuffers, GLsizei, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteFramebuffers, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindFramebuffer, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsFramebuffer, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetRenderbufferParameteriv, GLenum, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glRenderbufferStorage, GLenum, GLenum, GLsizei, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGenRenderbuffers, GLsizei, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteRenderbuffers, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindRenderbuffer, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsRenderbuffer, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetStringi, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClearBufferfi, GLenum, GLint, GLfloat, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClearBufferfv, GLenum, GLint, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClearBufferuiv, GLenum, GLint, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClearBufferiv, GLenum, GLint, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetTexParameterIuiv, GLenum, GLenum, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetTexParameterIiv, GLenum, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexParameterIuiv, GLenum, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexParameterIiv, GLenum, GLenum, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform4uiv, GLint, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform3uiv, GLint, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform2uiv, GLint, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform1uiv, GLint, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform4ui, GLint, GLuint, GLuint, GLuint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform3ui, GLint, GLuint, GLuint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform2ui, GLint, GLuint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniform1ui, GLint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetFragDataLocation, GLuint, const GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindFragDataLocation, GLuint, GLuint, const GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetUniformuiv, GLuint, GLint, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetVertexAttribIuiv, GLuint, GLenum, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetVertexAttribIiv, GLuint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribIPointer, GLuint, GLint, GLenum, GLsizei, const GLvoid *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glEndConditionalRender);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBeginConditionalRender, GLuint, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClampColor, GLenum, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetTransformFeedbackVarying, GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTransformFeedbackVaryings, GLuint, GLsizei, const GLchar* const *, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindBufferBase, GLenum, GLuint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindBufferRange, GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glEndTransformFeedback);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBeginTransformFeedback, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsEnabledi, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDisablei, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glEnablei, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetIntegeri_v, GLenum, GLuint, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetBooleani_v, GLenum, GLuint, GLboolean *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glColorMaski, GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glCopyBufferSubData, GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glUniformBlockBinding, GLuint, GLuint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetActiveUniformBlockName, GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetActiveUniformBlockiv, GLuint, GLuint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetUniformBlockIndex, GLuint, const GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetActiveUniformName, GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetActiveUniformsiv, GLuint, GLsizei, const GLuint *, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetUniformIndices, GLuint, GLsizei, const GLchar* const *, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glPrimitiveRestartIndex, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexBuffer, GLenum, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawElementsInstanced, GLenum, GLsizei, GLenum, const GLvoid *, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawArraysInstanced, GLenum, GLint, GLsizei, GLsizei);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSampleMaski, GLuint, GLbitfield);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetMultisamplefv, GLenum, GLuint, GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexImage3DMultisample, GLenum, GLsizei, GLint, GLsizei, GLsizei, GLsizei, GLboolean);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexImage2DMultisample, GLenum, GLsizei, GLint, GLsizei, GLsizei, GLboolean);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetSynciv, GLsync, GLenum, GLsizei, GLsizei *, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetInteger64v, GLenum, GLint64 *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glWaitSync, GLsync, GLbitfield, GLuint64);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glClientWaitSync, GLsync, GLbitfield, GLuint64);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteSync, GLsync);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsSync, GLsync);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFenceSync, GLenum, GLbitfield);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glProvokingVertex, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiDrawElementsBaseVertex, GLenum, const GLsizei *, GLenum, const GLvoid* const *, GLsizei, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawElementsInstancedBaseVertex, GLenum, GLsizei, GLenum, const GLvoid *, GLsizei, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawRangeElementsBaseVertex, GLenum, GLuint, GLuint, GLsizei, GLenum, const GLvoid *, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDrawElementsBaseVertex, GLenum, GLsizei, GLenum, const GLvoid *, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glFramebufferTexture, GLenum, GLenum, GLuint, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetBufferParameteri64v, GLenum, GLenum, GLint64 *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetInteger64i_v, GLenum, GLuint, GLint64 *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribP4uiv, GLuint, GLenum, GLboolean, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribP4ui, GLuint, GLenum, GLboolean, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribP3uiv, GLuint, GLenum, GLboolean, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribP3ui, GLuint, GLenum, GLboolean, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribP2uiv, GLuint, GLenum, GLboolean, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribP2ui, GLuint, GLenum, GLboolean, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribP1uiv, GLuint, GLenum, GLboolean, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribP1ui, GLuint, GLenum, GLboolean, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSecondaryColorP3uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSecondaryColorP3ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glColorP4uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glColorP4ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glColorP3uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glColorP3ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glNormalP3uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glNormalP3ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiTexCoordP4uiv, GLenum, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiTexCoordP4ui, GLenum, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiTexCoordP3uiv, GLenum, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiTexCoordP3ui, GLenum, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiTexCoordP2uiv, GLenum, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiTexCoordP2ui, GLenum, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiTexCoordP1uiv, GLenum, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glMultiTexCoordP1ui, GLenum, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexCoordP4uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexCoordP4ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexCoordP3uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexCoordP3ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexCoordP2uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexCoordP2ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexCoordP1uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glTexCoordP1ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexP4uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexP4ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexP3uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexP3ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexP2uiv, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexP2ui, GLenum, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetQueryObjectui64v, GLuint, GLenum, GLuint64 *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetQueryObjecti64v, GLuint, GLenum, GLint64 *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glQueryCounter, GLuint, GLenum);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetSamplerParameterIuiv, GLuint, GLenum, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetSamplerParameterfv, GLuint, GLenum, GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetSamplerParameterIiv, GLuint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetSamplerParameteriv, GLuint, GLenum, GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSamplerParameterIuiv, GLuint, GLenum, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSamplerParameterIiv, GLuint, GLenum, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSamplerParameterfv, GLuint, GLenum, const GLfloat *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSamplerParameterf, GLuint, GLenum, GLfloat);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSamplerParameteriv, GLuint, GLenum, const GLint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glSamplerParameteri, GLuint, GLenum, GLint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindSampler, GLuint, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glIsSampler, GLuint);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glDeleteSamplers, GLsizei, const GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGenSamplers, GLsizei, GLuint *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glGetFragDataIndex, GLuint, const GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glBindFragDataLocationIndexed, GLuint, GLuint, GLuint, const GLchar *);
  GL_PROFILE(QOpenGLFunctions_3_3_Core,glVertexAttribDivisor, GLuint, GLuint);


};

#endif // !QT_NO_OPENGL && !QT_OPENGL_ES_2

#endif // OPENGLFUNCTIONS_3_3_CORE_H

