#ifndef PLANEFLAGMODEL_H
#define PLANEFLAGMODEL_H

#include <QObject>

#include "../macros.h"

class PlaneFlagModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(bool, isRightFlagUp)
    AUTO_Q_PROPERTY(bool, isLeftFlagUp)

public:
    explicit PlaneFlagModel(QObject* parent = 0);
};

#endif // PLANEFLAGMODEL_H
