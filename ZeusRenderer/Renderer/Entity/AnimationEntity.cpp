#include "AnimationEntity.h"

AnimationEntity::AnimationEntity(const QString &dwcall, AnimationLoader *anim)
    :Entity()
{
    drawcall = dwcall;
    type = ANIMATION_ENTITY;
    animation = anim; // no mesh!
    axis = QVector3D(0,1,0);
    angle = 0;
}

AnimationEntity::AnimationEntity(const AnimationEntity &rhs)
    :Entity()
{
    type = ANIMATION_ENTITY;
    animation = rhs.animation;
    if(rhs.bounding)
        bounding = rhs.bounding->clone();
    else
        bounding = nullptr;
    position = rhs.position;
    angle = rhs.angle;
    axis = rhs.axis;
    size = rhs.size;
}

void AnimationEntity::animate(int animIndex, long startTime, long currentTime)
{
    animation->bonesTransform(animIndex, (float)(currentTime - startTime)*0.001f);
}

AnimationEntity::~AnimationEntity() {}

AnimationEntity *AnimationEntity::clone()
{
    return new AnimationEntity(*this);
}

void AnimationEntity::setPosition(float x, float y, float z)
{
    position = QVector3D(x,y,z);
    updateLocalMatrices();
}

void AnimationEntity::setRotation(float angle, float ax, float ay, float az)
{
    this->angle = angle;
    axis = QVector3D(ax,ay,az);
    updateLocalMatrices();
}

void AnimationEntity::setSize(float sx, float sy, float sz)
{
    size = QVector3D(sx,sy,sz);
    updateLocalMatrices();
}

void AnimationEntity::vertexTransform()
{
    modelMatrix.setToIdentity();
    modelMatrix.translate(position);
    modelMatrix.rotate(angle,axis);
    modelMatrix.scale(size);
}

void AnimationEntity::normalTransform()
{
    if(size.x() == size.y() && size.y() == size.z()) {
        normalMatrix = modelMatrix;
        return;
    }
    normalMatrix = modelMatrix.inverted().transposed();
}
