#include "rootlogic.h"

RootLogic::RootLogic(QObject* parent)
    : QObject(parent)
    , m_airportLogic(new AirportLogic(this))
{
#ifdef QT_DEBUG
    m_isDebugModeOn = true;
#else
    m_isDebugModeOn = false;
#endif
}
