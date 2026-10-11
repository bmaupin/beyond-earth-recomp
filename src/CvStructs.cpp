#include "CvGameCoreDLLPCH.h"
#include "CvUnit.h"
#include "CvAliens.h"
#include "CvTypes.h"
#include "CvGameCoreEnumSerialization.h"
#include <algorithm>

// TODO: Phase1 audit operator <<(FDataStream &,const VoteTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const VoteTypes&);
// TODO: Phase1 audit operator >>(FDataStream &,VoteTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, VoteTypes&);
// TODO: Phase1 audit operator <<(FDataStream &,const VoteSourceTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const VoteSourceTypes&);
// TODO: Phase1 audit operator >>(FDataStream &,VoteSourceTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, VoteSourceTypes&);
// TODO: Phase1 audit operator <<(FDataStream &,const BuildingClassTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const BuildingClassTypes&);
// TODO: Phase1 audit operator >>(FDataStream &,BuildingClassTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, BuildingClassTypes&);
// TODO: Phase1 audit operator <<(FDataStream &,const OrderTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const OrderTypes&);
// TODO: Phase1 audit operator >>(FDataStream &,OrderTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, OrderTypes&);
// TODO: Phase1 audit operator <<(FDataStream &,const MissionTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const MissionTypes&);
// TODO: Phase1 audit operator >>(FDataStream &,MissionTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, MissionTypes&);

// TODO: Phase1 audit operator <<void SerializeToSequenceContainer(FDataStream &,std::vector<int> &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern template FDataStream& operator<< <int>(FDataStream&, const std::vector<int>&);
extern template void SerializeToSequenceContainer<int, std::vector<int> >(FDataStream&, std::vector<int>&);
extern CvPlayerAI* structPlayers asm("_ZN10CvPlayerAI10m_aPlayersE");

int VoteSelectionData::GetID() const { return iId; }
void VoteSelectionData::SetID(int id) { iId = id; }
// TODO: Phase1 audit VoteSelectionData::read(FDataStream&): MISMATCH; BE/object instructions 113/107; Civ5 changed/new UNVERIFIED.
void VoteSelectionData::read(FDataStream& stream)
{
	unsigned int version;
	stream >> version >> iId >> eVoteSource;
	unsigned int count;
	stream >> count;
	for(unsigned int i = 0; i < count; ++i)
	{
		VoteSelectionSubData option;
		stream >> option.eVote >> option.ePlayer >> option.iCityId >> option.eOtherPlayer >> option.strText;
		aVoteOptions.push_back(option);
	}
}
// TODO: Phase1 audit VoteSelectionData::write(FDataStream&) const: MISMATCH; BE/object instructions 61/66; Civ5 changed/new UNVERIFIED.
void VoteSelectionData::write(FDataStream& stream) const
{
	stream << 1 << iId << eVoteSource << static_cast<unsigned int>(aVoteOptions.size());
	for(std::vector<VoteSelectionSubData>::const_iterator i = aVoteOptions.begin(); i != aVoteOptions.end(); ++i)
		stream << i->eVote << i->ePlayer << i->iCityId << i->eOtherPlayer << i->strText;
}
// TODO: Phase1 audit operator>>(FDataStream&, VoteSelectionData&): UNVERIFIED; BE/object instructions 16/16; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, VoteSelectionData& value) { value.read(stream); return stream; }
// TODO: Phase1 audit operator<<(FDataStream&, VoteSelectionData const&): UNVERIFIED; BE/object instructions 16/16; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const VoteSelectionData& value) { value.write(stream); return stream; }

