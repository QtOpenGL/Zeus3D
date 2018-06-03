#include "AABB.h"

AABB::AABB(const QVector3D &min, const QVector3D &max)
{
    minVertex = min;
    maxVertex = max;
    size = QVector3D(maxVertex.x()-minVertex.x(),
                     maxVertex.y()-minVertex.y(),
                     maxVertex.z()-minVertex.z());
    position = QVector3D(minVertex.x()+size.x()*0.5,
                         minVertex.y()+size.y()*0.5,
                         minVertex.z()+size.z()*0.5);

    vertices[0] = QVector3D(min.x(),min.y(),min.z());
    vertices[1] = QVector3D(max.x(),min.y(),min.z());
    vertices[2] = QVector3D(min.x(),max.y(),min.z());
    vertices[3] = QVector3D(max.x(),max.y(),min.z());
    vertices[4] = QVector3D(min.x(),min.y(),max.z());
    vertices[5] = QVector3D(max.x(),min.y(),max.z());
    vertices[6] = QVector3D(min.x(),max.y(),max.z());
    vertices[7] = QVector3D(max.x(),max.y(),max.z());
}

AABB::AABB(const QVector3D &pos, float sx, float sy, float sz)
{
    minVertex = QVector3D(pos.x()-sx*0.5,
                          pos.y()-sy*0.5,
                          pos.z()-sz*0.5);
    maxVertex = QVector3D(pos.x()+sx*0.5,
                          pos.y()+sy*0.5,
                          pos.z()+sz*0.5);
    size = QVector3D(sx,sy,sz);
    position = pos;

    vertices[0]=QVector3D(minVertex.x(),minVertex.y(),minVertex.z());
    vertices[1]=QVector3D(maxVertex.x(),minVertex.y(),minVertex.z());
    vertices[2]=QVector3D(minVertex.x(),maxVertex.y(),minVertex.z());
    vertices[3]=QVector3D(maxVertex.x(),maxVertex.y(),minVertex.z());
    vertices[4]=QVector3D(minVertex.x(),minVertex.y(),maxVertex.z());
    vertices[5]=QVector3D(maxVertex.x(),minVertex.y(),maxVertex.z());
    vertices[6]=QVector3D(minVertex.x(),maxVertex.y(),maxVertex.z());
    vertices[7]=QVector3D(maxVertex.x(),maxVertex.y(),maxVertex.z());
}

AABB::AABB(const AABB &rhs)
{
    minVertex = rhs.minVertex;
    maxVertex = rhs.maxVertex;
    size = rhs.size;
    position = rhs.position;
    for(int i=0;i<8;i++)
        vertices[i]=rhs.vertices[i];
}

AABB::~AABB(){}


void AABB::update(const QVector3D &newMinVertex, const QVector3D &newMaxVertex)
{
    // update bounding box
    minVertex = newMinVertex;
    maxVertex = newMaxVertex;
    size = QVector3D(maxVertex.x()-minVertex.x(),
                     maxVertex.y()-minVertex.y(),
                     maxVertex.z()-minVertex.z());
    position = QVector3D(minVertex.x()+size.x()*0.5,
                         minVertex.y()+size.y()*0.5,
                         minVertex.z()+size.z()*0.5);
    vertices[0] = QVector3D(newMinVertex.x(),newMinVertex.y(),newMinVertex.z());
    vertices[1] = QVector3D(newMaxVertex.x(),newMinVertex.y(),newMinVertex.z());
    vertices[2] = QVector3D(newMinVertex.x(),newMaxVertex.y(),newMinVertex.z());
    vertices[3] = QVector3D(newMaxVertex.x(),newMaxVertex.y(),newMinVertex.z());
    vertices[4] = QVector3D(newMinVertex.x(),newMinVertex.y(),newMaxVertex.z());
    vertices[5] = QVector3D(newMaxVertex.x(),newMinVertex.y(),newMaxVertex.z());
    vertices[6] = QVector3D(newMinVertex.x(),newMaxVertex.y(),newMaxVertex.z());
    vertices[7] = QVector3D(newMaxVertex.x(),newMaxVertex.y(),newMaxVertex.z());
}

void AABB::update(float sx, float sy, float sz)
{
    // update size
    update(QVector3D(position.x() - sx*0.5, position.y() - sy*0.5, position.z() - sz*0.5),
           QVector3D(position.x() + sx*0.5, position.y() + sy*0.5, position.z() + sz*0.5));
}

void AABB::update(const QVector3D &pos)
{
    // update position
    update(QVector3D(pos.x()-size.x()*0.5,pos.y()-size.y()*0.5,pos.z()-size.z()*0.5),
           QVector3D(pos.x()+size.x()*0.5,pos.y()+size.y()*0.5,pos.z()+size.z()*0.5));
}

AABB *AABB::clone()
{
    // clone a same one
    return new AABB(*this);
}

