#ifndef AIRPORTTILEMODEL_H
#define AIRPORTTILEMODEL_H

#include <QObject>

#include "../macros.h"

class AirportTileModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(QString, touchedBy)
    AUTO_Q_PROPERTY(int, tileType)

public:
    explicit AirportTileModel(QObject* parent = 0);

    static const int TILE_TYPE_GRASS = 0;
    static const int TILE_TYPE_ROAD = 1;
    static const int TILE_TYPE_BUILDING = 2;
    static const int TILE_TYPE_SEA = 3;

    void clear();
};

#endif // AIRPORTTILEMODEL_H
