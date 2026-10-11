#include "CvGameCoreDLLPCH.h"
#include "CvAliens.h"
#include "CvUnit.h"

short* CvAliens::m_aiPlotAlienNestSpawnCounter = NULL;
short* CvAliens::m_aiPlotAlienNestNumUnitsSpawned = NULL;
int CvAliens::m_globalAggressionLevel = 0;
int CvAliens::m_totalPlayerUnitsKilled = 0;
int CvAliens::m_totalLandUnitsLost = 0;
int CvAliens::m_totalSeaUnitsLost = 0;
int CvAliens::m_totalLandDamageDealt = 0;
int CvAliens::m_totalSeaDamageDealt = 0;
int CvAliens::m_totalLandDamageReceived = 0;
int CvAliens::m_totalSeaDamageReceived = 0;
std::map<IDInfo, AlienUnitData> CvAliens::m_alienUnitData;
std::vector<int> CvAliens::m_nestSites;
std::map<PlayerTypes, float> CvAliens::m_playerOpinionLevels;
std::map<PlayerTypes, bool> CvAliens::m_playerHostilityFlags;
std::map<IDInfo, int> CvAliens::m_aggroAttackTargets;
std::map<int, int> CvAliens::m_dangerPlots;
std::map<int, int> CvAliens::m_thumperPlots;
std::map<int, int> CvAliens::m_repulsorPlots;
std::map<int, int> CvAliens::m_attractorPlots;
std::map<UnitTypes, std::map<TeamTypes, bool> > CvAliens::m_unitTypesRevealedToTeam;
std::vector<IDInfo> CvAliens::m_activeThumperUnits;
std::vector<DirectionTypes> CvAliens::m_aeValidAlienSpawnDirections;
void* CvAliens::m_luaContext = NULL;

namespace
{
const float kHostileOpinion = -1.0f;
const float kFriendlyOpinion = 1.0f;

// TODO(Phase1 audit): __anon2dec9a220111::OpinionFromValue UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
AIAlienOpinion OpinionFromValue(float value)
{
	return value < 0.0f ? AI_ALIEN_OPINION_HOSTILE :
		(value > 0.0f ? AI_ALIEN_OPINION_FRIENDLY : AI_ALIEN_OPINION_NEUTRAL);
}
}

// TODO(Phase1 audit): CvAliens::Init MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=318; Civ5 changed/new=UNVERIFIED.
void CvAliens::Init()
{
	m_aeValidAlienSpawnDirections.clear();
	for (int i = 0; i < NUM_DIRECTION_TYPES; ++i)
		m_aeValidAlienSpawnDirections.push_back((DirectionTypes)i);
	NewGameInit();
}

// TODO(Phase1 audit): CvAliens::Uninit MISMATCH: Instruction 4 differs before first target reference: object [sub    $0x10,%esp] vs BE [sub    $0x20,%esp]; BE instructions=171; Civ5 changed/new=UNVERIFIED.
void CvAliens::Uninit()
{
	delete[] m_aiPlotAlienNestSpawnCounter;
	delete[] m_aiPlotAlienNestNumUnitsSpawned;
	m_aiPlotAlienNestSpawnCounter = NULL;
	m_aiPlotAlienNestNumUnitsSpawned = NULL;
	m_alienUnitData.clear();
	m_nestSites.clear();
	m_playerOpinionLevels.clear();
	m_playerHostilityFlags.clear();
	m_aggroAttackTargets.clear();
	m_dangerPlots.clear();
	m_thumperPlots.clear();
	m_repulsorPlots.clear();
	m_attractorPlots.clear();
	m_unitTypesRevealedToTeam.clear();
	m_activeThumperUnits.clear();
	m_aeValidAlienSpawnDirections.clear();
	m_luaContext = NULL;
}

