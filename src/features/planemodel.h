#ifndef PLANEMODEL_H
#define PLANEMODEL_H

#include <QObject>

#include "../macros.h"

class PlaneModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, id)

    AUTO_Q_PROPERTY(float, posX)
    AUTO_Q_PROPERTY(float, posY)
    AUTO_Q_PROPERTY(bool, isAlive)
    AUTO_Q_PROPERTY(bool, canBeControlled)

    AUTO_Q_PROPERTY(bool, isRightFlagUp)
    AUTO_Q_PROPERTY(bool, isLeftFlagUp)

    AUTO_Q_PROPERTY(bool, isSelected)
    AUTO_Q_PROPERTY(int, moveDirection)
    AUTO_Q_PROPERTY(double, moveRotation)

    AUTO_Q_PROPERTY(double, speed)
    AUTO_Q_PROPERTY(double, rotation)

    AUTO_Q_PROPERTY(bool, isOnGrass)
    AUTO_Q_PROPERTY(int, fuell)
    AUTO_Q_PROPERTY(int, fuellMax)

public:
    explicit PlaneModel(QObject* parent = 0);

    static const int MOVE_RIGHT = 0;
    static const int MOVE_LEFT = 1;
    static const int MOVE_GO = 2;
    static const int MOVE_STOP = 3;

    void clear();

    void changeMoveDirection(int moveDirection);
    void hitBuilding();
    void goToSea();
    void hitOtherPlane();
    void goOnGrass(bool isTrue);

    Q_INVOKABLE void move(int deltaTime);

signals:
    void planeDestroyed(int playerId);

private:
    int lastFuellSubstraction = 0;
};

#endif // PLANEMODEL_H
