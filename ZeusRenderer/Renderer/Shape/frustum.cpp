#include "Frustum.h"
#include <QMatrix4x4>

Frustum::Frustum()
{
    // normalized device coordinate vertices, it's a cube.
    // the front face
    ndcVertex[0]=QVector4D(-1.0f, -1.0f,  1.0f, 1.0f);
    ndcVertex[1]=QVector4D( 1.0f, -1.0f,  1.0f, 1.0f);
    ndcVertex[2]=QVector4D(-1.0f,  1.0f,  1.0f, 1.0f);
    ndcVertex[3]=QVector4D( 1.0f,  1.0f,  1.0f, 1.0f);
    // the back face
    ndcVertex[4]=QVector4D(-1.0f, -1.0f, -1.0f, 1.0f);
    ndcVertex[5]=QVector4D( 1.0f, -1.0f, -1.0f, 1.0f);
    ndcVertex[6]=QVector4D(-1.0f,  1.0f, -1.0f, 1.0f);
    ndcVertex[7]=QVector4D( 1.0f,  1.0f, -1.0f, 1.0f);

    // each face of cube
    // the left plane
    planeVertexIndex[0] = 0; planeVertexIndex[1] = 4; planeVertexIndex[2] = 6; planeVertexIndex[3] = 2;
    // the right plane
    planeVertexIndex[4] = 3; planeVertexIndex[5] = 7; planeVertexIndex[6] = 5; planeVertexIndex[7] = 1;
    // the bottom plane
    planeVertexIndex[8] = 1; planeVertexIndex[9] = 5; planeVertexIndex[10] = 4; planeVertexIndex[11] = 0;
    // the top plane
    planeVertexIndex[12] = 2; planeVertexIndex[13] = 6; planeVertexIndex[14] = 7; planeVertexIndex[15] = 3;
    // the front plane
    planeVertexIndex[16] = 0; planeVertexIndex[17] = 2; planeVertexIndex[18] = 3; planeVertexIndex[19] = 1;
    // the back plane
    planeVertexIndex[20] = 4; planeVertexIndex[21] = 5; planeVertexIndex[22] = 7; planeVertexIndex[23] = 6;
}

Frustum::~Frustum(){}

void Frustum::update(const QMatrix4x4 &invViewProjectMatrix)
{
    static QVector4D worldVert(0, 0, 0, 1);

    // invViewProjectMatrix is the inverse of projection * view
    // that is, transforming the vertex to the world
    for (int i = 0; i<8; i++) {
        // Put the ndc vertice to the world space
        worldVert = invViewProjectMatrix * ndcVertex[i];
        worldVertex[i] = QVector3D(worldVert.x() / worldVert.w(),
                                   worldVert.y() / worldVert.w(),
                                   worldVert.z() / worldVert.w());
    }

    // now calculate each norml of each face
    // each normal points inside of the frustum
    // the left plane's normal
    normals[LEFT] = QVector3D::crossProduct(worldVertex[0] - worldVertex[4],worldVertex[2] - worldVertex[4]);
    // the right plane's normal
    normals[RIGHT] = QVector3D::crossProduct(worldVertex[3] - worldVertex[5],worldVertex[1] - worldVertex[5]);
    // the bottom plane's normal
    normals[BOTTOM] = QVector3D::crossProduct(worldVertex[1] - worldVertex[4],worldVertex[0] - worldVertex[4]);
    // the top face's normal
    normals[TOP] = QVector3D::crossProduct(worldVertex[2] - worldVertex[6],worldVertex[3] - worldVertex[6]);
    // the front plane's normal
    normals[FRONT] = QVector3D::crossProduct(worldVertex[1] - worldVertex[0],worldVertex[3] - worldVertex[0]);
    // the back plane's normal
    normals[BACK] = QVector3D::crossProduct(worldVertex[6] - worldVertex[4],worldVertex[7] - worldVertex[4]);
    // normalize them
    normals[LEFT].normalize();
    normals[RIGHT].normalize();
    normals[BOTTOM].normalize();
    normals[TOP].normalize();
    normals[FRONT].normalize();
    normals[BACK].normalize();

    // now we calcue the d component for each plane's equation.
    // fromt ax+by+cz+d=0, we got d = -(a,b,c)*(x,y,z)
    ds[LEFT] = QVector3D::dotProduct(-normals[LEFT], worldVertex[2]);
    ds[RIGHT] = QVector3D::dotProduct(-normals[RIGHT], worldVertex[3]);
    ds[BOTTOM] = QVector3D::dotProduct(-normals[BOTTOM], worldVertex[1]);
    ds[TOP] = QVector3D::dotProduct(-normals[TOP], worldVertex[6]);
    ds[FRONT] = QVector3D::dotProduct(-normals[FRONT], worldVertex[0]);
    ds[BACK] = QVector3D::dotProduct(-normals[BACK], worldVertex[4]);

    // the four edges of frustum
    // top left, bottom left, top right, bottom right
    for (int i = 0; i<4; i++) {
        edgeDir[i] = worldVertex[i] - worldVertex[i + 4];
        edgeLength[i] = edgeDir[i].length();
        edgeDir[i].normalize();
    }
    // cache them
    planes[LEFT].update(normals[LEFT], ds[LEFT]);
    planes[RIGHT].update(normals[RIGHT], ds[RIGHT]);
    planes[BOTTOM].update(normals[BOTTOM], ds[BOTTOM]);
    planes[TOP].update(normals[TOP], ds[TOP]);
    planes[FRONT].update(normals[FRONT], ds[FRONT]);
    planes[BACK].update(normals[BACK], ds[BACK]);
}

