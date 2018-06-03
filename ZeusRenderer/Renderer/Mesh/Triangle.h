#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <QVector3D>
#include <QVector2D>
/*
 * Triangle.h
 *
 *  Created on: 2018-5-28
 *      Author: Zeus
 */
class Triangle
{
public:
    QVector3D normal;
    float pd;

    Triangle(const QVector3D& a, const QVector3D& b, const QVector3D& c);
    ~Triangle() {}
    bool pointIsIn(const QVector3D& point);
    bool pointIsIn(const QVector2D& point);
    float caculateY(const float x, const float z);

private:
    QVector3D pa,pb,pc;
    void caculateNormal();
};

#endif // TRIANGLE_H
