#ifndef SPAWNPOINTMODEL_H
#define SPAWNPOINTMODEL_H

#include <QObject>

#include "../macros.h"

class SpawnPointModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(int, moveRotation)

public:
    explicit SpawnPointModel(QObject* parent = 0);
};

#endif // SPAWNPOINTMODEL_H
