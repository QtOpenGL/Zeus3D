#ifndef SHADOW_H
#define SHADOW_H
#include "../Interactive/Camera3D.h"
#include "FrameBuffer.h"
/*
 * Shadow.h
 *
 * Describe: shadow for parallel lighting
 *
 * Created on: 2018-5-29
 *      Author: Zeus
 */
class Shadow
{
public:
    // ortho projection
    float leftP,rightP,bottomP,topP,nearP,farP;
    // cascading camera and matrix
    QMatrix4x4 lightSpaceMatrix;
    // parallel light direction
    QVector3D lightDir;

    Shadow(int width,int height);
    ~Shadow();

    void setOrthoProjection(const float &left,const float &right,
                            const float &bottom,const float &top,
                            const float &nearPlane,const float &farPlane);
    // update light direction
    void update(const QVector3D &pos,const QVector3D &dir);

    FrameBuffer* getFramebuffer();

private:
    FrameBuffer* framebuffer;
};

#endif // SHADOW_H
