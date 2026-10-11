#pragma once

#include <vector>
#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvGameCoreDLLUtil/include/CvString.h"

struct GenericYieldHealthChange;
struct OrderData;
class FDataStream;
enum VoteTypes : int;
enum VoteSourceTypes : int;

struct VoteSelectionSubData
{
	// TODO: Phase1 audit VoteSelectionSubData::VoteSelectionSubData(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	VoteSelectionSubData() : eVote(static_cast<VoteTypes>(-1)), ePlayer(NO_PLAYER), iCityId(-1), eOtherPlayer(NO_PLAYER) {}
	VoteTypes eVote;
	PlayerTypes ePlayer;
	int iCityId;
	PlayerTypes eOtherPlayer;
	CvString strText;
};

struct VoteSelectionData
{
	// TODO: Phase1 audit VoteSelectionData::VoteSelectionData(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	VoteSelectionData() : iId(0), eVoteSource(static_cast<VoteSourceTypes>(-1)) {}
	int GetID() const;
	void SetID(int id);
	// TODO: Phase1 audit VoteSelectionData::read(FDataStream&): MISMATCH; BE/object instructions 113/107; Civ5 changed/new UNVERIFIED.
	void read(FDataStream& stream);
	// TODO: Phase1 audit VoteSelectionData::write(FDataStream&) const: MISMATCH; BE/object instructions 61/66; Civ5 changed/new UNVERIFIED.
	void write(FDataStream& stream) const;
	int iId;
	VoteSourceTypes eVoteSource;
	std::vector<VoteSelectionSubData> aVoteOptions;
};

struct VoteTriggeredData
{
	// TODO: Phase1 audit VoteTriggeredData::VoteTriggeredData(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	VoteTriggeredData() : iId(0), eVoteSource(static_cast<VoteSourceTypes>(-1)) {}
	int GetID() const;
	void SetID(int id);
	// TODO: Phase1 audit VoteTriggeredData::read(FDataStream&): MISMATCH; BE/object instructions 45/46; Civ5 changed/new UNVERIFIED.
	void read(FDataStream& stream);
	// TODO: Phase1 audit VoteTriggeredData::write(FDataStream&) const: MISMATCH; BE/object instructions 46/47; Civ5 changed/new UNVERIFIED.
	void write(FDataStream& stream) const;
	int iId;
	VoteSourceTypes eVoteSource;
	VoteSelectionSubData kVoteOption;
};

struct BuildingYieldChange
{
	// TODO: Phase1 audit BuildingYieldChange::BuildingYieldChange(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	BuildingYieldChange() : eBuildingClass(NO_BUILDINGCLASS), eYield(NO_YIELD), iChange(0) {}
	BuildingClassTypes eBuildingClass;
	YieldTypes eYield;
	int iChange;
};

struct BuildingGreatWork
{
	// TODO: Phase1 audit BuildingGreatWork::BuildingGreatWork(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	BuildingGreatWork() : eBuildingClass(NO_BUILDINGCLASS), iSlot(-1), iGreatWorkIndex(-1) {}
	BuildingClassTypes eBuildingClass;
	int iSlot;
	int iGreatWorkIndex;
};

struct PlotExtraYield
{
	// TODO: Phase1 audit PlotExtraYield::PlotExtraYield(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	PlotExtraYield() : m_iX(-1), m_iY(-1) {}
	int m_iX;
	int m_iY;
	std::vector<int> m_aeExtraYield;
};

struct PlotExtraCost
{
	// TODO: Phase1 audit PlotExtraCost::PlotExtraCost(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	PlotExtraCost() : m_iX(-1), m_iY(-1), m_iCost(0) {}
	int m_iX;
	int m_iY;
	int m_iCost;
};

