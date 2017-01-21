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
    , m_moveDirection(0)
    , m_moveRotation(0)

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
    set_moveDirection(0);
    set_moveRotation(0);

    set_fuell(0);
    set_fuellMax(0);
}

// 0 - stop
// 1 - right
// 2 - left
// 3 - go
#include <QDebug>
void PlaneModel::changeMoveDirection()
{
    if (isRightFlagUp() == isLeftFlagUp()) {
        if (isRightFlagUp()) {
            set_moveDirection(3);
        } else {
            set_moveDirection(0);
        }
    } else {
        if (isRightFlagUp()) {
            set_moveDirection(1);
        } else {
            set_moveDirection(2);
        }
    }

//    qDebug() << "AirportLogic::changeMoveDirection()" << moveDirection();
}

#include <QDebug>
void PlaneModel::move(int deltaTime)
{
    Q_UNUSED(deltaTime)

    if (moveDirection() != 0) {
        int rotationSpeed = 1;
        if (moveDirection() == 1) {
            set_moveRotation((moveRotation() + rotationSpeed) % 360);

        } else if (moveDirection() == 2) {
            set_moveRotation(((moveRotation() - rotationSpeed) + 360) % 360);

        } else {
            float velocity = .3;
            double moveRotationInRadians = qDegreesToRadians((float)moveRotation());
            float newPosX = velocity * qCos(moveRotationInRadians);
            float newPosY = velocity * qSin(moveRotationInRadians);
            set_posX(posX() + newPosX);
            set_posY(posY() + newPosY);
        }
    }
}
