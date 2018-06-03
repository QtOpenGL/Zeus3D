#include "PointLight.h"

int PointLight::numPointLights = 0;

PointLight::PointLight(const QVector3D &pos)
    :Lighting()
{
    index = numPointLights;
    ++ numPointLights;
    this->setType(POINT_LIGHT);
    this->setPosition(pos);
    // set default configuration
    this->setAttenuation(1.0f,0.025,0.008);
    this->setLightColor(QVector3D(0.1f,0.0,0.0),
                        QVector3D(0.9f,0.0,0.0),
                        QVector3D(0.6f,0.0,0.0));
}

PointLight::~PointLight() {}
