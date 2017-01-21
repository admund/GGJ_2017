#ifndef AIRPORTLOGIC_H
#define AIRPORTLOGIC_H

#include <QObject>

#include "airportgridmodel.h"
#include "flagcontrollerlogic.h"
#include "../macros.h"

class AirportLogic : public QObject
{
    Q_OBJECT

    AUTO_READ_ONLY_Q_PROPERTY(bool, editMode)
    AUTO_Q_PROPERTY(AirportGridModel*, airportGrid)
    AUTO_Q_PROPERTY(FlagControllerLogic*, flagController)

public:
    explicit AirportLogic(QObject* parent = 0);

    void init(); // TODO add some JSON path

    void saveMap();
    void changeFlag(bool isRight);
};

#endif // AIRPORTLOGIC_H