int VoteTriggeredData::GetID() const { return iId; }
void VoteTriggeredData::SetID(int id) { iId = id; }
// TODO: Phase1 audit VoteTriggeredData::read(FDataStream&): MISMATCH; BE/object instructions 45/46; Civ5 changed/new UNVERIFIED.
void VoteTriggeredData::read(FDataStream& stream)
{
	unsigned int version;
	stream >> version >> iId >> eVoteSource >> kVoteOption.eVote >> kVoteOption.ePlayer
		>> kVoteOption.iCityId >> kVoteOption.eOtherPlayer >> kVoteOption.strText;
}
// TODO: Phase1 audit VoteTriggeredData::write(FDataStream&) const: MISMATCH; BE/object instructions 46/47; Civ5 changed/new UNVERIFIED.
void VoteTriggeredData::write(FDataStream& stream) const
{
	stream << 1 << iId << eVoteSource << kVoteOption.eVote << kVoteOption.ePlayer
		<< kVoteOption.iCityId << kVoteOption.eOtherPlayer << kVoteOption.strText;
}
// TODO: Phase1 audit operator>>(FDataStream&, VoteTriggeredData&): UNVERIFIED; BE/object instructions 16/16; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, VoteTriggeredData& value) { value.read(stream); return stream; }
// TODO: Phase1 audit operator<<(FDataStream&, VoteTriggeredData const&): UNVERIFIED; BE/object instructions 16/16; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const VoteTriggeredData& value) { value.write(stream); return stream; }

// TODO: Phase1 audit operator>>(FDataStream&, BuildingYieldChange&): MISMATCH; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, BuildingYieldChange& value)
{
	stream >> value.eBuildingClass >> value.eYield >> value.iChange;
	return stream;
}
// TODO: Phase1 audit operator<<(FDataStream&, BuildingYieldChange const&): MISMATCH; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const BuildingYieldChange& value)
{
	stream << value.eBuildingClass << value.eYield << value.iChange;
	return stream;
}
// TODO: Phase1 audit operator>>(FDataStream&, GenericYieldHealthChange&): MISMATCH; BE/object instructions 29/29; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, GenericYieldHealthChange& value)
{
	for(int i = 0; i < 7; ++i) stream >> value.m_yieldChanges[i];
	stream >> value.m_healthChange;
	return stream;
}
// TODO: Phase1 audit operator<<(FDataStream&, GenericYieldHealthChange const&): MISMATCH; BE/object instructions 29/29; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const GenericYieldHealthChange& value)
{
	for(int i = 0; i < 7; ++i) stream << value.m_yieldChanges[i];
	stream << value.m_healthChange;
	return stream;
}
// TODO: Phase1 audit operator>>(FDataStream&, BuildingGreatWork&): MISMATCH; BE/object instructions 26/29; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, BuildingGreatWork& value)
{
	stream >> value.eBuildingClass >> value.iSlot >> value.iGreatWorkIndex;
	return stream;
}
// TODO: Phase1 audit operator<<(FDataStream&, BuildingGreatWork const&): MISMATCH; BE/object instructions 26/29; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const BuildingGreatWork& value)
{
	stream << value.eBuildingClass << value.iSlot << value.iGreatWorkIndex;
	return stream;
}

void checkBattleUnitType(BattleUnitTypes) {}

