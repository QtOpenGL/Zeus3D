#ifndef PLAYER_H
#define PLAYER_H
#include "Transform3D.h"
#include "InputManager.h"
#include "../Entity/Entity.h"
#include <QElapsedTimer>
/*
 * Player.h
 *
 *  Created on: 2018-5-26
 *      Author: Zeus
 */
class Player
{
public:
    Player(Entity *target);

    void move();
    QMatrix4x4 toMatrix();
    QVector3D getPosition()const;
    float getRotY()const;

private:
    const float RUN_SPEED = 20;
    const float TURN_SPEED = 160;
    const float GRAVITY = -20;
    const float JUMP_POWER = 5;

    float currentSpeed = 0;
    float currentTurnSpeed = 0;
    float upwardsSpeed = 0;
    bool isInAir = false;
    float rotX,rotY,rotZ;
    Entity* target;
    QVector3D position;

    Transform3D matrix;
    QElapsedTimer m_frameTimer;

    void checkInputs();
    void jump();
};

#endif // PLAYER_H
