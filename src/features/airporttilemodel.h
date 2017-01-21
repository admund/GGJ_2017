#ifndef AIRPORTTILEMODEL_H
#define AIRPORTTILEMODEL_H

#include <QObject>

#include "../macros.h"

// TILES_TYPE
// 0 - grass
// 1 - road
// 2 - building
// 3 - sea

class AirportTileModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(QString, touchedBy)
    AUTO_Q_PROPERTY(int, tileType)

public:
    explicit AirportTileModel(QObject* parent = 0);

    void clear();
};

#endif // AIRPORTTILEMODEL_H