// TODO(Phase1 audit): CvAliens::NewGameInit MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=367; Civ5 changed/new=UNVERIFIED.
void CvAliens::NewGameInit()
{
	m_globalAggressionLevel = 0;
	m_totalPlayerUnitsKilled = 0;
	m_totalLandUnitsLost = 0;
	m_totalSeaUnitsLost = 0;
	m_totalLandDamageDealt = 0;
	m_totalSeaDamageDealt = 0;
	m_totalLandDamageReceived = 0;
	m_totalSeaDamageReceived = 0;
	m_alienUnitData.clear();
	m_nestSites.clear();
	m_playerOpinionLevels.clear();
	m_playerHostilityFlags.clear();
	m_aggroAttackTargets.clear();
	m_dangerPlots.clear();
	m_thumperPlots.clear();
	m_repulsorPlots.clear();
	m_attractorPlots.clear();
	m_unitTypesRevealedToTeam.clear();
	m_activeThumperUnits.clear();
}

// TODO(Phase1 audit): CvAliens::DoTurn MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=72; Civ5 changed/new=UNVERIFIED.
void CvAliens::DoTurn()
{
	UpdateDangerPlots();
	UpdateThumperPlots();
	UpdateRepulsorPlots();
	UpdateAggroLevels();
	UpdateOpinionLevels();
	UpdateAggressionLevels();
	DoNests();
	DoUnits();
}

// TODO(Phase1 audit): CvAliens::CreateNest MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=159; Civ5 changed/new=UNVERIFIED.
void CvAliens::CreateNest(CvPlot& plot, bool)
{
	const int plotIndex = plot.GetPlotIndex();
	for (std::vector<int>::const_iterator it = m_nestSites.begin(); it != m_nestSites.end(); ++it)
		if (*it == plotIndex)
			return;
	m_nestSites.push_back(plotIndex);
	if (m_aiPlotAlienNestSpawnCounter)
		m_aiPlotAlienNestSpawnCounter[plotIndex] = 0;
	if (m_aiPlotAlienNestNumUnitsSpawned)
		m_aiPlotAlienNestNumUnitsSpawned[plotIndex] = 0;
}

// TODO(Phase1 audit): CvAliens::RemoveNest MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x1c,%esp] vs BE [sub    $0x2c,%esp]; BE instructions=101; Civ5 changed/new=UNVERIFIED.
void CvAliens::RemoveNest(CvPlot& plot, PlayerTypes)
{
	const int plotIndex = plot.GetPlotIndex();
	for (std::vector<int>::iterator it = m_nestSites.begin(); it != m_nestSites.end(); ++it)
	{
		if (*it == plotIndex)
		{
			m_nestSites.erase(it);
			break;
		}
	}
	if (m_aiPlotAlienNestSpawnCounter)
		m_aiPlotAlienNestSpawnCounter[plotIndex] = 0;
	if (m_aiPlotAlienNestNumUnitsSpawned)
		m_aiPlotAlienNestNumUnitsSpawned[plotIndex] = 0;
}

// TODO(Phase1 audit): CvAliens::SpawnNormalUnitFromNest MISMATCH: First instruction opcode differs: object call, BE push; BE instructions=404; Civ5 changed/new=UNVERIFIED.
void CvAliens::SpawnNormalUnitFromNest(CvPlot* plot, bool, bool)
{
	if (plot)
		UpdateNestSpawnCounter(plot);
}

// TODO(Phase1 audit): CvAliens::AttemptHiddenSpawn MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=332; Civ5 changed/new=UNVERIFIED.
bool CvAliens::AttemptHiddenSpawn(UnitTypes) { return false; }
// TODO(Phase1 audit): CvAliens::AttemptWildAreaSpawn MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=75; Civ5 changed/new=UNVERIFIED.
bool CvAliens::AttemptWildAreaSpawn(UnitTypes) { return false; }
// TODO(Phase1 audit): CvAliens::DoAlienKillCivilian MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=119; Civ5 changed/new=UNVERIFIED.
void CvAliens::DoAlienKillCivilian(const CvUnit&, CvUnit&) {}
// TODO(Phase1 audit): CvAliens::DoCityThumperStrike MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=383; Civ5 changed/new=UNVERIFIED.
void CvAliens::DoCityThumperStrike(const CvCity&, int, int, int) {}

