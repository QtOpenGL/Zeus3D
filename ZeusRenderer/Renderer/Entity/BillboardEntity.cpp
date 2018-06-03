#include "BillboardEntity.h"

BillboardEntity::BillboardEntity(Mesh *mesh)
    :Entity()
{
    type = BILLBOARD_ENTITY;
    this->mesh = mesh;
}

BillboardEntity::BillboardEntity(const BillboardEntity &rhs)
    :Entity()
{
    type = BILLBOARD_ENTITY;
    mesh = rhs.mesh;
    material = rhs.material;
    if(rhs.bounding)
        bounding = rhs.bounding->clone();
    else
        bounding = nullptr;
    position = rhs.position;
    size = rhs.size;
}

BillboardEntity::~BillboardEntity() {}

BillboardEntity *BillboardEntity::clone()
{
    return new BillboardEntity(*this);
}

void BillboardEntity::caculateLocalAABB(bool looseWidth, bool looseAll)
{
    Q_UNUSED(looseWidth);
    Entity::caculateLocalAABB(true, looseAll); // Always looseWidth
}

void BillboardEntity::vertexTransform()
{
    modelMatrix.setToIdentity();
    modelMatrix.translate(position);
    modelMatrix.scale(size);
}

// no normal
void BillboardEntity::normalTransform() {}

void BillboardEntity::setPosition(float x, float y, float z)
{
    position = QVector3D(x,y,z);
    updateLocalMatrices();
}

void BillboardEntity::setSize(float sx, float sy, float sz)
{
    size = QVector3D(sx,sy,sz);
    updateLocalMatrices();
}
