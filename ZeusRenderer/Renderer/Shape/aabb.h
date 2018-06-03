#ifndef AABB_H
#define AABB_H
#include "BoundingBox.h"
/*
 * AABB bounding box
 */

class AABB : public BoundingBox
{
public:
    QVector3D size;
    QVector3D minVertex, maxVertex;

    // Contructor / Destructor
    AABB(const QVector3D& min,const QVector3D& max);
    AABB(const QVector3D& pos,float sx,float sy,float sz);
    AABB(const AABB& rhs);
    virtual ~AABB();

    virtual AABB* clone();
    virtual bool checkWithFrustum(Frustum* frustum, bool isMain, bool simpleCheck
                                  , bool forceSimple = false);

    // Update AABB bounding box
    void update(const QVector3D& newMinVertex,const QVector3D& newMaxVertex);
    void update(float sx, float sy, float sz);
    virtual void update(const QVector3D& pos);
    virtual void merge(const std::vector<BoundingBox*>& others);

private:
    QVector3D vertices[8];// 8 vertices of bounding box
    bool vertexInsideFrustum(const QVector3D& vertex,const Frustum* frustum);
    bool intersectsWithRay(const QVector3D& origin,const QVector3D& dir,float maxDistance);
    bool cameraVertexInside(const QVector3D& vertex);
};

#endif // AABB_H
