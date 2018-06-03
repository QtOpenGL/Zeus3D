#ifndef FRAMETEXTURE2D_H
#define FRAMETEXTURE2D_H
#include "../Context.h"
/*
 * the frame buffer texture
 */
class FrameTexture2D
{
public:
    enum FrameTextureType{TEXTURE_TYPE_COLOR = 1,TEXTURE_TYPE_DEPTH = 2};
    enum TexturePrecision{LOW_PRE = 0,HIGH_PRE = 1,TOP_PRE = 2};

    // properties
    float width,height;
    int type, precision;
    GLuint id;

    FrameTexture2D(float wi,float he,int ty,int prec,int c);
    ~FrameTexture2D();
};

#endif // FRAMETEXTURE2D_H
