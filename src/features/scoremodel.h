#ifndef SCOREMODEL_H
#define SCOREMODEL_H

#include <QObject>

#include "../macros.h"

class ScoreModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, goodScore)
    AUTO_Q_PROPERTY(int, badScore)

public:
    explicit ScoreModel(QObject* parent = 0);

public slots:
    void onPlaneDestroyed(int playerId);
    void onPlaneGoAway();
};

#endif // SCOREMODEL_H
