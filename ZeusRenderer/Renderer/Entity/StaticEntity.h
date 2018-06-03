#ifndef STATICENTITY_H
#define STATICENTITY_H
#include "Entity.h"
#include "../Mesh/Batch.h"

class StaticEntity : public Entity
{
public:
    QVector3D axis;
    float angle;

    StaticEntity(const QString &dwcall, Mesh* mesh);
    StaticEntity(Mesh* mesh, Mesh* meshMid, Mesh* meshLow);
    StaticEntity(const StaticEntity& rhs);
    virtual ~StaticEntity();
    virtual StaticEntity* clone();

    virtual void vertexTransform();
    virtual void normalTransform();
    virtual void setPosition(float x,float y,float z);
    virtual void setRotation(float angle, float ax, float ay, float az);
    virtual void setSize(float sx, float sy, float sz);
};

#endif // STATICENTITY_H
