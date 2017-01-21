#include "airporttilemodel.h"

AirportTileModel::AirportTileModel(QObject* parent)
    : QObject(parent)
    , m_tileType(0)
{
}

void AirportTileModel::clear()
{
    set_tileType(0);
}
