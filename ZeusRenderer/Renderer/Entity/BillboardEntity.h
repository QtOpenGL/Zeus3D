#ifndef BILLBOARDENTITY_H
#define BILLBOARDENTITY_H
#include "Entity.h"
/*
 * BillboardEntity.h
 *
 *  Created on: 2018-5-28
 *      Author: Zeus
 */
class BillboardEntity : Entity
{
public:
    BillboardEntity(Mesh* mesh);
    BillboardEntity(const BillboardEntity& rhs);
    virtual ~BillboardEntity();
    virtual BillboardEntity* clone();
    virtual void caculateLocalAABB(bool looseWidth, bool looseAll);
    virtual void vertexTransform();
    virtual void normalTransform();
    virtual void setPosition(float x, float y, float z);
    virtual void setSize(float sx, float sy, float sz);
    // rotate automatically
    virtual void setRotation(float angle, float ax, float ay, float az) {}
};

#endif // BILLBOARDENTITY_H
