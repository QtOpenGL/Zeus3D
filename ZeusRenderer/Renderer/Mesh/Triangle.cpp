#include "Triangle.h"
/*
        pa
        /\
       /  \
     pb----pc
*/
Triangle::Triangle(const QVector3D &a, const QVector3D &b, const QVector3D &c)
{
    pa = a;
    pb = b;
    pc = c;
    caculateNormal();
    // ax + by + cz + d = 0, pd is d of this equation
    pd = -normal.dotProduct(normal,pa);
}

bool Triangle::pointIsIn(const QVector3D &point)
{
    // Determine whether point is in this triangle
    // Algorithm: https://www.cnblogs.com/graphics/archive/2010/08/05/1793393.html
    QVector3D v0 = pc - pb;
    QVector3D v1 = pa - pb;
    QVector3D v2 = point - pb;

    float dot00 = QVector3D::dotProduct(v0,v0);
    float dot01 = QVector3D::dotProduct(v0,v1);
    float dot02 = QVector3D::dotProduct(v0,v2);
    float dot11 = QVector3D::dotProduct(v1,v1);
    float dot12 = QVector3D::dotProduct(v1,v2);

    float inverDeno = 1.0f / (dot00 * dot11 - dot01 * dot01);

    float u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
    if (u < 0 || u > 1) // if u out of range, return directly
        return false;

    float v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
    if (v < 0 || v > 1) // if v out of range, return directly
        return false;

    return u + v <= 1;
}

bool Triangle::pointIsIn(const QVector2D &point)
{
    // Determine whether point in this project triangle
    QVector2D v0 = QVector2D(pc.x(), pc.z()) - QVector2D(pb.x(), pb.z());
    QVector2D v1 = QVector2D(pa.x(), pa.z()) - QVector2D(pb.x(), pb.z());
    QVector2D v2 = point - QVector2D(pb.x(), pb.z());

    float dot00 = v0.x()*v0.x() + v0.y()*v0.y();
    float dot01 = v0.x()*v1.x() + v0.y()*v1.y();
    float dot02 = v0.x()*v2.x() + v0.y()*v2.y();
    float dot11 = v1.x()*v1.x() + v1.y()*v1.y();
    float dot12 = v1.x()*v2.x() + v1.y()*v2.y();

    float inverDeno = 1.0f / (dot00 * dot11 - dot01 * dot01);

    float u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
    if (u < 0 || u > 1) // if u out of range, return directly
        return false;

    float v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
    if (v < 0 || v > 1) // if v out of range, return directly
        return false;

    return u + v <= 1;
}

float Triangle::caculateY(const float x, const float z)
{
    // calculate the y value in this triangle accroding the given x and z.
    float a = normal.x(), b = normal.y(), c = normal.z(), d = pd;
    float y = -(d + a*x + c*z) / b;
    return y;
}

void Triangle::caculateNormal()
{
    QVector3D ba = pa - pb;
    QVector3D bc = pc - pb;
    normal = QVector3D::crossProduct(bc,ba);
}
