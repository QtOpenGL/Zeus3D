#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "Frustum.h"
/*
 * bounding box abstract interface class
 */

class BoundingBox
{
public:
    QVector3D position;

    BoundingBox();
    BoundingBox(const BoundingBox& rhs);
    virtual ~BoundingBox();

    virtual BoundingBox* clone() = 0;
    virtual bool checkWithFrustum(Frustum* frustum, bool isMain, bool simpleCheck
                                  , bool forceSimple = false) = 0;
    virtual void update(const QVector3D& pos) = 0;
    virtual void merge(const std::vector<BoundingBox*>& others) = 0;
};

#endif // BOUNDINGBOX_H
