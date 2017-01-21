#include "scoremodel.h"

ScoreModel::ScoreModel(QObject* parent)
    : QObject(parent)
    , m_goodScore(0)
    , m_badScore(0)
{
}

void ScoreModel::onPlaneDestroyed(int playerId)
{
    Q_UNUSED(playerId)
    set_badScore(badScore() + 1);
}

void ScoreModel::onPlaneGoAway()
{
    set_goodScore(goodScore() + 1);
}
