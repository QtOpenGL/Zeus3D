#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Lighting.h"

class PointLight : public Lighting
{
public:
    static int numPointLights;
    uint index;
    PointLight(const QVector3D &pos);
    virtual ~PointLight();

    void setAttenuation(const float &cons,const float &lin,const float &quad);
    QVector3D getAttenuation()const;
protected:
    float constant;
    float linear;
    float quadratic;
};


inline void PointLight::setAttenuation(const float &cons,
                              const float &lin,
                              const float &quad)
{
    constant = cons;
    linear   = lin;
    quadratic = quad;
}

inline QVector3D PointLight::getAttenuation() const
{
    return QVector3D(constant,linear,quadratic);
}

#endif // POINTLIGHT_H
