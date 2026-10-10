#pragma once

class CvUnit;
class CvPlot;
struct lua_State;
class FDataStream;

class CvStrategicSite {
  protected:
    PlayerTypes m_eOwner;
    int m_iID;
    int m_iX;
    int m_iY;
    int m_combatStrength;
    int m_baseUnitDefense;
    int m_threatValue;
    int m_damage;
    int m_extraHitPoints;
    bool m_madeAttacThisTurn;
    IDInfo m_combatUnit;

  public:
    CvStrategicSite();
    virtual ~CvStrategicSite();
    void Init(int, PlayerTypes, int, int);
    void Uninit();
    void Reset(int, PlayerTypes, int, int);
    IDInfo GetIDInfo() const;
    CvPlot * GetPlot() const;
    TeamTypes GetTeam() const;
    void SetID(int);
    void SetThreatValue(int);
    PlayerTypes GetOwner() const;
    int GetID() const;
    int GetX() const;
    int GetY() const;
    int GetDamage() const;
    int GetExtraHitPoints() const;
    int GetThreatValue() const;
    bool IsAlien() const;
    int GetUnitDefense() const;
    const CvUnit * GetCombatUnit() const;
    CvUnit * GetCombatUnit();
    void SetCombatUnit(CvUnit *, bool);
    void ClearCombat();
    void ChangeExtraHitPoints(int);
    bool IsFighting() const;
    bool HasMadeAttackThisTurn() const;
    void SetMadeAttackThisTurn(bool);
    CvUnit * GetValidRangeStrikeTarget(const CvPlot &) const;
    CityTaskResult RangeStrike(int, int);
    CvUnit * GetDefendingUnit() const;
    virtual const char * GetName() const;
    virtual const char * GetNameKey() const;
    virtual int GetMaxHitPoints() const;
    virtual bool CanRangeStrike() const;
    virtual bool CanRangeStrikeAt(int, int) const;
    virtual bool CanRangeStrikeNow() const;
    virtual bool CanUseIndirectFire() const;
    virtual int GetStrikeRange() const;
    virtual int GetRangedDamageVsUnit(CvUnit &, bool) const;
    virtual int GetCombatStrength(bool) const;
    virtual int GetCombatStrengthWhenAttackingUnit(bool, CvUnit &) const;
    virtual const char * GetBombardEffectTag();
    virtual unsigned int GetBombardEffectTagHash();
    virtual void SetDamage(int, bool);
    virtual void ChangeDamage(int);
    virtual void UpdateCombatStrength();
    virtual int GetAirstrikeDefenseDamage(CvUnit &, bool);
    virtual bool CanTeamAttackSite(TeamTypes);
    virtual bool DoConfirmAttackPopup(TeamTypes);
    virtual void Read(FDataStream &);
    virtual void Write(FDataStream &) const;
    virtual void LuaPushStrategicSiteData(lua_State *) const;
  protected:
    int CalculateDefaultRangeDamageVsUnit(int, int, bool) const;
};

class CvCityStrategicSite : public CvStrategicSite
{
protected:
	int m_extraStrikeRange;
};
