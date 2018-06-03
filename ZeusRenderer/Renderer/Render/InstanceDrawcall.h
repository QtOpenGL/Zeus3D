#ifndef INSTANCEDRAWCALL_H
#define INSTANCEDRAWCALL_H
#include "DrawCall.h"
/*
 * InstanceDrawcall.h
 *
 *  Created on: 2018-5-26
 *      Author: Zeus
 */
class InstanceBatch;
class InstanceDrawcall : public DrawCall
{
public:
    bool isSimple;
    int objectToDraw;
    InstanceBatch* instanceBatch;

    InstanceDrawcall(InstanceBatch* instance, bool simple);
    virtual ~InstanceDrawcall();
    virtual void createSimple();
    virtual void releaseSimple();
    virtual void draw(ShaderProgram* shader,int pass);
    void updateMatrices(const float* modelMatrices);

private:
    int vertexCount,indexCount;
    bool indexed;
};

#endif // INSTANCEDRAWCALL_H
