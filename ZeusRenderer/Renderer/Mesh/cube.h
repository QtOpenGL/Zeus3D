#ifndef CUBE_H
#define CUBE_H
#include "Mesh.h"
/*
 * 立方体网格
 */
class Cube : public Mesh
{
public:
    Cube();
    Cube(const Cube& rhs);
    virtual ~Cube();

private:
    virtual void initFaces()override;
};

#endif // CUBE_H
