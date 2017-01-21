#include "planeflagmodel.h"

PlaneFlagModel::PlaneFlagModel(QObject* parent)
    : QObject(parent)
    , m_isRightFlagUp(false)
    , m_isLeftFlagUp(false)
{
}