// TODO(Phase1 audit): CvAliens::AddRepelEffectToPlotRange MISMATCH: Instruction 1 differs before first target reference: object [push   %ebp] vs BE [push   %ebx]; BE instructions=20; Civ5 changed/new=UNVERIFIED.
void CvAliens::AddRepelEffectToPlotRange(PlayerTypes player, const CvPlot& plot, int range)
{
	MarkRepulsorPlotsInRange(player, plot.getX(), plot.getY(), range);
}

// TODO(Phase1 audit): CvAliens::MarkRepulsorPlotsInRange MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x2c,%esp] vs BE [sub    $0x3c,%esp]; BE instructions=213; Civ5 changed/new=UNVERIFIED.
void CvAliens::MarkRepulsorPlotsInRange(PlayerTypes, int x, int y, int range)
{
	for (int dx = -range; dx <= range; ++dx)
		for (int dy = -range; dy <= range; ++dy)
			if (dx * dx + dy * dy <= range * range)
				++m_repulsorPlots[(x + dx) | ((y + dy) << 16)];
}

// TODO(Phase1 audit): CvAliens::AddAttractorPlot MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=35; Civ5 changed/new=UNVERIFIED.
void CvAliens::AddAttractorPlot(PlayerTypes, const CvPlot& plot, int strength)
{
	m_attractorPlots[plot.GetPlotIndex()] += strength;
}

// TODO(Phase1 audit): CvAliens::ClearAttractorPlot MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x18,%esp] vs BE [push   %esi]; BE instructions=34; Civ5 changed/new=UNVERIFIED.
void CvAliens::ClearAttractorPlot(PlayerTypes, const CvPlot& plot)
{
	m_attractorPlots.erase(plot.GetPlotIndex());
}

// TODO(Phase1 audit): CvAliens::IsPlotValidForAlienNest MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=220; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsPlotValidForAlienNest(const CvPlot& plot)
{
	return !plot.isWater() && !plot.isImpassable() && plot.getOwner() == NO_PLAYER;
}

// TODO(Phase1 audit): CvAliens::IsPlotValidForAlienUnit MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=101; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsPlotValidForAlienUnit(const CvPlot& plot, const CvUnit& unit, bool)
{
	if (plot.isImpassable() || unit.IsOrbitalUnit())
		return false;
	return unit.getDomainType() == (DomainTypes)1 ? plot.isWater() : !plot.isWater();
}

// TODO(Phase1 audit): CvAliens::GetOpinionForPlayer MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=43; Civ5 changed/new=UNVERIFIED.
AIAlienOpinion CvAliens::GetOpinionForPlayer(PlayerTypes player)
{
	return OpinionFromValue(GetOpinionValueForPlayer(player));
}

// TODO(Phase1 audit): CvAliens::GetOpinionValueForPlayer MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [sub    $0x18,%esp]; BE instructions=16; Civ5 changed/new=UNVERIFIED.
float CvAliens::GetOpinionValueForPlayer(PlayerTypes player)
{
	std::map<PlayerTypes, float>::const_iterator it = m_playerOpinionLevels.find(player);
	return it == m_playerOpinionLevels.end() ? 0.0f : it->second;
}

// TODO(Phase1 audit): CvAliens::SetOpinionForPlayer MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x18,%esp] vs BE [push   %edi]; BE instructions=55; Civ5 changed/new=UNVERIFIED.
void CvAliens::SetOpinionForPlayer(PlayerTypes player, AIAlienOpinion opinion)
{
	SetOpinionValueForPlayer(player, opinion == AI_ALIEN_OPINION_HOSTILE ? kHostileOpinion :
		(opinion == AI_ALIEN_OPINION_FRIENDLY ? kFriendlyOpinion : 0.0f));
}

