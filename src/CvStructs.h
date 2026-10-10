#pragma once

struct CvAreaBoundaries
{
	CvAreaBoundaries() : m_iNorthEdge(0), m_iSouthEdge(0), m_iEastEdge(0), m_iWestEdge(0) {}
	int m_iNorthEdge;
	int m_iSouthEdge;
	int m_iEastEdge;
	int m_iWestEdge;
};

class CvUnit;
class CvStrategicSite;
class CvPlot;

struct CvCombatMemberEntry
{
	PlayerTypes m_ePlayer;
	int m_iID;
	unsigned short m_bfFlags;
	short m_iDamage;
	short m_iFinalDamage;
	short m_iMaxHitPoints;
	short m_iX;
	short m_iY;
	UnitCombatTypes m_eCombatType;
	EraTypes m_eEra;
	unsigned int m_uiWeaponType;
	float m_fWeaponOption;
};

class CvCombatInfo
{
public:
	CvUnit* getUnit(BattleUnitTypes unitType) const;
	CvStrategicSite* getStrategicSite(BattleUnitTypes unitType) const;
	CvPlot* getPlot() const;
	bool getAttackerAdvances() const;
	bool getVisualizeCombat() const;
	int getDamageInflicted(BattleUnitTypes unitType) const;
	int getFinalDamage(BattleUnitTypes unitType) const;
	CvCombatMemberEntry* getDamageMembers();
	const CvCombatMemberEntry* getDamageMembers() const;
	int getDamageMemberCount() const;
	int getMaxDamageMemberCount() const;
	bool getDefenderRetaliates() const;
	int getAttackNuclearLevel() const;
	bool getAttackIsRanged() const;
	bool getAttackIsBombingMission() const;
	bool getAttackIsAirSweep() const;
	bool getDefenderCaptured() const;
	bool getAttackIsAttackOrbital() const;
	unsigned int getVisFXHash() const;
};

struct MissionData
{
	MissionData()
		: eMissionType(NO_MISSION)
		, iData1(0)
		, iData2(0)
		, iFlags(0)
		, iPushTurn(0)
	{
	}

	MissionTypes eMissionType;
	int iData1;
	int iData2;
	int iFlags;
	int iPushTurn;
};

// TODO: CvStructs.h (remaining SDK structures).
