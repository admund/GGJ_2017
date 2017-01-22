#include "skillslogic.h"

SkillsLogic::SkillsLogic(QObject* parent)
    : QObject(parent)
    , m_speedUpSkillCnt(0)
    , m_fuellSkillCnt(0)
    , m_doubleSkillCnt(0)

    , m_dropSkillTimeMax(0)
    , m_dropSkillTime(0)
    , m_dropItemNr(-1)
{

}

void SkillsLogic::speedUpSkill()
{
    if (speedUpSkillCnt() > 0) {
        set_speedUpSkillCnt(speedUpSkillCnt() - 1);
        emit speedUpSkillSignal();
    }
}

void SkillsLogic::fuellSkill()
{
    if (fuellSkillCnt() > 0) {
        set_fuellSkillCnt(fuellSkillCnt() - 1);
        emit fuellSkillSignal();
    }
}

void SkillsLogic::doubleSkill()
{
    if (doubleSkillCnt() > 0) {
        set_doubleSkillCnt(doubleSkillCnt() - 1);
        emit doubleSkillSignal();
    }
}

void SkillsLogic::getSkill(int skillId)
{
    if (skillId == 0) {
        set_fuellSkillCnt(fuellSkillCnt() + 1);
    } else if (skillId == 1) {
        set_speedUpSkillCnt(speedUpSkillCnt() + 1);
    } else if (skillId == 2) {
        set_doubleSkillCnt(doubleSkillCnt() + 1);
    }
}
