#include "flagcontrollerlogic.h"

FlagControllerLogic::FlagControllerLogic(QObject* parent)
    : QObject(parent)
    , m_planeFlag(new PlaneFlagModel(this))
{
}
