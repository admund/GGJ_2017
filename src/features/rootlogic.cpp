#include "rootlogic.h"

RootLogic::RootLogic(QObject* parent)
    : QObject(parent)
//    , m_matching(new MatchingLogic(this))
//    , m_dialogs(new DialogsLogic(this))
//    , m_login(new LoginLogic(this))
//    , m_table(new TableLogic(this))
//    , m_skills(new SkillsLogic(this))
{
#ifdef QT_DEBUG
    m_isDebugModeOn = true;
#else
    m_isDebugModeOn = false;
#endif
}
