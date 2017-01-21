#ifndef AIRPORTLOGIC_H
#define AIRPORTLOGIC_H

#include <QObject>

#include "airportgridmodel.h"
#include "flagcontrollerlogic.h"
#include "planelistmodel.h"
#include "../macros.h"

class AirportLogic : public QObject
{
    Q_OBJECT

    AUTO_READ_ONLY_Q_PROPERTY(bool, editMode)
    AUTO_Q_PROPERTY(int, selectedPlane)
    AUTO_Q_PROPERTY(AirportGridModel*, airportGrid)
    AUTO_Q_PROPERTY(PlaneListModel*, planeList)
    AUTO_Q_PROPERTY(FlagControllerLogic*, flagController)

public:
    explicit AirportLogic(QObject* parent = 0);

    Q_INVOKABLE void setCellSize();
    Q_INVOKABLE void checkCollisions();
    Q_INVOKABLE void changeMoveDirection(int moveDirection);
    Q_INVOKABLE void changeSelectedPlane();

    void init(); // TODO add some JSON path
    void saveMap();

private slots:
    void onPlaneDestroyed(int planeId);

private:
    bool isInited = false;
    int cellSize = 0;
    QList<QRect> gridRects;
};

#endif // AIRPORTLOGIC_H
