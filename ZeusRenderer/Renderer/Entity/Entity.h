#ifndef ENTITY_H
#define ENTITY_H
#include "../Mesh/Mesh.h"
#include "../Shape/AABB.h"
#include "../Mesh/Batch.h"
#include "../Shape/Frustum.h"
#include "../Render/DrawCall.h"
#include "../Material/MaterialManager.h"

#include <QMatrix4x4>
/*
 * Entity.h
 *
 *  Created on: 2018-5-24
 *      Author: Zeus
 */

class Entity
{
public:
    enum EntityType{STATIC_ENTITY = 0,BILLBOARD_ENTITY = 1,ANIMATION_ENTITY = 2};
    EntityType type;
    // Entity basic attribute
    QVector3D position;
    QVector3D size;
    QString drawcall;

    // Each entity has it's own mesh
    Mesh* mesh;
    Mesh* meshMid;
    Mesh* meshLow;

    // Material index
    int material;
    // Transform matrix
    QMatrix4x4 modelMatrix,normalMatrix;

    // Bounding box
    BoundingBox* bounding;
    QVector3D localBoundPosition;

    // Constructor/Destructor
    Entity();
    Entity(const Entity& rhs);
    virtual ~Entity();
    virtual Entity* clone() = 0;

    // Calculate it's bounding box
    virtual void caculateLocalAABB(bool looseWidth,bool looseAll);
    virtual void vertexTransform() = 0;
    virtual void normalTransform() = 0;

    // update local matrix
    void updateLocalMatrices();
    // Bind material
    void bindMaterial(int mid);
    // Visiable detection
    bool checkInFrustum(Frustum* frustum);

    // Transform as needed
    virtual void setPosition(float x, float y, float z) = 0;
    virtual void setRotation(float angle, float ax, float ay, float az) = 0;
    virtual void setSize(float sx, float sy, float sz) = 0;
};

#endif // ENTITY_H
