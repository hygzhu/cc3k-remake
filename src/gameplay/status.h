#ifndef STATUS_H
#define STATUS_H

class Status {

public:
    Status();
    Status(int baseHp, int baseMp, int baseDef, int baseAtk,
           int baseLuck, int baseInt, int baseSpd, int baseDex,
           int currHp, int currMp);
    void printStatus();


    // Getters
    int getBaseHp() const { return m_base_hp; }
    int getBaseMp() const { return m_base_mp; }
    int getBaseDef() const { return m_base_def; }
    int getBaseAtk() const { return m_base_atk; }
    int getBaseLuck() const { return m_base_luck; }
    int getBaseInt() const { return m_base_int; }
    int getBaseSpd() const { return m_base_spd; }
    int getBaseDex() const { return m_base_dex; }
    int getCurrHp() const { return m_curr_hp; }
    int getCurrMp() const { return m_curr_mp; }

    // Setters
    void setBaseHp(int baseHp) { m_base_hp = baseHp; }
    void setBaseMp(int baseMp) { m_base_mp = baseMp; }
    void setBaseDef(int baseDef) { m_base_def = baseDef; }
    void setBaseAtk(int baseAtk) { m_base_atk = baseAtk; }
    void setBaseLuck(int baseLuck) { m_base_luck = baseLuck; }
    void setBaseInt(int baseInt) { m_base_int = baseInt; }
    void setBaseSpd(int baseSpd) { m_base_spd = baseSpd; }
    void setBaseDex(int baseDex) { m_base_dex = baseDex; }
    void setCurrHp(int currHp) { m_curr_hp = currHp; }
    void setCurrMp(int currMp) { m_curr_mp = currMp; }

private:
    int m_base_hp;
    int m_base_mp;
    int m_base_def;
    int m_base_atk;
    int m_base_luck;
    int m_base_int;
    int m_base_spd;
    int m_base_dex;

    int m_curr_hp;
    int m_curr_mp;



};

#endif