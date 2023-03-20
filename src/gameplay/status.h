#ifndef STATUS_H
#define STATUS_H

class Status {

public:
  Status();
  Status(double baseHp, double baseMp, double baseAtk, double baseDef,
         double baseLuck, double baseInt, double baseSpd, double baseDex,
         double currHp, double currMp);
  void printStatus();

  // Combat
  double getCurrentAttack();
  void defendFrom(Status &other);
  bool isAlive();

  // Getters
  double getBaseHp() const { return m_base_hp; }
  double getBaseMp() const { return m_base_mp; }
  double getBaseDef() const { return m_base_def; }
  double getBaseAtk() const { return m_base_atk; }
  double getBaseLuck() const { return m_base_luck; }
  double getBaseInt() const { return m_base_int; }
  double getBaseSpd() const { return m_base_spd; }
  double getBaseDex() const { return m_base_dex; }
  double getCurrHp() const { return m_curr_hp; }
  double getCurrMp() const { return m_curr_mp; }

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
  double m_base_hp;
  double m_base_mp;
  double m_base_def;
  double m_base_atk;
  double m_base_luck;
  double m_base_int;
  double m_base_spd;
  double m_base_dex;

  double m_curr_hp;
  double m_curr_mp;
};

#endif