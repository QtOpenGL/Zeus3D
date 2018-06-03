#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>
#include "../Shape/Frustum.h"
/*
 * camera3d.h
 *
 *  Created on: 2018-5-24
 *      Author: Zeus
 */
class Camera3D
{
public:
    bool simpleCheck,isMain;
    Frustum *frustum;
    float fovy,aspect,zNear,zFar;

    // Constants
    static const QVector3D LocalForward;
    static const QVector3D LocalUp;
    static const QVector3D LocalRight;

    // Constructors
    Camera3D();
    virtual void move();
    virtual ~Camera3D();

    // Materix getter
    virtual QVector3D getPosition();
    QMatrix4x4 getViewMatrix();
    QMatrix4x4 getProjectMatrix();
    QMatrix4x4 getViewProjectMatrix();
    QMatrix4x4 getInvViewProjectMatrix();

    // shadow map effect
    void setLightSpaceMatrix(const QMatrix4x4& target);
    QMatrix4x4 getLightSpaceMatrix()const;

    // move camera and projection
    void moveTo(QVector3D position);
    void updateFrustum();
    void clone(Camera3D *src);
    void initPerspectProject(float fov,float asp,float zNea,float zFar);
    void initOrthoProject(float left,float right,float bottom,float top,float near,float far);

    // Queries
    QVector3D forward() const;
    QVector3D up() const;
    QVector3D right() const;
    // Accessors
    const QVector3D& translation() const;
    const QQuaternion& rotation() const;

protected:
    bool m_dirty;
    QVector3D m_translation;
    QQuaternion m_rotation;
    QMatrix4x4 m_world;

    QMatrix4x4 viewMatrix, projectMatrix, viewProjectMatrix;
    QMatrix4x4 invViewProjectMatrix;
    QMatrix4x4 lightSpaceMatrix;

    virtual const QMatrix4x4& toMatrix();

    // Transform By (Add/Scale)
    void translate(const QVector3D &dt);
    void translate(float dx, float dy, float dz);
    void rotate(const QQuaternion &dr);
    void rotate(float angle, const QVector3D &axis);
    void rotate(float angle, float ax, float ay, float az);

    // Transform To (Setters)
    void setTranslation(const QVector3D &t);
    void setTranslation(float x, float y, float z);
    void setRotation(const QQuaternion &r);
    void setRotation(float angle, const QVector3D &axis);
    void setRotation(float angle, float ax, float ay, float az);
};

// Constructors
inline Camera3D::Camera3D() : m_dirty(true)
{
    frustum = new Frustum();
    simpleCheck = false;
    isMain = false;
}

// Transform By (Add/Scale)
inline void Camera3D::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void Camera3D::rotate(float angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Camera3D::rotate(float angle, float ax, float ay,float az) { rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

// Transform To (Setters)
inline void Camera3D::setTranslation(float x, float y, float z) { setTranslation(QVector3D(x, y, z)); }
inline void Camera3D::setRotation(float angle, const QVector3D &axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Camera3D::setRotation(float angle, float ax, float ay, float az) { setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

// Accessors
inline const QVector3D& Camera3D::translation() const { return m_translation; }
inline const QQuaternion& Camera3D::rotation() const { return m_rotation; }

inline QMatrix4x4 Camera3D::getViewMatrix()
{
    if(m_dirty){
        viewMatrix = this->toMatrix();
        viewProjectMatrix = projectMatrix * viewMatrix;
        updateFrustum();
    }
    return viewMatrix;
}

inline QMatrix4x4 Camera3D::getProjectMatrix()
{
    return projectMatrix;
}

inline QMatrix4x4 Camera3D::getViewProjectMatrix()
{
    if(m_dirty){
        viewMatrix = this->toMatrix();
        viewProjectMatrix = projectMatrix * viewMatrix;
        updateFrustum();
    }
    return viewProjectMatrix;
}

inline QMatrix4x4 Camera3D::getInvViewProjectMatrix()
{
    if(m_dirty){
        viewMatrix = this->toMatrix();
        viewProjectMatrix = projectMatrix * viewMatrix;
        updateFrustum();
    }
    return invViewProjectMatrix;
}

inline void Camera3D::setLightSpaceMatrix(const QMatrix4x4& target)
{
    this->lightSpaceMatrix = target;
}

inline QMatrix4x4 Camera3D::getLightSpaceMatrix() const
{
    return this->lightSpaceMatrix;
}

#endif // CAMERA3D_H
