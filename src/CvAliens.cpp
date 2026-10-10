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

AIAlienOpinion OpinionFromValue(float value)
{
	return value < 0.0f ? AI_ALIEN_OPINION_HOSTILE :
		(value > 0.0f ? AI_ALIEN_OPINION_FRIENDLY : AI_ALIEN_OPINION_NEUTRAL);
}
}

void CvAliens::Init()
{
	m_aeValidAlienSpawnDirections.clear();
	for (int i = 0; i < NUM_DIRECTION_TYPES; ++i)
		m_aeValidAlienSpawnDirections.push_back((DirectionTypes)i);
	NewGameInit();
}

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

void CvAliens::SpawnNormalUnitFromNest(CvPlot* plot, bool, bool)
{
	if (plot)
		UpdateNestSpawnCounter(plot);
}

bool CvAliens::AttemptHiddenSpawn(UnitTypes) { return false; }
bool CvAliens::AttemptWildAreaSpawn(UnitTypes) { return false; }
void CvAliens::DoAlienKillCivilian(const CvUnit&, CvUnit&) {}
void CvAliens::DoCityThumperStrike(const CvCity&, int, int, int) {}

void CvAliens::AddRepelEffectToPlotRange(PlayerTypes player, const CvPlot& plot, int range)
{
	MarkRepulsorPlotsInRange(player, plot.getX(), plot.getY(), range);
}

void CvAliens::MarkRepulsorPlotsInRange(PlayerTypes, int x, int y, int range)
{
	for (int dx = -range; dx <= range; ++dx)
		for (int dy = -range; dy <= range; ++dy)
			if (dx * dx + dy * dy <= range * range)
				++m_repulsorPlots[(x + dx) | ((y + dy) << 16)];
}

void CvAliens::AddAttractorPlot(PlayerTypes, const CvPlot& plot, int strength)
{
	m_attractorPlots[plot.GetPlotIndex()] += strength;
}

void CvAliens::ClearAttractorPlot(PlayerTypes, const CvPlot& plot)
{
	m_attractorPlots.erase(plot.GetPlotIndex());
}

bool CvAliens::IsPlotValidForAlienNest(const CvPlot& plot)
{
	return !plot.isWater() && !plot.isImpassable() && plot.getOwner() == NO_PLAYER;
}

bool CvAliens::IsPlotValidForAlienUnit(const CvPlot& plot, const CvUnit& unit, bool)
{
	if (plot.isImpassable() || unit.IsOrbitalUnit())
		return false;
	return unit.getDomainType() == (DomainTypes)1 ? plot.isWater() : !plot.isWater();
}

AIAlienOpinion CvAliens::GetOpinionForPlayer(PlayerTypes player)
{
	return OpinionFromValue(GetOpinionValueForPlayer(player));
}

float CvAliens::GetOpinionValueForPlayer(PlayerTypes player)
{
	std::map<PlayerTypes, float>::const_iterator it = m_playerOpinionLevels.find(player);
	return it == m_playerOpinionLevels.end() ? 0.0f : it->second;
}

void CvAliens::SetOpinionForPlayer(PlayerTypes player, AIAlienOpinion opinion)
{
	SetOpinionValueForPlayer(player, opinion == AI_ALIEN_OPINION_HOSTILE ? kHostileOpinion :
		(opinion == AI_ALIEN_OPINION_FRIENDLY ? kFriendlyOpinion : 0.0f));
}

void CvAliens::SetOpinionValueForPlayer(PlayerTypes player, float value)
{
	m_playerOpinionLevels[player] = value;
	OnPlayerOpinionChanged(player);
}

AIAlienOpinion CvAliens::GetGlobalOpinion()
{
	if (m_playerOpinionLevels.empty())
		return AI_ALIEN_OPINION_NEUTRAL;
	float total = 0.0f;
	for (std::map<PlayerTypes, float>::const_iterator it = m_playerOpinionLevels.begin(); it != m_playerOpinionLevels.end(); ++it)
		total += it->second;
	return OpinionFromValue(total / m_playerOpinionLevels.size());
}

