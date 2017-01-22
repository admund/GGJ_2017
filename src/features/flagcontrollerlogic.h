#ifndef FLAGCONTROLLERLOGIC_H
#define FLAGCONTROLLERLOGIC_H

#include <QObject>
#include <QList>

#include "planemodel.h"
#include "../macros.h"

class FlagControllerLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(PlaneModel*, selectedPlane)
    AUTO_Q_PROPERTY(int, greatJobTime)

public:
    explicit FlagControllerLogic(QObject* parent = 0);

public slots:
    void onPlaneGoAway();
};

#endif // FLAGCONTROLLERLOGIC_H