// TODO: Phase1 audit CvCombatInfo::CvCombatInfo(): UNVERIFIED; BE/object instructions 52/52; Civ5 changed/new UNVERIFIED.
CvCombatInfo::CvCombatInfo()
	: m_pTargetPlot(NULL), m_bAttackerAdvances(false), m_bAttackIsRanged(false),
	  m_bAttackIsBombingMission(false), m_bAttackIsAirSweep(false), m_bAttackIsAttackOrbital(false),
	  m_bDefenderRetaliates(true), m_bDefenderCaptured(false), m_iNuclearDamageLevel(0),
	  m_bVisualize(false), m_bAttackedAdvancedVis(false), m_uiVisFXHash(static_cast<unsigned int>(-1)),
	  m_iDamageMemberCount(0)
{
	for(int i = 0; i < BATTLE_UNIT_COUNT; ++i)
	{
		m_pUnits[i] = NULL;
		m_pStrategicSites[i] = NULL;
		m_iFinalDamage[i] = 0;
		m_iDamageInflicted[i] = 0;
		m_iFearDamageInflicted[i] = 0;
		m_iExperienceChange[i] = 0;
		m_iMaxExperienceAllowed[i] = 0;
		m_bInBorders[i] = false;
		m_bUpdateGlobal[i] = false;
	}
}
CvCombatInfo& CvCombatInfo::operator=(const CvCombatInfo& other)
{
	m_pTargetPlot = other.m_pTargetPlot;
	m_bAttackerAdvances = other.m_bAttackerAdvances;
	m_bAttackIsRanged = other.m_bAttackIsRanged;
	m_bAttackIsBombingMission = other.m_bAttackIsBombingMission;
	m_bAttackIsAirSweep = other.m_bAttackIsAirSweep;
	m_bAttackIsAttackOrbital = other.m_bAttackIsAttackOrbital;
	m_bDefenderCaptured = other.m_bDefenderCaptured;
	m_bDefenderRetaliates = other.m_bDefenderRetaliates;
	m_iNuclearDamageLevel = other.m_iNuclearDamageLevel;
	m_bVisualize = other.m_bVisualize;
	m_bAttackedAdvancedVis = other.m_bAttackedAdvancedVis;
	m_uiVisFXHash = other.m_uiVisFXHash;
	// The target does not copy strategic sites or primary combat-member records.
	for(int i = 0; i < BATTLE_UNIT_COUNT; ++i)
	{
		m_pUnits[i] = other.m_pUnits[i];
		m_iFinalDamage[i] = other.m_iFinalDamage[i];
		m_iDamageInflicted[i] = other.m_iDamageInflicted[i];
		m_iFearDamageInflicted[i] = other.m_iFearDamageInflicted[i];
		m_iExperienceChange[i] = other.m_iExperienceChange[i];
		m_iMaxExperienceAllowed[i] = other.m_iMaxExperienceAllowed[i];
		m_bInBorders[i] = other.m_bInBorders[i];
		m_bUpdateGlobal[i] = other.m_bUpdateGlobal[i];
	}
	m_iDamageMemberCount = other.m_iDamageMemberCount;
	for(int i = 0; i < m_iDamageMemberCount; ++i) m_kDamageMembers[i] = other.m_kDamageMembers[i];
	return *this;
}
CvUnit* CvCombatInfo::getUnit(BattleUnitTypes type) const { return m_pUnits[type]; }
void CvCombatInfo::setUnit(BattleUnitTypes type, CvUnit* unit) { m_pUnits[type] = unit; }
// TODO: Phase1 audit CvCombatInfo::getStrategicSite(BattleUnitTypes) const: UNVERIFIED; BE/object instructions 32/32; Civ5 changed/new UNVERIFIED.
CvStrategicSite* CvCombatInfo::getStrategicSite(BattleUnitTypes type) const
{
	if(m_pStrategicSites[type]) return m_pStrategicSites[type];
	if(type == BATTLE_UNIT_DEFENDER && m_pTargetPlot && m_pTargetPlot->getPlotStrategicSite())
		return m_pTargetPlot->getPlotStrategicSite();
	return NULL;
}
void CvCombatInfo::setStrategicSite(BattleUnitTypes type, CvStrategicSite* site) { m_pStrategicSites[type] = site; }
CvPlot* CvCombatInfo::getPlot() const { return m_pTargetPlot; }
void CvCombatInfo::setPlot(CvPlot* plot) { m_pTargetPlot = plot; }
bool CvCombatInfo::getAttackerAdvances() const { return m_bAttackerAdvances; }
void CvCombatInfo::setAttackerAdvances(bool value) { m_bAttackerAdvances = value; }
bool CvCombatInfo::getDefenderRetaliates() const { return m_bDefenderRetaliates; }
void CvCombatInfo::setDefenderRetaliates(bool value) { m_bDefenderRetaliates = value; }
bool CvCombatInfo::getAttackIsRanged() const { return m_bAttackIsRanged; }
void CvCombatInfo::setAttackIsRanged(bool value) { m_bAttackIsRanged = value; }
bool CvCombatInfo::getAttackIsBombingMission() const { return m_bAttackIsBombingMission; }
void CvCombatInfo::setAttackIsBombingMission(bool value) { m_bAttackIsBombingMission = value; }
bool CvCombatInfo::getAttackIsAirSweep() const { return m_bAttackIsAirSweep; }
void CvCombatInfo::setAttackIsAirSweep(bool value) { m_bAttackIsAirSweep = value; }
bool CvCombatInfo::getAttackIsAttackOrbital() const { return m_bAttackIsAttackOrbital; }
void CvCombatInfo::setAttackIsAttackOrbital(bool value) { m_bAttackIsAttackOrbital = value; }
unsigned int CvCombatInfo::getVisFXHash() const { return m_uiVisFXHash; }
void CvCombatInfo::setVisFXHash(unsigned int value) { m_uiVisFXHash = value; }
bool CvCombatInfo::getDefenderCaptured() const { return m_bDefenderCaptured; }
void CvCombatInfo::setDefenderCaptured(bool value) { m_bDefenderCaptured = value; }
int CvCombatInfo::getDamageInflicted(BattleUnitTypes type) const { return m_iDamageInflicted[type]; }
void CvCombatInfo::setDamageInflicted(BattleUnitTypes type, int value) { m_iDamageInflicted[type] = value; }
int CvCombatInfo::getFinalDamage(BattleUnitTypes type) const { return m_iFinalDamage[type]; }
void CvCombatInfo::setFinalDamage(BattleUnitTypes type, int value) { m_iFinalDamage[type] = value; }
int CvCombatInfo::getFearDamageInflicted(BattleUnitTypes type) const { return m_iFearDamageInflicted[type]; }
void CvCombatInfo::setFearDamageInflicted(BattleUnitTypes type, int value) { m_iFearDamageInflicted[type] = value; }
int CvCombatInfo::getExperience(BattleUnitTypes type) const { return m_iExperienceChange[type]; }
void CvCombatInfo::setExperience(BattleUnitTypes type, int value) { m_iExperienceChange[type] = value; }
int CvCombatInfo::getMaxExperienceAllowed(BattleUnitTypes type) const { return m_iMaxExperienceAllowed[type]; }
void CvCombatInfo::setMaxExperienceAllowed(BattleUnitTypes type, int value) { m_iMaxExperienceAllowed[type] = value; }
bool CvCombatInfo::getInBorders(BattleUnitTypes type) const { return m_bInBorders[type]; }
void CvCombatInfo::setInBorders(BattleUnitTypes type, bool value) { m_bInBorders[type] = value; }
bool CvCombatInfo::getUpdateGlobal(BattleUnitTypes type) const { return m_bUpdateGlobal[type]; }
void CvCombatInfo::setUpdateGlobal(BattleUnitTypes type, bool value) { m_bUpdateGlobal[type] = value; }
bool CvCombatInfo::getVisualizeCombat() const { return m_bVisualize; }
void CvCombatInfo::setVisualizeCombat(bool value) { m_bVisualize = value; }
bool CvCombatInfo::getAttackerAdvancedVisualization() const { return m_bAttackedAdvancedVis; }
void CvCombatInfo::setAttackerAdvancedVisualization(bool value) { m_bAttackedAdvancedVis = value; }
bool CvCombatInfo::getAttackIsNuclear() const { return m_iNuclearDamageLevel > 0; }
int CvCombatInfo::getAttackNuclearLevel() const { return m_iNuclearDamageLevel; }
void CvCombatInfo::setAttackNuclearLevel(int value) { m_iNuclearDamageLevel = value; }
// TODO: Phase1 audit CvCombatInfo::getCombatMember(BattleUnitTypes) const: MISMATCH; BE/object instructions 8/4; Civ5 changed/new UNVERIFIED.
const CvCombatMemberEntry* CvCombatInfo::getCombatMember(BattleUnitTypes type) const { return &m_kCombatMembers[type]; }
CvCombatMemberEntry* CvCombatInfo::getDamageMembers() { return m_kDamageMembers; }
const CvCombatMemberEntry* CvCombatInfo::getDamageMembers() const { return m_kDamageMembers; }
int CvCombatInfo::getDamageMemberCount() const { return m_iDamageMemberCount; }
int CvCombatInfo::getMaxDamageMemberCount() const { return 32; }
void CvCombatInfo::setDamageMemberCount(int value) { m_iDamageMemberCount = std::min(value, 32); }