void CvAliens::SetHostilityFlagForPlayer(PlayerTypes player, bool hostile)
{
	m_playerHostilityFlags[player] = hostile;
}

bool CvAliens::GetHostilityFlagForPlayer(PlayerTypes player)
{
	std::map<PlayerTypes, bool>::const_iterator it = m_playerHostilityFlags.find(player);
	return it != m_playerHostilityFlags.end() && it->second;
}

bool CvAliens::IsHostileToPlayer(PlayerTypes player)
{
	return GetHostilityFlagForPlayer(player) || GetOpinionForPlayer(player) == AI_ALIEN_OPINION_HOSTILE;
}

int CvAliens::GetDangerValueAtPlot(int plotIndex)
{
	std::map<int, int>::const_iterator it = m_dangerPlots.find(plotIndex);
	return it == m_dangerPlots.end() ? 0 : it->second;
}

int CvAliens::GetRepelChanceAtPlot(int plotIndex)
{
	std::map<int, int>::const_iterator it = m_repulsorPlots.find(plotIndex);
	return it == m_repulsorPlots.end() ? 0 : it->second;
}

void CvAliens::OnAlienUnitSetXY(CvUnit& unit, CvPlot& plot)
{
	AddAlienUnitData(unit, plot);
}

void CvAliens::OnOrbitalAlienAttractionChanged(PlayerTypes player, const CvPlot& plot, int strength, bool active)
{
	if (active)
		AddAttractorPlot(player, plot, strength);
	else
		ClearAttractorPlot(player, plot);
}

int CvAliens::GetAlienMiasmaHealRate() { return 0; }

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

std::vector<CvUnit*> CvAliens::GetAllActiveThumperUnitsForCity(const CvCity&) { return std::vector<CvUnit*>(); }
void CvAliens::Read(FDataStream&, unsigned int) { NewGameInit(); }
void CvAliens::Write(FDataStream&) {}
void CvAliens::OnNestAttacked(AlienNestAttackedEvent&) {}
void CvAliens::OnNestDestroyed(AlienNestClearedEvent&) {}
void CvAliens::OnUnitCreated(UnitCreatedEvent&) {}
void CvAliens::OnUnitAttacked(UnitAttackedEvent&) {}
void CvAliens::OnUnitKilled(UnitKilledEvent&) {}
void CvAliens::OnOutpostFounded(OutpostFoundedEvent&) {}
void CvAliens::OnCityMoved(CityMovedEvent&) {}
void CvAliens::OnCityKilled(CityKilledEvent&) {}
void CvAliens::OnBuildFinished(BuildFinishedEvent&) {}
void CvAliens::LogStory(CvString) {}

void CvAliens::DoNests()
{
	for (std::vector<int>::const_iterator it = m_nestSites.begin(); it != m_nestSites.end(); ++it)
		if (m_aiPlotAlienNestSpawnCounter)
			++m_aiPlotAlienNestSpawnCounter[*it];
}

bool CvAliens::IsPlotValidForAnyAlienSpawn(const CvPlot& plot, bool water)
{
	return !plot.isImpassable() && plot.isWater() == water && !HasPlotActiveAlienRepel(plot);
}

bool CvAliens::CreateNewAlienUnitAtPlot(CvPlot&, bool) { return false; }
void CvAliens::LogData(CvString) {}

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

void CvAliens::UpdateThumperPlots() {}
void CvAliens::UpdateRepulsorPlots() {}

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

void CvAliens::UpdateOpinionLevels() {}
void CvAliens::UpdateAggressionLevels() {}

void CvAliens::DoUnits()
{
	for (std::map<IDInfo, AlienUnitData>::iterator it = m_alienUnitData.begin(); it != m_alienUnitData.end(); ++it)
		UpdateColossalUnitDisappearance(it->second);
}

void CvAliens::UpdateNestSpawnCounter(CvPlot* plot)
{
	if (plot && m_aiPlotAlienNestSpawnCounter)
		++m_aiPlotAlienNestSpawnCounter[plot->GetPlotIndex()];
}

int CvAliens::GetNestRespawnRate() { return 0; }

