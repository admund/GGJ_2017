#include "planemodel.h"

#include <QtMath>

PlaneModel::PlaneModel(QObject* parent)
    : QObject(parent)
    , m_id(0)
    , m_posX(0)
    , m_posY(0)
    , m_isAlive(true)

    , m_isRightFlagUp(false)
    , m_isLeftFlagUp(false)

    , m_isSelected(false)
    , m_moveDirection(MOVE_STOP)
    , m_moveRotation(0)

    , m_speed(0)
    , m_rotation(0)

    , m_isOnGrass(false)
    , m_fuell(0)
    , m_fuellMax(0)
{
}

void PlaneModel::clear()
{
    set_posX(0);
    set_posY(0);

    set_isRightFlagUp(false);
    set_isLeftFlagUp(false);

    set_isAlive(true);
    set_moveDirection(MOVE_STOP);
    set_moveRotation(0);

    set_isOnGrass(false);
    set_fuell(0);
    set_fuellMax(0);
}

#include <QDebug>
//void PlaneModel::changeMoveDirection()
//{
//    if (isRightFlagUp() == isLeftFlagUp()) {
//        if (isRightFlagUp()) {
//            set_moveDirection(MOVE_GO);
//        } else {
//            set_moveDirection(MOVE_STOP);
//        }
//    } else {
//        if (isRightFlagUp()) {
//            set_moveDirection(MOVE_RIGHT);
//        } else {
//            set_moveDirection(MOVE_LEFT);
//        }
//    }

//    //    qDebug() << "AirportLogic::changeMoveDirection()" << moveDirection();
//}

void PlaneModel::hitBuilding()
{
    set_fuell(0);
}

void PlaneModel::goToSea()
{
    set_fuell(0);
}

void PlaneModel::hitOtherPlane()
{
    set_fuell(0);
}

void PlaneModel::goOnGrass(bool isTrue)
{
    set_isOnGrass(isTrue);
}

void PlaneModel::changeMoveDirection(int moveDirection)
{
    set_moveDirection(moveDirection);

    if (moveDirection == MOVE_RIGHT) {
        set_isLeftFlagUp(false);
        set_isRightFlagUp(true);
    } else if (moveDirection == MOVE_LEFT) {
        set_isLeftFlagUp(true);
        set_isRightFlagUp(false);
    } else if (moveDirection == MOVE_GO) {
        set_isLeftFlagUp(true);
        set_isRightFlagUp(true);
    } else {//if (moveDirection == MOVE_STOP) {
        set_isLeftFlagUp(false);
        set_isRightFlagUp(false);
    }
}

#include <QDebug>
void PlaneModel::move(int deltaTime)
{
    Q_UNUSED(deltaTime)

    if (moveDirection() != MOVE_STOP) {
        if (moveDirection() == MOVE_RIGHT) {
            double newRotation = moveRotation() + rotation();
            if (newRotation > 360) {
                newRotation = newRotation - 360;
            }
            set_moveRotation(newRotation);

        } else if (moveDirection() == MOVE_LEFT) {
            double newRotation = moveRotation() - rotation();
            if (newRotation < 0) {
                newRotation = newRotation + 360;
            }
            set_moveRotation(newRotation);

        } else {
            double moveRotationInRadians = qDegreesToRadians((float)moveRotation());
            float newPosX = speed() * qCos(moveRotationInRadians);
            float newPosY = speed() * qSin(moveRotationInRadians);
            set_posX(posX() + newPosX);
            set_posY(posY() + newPosY);
        }

        lastFuellSubstraction += deltaTime;
        if (isOnGrass() && lastFuellSubstraction > 500
                || lastFuellSubstraction > 1000) {
            set_fuell(fuell() - 1);
            lastFuellSubstraction = 0;
        }
    }
}