// TODO: Phase1 audit CvMissionDefinition::CvMissionDefinition(): UNVERIFIED; BE/object instructions 9/9; Civ5 changed/new UNVERIFIED.
CvMissionDefinition::CvMissionDefinition()
	: m_eMissionType(NO_MISSION), m_fMissionTime(0), m_pPlot(NULL), m_pSecondaryPlot(NULL)
{
	for(int i = 0; i < BATTLE_UNIT_COUNT; ++i) m_aUnits[i] = NULL;
}
MissionTypes CvMissionDefinition::getMissionType() const { return m_eMissionType; }
void CvMissionDefinition::setMissionType(MissionTypes type) { m_eMissionType = type; }
float CvMissionDefinition::getMissionTime() const { return m_fMissionTime; }
void CvMissionDefinition::setMissionTime(float time) { m_fMissionTime = time; }
CvUnit* CvMissionDefinition::getUnit(BattleUnitTypes type) const { return m_aUnits[type]; }
void CvMissionDefinition::setUnit(BattleUnitTypes type, CvUnit* unit) { m_aUnits[type] = unit; }
const CvPlot* CvMissionDefinition::getPlot() const { return m_pPlot; }
void CvMissionDefinition::setPlot(const CvPlot* plot) { m_pPlot = plot; }
const CvPlot* CvMissionDefinition::getSecondaryPlot() const { return m_pSecondaryPlot; }
void CvMissionDefinition::setSecondaryPlot(const CvPlot* plot) { m_pSecondaryPlot = plot; }
// The target leaves damage uninitialized and retains a null secondary plot when copying.
// TODO: Phase1 audit CvAirMissionDefinition::CvAirMissionDefinition(): UNVERIFIED; BE/object instructions 20/20; Civ5 changed/new UNVERIFIED.
CvAirMissionDefinition::CvAirMissionDefinition() { m_eMissionType = CvTypes::getMISSION_AIRPATROL(); }
// TODO: Phase1 audit CvAirMissionDefinition::CvAirMissionDefinition(CvAirMissionDefinition const&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
CvAirMissionDefinition::CvAirMissionDefinition(const CvAirMissionDefinition& other)
{
	m_fMissionTime = other.m_fMissionTime;
	m_eMissionType = other.m_eMissionType;
	m_pPlot = other.m_pPlot;
	for(int i = 0; i < BATTLE_UNIT_COUNT; ++i)
	{
		m_iDamage[i] = other.m_iDamage[i];
		m_aUnits[i] = other.m_aUnits[i];
	}
}
int CvAirMissionDefinition::getDamage(BattleUnitTypes type) const { return m_iDamage[type]; }
void CvAirMissionDefinition::setDamage(BattleUnitTypes type, int damage) { m_iDamage[type] = damage; }
// TODO: Phase1 audit CvAirMissionDefinition::isDead(BattleUnitTypes) const: UNVERIFIED; BE/object instructions 19/19; Civ5 changed/new UNVERIFIED.
bool CvAirMissionDefinition::isDead(BattleUnitTypes type) const { return m_iDamage[type] >= m_aUnits[type]->GetMaxHitPoints(); }

