#ifndef ANIMATIONENTITY_H
#define ANIMATIONENTITY_H
#include "Entity.h"
#include "../Loader/AnimationLoader.h"
/*
 * AnimationEntity.h
 *
 *  Created on: 2018-5-28
 *      Author: a
 */
class AnimationEntity : public Entity
{
public:
    // rotation
    QVector3D axis;
    float angle;
    AnimationLoader* animation;

    AnimationEntity(const QString &dwcall,AnimationLoader* anim);
    AnimationEntity(const AnimationEntity& rhs);
    void animate(int animIndex,long startTime,long currentTime);
    virtual ~AnimationEntity();
    virtual AnimationEntity* clone();
    virtual void setPosition(float x, float y, float z);
    virtual void setRotation(float angle, float ax, float ay, float az);
    virtual void setSize(float sx, float sy, float sz);

private:
    virtual void vertexTransform();
    virtual void normalTransform();
};

#endif // ANIMATIONENTITY_H