void CvAliens::ChangePlayerOpinionValue(PlayerTypes player, float value)
{
	SetOpinionValueForPlayer(player, GetOpinionValueForPlayer(player) + value);
}

bool CvAliens::IsPlotValidForAlienUnitSpawn(const CvPlot& plot, UnitTypes)
{
	return IsPlotValidForAnyAlienSpawn(plot, plot.isWater());
}

bool CvAliens::IsTargetValidForAlienAttack(const CvPlot& plot, const CvUnit& unit)
{
	return IsPlotValidForAlienUnit(plot, unit, false);
}

bool CvAliens::IsTargetValidForAlienPlunder(const CvPlot& plot, const CvUnit& unit)
{
	return IsTargetValidForAlienAttack(plot, unit) && plot.getImprovementType() != NO_IMPROVEMENT;
}

int CvAliens::ScoreAlienWanderPlot(const CvPlot& plot, const CvUnit&)
{
	return GetDangerValueAtPlot(plot.GetPlotIndex()) - GetRepelChanceAtPlot(plot.GetPlotIndex());
}

std::vector<CvUnit*> CvAliens::GetAllAlienUnits() { return std::vector<CvUnit*>(); }
std::vector<CvUnit*> CvAliens::GetAllNormalAlienUnits(DomainTypes) { return std::vector<CvUnit*>(); }
std::vector<CvUnit*> CvAliens::GetAllColossalAlienUnits(DomainTypes) { return std::vector<CvUnit*>(); }
std::vector<CvUnit*> CvAliens::GetAllNonsentientAlienUnits() { return std::vector<CvUnit*>(); }

bool CvAliens::IsUnitTypeRevealed(UnitTypes unit, TeamTypes team)
{
	std::map<UnitTypes, std::map<TeamTypes, bool> >::const_iterator unitIt = m_unitTypesRevealedToTeam.find(unit);
	if (unitIt == m_unitTypesRevealedToTeam.end())
		return false;
	std::map<TeamTypes, bool>::const_iterator teamIt = unitIt->second.find(team);
	return teamIt != unitIt->second.end() && teamIt->second;
}

void CvAliens::SetUnitTypeRevealed(UnitTypes unit, TeamTypes team, bool revealed)
{
	m_unitTypesRevealedToTeam[unit][team] = revealed;
}

bool CvAliens::CanUnitPillageAlienNest(const CvUnit& unit, const CvPlot& plot)
{
	return unit.isAlien() == false && IsPlotValidForAlienNest(plot);
}

int CvAliens::GetFlagColorForPlayer(CvUnit&, PlayerTypes player)
{
	return IsHostileToPlayer(player) ? 0 : 1;
}

void CvAliens::OnPlayerOpinionChanged(PlayerTypes) {}

bool CvAliens::HasPlotActiveAlienRepel(const CvPlot& plot)
{
	return GetRepelChanceAtPlot(plot.GetPlotIndex()) > 0;
}

void CvAliens::AddAlienUnitData(CvUnit& unit, CvPlot& plot)
{
	AlienUnitData& data = m_alienUnitData[unit.GetIDInfo()];
	data.m_iTurnsSinceSpawn = 0;
	data.m_iLastPlotIndex = plot.GetPlotIndex();
	data.m_iUnknown1 = 0;
	data.m_iUnknown2 = 0;
}

void CvAliens::AddDangerToPlotArea(CvPlot& plot, int value)
{
	m_dangerPlots[plot.GetPlotIndex()] += value;
}

bool CvAliens::ShouldSpawnAlienFromNest(CvPlot* plot)
{
	return plot && !HasPlotActiveAlienRepel(*plot);
}

void CvAliens::UpdateColossalUnitDisappearance(AlienUnitData& data)
{
	++data.m_iTurnsSinceSpawn;
}

void CvAliens::DoColossalAlienDisappearance(CvUnit&) {}

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

int CvAliens::GetAggroForTarget(IDInfo target)
{
	std::map<IDInfo, int>::const_iterator it = m_aggroAttackTargets.find(target);
	return it == m_aggroAttackTargets.end() ? 0 : it->second;
}
