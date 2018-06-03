#include "FrameTexture2D.h"

FrameTexture2D::FrameTexture2D(float wi, float he, int ty, int prec, int component)
    :width(wi),height(he),type(ty),precision(prec)
{
    // set some common attributes
    GlobalContext::contextFunc->glGenTextures(1,&id);
    GlobalContext::contextFunc->glActiveTexture(GL_TEXTURE0);
    GlobalContext::contextFunc->glBindTexture(GL_TEXTURE_2D,id);

    // set filter and wrap format
    GLint filterParam = precision == HIGH_PRE ? GL_LINEAR : GL_NEAREST;
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParam);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterParam);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
    float borderColor[4]={1,1,1,1};
    GlobalContext::contextFunc->glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,borderColor);

    // set texture format according the precision
    GLint preDepth = precision == HIGH_PRE ? GL_DEPTH_COMPONENT32F : GL_DEPTH_COMPONENT24;
    GLint preColor = precision == HIGH_PRE ? GL_RGBA16F : GL_RGBA8;
    GLint numFormat = GL_UNSIGNED_BYTE;
    if(precision == TOP_PRE){
        preColor = GL_RGBA32F;
        numFormat = GL_FLOAT;
    }
    GLenum format = GL_RGBA;
    if (component == 3) {
        format = GL_RGB;
        preColor = precision == HIGH_PRE ? GL_RGB16F : GL_RGB8;
    }

    // set internal format
    switch(type) {
    case TEXTURE_TYPE_COLOR:
        GlobalContext::contextFunc->glTexImage2D(GL_TEXTURE_2D, 0, preColor, width,
                                                 height, 0, format, numFormat, 0);
        break;
    case TEXTURE_TYPE_DEPTH:
        GlobalContext::contextFunc->glTexImage2D(GL_TEXTURE_2D, 0, preDepth, width,
                                                 height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        break;
    }
    GlobalContext::contextFunc->glBindTexture(GL_TEXTURE_2D,0);
}

FrameTexture2D::~FrameTexture2D()
{
    GlobalContext::contextFunc->glDeleteTextures(1,&id);
}