// TODO(Phase1 audit): CvAliens::SetOpinionValueForPlayer MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x18,%esp] vs BE [push   %edi]; BE instructions=39; Civ5 changed/new=UNVERIFIED.
void CvAliens::SetOpinionValueForPlayer(PlayerTypes player, float value)
{
	m_playerOpinionLevels[player] = value;
	OnPlayerOpinionChanged(player);
}

// TODO(Phase1 audit): CvAliens::GetGlobalOpinion MISMATCH: First instruction opcode differs: object push, BE call; BE instructions=17; Civ5 changed/new=UNVERIFIED.
AIAlienOpinion CvAliens::GetGlobalOpinion()
{
	if (m_playerOpinionLevels.empty())
		return AI_ALIEN_OPINION_NEUTRAL;
	float total = 0.0f;
	for (std::map<PlayerTypes, float>::const_iterator it = m_playerOpinionLevels.begin(); it != m_playerOpinionLevels.end(); ++it)
		total += it->second;
	return OpinionFromValue(total / m_playerOpinionLevels.size());
}

// TODO(Phase1 audit): CvAliens::SetHostilityFlagForPlayer UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
void CvAliens::SetHostilityFlagForPlayer(PlayerTypes player, bool hostile)
{
	m_playerHostilityFlags[player] = hostile;
}

// TODO(Phase1 audit): CvAliens::GetHostilityFlagForPlayer MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=33; Civ5 changed/new=UNVERIFIED.
bool CvAliens::GetHostilityFlagForPlayer(PlayerTypes player)
{
	std::map<PlayerTypes, bool>::const_iterator it = m_playerHostilityFlags.find(player);
	return it != m_playerHostilityFlags.end() && it->second;
}

// TODO(Phase1 audit): CvAliens::IsHostileToPlayer MISMATCH: Instruction 3 differs before first target reference: object [sub    $0x14,%esp] vs BE [push   %eax]; BE instructions=27; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsHostileToPlayer(PlayerTypes player)
{
	return GetHostilityFlagForPlayer(player) || GetOpinionForPlayer(player) == AI_ALIEN_OPINION_HOSTILE;
}

// TODO(Phase1 audit): CvAliens::GetDangerValueAtPlot MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=50; Civ5 changed/new=UNVERIFIED.
int CvAliens::GetDangerValueAtPlot(int plotIndex)
{
	std::map<int, int>::const_iterator it = m_dangerPlots.find(plotIndex);
	return it == m_dangerPlots.end() ? 0 : it->second;
}

// TODO(Phase1 audit): CvAliens::GetRepelChanceAtPlot MISMATCH: Instruction 3 differs before first target reference: object [sub    $0x24,%esp] vs BE [push   %eax]; BE instructions=25; Civ5 changed/new=UNVERIFIED.
int CvAliens::GetRepelChanceAtPlot(int plotIndex)
{
	std::map<int, int>::const_iterator it = m_repulsorPlots.find(plotIndex);
	return it == m_repulsorPlots.end() ? 0 : it->second;
}

// TODO(Phase1 audit): CvAliens::OnAlienUnitSetXY MISMATCH: First instruction opcode differs: object call, BE push; BE instructions=39; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnAlienUnitSetXY(CvUnit& unit, CvPlot& plot)
{
	AddAlienUnitData(unit, plot);
}

// TODO(Phase1 audit): CvAliens::OnOrbitalAlienAttractionChanged MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [sub    $0x18,%esp]; BE instructions=19; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnOrbitalAlienAttractionChanged(PlayerTypes player, const CvPlot& plot, int strength, bool active)
{
	if (active)
		AddAttractorPlot(player, plot, strength);
	else
		ClearAttractorPlot(player, plot);
}

// TODO(Phase1 audit): CvAliens::GetAlienMiasmaHealRate MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=33; Civ5 changed/new=UNVERIFIED.
int CvAliens::GetAlienMiasmaHealRate() { return 0; }

