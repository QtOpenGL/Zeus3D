#ifndef DIRLIGHT_H
#define DIRLIGHT_H
#include "Lighting.h"

class DirLight : public Lighting
{
public:
    DirLight(const QVector3D &dir);
    virtual ~DirLight();
};

#endif // DIRLIGHT_H
