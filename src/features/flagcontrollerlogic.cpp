#include "flagcontrollerlogic.h"

FlagControllerLogic::FlagControllerLogic(QObject* parent)
    : QObject(parent)
    , m_selectedPlane(nullptr)
    , m_greatJobTime(0)
{
}

void FlagControllerLogic::onPlaneGoAway()
{
    set_greatJobTime(3000);
}
