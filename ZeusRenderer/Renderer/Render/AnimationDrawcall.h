#ifndef ANIMATIONDRAWCALL_H
#define ANIMATIONDRAWCALL_H
#include "DrawCall.h"
/*
 * AnimationDrawcall.h
 *
 *  Created on: 2018-5-28
 *      Author: Zeus
 */
class AnimationLoader;
class AnimationBatch;
class AnimationDrawcall : public DrawCall
{
public:
    AnimationDrawcall();
    AnimationDrawcall(AnimationLoader* anim);
    virtual ~AnimationDrawcall();
    virtual void createSimple();
    virtual void releaseSimple();
    virtual void draw(ShaderProgram* shader,int pass);

private:
    int vertexCount, indexCount;
    AnimationBatch* animData;
};

#endif // ANIMATIONDRAWCALL_H