struct CvAreaBoundaries
{
	// TODO: Phase1 audit CvAreaBoundaries::CvAreaBoundaries(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
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
	// TODO: Phase1 audit CvCombatMemberEntry::CvCombatMemberEntry(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	CvCombatMemberEntry()
		: m_ePlayer(NO_PLAYER), m_iID(-1), m_bfFlags(0), m_iDamage(0), m_iFinalDamage(0),
		  m_iMaxHitPoints(0), m_iX(0), m_iY(0), m_eCombatType(static_cast<UnitCombatTypes>(-1)),
		  m_eEra(static_cast<EraTypes>(-1)), m_uiWeaponType(0), m_fWeaponOption(0) {}
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
	// TODO: Phase1 audit CvCombatInfo::CvCombatInfo(): UNVERIFIED; BE/object instructions 52/52; Civ5 changed/new UNVERIFIED.
	CvCombatInfo();
	CvCombatInfo& operator=(const CvCombatInfo& other);
	void setUnit(BattleUnitTypes unitType, CvUnit* unit);
	void setStrategicSite(BattleUnitTypes unitType, CvStrategicSite* site);
	void setPlot(CvPlot* plot);
	void setAttackerAdvances(bool value);
	void setDefenderRetaliates(bool value);
	void setAttackIsRanged(bool value);
	void setAttackIsBombingMission(bool value);
	void setAttackIsAirSweep(bool value);
	void setAttackIsAttackOrbital(bool value);
	void setVisFXHash(unsigned int value);
	void setDefenderCaptured(bool value);
	void setDamageInflicted(BattleUnitTypes unitType, int value);
	void setFinalDamage(BattleUnitTypes unitType, int value);
	int getFearDamageInflicted(BattleUnitTypes unitType) const;
	void setFearDamageInflicted(BattleUnitTypes unitType, int value);
	int getExperience(BattleUnitTypes unitType) const;
	void setExperience(BattleUnitTypes unitType, int value);
	int getMaxExperienceAllowed(BattleUnitTypes unitType) const;
	void setMaxExperienceAllowed(BattleUnitTypes unitType, int value);
	bool getInBorders(BattleUnitTypes unitType) const;
	void setInBorders(BattleUnitTypes unitType, bool value);
	bool getUpdateGlobal(BattleUnitTypes unitType) const;
	void setUpdateGlobal(BattleUnitTypes unitType, bool value);
	void setVisualizeCombat(bool value);
	bool getAttackerAdvancedVisualization() const;
	void setAttackerAdvancedVisualization(bool value);
	bool getAttackIsNuclear() const;
	void setAttackNuclearLevel(int value);
	// TODO: Phase1 audit CvCombatInfo::getCombatMember(BattleUnitTypes) const: MISMATCH; BE/object instructions 8/4; Civ5 changed/new UNVERIFIED.
	const CvCombatMemberEntry* getCombatMember(BattleUnitTypes unitType) const;
	void setDamageMemberCount(int value);
	CvUnit* getUnit(BattleUnitTypes unitType) const;
	// TODO: Phase1 audit CvCombatInfo::getStrategicSite(BattleUnitTypes) const: UNVERIFIED; BE/object instructions 32/32; Civ5 changed/new UNVERIFIED.
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
protected:
	CvUnit* m_pUnits[BATTLE_UNIT_COUNT];
	CvStrategicSite* m_pStrategicSites[BATTLE_UNIT_COUNT];
	CvPlot* m_pTargetPlot;
	bool m_bAttackerAdvances;
	bool m_bAttackIsRanged;
	bool m_bAttackIsBombingMission;
	bool m_bAttackIsAirSweep;
	bool m_bAttackIsAttackOrbital;
	bool m_bDefenderRetaliates;
	bool m_bDefenderCaptured;
	int m_iNuclearDamageLevel;
	int m_iFinalDamage[BATTLE_UNIT_COUNT];
	int m_iDamageInflicted[BATTLE_UNIT_COUNT];
	int m_iFearDamageInflicted[BATTLE_UNIT_COUNT];
	int m_iExperienceChange[BATTLE_UNIT_COUNT];
	int m_iMaxExperienceAllowed[BATTLE_UNIT_COUNT];
	bool m_bInBorders[BATTLE_UNIT_COUNT];
	bool m_bUpdateGlobal[BATTLE_UNIT_COUNT];
	bool m_bVisualize;
	bool m_bAttackedAdvancedVis;
	unsigned int m_uiVisFXHash;
	CvCombatMemberEntry m_kCombatMembers[BATTLE_UNIT_COUNT];
	int m_iDamageMemberCount;
	CvCombatMemberEntry m_kDamageMembers[32];
};

void checkBattleUnitType(BattleUnitTypes unitType);

class CvMissionDefinition
{
public:
	// TODO: Phase1 audit CvMissionDefinition::CvMissionDefinition(): UNVERIFIED; BE/object instructions 9/9; Civ5 changed/new UNVERIFIED.
	CvMissionDefinition();
	MissionTypes getMissionType() const;
	void setMissionType(MissionTypes type);
	float getMissionTime() const;
	void setMissionTime(float time);
	CvUnit* getUnit(BattleUnitTypes unitType) const;
	void setUnit(BattleUnitTypes unitType, CvUnit* unit);
	const CvPlot* getPlot() const;
	void setPlot(const CvPlot* plot);
	const CvPlot* getSecondaryPlot() const;
	void setSecondaryPlot(const CvPlot* plot);
protected:
	MissionTypes m_eMissionType;
	CvUnit* m_aUnits[BATTLE_UNIT_COUNT];
	float m_fMissionTime;
	const CvPlot* m_pPlot;
	const CvPlot* m_pSecondaryPlot;
};

