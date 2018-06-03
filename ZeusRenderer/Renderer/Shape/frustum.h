#ifndef FRUSTUM_H
#define FRUSTUM_H
#include <QVector3D>
#include <QVector4D>
/*
 * Frustum for view and project
 */
struct Plane{
    QVector3D normal;
    float d;
    Plane() {}
    Plane(const QVector3D& pn, const float pd):normal(pn),d(pd) {}
    void update(const QVector3D& pn, const float pd) {
        normal = pn;
        d = pd;
    }
};

struct Line {
    QVector3D dir;
    QVector3D origin;
    Line(const QVector3D& ld, const QVector3D& lo):dir(ld),origin(lo) {}
};

class Frustum
{
public:
    QVector4D ndcVertex[8]; // the cube vertice in ndc space
    QVector3D worldVertex[8]; // the cube vertice in world space
    QVector3D normals[6];// each plane's normal

    Plane planes[6]; // six planes of the frustum
    uint planeVertexIndex[24]; // each plane's indice
    float ds[6]; // the d component of plane equation, ax+by+cx+d=0

    // the four edges of frustum
    // top left, bottom left, top right, bottom right
    QVector3D edgeDir[4];
    float edgeLength[4];

    Frustum();
    ~Frustum();
    void update(const QMatrix4x4& invViewProjectMatrix);
    bool intersectsWithRay(const QVector3D& origin, const QVector3D& dir, float maxDistance);

    // calculate the intersection between the line and plane
    static bool CaculateIntersect(const Line& line, const Plane& plane,
                                  const float lineDistance, QVector3D& result);
private:
    enum PLANE{LEFT = 0,RIGHT = 1,BOTTOM = 2,TOP = 3,FRONT = 4,BACK = 5};
};

#endif // FRUSTUM_H
