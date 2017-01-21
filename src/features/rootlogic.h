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

public:
    explicit RootLogic(QObject* parent = 0);

signals:
    QML_CALL void qmlFullyLoaded();
};

#endif // ROOTLOGIC_H
