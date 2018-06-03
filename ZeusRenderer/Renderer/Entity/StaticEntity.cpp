#include "StaticEntity.h"
#include "../Render/StaticDrawcall.h"

StaticEntity::StaticEntity(const QString &dwcall, Mesh *mesh)
    :Entity()
{
    type = STATIC_ENTITY;
    angle = 0;
    axis = QVector3D(0,1,0);
    drawcall = dwcall;
    this->mesh = mesh;
}


StaticEntity::StaticEntity(Mesh *mesh, Mesh *meshMid, Mesh *meshLow)
    :Entity()
{
    type = STATIC_ENTITY;
    angle = 0;
    axis = QVector3D(0,1,0);
    this->mesh = mesh;
    this->meshMid = meshMid;
    this->meshLow = meshLow;
}

StaticEntity::StaticEntity(const StaticEntity &rhs)
    :Entity()
{
    type = STATIC_ENTITY;
    mesh = rhs.mesh;
    meshMid = rhs.meshMid;
    meshLow = rhs.meshLow;
    material = rhs.material;
    // clone a new one instead of just assignment
    if (rhs.bounding)
        bounding = rhs.bounding->clone();
    else
        bounding = nullptr;
    position = rhs.position;
    angle = rhs.angle;
    axis = rhs.axis;
    size = rhs.size;
}

StaticEntity::~StaticEntity()
{
}

StaticEntity *StaticEntity::clone()
{
    // clone a new one
    return new StaticEntity(*this);
}

void StaticEntity::vertexTransform()
{
    // transform the entity.
    // the order of these transformations is vital.
    modelMatrix.setToIdentity();
    modelMatrix.translate(position);
    modelMatrix.rotate(angle,axis);
    modelMatrix.scale(size);
}

void StaticEntity::normalTransform()
{
    // There is a truth: scaling would influent the normal most.
    if(size.x() == size.y() && size.y() == size.z()) {
        // If it's a uniform scaling, we don't need to inverse it and then transpose it.
        normalMatrix = modelMatrix;
        return;
    }
    normalMatrix = modelMatrix.inverted().transposed();
}

void StaticEntity::setPosition(float x, float y, float z)
{
    position = QVector3D(x,y,z);
    updateLocalMatrices();
}

void StaticEntity::setRotation(float angle, float ax, float ay, float az)
{
    this->angle = angle;
    this->axis = QVector3D(ax,ay,az);
    updateLocalMatrices();
}

void StaticEntity::setSize(float sx, float sy, float sz)
{
    size = QVector3D(sx,sy,sz);
    updateLocalMatrices();
}
