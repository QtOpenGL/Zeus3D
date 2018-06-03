#include "Shadow.h"

Shadow::Shadow(int width, int height)
{
    framebuffer = new FrameBuffer(width,height,FrameTexture2D::LOW_PRE,3);
    framebuffer->attachDepthBuffer(FrameTexture2D::HIGH_PRE);
    // set deafult configure
    this->setOrthoProjection(-500,500,-500,500,1.0f,900.0f);
}

Shadow::~Shadow()
{
    if(framebuffer)delete framebuffer;
    framebuffer = nullptr;
}

void Shadow::setOrthoProjection(const float &left, const float &right,
                                const float &bottom, const float &top,
                                const float &nearPlane, const float &farPlane)
{
    this->leftP = left;
    this->rightP = right;
    this->bottomP = bottom;
    this->topP = top;
    this->nearP = nearPlane;
    this->farP = farPlane;
}

void Shadow::update(const QVector3D &pos,const QVector3D &dir)
{
    QMatrix4x4 lightProjection;
    lightProjection.setToIdentity();
    lightProjection.ortho(leftP,rightP,bottomP,topP,nearP,farP);
    QMatrix4x4 lightView;
    lightView.setToIdentity();
    lightView.lookAt(pos,pos+dir*(farP - nearP),QVector3D(0.0f,1.0f,0.0f));
    lightSpaceMatrix = lightProjection * lightView;
}

FrameBuffer *Shadow::getFramebuffer()
{
    return this->framebuffer;
}
