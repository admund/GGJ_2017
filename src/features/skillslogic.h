#ifndef SKILLSLOGIC_H
#define SKILLSLOGIC_H

#include <QObject>

#include "../macros.h"

class SkillsLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, speedUpSkillCnt)
    AUTO_Q_PROPERTY(int, fuellSkillCnt)
    AUTO_Q_PROPERTY(int, doubleSkillCnt)

    AUTO_Q_PROPERTY(int, dropSkillTimeMax)
    AUTO_Q_PROPERTY(int, dropSkillTime)
    AUTO_Q_PROPERTY(int, dropItemNr)

public:
    explicit SkillsLogic(QObject* parent = 0);

    Q_INVOKABLE void speedUpSkill();
    Q_INVOKABLE void fuellSkill();
    Q_INVOKABLE void doubleSkill();

    Q_INVOKABLE void getSkill(int skillId);

signals:
    void speedUpSkillSignal();
    void fuellSkillSignal();
    void doubleSkillSignal();
};

#endif // SKILLSLOGIC_H
