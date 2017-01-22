#ifndef ROOTLOGIC_H
#define ROOTLOGIC_H

#include <QObject>

#include "airportlogic.h"
#include "../macros.h"

class RootLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(bool, isDebugModeOn)

    AUTO_Q_PROPERTY(AirportLogic*, airportLogic)

    AUTO_Q_PROPERTY(bool, showChooseMap)
    AUTO_Q_PROPERTY(bool, showLoading)
    AUTO_Q_PROPERTY(bool, showAirport)

public:
    explicit RootLogic(QObject* parent = 0);

signals:
    QML_CALL void qmlFullyLoaded();

    Q_INVOKABLE void initLevel(int levelId);
};

#endif // ROOTLOGIC_H