// TODO(Phase1 audit): CvAliens::PlotHasNonsentient MISMATCH: Instruction 2 differs before first target reference: object [push   %edi] vs BE [sub    $0x8,%esp]; BE instructions=33; Civ5 changed/new=UNVERIFIED.
bool CvAliens::PlotHasNonsentient(const CvPlot& plot)
{
	for (int i = 0; i < plot.getNumUnits(); ++i)
	{
		CvUnit* unit = plot.getUnitByIndex(i);
		if (unit && unit->isAlien())
			return true;
	}
	return false;
}

// TODO(Phase1 audit): CvAliens::GetAllActiveThumperUnitsForCity MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=72; Civ5 changed/new=UNVERIFIED.
std::vector<CvUnit*> CvAliens::GetAllActiveThumperUnitsForCity(const CvCity&) { return std::vector<CvUnit*>(); }
// TODO(Phase1 audit): CvAliens::Read MISMATCH: First instruction opcode differs: object call, BE push; BE instructions=150; Civ5 changed/new=UNVERIFIED.
void CvAliens::Read(FDataStream&, unsigned int) { NewGameInit(); }
// TODO(Phase1 audit): CvAliens::Write MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=120; Civ5 changed/new=UNVERIFIED.
void CvAliens::Write(FDataStream&) {}
// TODO(Phase1 audit): CvAliens::OnNestAttacked MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=93; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnNestAttacked(AlienNestAttackedEvent&) {}
// TODO(Phase1 audit): CvAliens::OnNestDestroyed MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=199; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnNestDestroyed(AlienNestClearedEvent&) {}
// TODO(Phase1 audit): CvAliens::OnUnitCreated MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=22; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnUnitCreated(UnitCreatedEvent&) {}
// TODO(Phase1 audit): CvAliens::OnUnitAttacked MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=533; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnUnitAttacked(UnitAttackedEvent&) {}
// TODO(Phase1 audit): CvAliens::OnUnitKilled MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=308; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnUnitKilled(UnitKilledEvent&) {}
// TODO(Phase1 audit): CvAliens::OnOutpostFounded MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=136; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnOutpostFounded(OutpostFoundedEvent&) {}
// TODO(Phase1 audit): CvAliens::OnCityMoved MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=46; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnCityMoved(CityMovedEvent&) {}
// TODO(Phase1 audit): CvAliens::OnCityKilled MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=50; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnCityKilled(CityKilledEvent&) {}
// TODO(Phase1 audit): CvAliens::OnBuildFinished MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=38; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnBuildFinished(BuildFinishedEvent&) {}
// TODO(Phase1 audit): CvAliens::LogStory MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=97; Civ5 changed/new=UNVERIFIED.
void CvAliens::LogStory(CvString) {}

// TODO(Phase1 audit): CvAliens::DoNests MISMATCH: Instruction 1 differs before first target reference: object [push   %esi] vs BE [push   %ebp]; BE instructions=145; Civ5 changed/new=UNVERIFIED.
void CvAliens::DoNests()
{
	for (std::vector<int>::const_iterator it = m_nestSites.begin(); it != m_nestSites.end(); ++it)
		if (m_aiPlotAlienNestSpawnCounter)
			++m_aiPlotAlienNestSpawnCounter[*it];
}

// TODO(Phase1 audit): CvAliens::IsPlotValidForAnyAlienSpawn MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=61; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsPlotValidForAnyAlienSpawn(const CvPlot& plot, bool water)
{
	return !plot.isImpassable() && plot.isWater() == water && !HasPlotActiveAlienRepel(plot);
}

// TODO(Phase1 audit): CvAliens::CreateNewAlienUnitAtPlot MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=181; Civ5 changed/new=UNVERIFIED.
bool CvAliens::CreateNewAlienUnitAtPlot(CvPlot&, bool) { return false; }
// TODO(Phase1 audit): CvAliens::LogData MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=198; Civ5 changed/new=UNVERIFIED.
void CvAliens::LogData(CvString) {}

