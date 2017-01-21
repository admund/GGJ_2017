#include "airporttilemodel.h"

AirportTileModel::AirportTileModel(QObject* parent)
    : QObject(parent)
    , m_touchedBy("")
    , m_tileType(0)
{
}

void AirportTileModel::clear()
{
    set_touchedBy("");
    set_tileType(0);
}