// TODO: Phase1 audit AlienUnitData::IsColossal() const: MISMATCH; BE/object instructions 29/30; Civ5 changed/new UNVERIFIED. Raw player/team stride or member access requires authentic layout (no ABI shortcut).
bool AlienUnitData::IsColossal() const
{
	CvPlayer* player = reinterpret_cast<CvPlayer*>(reinterpret_cast<char*>(structPlayers) + static_cast<unsigned int>(m_eOwner) * 0xf598u);
	CvUnit* unit = player->getUnit(m_iUnitID);
	return unit ? GC.getUnitInfo(unit->getUnitType())->IsAlienColossus() : false;
}
// TODO: Phase1 audit operator<<(FDataStream&, OrderData const&): MISMATCH; BE/object instructions 38/41; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const OrderData& value)
{
	stream << value.eOrderType << value.iPlotIndex << value.iSpecificType << value.iData2 << value.bSave << value.bRush;
	return stream;
}
// TODO: Phase1 audit operator>>(FDataStream&, OrderData&): MISMATCH; BE/object instructions 38/41; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, OrderData& value)
{
	stream >> value.eOrderType >> value.iPlotIndex >> value.iSpecificType >> value.iData2 >> value.bSave >> value.bRush;
	return stream;
}
// TODO: Phase1 audit operator<<(FDataStream&, PlotExtraYield const&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const PlotExtraYield& value)
{
	stream << value.m_iX << value.m_iY << value.m_aeExtraYield;
	return stream;
}
// TODO: Phase1 audit operator>>(FDataStream&, PlotExtraYield&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, PlotExtraYield& value)
{
	stream >> value.m_iX >> value.m_iY;
	SerializeToSequenceContainer<int, std::vector<int> >(stream, value.m_aeExtraYield);
	return stream;
}
// TODO: Phase1 audit operator<<(FDataStream&, PlotExtraCost const&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const PlotExtraCost& value)
{
	stream << value.m_iX << value.m_iY << value.m_iCost;
	return stream;
}
// TODO: Phase1 audit operator>>(FDataStream&, PlotExtraCost&): UNVERIFIED; BE/object instructions 26/26; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, PlotExtraCost& value)
{
	stream >> value.m_iX >> value.m_iY >> value.m_iCost;
	return stream;
}
// TODO: Phase1 audit operator<<(FDataStream&, AlienUnitData const&): UNVERIFIED; BE/object instructions 37/37; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const AlienUnitData& value)
{
	const int owner = static_cast<int>(value.m_eOwner);
	stream << owner << value.m_iUnitID << value.m_iTurnsSinceSpawn << value.m_iLastPlotIndex << value.m_bActive;
	return stream;
}
// TODO: Phase1 audit operator>>(FDataStream&, AlienUnitData&): UNVERIFIED; BE/object instructions 37/37; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, AlienUnitData& value)
{
	int owner;
	stream >> owner;
	value.m_eOwner = static_cast<PlayerTypes>(owner);
	stream >> value.m_iUnitID >> value.m_iTurnsSinceSpawn >> value.m_iLastPlotIndex >> value.m_bActive;
	return stream;
}
// TODO: Phase1 audit operator<<(FDataStream&, MissionData const&): MISMATCH; BE/object instructions 34/37; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream& stream, const MissionData& value)
{
	stream << value.eMissionType << value.iData1 << value.iData2 << value.iFlags << value.iPushTurn;
	return stream;
}
// TODO: Phase1 audit operator>>(FDataStream&, MissionData&): MISMATCH; BE/object instructions 34/37; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream& stream, MissionData& value)
{
	stream >> value.eMissionType >> value.iData1 >> value.iData2 >> value.iFlags >> value.iPushTurn;
	return stream;
}