// TODO(Phase1 audit): CvAliens::UpdateDangerPlots UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=52; Civ5 changed/new=UNVERIFIED.
void CvAliens::UpdateDangerPlots()
{
	for (std::map<int, int>::iterator it = m_dangerPlots.begin(); it != m_dangerPlots.end();)
	{
		if (--it->second <= 0)
			m_dangerPlots.erase(it++);
		else
			++it;
	}
}

// TODO(Phase1 audit): CvAliens::UpdateThumperPlots MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=52; Civ5 changed/new=UNVERIFIED.
void CvAliens::UpdateThumperPlots() {}
// TODO(Phase1 audit): CvAliens::UpdateRepulsorPlots MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=79; Civ5 changed/new=UNVERIFIED.
void CvAliens::UpdateRepulsorPlots() {}

// TODO(Phase1 audit): CvAliens::UpdateAggroLevels MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x1c,%esp] vs BE [sub    $0x2c,%esp]; BE instructions=52; Civ5 changed/new=UNVERIFIED.
void CvAliens::UpdateAggroLevels()
{
	for (std::map<IDInfo, int>::iterator it = m_aggroAttackTargets.begin(); it != m_aggroAttackTargets.end();)
	{
		if (--it->second <= 0)
			m_aggroAttackTargets.erase(it++);
		else
			++it;
	}
}

// TODO(Phase1 audit): CvAliens::UpdateOpinionLevels MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=84; Civ5 changed/new=UNVERIFIED.
void CvAliens::UpdateOpinionLevels() {}
// TODO(Phase1 audit): CvAliens::UpdateAggressionLevels MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=41; Civ5 changed/new=UNVERIFIED.
void CvAliens::UpdateAggressionLevels() {}

// TODO(Phase1 audit): CvAliens::DoUnits MISMATCH: First instruction opcode differs: object call, BE push; BE instructions=240; Civ5 changed/new=UNVERIFIED.
void CvAliens::DoUnits()
{
	for (std::map<IDInfo, AlienUnitData>::iterator it = m_alienUnitData.begin(); it != m_alienUnitData.end(); ++it)
		UpdateColossalUnitDisappearance(it->second);
}

// TODO(Phase1 audit): CvAliens::UpdateNestSpawnCounter MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=165; Civ5 changed/new=UNVERIFIED.
void CvAliens::UpdateNestSpawnCounter(CvPlot* plot)
{
	if (plot && m_aiPlotAlienNestSpawnCounter)
		++m_aiPlotAlienNestSpawnCounter[plot->GetPlotIndex()];
}

// TODO(Phase1 audit): CvAliens::GetNestRespawnRate MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=33; Civ5 changed/new=UNVERIFIED.
int CvAliens::GetNestRespawnRate() { return 0; }

// TODO(Phase1 audit): CvAliens::ChangePlayerOpinionValue MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=111; Civ5 changed/new=UNVERIFIED.
void CvAliens::ChangePlayerOpinionValue(PlayerTypes player, float value)
{
	SetOpinionValueForPlayer(player, GetOpinionValueForPlayer(player) + value);
}

// TODO(Phase1 audit): CvAliens::IsPlotValidForAlienUnitSpawn MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x8,%esp] vs BE [push   %edi]; BE instructions=57; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsPlotValidForAlienUnitSpawn(const CvPlot& plot, UnitTypes)
{
	return IsPlotValidForAnyAlienSpawn(plot, plot.isWater());
}

// TODO(Phase1 audit): CvAliens::IsTargetValidForAlienAttack MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=108; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsTargetValidForAlienAttack(const CvPlot& plot, const CvUnit& unit)
{
	return IsPlotValidForAlienUnit(plot, unit, false);
}

// TODO(Phase1 audit): CvAliens::IsTargetValidForAlienPlunder MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=96; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsTargetValidForAlienPlunder(const CvPlot& plot, const CvUnit& unit)
{
	return IsTargetValidForAlienAttack(plot, unit) && plot.getImprovementType() != NO_IMPROVEMENT;
}

