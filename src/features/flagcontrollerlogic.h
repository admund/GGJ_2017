#ifndef FLAGCONTROLLERLOGIC_H
#define FLAGCONTROLLERLOGIC_H

#include <QObject>
#include <QList>

#include "planeflagmodel.h"
#include "../macros.h"

class FlagControllerLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(PlaneFlagModel*, planeFlag)

public:
    explicit FlagControllerLogic(QObject* parent = 0);

private:
//    QList<PlaneFlagModel*> planeFlagList;
};

#endif // FLAGCONTROLLERLOGIC_H
