#include "status.h"

Status::Status() :
        m_base_hp(100), m_base_mp(50), m_base_def(10), m_base_atk(20),
        m_base_luck(5), m_base_int(15), m_base_spd(10), m_base_dex(10),
        m_curr_hp(100), m_curr_mp(50)
{}

Status::Status(int baseHp, int baseMp, int baseDef, int baseAtk,
           int baseLuck, int baseInt, int baseSpd, int baseDex,
           int currHp, int currMp) :
        m_base_hp(baseHp), m_base_mp(baseMp), m_base_def(baseDef),
        m_base_atk(baseAtk), m_base_luck(baseLuck), m_base_int(baseInt),
        m_base_spd(baseSpd), m_base_dex(baseDex), m_curr_hp(currHp),
        m_curr_mp(currMp)
{}

void Status::printStatus() {
    std::cout << "Current HP: " << m_curr_hp << std::endl;
    std::cout << "Current MP: " << m_curr_mp << std::endl;
    std::cout << "Base HP: " << m_base_hp << std::endl;
    std::cout << "Base MP: " << m_base_mp << std::endl;
    std::cout << "Base DEF: " << m_base_def << std::endl;
    std::cout << "Base ATK: " << m_base_atk << std::endl;
    std::cout << "Base LUCK: " << m_base_luck << std::endl;
    std::cout << "Base INT: " << m_base_int << std::endl;
    std::cout << "Base SPD: " << m_base_spd << std::endl;
    std::cout << "Base DEX: " << m_base_dex << std::endl;
}