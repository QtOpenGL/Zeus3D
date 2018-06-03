#ifndef QUAD_H
#define QUAD_H
#include "Mesh.h"
/*
 * Quad mesh
 */

class Quad : public Mesh
{
private:
    virtual void initFaces();
public:
    Quad();
    Quad(const Quad& rhs);
    virtual ~Quad();
};

#endif // QUAD_H
