#ifndef ROOTLOGIC_H
#define ROOTLOGIC_H

#include <QObject>

//#include "login/loginscreenlogic.h"
//#include "matching/matchinglogic.h"
//#include "dialogs/dialogslogic.h"
//#include "table/tablelogic.h"
//#include "login/loginlogic.h"
//#include "skills/skillslogic.h"
#include "../macros.h"

class RootLogic : public QObject
{
    Q_OBJECT

//    AUTO_Q_PROPERTY(MatchingLogic*, matching)
//    AUTO_Q_PROPERTY(DialogsLogic*, dialogs)
//    AUTO_Q_PROPERTY(LoginLogic*, login)
//    AUTO_Q_PROPERTY(TableLogic*, table)
//    AUTO_Q_PROPERTY(SkillsLogic*, skills)

    AUTO_Q_PROPERTY(bool, isDebugModeOn)

public:
    explicit RootLogic(QObject* parent = 0);

signals:
    QML_CALL void qmlFullyLoaded();
};

#endif // ROOTLOGIC_H