// TODO(Phase1 audit): CvAliens::ScoreAlienWanderPlot MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=254; Civ5 changed/new=UNVERIFIED.
int CvAliens::ScoreAlienWanderPlot(const CvPlot& plot, const CvUnit&)
{
	return GetDangerValueAtPlot(plot.GetPlotIndex()) - GetRepelChanceAtPlot(plot.GetPlotIndex());
}

// TODO(Phase1 audit): CvAliens::GetAllAlienUnits MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=56; Civ5 changed/new=UNVERIFIED.
std::vector<CvUnit*> CvAliens::GetAllAlienUnits() { return std::vector<CvUnit*>(); }
// TODO(Phase1 audit): CvAliens::GetAllNormalAlienUnits MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=71; Civ5 changed/new=UNVERIFIED.
std::vector<CvUnit*> CvAliens::GetAllNormalAlienUnits(DomainTypes) { return std::vector<CvUnit*>(); }
// TODO(Phase1 audit): CvAliens::GetAllColossalAlienUnits MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=71; Civ5 changed/new=UNVERIFIED.
std::vector<CvUnit*> CvAliens::GetAllColossalAlienUnits(DomainTypes) { return std::vector<CvUnit*>(); }
// TODO(Phase1 audit): CvAliens::GetAllNonsentientAlienUnits MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=65; Civ5 changed/new=UNVERIFIED.
std::vector<CvUnit*> CvAliens::GetAllNonsentientAlienUnits() { return std::vector<CvUnit*>(); }

// TODO(Phase1 audit): CvAliens::IsUnitTypeRevealed MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=65; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsUnitTypeRevealed(UnitTypes unit, TeamTypes team)
{
	std::map<UnitTypes, std::map<TeamTypes, bool> >::const_iterator unitIt = m_unitTypesRevealedToTeam.find(unit);
	if (unitIt == m_unitTypesRevealedToTeam.end())
		return false;
	std::map<TeamTypes, bool>::const_iterator teamIt = unitIt->second.find(team);
	return teamIt != unitIt->second.end() && teamIt->second;
}

// TODO(Phase1 audit): CvAliens::SetUnitTypeRevealed MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=94; Civ5 changed/new=UNVERIFIED.
void CvAliens::SetUnitTypeRevealed(UnitTypes unit, TeamTypes team, bool revealed)
{
	m_unitTypesRevealedToTeam[unit][team] = revealed;
}

// TODO(Phase1 audit): CvAliens::CanUnitPillageAlienNest MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x8,%esp] vs BE [push   %esi]; BE instructions=50; Civ5 changed/new=UNVERIFIED.
bool CvAliens::CanUnitPillageAlienNest(const CvUnit& unit, const CvPlot& plot)
{
	return unit.isAlien() == false && IsPlotValidForAlienNest(plot);
}

// TODO(Phase1 audit): CvAliens::GetFlagColorForPlayer UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=26; Civ5 changed/new=UNVERIFIED.
int CvAliens::GetFlagColorForPlayer(CvUnit&, PlayerTypes player)
{
	return IsHostileToPlayer(player) ? 0 : 1;
}

// TODO(Phase1 audit): CvAliens::OnPlayerOpinionChanged MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=110; Civ5 changed/new=UNVERIFIED.
void CvAliens::OnPlayerOpinionChanged(PlayerTypes) {}

// TODO(Phase1 audit): CvAliens::HasPlotActiveAlienRepel MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=72; Civ5 changed/new=UNVERIFIED.
bool CvAliens::HasPlotActiveAlienRepel(const CvPlot& plot)
{
	return GetRepelChanceAtPlot(plot.GetPlotIndex()) > 0;
}

