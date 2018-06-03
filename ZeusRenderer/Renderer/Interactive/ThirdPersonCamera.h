#ifndef THIRDPERSONCAMERA_H
#define THIRDPERSONCAMERA_H
#include "Camera3D.h"
#include "Player.h"
/*
 * ThirdPersonCamera.h
 *
 *  Created on: 2018-5-26
 *      Author: Zeus
 */

class ThirdPersonCamera : public Camera3D
{
public:
    ThirdPersonCamera(Player *target);
    virtual ~ThirdPersonCamera();

    void move();
    virtual QVector3D getPosition();

private:
    Player* player;
    float yaw,pitch;
    float angleAroundPlayer,distanceFromPlayer;
    QVector3D position;

    virtual const QMatrix4x4& toMatrix();

    void calculateCameraPosition(float horizDistance, float verticDistance);
    float calculateHorizontalDistance();
    float calculateVerticalDistance();
    void calculateZoom();
    void calculatePitch();
    void calculateAngleAroundPlayer();
};

inline QVector3D ThirdPersonCamera::getPosition()
{
    return this->position;
}

#endif // THIRDPERSONCAMERA_H
