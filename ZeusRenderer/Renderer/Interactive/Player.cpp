#include "Player.h"
#include "InputManager.h"
#include <QTime>
#include <QtMath>
#include <QDebug>

Player::Player(Entity *entity)
    :target(entity)
{
    rotY = rotX = rotZ = 0;
    position = entity->position;
    matrix.setTranslation(position);
    currentSpeed = 0;
    currentTurnSpeed = 0;
    upwardsSpeed = 0;
    isInAir = false;
    m_frameTimer.start();
}

void Player::move()
{
    // calculate delta time
    qint64 elapsedTime = m_frameTimer.elapsed();
    float deltaTime = (elapsedTime)/1000.0f;

    // check key board operation
    checkInputs();

    // rotate the angle with y-axis.
    matrix.rotate(currentTurnSpeed*deltaTime,0.0,1.0,0.0);
    rotY += currentTurnSpeed*deltaTime;
    rotY = fmod(rotY,360.0f);

    // calc the delta distance
    float distance = currentSpeed*deltaTime;
    float dx = (float) (distance * qSin(qDegreesToRadians(rotY)));
    float dz = (float) (distance * qCos(qDegreesToRadians(rotY)));

    // jump it
    upwardsSpeed += GRAVITY*deltaTime;
    position += QVector3D(dx,upwardsSpeed,dz);
    if(position.y() < 0){
        upwardsSpeed = 0;
        isInAir = false;
        position.setY(0);
    }
    matrix.setTranslation(position);
    target->modelMatrix = matrix.toMatrix();
    target->normalTransform();
    m_frameTimer.start();
}

QMatrix4x4 Player::toMatrix()
{
    return matrix.toMatrix();
}

QVector3D Player::getPosition() const
{
    return this->position;
}

float Player::getRotY() const
{
    return this->rotY;
}

void Player::checkInputs()
{
    if(InputManager::keyPressed(Qt::Key_W)){
        currentSpeed = RUN_SPEED;
    }
    else if(InputManager::keyPressed(Qt::Key_S)){
        currentSpeed = -RUN_SPEED;
    }
    else{
        currentSpeed = 0;
    }

    if(InputManager::keyPressed(Qt::Key_D)){
        currentTurnSpeed = -TURN_SPEED;
    }
    else if(InputManager::keyPressed(Qt::Key_A)){
        currentTurnSpeed = TURN_SPEED;
    }
    else{
        currentTurnSpeed = 0;
    }

    if(InputManager::keyPressed(Qt::Key_Space)){
        jump();
    }
}

void Player::jump()
{
    if (!isInAir) {
        upwardsSpeed = JUMP_POWER;
        isInAir = true;
    }
}
