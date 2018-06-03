#include "DirLight.h"

DirLight::DirLight(const QVector3D &dir)
    :Lighting()
{
    this->setDirection(dir);
    this->setType(DIRECTION_LIGHT);
    this->setLightColor(QVector3D(0.02f, 0.02f, 0.02f),
                        QVector3D(0.3f, 0.3f, 0.3f),
                        QVector3D(0.1f, 0.1f, 0.1f));
}

DirLight::~DirLight() {}
