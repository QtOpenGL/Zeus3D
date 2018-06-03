#ifndef SPHERE_H
#define SPHERE_H
#include "Mesh.h"
/*
 * 球体
 */
class Sphere : public Mesh
{
private:
    int longitude,latitude;//经度，维度
    virtual void initFaces();

public:
    Sphere(int m,int n);
    Sphere(const Sphere& rhs);
    virtual ~Sphere();
};

#endif // SPHERE_H
