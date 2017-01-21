#include "planemodel.h"

#include <QtMath>

PlaneModel::PlaneModel(QObject* parent)
    : QObject(parent)
    , m_id(0)
    , m_posX(0)
    , m_posY(0)
    , m_isAlive(true)
    , m_canBeControlled(false)
    , m_isUnload(false)
    , m_isScored(false)

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
    set_canBeControlled(false);
    set_isUnload(false);
    set_isScored(false);

    set_moveDirection(MOVE_STOP);
    set_moveRotation(0);

    set_isOnGrass(false);
    set_fuell(0);
    set_fuellMax(0);
}

#include <QDebug>
void PlaneModel::hitBuilding()
{
    set_fuell(0);
    set_isAlive(false);

//    qDebug() << "hitBuilding planeDestroyed";
    emit planeDestroyed(id());
}

void PlaneModel::goToSea()
{
    set_fuell(0);
    set_isAlive(false);
//    qDebug() << "goToSea planeDestroyed";
    emit planeDestroyed(id());
}

void PlaneModel::goToRunwayStart()
{
    qDebug() << "void PlaneModel::goToRunwayStart()";
    qDebug() << "canBeControlled()" << canBeControlled();
    if (!canBeControlled() && !isUnload()) {
        set_canBeControlled(true);
        emit checkPlaneControll(id());
    } else {
        qDebug() << "isUnload()" << isUnload();
        if (isUnload() && !isScored()) {
            set_canBeControlled(false);
            set_moveDirection(MOVE_GO);
            emit checkPlaneControll(id());

            set_isScored(true);
            emit planeGoAway();
        }
    }
}

void PlaneModel::goToRamp() {
    qDebug() << "void PlaneModel::goToRamp()";

    set_isUnload(true);
    set_fuell(fuellMax());
}


void PlaneModel::hitOtherPlane()
{
    set_fuell(0);
    set_isAlive(false);
//    qDebug() << "hitOtherPlane planeDestroyed";
    emit planeDestroyed(id());
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
    } else { //if (moveDirection == MOVE_STOP) {
        set_isLeftFlagUp(false);
        set_isRightFlagUp(false);
    }
}

void PlaneModel::move(int deltaTime)
{
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
        if ((isOnGrass() && lastFuellSubstraction > 500) || lastFuellSubstraction > 1000) {
            set_fuell(fuell() - 1);
            lastFuellSubstraction = 0;

            if (fuell() <= 0) {
//                qDebug() << "if (fuell() <= 0) planeDestroyed";
                emit planeDestroyed(id());
            }
        }

        if (posX() < -200 || posX() > 1500) {
            set_fuell(0);
            set_isAlive(false);
//            qDebug() << "posX() < -200 || posX() > 1500 planeDestroyed";
            if (!isScored()) {
                emit planeDestroyed(id());
            }
        }

        if (posY() < -200 || posY() > 1000) {
            set_fuell(0);
            set_isAlive(false);
//            qDebug() << "(posY() < -200 || posY() > 1000) planeDestroyed";
            if (!isScored()) {
                emit planeDestroyed(id());
            }
        }
    }
}