bool AABB::checkWithFrustum(Frustum *frustum, bool isMain, bool simpleCheck
                            , bool forceSimple)
{
    // check each vertex of bounding box
    for(int i = 0;i < 8;i++) {
        if(vertexInsideFrustum(vertices[i],frustum))
            return true;
    }

    // check frustum vertice
    for (int i = 0; i < 8; i++) {
        if (cameraVertexInside(frustum->worldVertex[i]))
            return true;
    }

    // check the border edges of frustum
    if (isMain) {
        for (int i = 0; i < 4; i++) {
            if (intersectsWithRay(frustum->worldVertex[i + 4],
                                  frustum->edgeDir[i], frustum->edgeLength[i]))
                return true;
        }
    }

    // more accurate detection
    if (!forceSimple && !simpleCheck) {
        if (frustum->intersectsWithRay(vertices[0], QVector3D(1, 0, 0), size.x()))
            return true;
        if (frustum->intersectsWithRay(vertices[0], QVector3D(0, 1, 0), size.y()))
            return true;
        if (frustum->intersectsWithRay(vertices[0], QVector3D(0, 0, 1), size.z()))
            return true;
        if (frustum->intersectsWithRay(vertices[7], QVector3D(-1, 0, 0), size.x()))
            return true;
        if (frustum->intersectsWithRay(vertices[7], QVector3D(0, -1, 0), size.y()))
            return true;
        if (frustum->intersectsWithRay(vertices[7], QVector3D(0, 0, -1), size.z()))
            return true;
        if (frustum->intersectsWithRay(vertices[4], QVector3D(1, 0, 0), size.x()))
            return true;
        if (frustum->intersectsWithRay(vertices[3], QVector3D(-1, 0, 0), size.x()))
            return true;
        if (frustum->intersectsWithRay(vertices[4], QVector3D(0, 1, 0), size.y()))
            return true;
        if (frustum->intersectsWithRay(vertices[1], QVector3D(0, 1, 0), size.y()))
            return true;
        if (frustum->intersectsWithRay(vertices[2], QVector3D(0, 0, 1), size.z()))
            return true;
        if (frustum->intersectsWithRay(vertices[1], QVector3D(0, 0, 1), size.z()))
            return true;
    }

    return false;
}

void AABB::merge(const std::vector<BoundingBox *> &others)
{
    // merge servel bounding boxs into a new one
    if(others.empty())return;
    AABB* first = static_cast<AABB*>(others[0]);
    QVector3D min = first->minVertex;
    QVector3D max = first->maxVertex;
    // if there is just only one bounding box, we replace it.
    if (others.size() > 1) {
        for (unsigned int i = 1; i < others.size(); i++) {
            AABB* other = (AABB*)(others[i]);
            float sx = other->minVertex.x();
            float sy = other->minVertex.y();
            float sz = other->minVertex.z();
            float lx = other->maxVertex.x();
            float ly = other->maxVertex.y();
            float lz = other->maxVertex.z();

            min.setX(min.x() > sx ? sx : min.x());
            min.setY(min.y() > sy ? sy : min.y());
            min.setZ(min.z() > sz ? sz : min.z());
            max.setX(max.x() < lx ? lx : max.x());
            max.setY(max.y() < ly ? ly : max.y());
            max.setZ(max.z() < lz ? lz : max.z());
        }
    }
    minVertex = min;
    maxVertex = max;
    update(minVertex, maxVertex);
}

bool AABB::vertexInsideFrustum(const QVector3D &vertex, const Frustum *frustum)
{
    // check if the given vertex is in the frustum
    for(int i=0;i<6;i++) {
        // simple detection according plane equation
        if(QVector3D::dotProduct(frustum->normals[i],vertex)
                + frustum->ds[i] < 0)
            return false;
    }
    return true;
}

bool AABB::intersectsWithRay(const QVector3D &origin, const QVector3D &dir, float maxDistance)
{
    // intersection detecting between line and bounding box
    float distance=0;
    QVector3D vertex;

    if (dir.x() != 0){
        float	d[2]	= { vertices[0].x(), vertices[7].x() };
        float	invDirX = 1.0 / dir.x();
        for (int i = 0; i < 2; i++){
            distance = (d[i] - origin.x()) * invDirX;
            if (distance >= 0 && distance <= maxDistance){
                vertex = dir * distance + origin;
                if (vertex.y() >= vertices[0].y() && vertex.y() <= vertices[7].y()
                        && vertex.z() >= vertices[0].z() && vertex.z() <= vertices[7].z())
                    return(true);
            }
        }
    }

    if (dir.y() != 0){
        float	d[2]	= { vertices[0].y(), vertices[7].y() };
        float	invDirY = 1.0 / dir.y();
        for (int i = 0; i < 2; i++){
            distance = (d[i] - origin.y()) * invDirY;
            if (distance >= 0 && distance <= maxDistance){
                vertex = dir * distance + origin;
                if (vertex.x() >= vertices[0].x() && vertex.x() <= vertices[7].x()
                        && vertex.z() >= vertices[0].z() && vertex.z() <= vertices[7].z())
                    return(true);
            }
        }
    }

    if (dir.z() != 0){
        float	d[2]	= { vertices[0].z(), vertices[7].z() };
        float	invDirZ = 1.0 / dir.z();
        for (int i = 0; i < 2; i++){
            distance = (d[i] - origin.z()) * invDirZ;
            if (distance >= 0 && distance <= maxDistance){
                vertex = dir * distance + origin;
                if (vertex.x() >= vertices[0].x() && vertex.x() <= vertices[7].x()
                        && vertex.y() >= vertices[0].y() && vertex.y() <= vertices[7].y())
                    return(true);
            }
        }
    }

    return false;
}

bool AABB::cameraVertexInside(const QVector3D &vertex)
{
    if(vertex.x() < minVertex.x() || vertex.x() > maxVertex.x())
        return false;
    if(vertex.y() < minVertex.y() || vertex.y() > maxVertex.y())
        return false;
    if(vertex.z() < minVertex.z() || vertex.z() > maxVertex.z())
        return false;
    return true;
}
