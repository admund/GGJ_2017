#include "rootlogic.h"

RootLogic::RootLogic(QObject* parent)
    : QObject(parent)
    , m_airportLogic(new AirportLogic(this))
    , m_showLoading(false)
    , m_showChooseMap(false)
    , m_showAirport(false)
    , m_loadinglevelId(1)
{
#ifdef QT_DEBUG
    m_isDebugModeOn = true;
#else
    m_isDebugModeOn = false;
#endif
}
