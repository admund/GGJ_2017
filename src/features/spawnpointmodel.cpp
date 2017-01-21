#include "spawnpointmodel.h"

SpawnPointModel::SpawnPointModel(QObject* parent)
    : QObject(parent)
    , m_posX(0)
    , m_posY(0)
    , m_moveRotation(0)
{
}
