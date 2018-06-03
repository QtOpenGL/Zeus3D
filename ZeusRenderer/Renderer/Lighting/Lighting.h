#ifndef LIGHTING_H
#define LIGHTING_H
#include <QVector3D>

class Lighting
{
public:
    enum LIGHT_TYPE{DIRECTION_LIGHT,POINT_LIGHT};

    Lighting();
    virtual ~Lighting();

    // setter
    void setPosition(const QVector3D &pos);
    void setDirection(const QVector3D &dir);
    void setAmbient(const QVector3D &amb);
    void setDiffuse(const QVector3D &dif);
    void setSpecular(const QVector3D &spec);
    void setLightColor(const QVector3D &amb,const QVector3D &dif,
                       const QVector3D &spec);

    // getter
    LIGHT_TYPE getType() const;
    QVector3D getPosition()const;
    QVector3D getDirection()const;
    QVector3D getAmbient()const;
    QVector3D getDiffuse()const;
    QVector3D getSpecular()const;
protected:
    QVector3D position;
    QVector3D direction;
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    LIGHT_TYPE type;

    void setType(LIGHT_TYPE target);
};

inline void Lighting::setPosition(const QVector3D &pos)
{
    this->position = pos;
}

inline void Lighting::setDirection(const QVector3D &dir)
{
    this->direction = dir;
}

inline void Lighting::setAmbient(const QVector3D &amb)
{
    this->ambient = amb;
}

inline void Lighting::setDiffuse(const QVector3D &dif)
{
    this->diffuse = dif;
}

inline void Lighting::setSpecular(const QVector3D &spec)
{
    this->specular = spec;
}

inline void Lighting::setLightColor(const QVector3D &amb, const QVector3D &dif, const QVector3D &spec)
{
    setAmbient(amb);
    setDiffuse(dif);
    setSpecular(spec);
}

inline Lighting::LIGHT_TYPE Lighting::getType() const
{
    return this->type;
}

inline QVector3D Lighting::getPosition() const
{
    return this->position;
}

inline QVector3D Lighting::getDirection() const
{
    return this->direction;
}

inline QVector3D Lighting::getAmbient() const
{
    return this->ambient;
}

inline QVector3D Lighting::getDiffuse() const
{
    return this->diffuse;
}

inline QVector3D Lighting::getSpecular() const
{
    return this->specular;
}

inline void Lighting::setType(Lighting::LIGHT_TYPE target)
{
    this->type = target;
}


#endif // LIGHTING_H
