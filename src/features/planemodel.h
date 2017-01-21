#ifndef PLANEMODEL_H
#define PLANEMODEL_H

#include <QObject>

#include "../macros.h"

class PlaneModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, id)

    AUTO_Q_PROPERTY(bool, isAlive)
    AUTO_Q_PROPERTY(float, posX)
    AUTO_Q_PROPERTY(float, posY)

    AUTO_Q_PROPERTY(bool, isRightFlagUp)
    AUTO_Q_PROPERTY(bool, isLeftFlagUp)

    AUTO_Q_PROPERTY(bool, isSelected)
    AUTO_Q_PROPERTY(int, moveDirection)
    AUTO_Q_PROPERTY(int, moveRotation)

    AUTO_Q_PROPERTY(int, fuell)
    AUTO_Q_PROPERTY(int, fuellMax)

public:
    explicit PlaneModel(QObject* parent = 0);

    void clear();

    void changeMoveDirection();

    Q_INVOKABLE void move(int deltaTime);

private:
    int lastFuellSubstraction = 0;
};

#endif // PLANEMODEL_H