class CvAirMissionDefinition : public CvMissionDefinition
{
public:
	// TODO: Phase1 audit CvAirMissionDefinition::CvAirMissionDefinition(): UNVERIFIED; BE/object instructions 20/20; Civ5 changed/new UNVERIFIED.
	CvAirMissionDefinition();
	// TODO: Phase1 audit CvAirMissionDefinition::CvAirMissionDefinition(CvAirMissionDefinition const&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
	CvAirMissionDefinition(const CvAirMissionDefinition& other);
	int getDamage(BattleUnitTypes unitType) const;
	void setDamage(BattleUnitTypes unitType, int damage);
	// TODO: Phase1 audit CvAirMissionDefinition::isDead(BattleUnitTypes) const: UNVERIFIED; BE/object instructions 19/19; Civ5 changed/new UNVERIFIED.
	bool isDead(BattleUnitTypes unitType) const;
protected:
	int m_iDamage[BATTLE_UNIT_COUNT];
};

struct MissionData
{
	// TODO: Phase1 audit MissionData::MissionData(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
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

struct AlienUnitData;
// TODO: Phase1 audit operator<<(FDataStream&, VoteSelectionData const&): UNVERIFIED; BE/object instructions 16/16; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const VoteSelectionData&);
// TODO: Phase1 audit operator>>(FDataStream&, VoteSelectionData&): UNVERIFIED; BE/object instructions 16/16; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, VoteSelectionData&);
// TODO: Phase1 audit operator<<(FDataStream&, VoteTriggeredData const&): UNVERIFIED; BE/object instructions 16/16; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const VoteTriggeredData&);
// TODO: Phase1 audit operator>>(FDataStream&, VoteTriggeredData&): UNVERIFIED; BE/object instructions 16/16; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, VoteTriggeredData&);
// TODO: Phase1 audit operator<<(FDataStream&, BuildingYieldChange const&): MISMATCH; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const BuildingYieldChange&);
// TODO: Phase1 audit operator>>(FDataStream&, BuildingYieldChange&): MISMATCH; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, BuildingYieldChange&);
// TODO: Phase1 audit operator<<(FDataStream&, GenericYieldHealthChange const&): MISMATCH; BE/object instructions 29/29; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const GenericYieldHealthChange&);
// TODO: Phase1 audit operator>>(FDataStream&, GenericYieldHealthChange&): MISMATCH; BE/object instructions 29/29; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, GenericYieldHealthChange&);
// TODO: Phase1 audit operator<<(FDataStream&, BuildingGreatWork const&): MISMATCH; BE/object instructions 26/29; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const BuildingGreatWork&);
// TODO: Phase1 audit operator>>(FDataStream&, BuildingGreatWork&): MISMATCH; BE/object instructions 26/29; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, BuildingGreatWork&);
// TODO: Phase1 audit operator<<(FDataStream&, OrderData const&): MISMATCH; BE/object instructions 38/41; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const OrderData&);
// TODO: Phase1 audit operator>>(FDataStream&, OrderData&): MISMATCH; BE/object instructions 38/41; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, OrderData&);
// TODO: Phase1 audit operator<<(FDataStream&, PlotExtraYield const&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const PlotExtraYield&);
// TODO: Phase1 audit operator>>(FDataStream&, PlotExtraYield&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, PlotExtraYield&);
// TODO: Phase1 audit operator<<(FDataStream&, PlotExtraCost const&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const PlotExtraCost&);
// TODO: Phase1 audit operator>>(FDataStream&, PlotExtraCost&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, PlotExtraCost&);
// TODO: Phase1 audit operator<<(FDataStream&, AlienUnitData const&): UNVERIFIED; BE/object instructions 37/37; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const AlienUnitData&);
// TODO: Phase1 audit operator>>(FDataStream&, AlienUnitData&): UNVERIFIED; BE/object instructions 37/37; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, AlienUnitData&);
// TODO: Phase1 audit operator<<(FDataStream&, MissionData const&): MISMATCH; BE/object instructions 34/37; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const MissionData&);
// TODO: Phase1 audit operator>>(FDataStream&, MissionData&): MISMATCH; BE/object instructions 34/37; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, MissionData&);