bool Frustum::intersectsWithRay(const QVector3D &origin, const QVector3D &dir, float maxDistance)
{
    // the detection of intersection with ray
    Line line(dir, origin);
    // recrod the intersection point
    QVector3D interPoint(0, 0, 0);

    // we have to detect it with each plane
    for (uint i = 0; i < 6; i++) {
        bool isInter = CaculateIntersect(line, planes[i], maxDistance, interPoint);
        if (!isInter) continue;
        // get this plane vertice's indice
        uint pi0 = planeVertexIndex[i * 4];
        uint pi1 = planeVertexIndex[i * 4 + 1];
        uint pi2 = planeVertexIndex[i * 4 + 2];
        uint pi3 = planeVertexIndex[i * 4 + 3];
        // get the corresponding vertex of each index
        QVector3D a = worldVertex[pi0];
        QVector3D b = worldVertex[pi1];
        QVector3D c = worldVertex[pi2];
        QVector3D d = worldVertex[pi3];

        // check if the intersection point is inside ot the plane
        QVector3D ia = a - interPoint;
        QVector3D ib = b - interPoint;
        QVector3D ic = c - interPoint;
        QVector3D id = d - interPoint;
        QVector3D aib = QVector3D::crossProduct(ia,ib);
        QVector3D bic = QVector3D::crossProduct(ib,ic);
        QVector3D cid = QVector3D::crossProduct(ic,id);
        QVector3D dia = QVector3D::crossProduct(id,ia);
        if ((QVector3D::dotProduct(aib,bic) >= 0 && QVector3D::dotProduct(bic,cid) >= 0 &&
             QVector3D::dotProduct(cid,dia) >= 0 && QVector3D::dotProduct(dia,aib) >= 0)
            ||
            (QVector3D::dotProduct(aib,bic) <= 0 && QVector3D::dotProduct(bic,cid) <= 0 &&
             QVector3D::dotProduct(cid,dia) <= 0 && QVector3D::dotProduct(dia,aib) <= 0))
            return true;
    }
    return false;
}

bool Frustum::CaculateIntersect(const Line &line, const Plane &plane,
                                const float lineDistance, QVector3D &result)
{
    QVector3D from = line.origin;// (x1, y1, z1)
    QVector3D direction = line.dir;// (Vx, Vy, Vz)

    // from plane: ax + by + cz + d = 0
    QVector3D planeNorm = plane.normal;// (a, b, c)
    float dTerm = plane.d;// constant term of plane

    // we got cos(angle) of these two vectors
    float cangle = QVector3D::dotProduct(planeNorm,direction);// a*Vx + b*Vy + c*Vz
    // calculate the value of equation:
    float value = QVector3D::dotProduct(planeNorm,from);// a*x1 + b*y1 + c*z1

    // if denominator=0, no intersect
    if (cangle == 0) return false;

    // find t = -(a*x1 + b*y1 + c*z1 + d) / (a*Vx + b*Vy + c*Vz)
    // we got the distance between intersecting point and origin of the line
    float t = -(value + dTerm) / cangle;
    if (t < 0 || t > lineDistance) // intersect is outside
        return false;

    // find intersection point
    result = from + (t * direction);
    return true;
}