// TODO(Phase1 audit): CvAliens::AddAlienUnitData UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=48; Civ5 changed/new=UNVERIFIED.
void CvAliens::AddAlienUnitData(CvUnit& unit, CvPlot& plot)
{
	const IDInfo id = unit.GetIDInfo();
	const int plotIndex = plot.GetPlotIndex();
	if(m_alienUnitData.find(id) != m_alienUnitData.end()) return;
	AlienUnitData& data = m_alienUnitData[id];
	data.m_eOwner = id.eOwner;
	data.m_iUnitID = id.iID;
	data.m_iTurnsSinceSpawn = 0;
	data.m_iLastPlotIndex = plotIndex;
	data.m_bActive = true;
}

// TODO(Phase1 audit): CvAliens::AddDangerToPlotArea MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=252; Civ5 changed/new=UNVERIFIED.
void CvAliens::AddDangerToPlotArea(CvPlot& plot, int value)
{
	m_dangerPlots[plot.GetPlotIndex()] += value;
}

// TODO(Phase1 audit): CvAliens::ShouldSpawnAlienFromNest UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=16; Civ5 changed/new=UNVERIFIED.
bool CvAliens::ShouldSpawnAlienFromNest(CvPlot* plot)
{
	return plot && !HasPlotActiveAlienRepel(*plot);
}

// TODO(Phase1 audit): CvAliens::UpdateColossalUnitDisappearance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=275; Civ5 changed/new=UNVERIFIED.
void CvAliens::UpdateColossalUnitDisappearance(AlienUnitData& data)
{
	++data.m_iTurnsSinceSpawn;
}

// TODO(Phase1 audit): CvAliens::DoColossalAlienDisappearance MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=86; Civ5 changed/new=UNVERIFIED.
void CvAliens::DoColossalAlienDisappearance(CvUnit&) {}

// TODO(Phase1 audit): CvAliens::IsAttractorPlot MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=47; Civ5 changed/new=UNVERIFIED.
bool CvAliens::IsAttractorPlot(const CvPlot& plot, int& strength)
{
	std::map<int, int>::const_iterator it = m_attractorPlots.find(plot.GetPlotIndex());
	if (it == m_attractorPlots.end())
	{
		strength = 0;
		return false;
	}
	strength = it->second;
	return true;
}

// TODO(Phase1 audit): CvAliens::GetAggroForTarget MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=28; Civ5 changed/new=UNVERIFIED.
int CvAliens::GetAggroForTarget(IDInfo target)
{
	std::map<IDInfo, int>::const_iterator it = m_aggroAttackTargets.find(target);
	return it == m_aggroAttackTargets.end() ? 0 : it->second;
}
// TODO(Phase1 audit): CvAliensLuaContext::OnNewGameInit() UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=40; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::OnUpdateUnits() UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=40; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::lGetAllNestSites(lua_State*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=106; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::RegisterFunction(char const*, char const*, int (*)(lua_State*)) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=192; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::lGetAllAlienUnits(lua_State*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=109; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::lGetGlobalOpinion(lua_State*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=27; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::RegisterFunctions() UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=70; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::lGetNumNormalUnits(lua_State*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=45; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::lGetNumColossalUnits(lua_State*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=45; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::LuaPushGlobalFunction(char const*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=72; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::OnPlayerOpinionChanged(PlayerTypes) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=47; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::TryGetNormalUnitToSpawn(DomainTypes) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=49; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::lGetAllColossalAlienUnits(lua_State*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=114; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::TryGetColossalUnitToSpawn(DomainTypes) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=49; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::GetWeightedUnitTypeToSpawn(CvPlot&) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=57; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::lIsPlotValidForAnyAlienSpawn(lua_State*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=29; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::Init() UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=61; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::Reset() UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=24; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::Uninit() UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=24; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::LuaReader(lua_State*, void*, unsigned int*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=39; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::LuaWriter(lua_State*, void const*, unsigned int, void*) UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=27; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::CvAliensLuaContext() UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=3; Civ5 changed/new=UNVERIFIED.
// TODO(Phase1 audit): CvAliensLuaContext::~CvAliensLuaContext() UNVERIFIED: missing target declaration/definition (DWARF-owned); BE instructions=28; Civ5 changed/new=UNVERIFIED.
