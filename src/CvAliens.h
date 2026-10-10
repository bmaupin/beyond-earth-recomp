#pragma once

#include <map>
#include <vector>

class CvPlot;
class CvUnit;
class CvCity;
class FDataStream;
class CvString;
struct IDInfo;

enum AIAlienOpinion
{
	AI_ALIEN_OPINION_HOSTILE = 0,
	AI_ALIEN_OPINION_NEUTRAL,
	AI_ALIEN_OPINION_FRIENDLY
};

struct AlienUnitData
{
	int m_iTurnsSinceSpawn;
	int m_iLastPlotIndex;
	int m_iUnknown1;
	int m_iUnknown2;
};

class UnitData;
class UnitAttackedData;
class UnitKilledData;
class CityMovedData;
class CityKilledData;
class OutpostFoundedData;
class BuildFinishedData;
class AlienNestAttackedData;
class AlienNestClearedData;
class GCEventContainer;
class GCEventSystemAccessor;
namespace Events
{
	template <int N> struct Int2Type {};
	class LinearEventDispatcher {};
	class NullEventClass {};
	class EmptySubscriptionValidator {};
	template <class A, class B> class BaseEvent {};
	template <class A, class B, class C, class D, class E, class F, class G> class EventTemplate {};
}

typedef Events::EventTemplate<Events::Int2Type<12>, OutpostFoundedData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> OutpostFoundedEvent;
typedef Events::EventTemplate<Events::Int2Type<13>, BuildFinishedData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> BuildFinishedEvent;
typedef Events::EventTemplate<Events::Int2Type<18>, UnitData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> UnitCreatedEvent;
typedef Events::EventTemplate<Events::Int2Type<19>, UnitAttackedData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> UnitAttackedEvent;
typedef Events::EventTemplate<Events::Int2Type<20>, UnitKilledData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> UnitKilledEvent;
typedef Events::EventTemplate<Events::Int2Type<22>, CityKilledData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> CityKilledEvent;
typedef Events::EventTemplate<Events::Int2Type<24>, CityMovedData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> CityMovedEvent;
typedef Events::EventTemplate<Events::Int2Type<32>, AlienNestAttackedData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> AlienNestAttackedEvent;
typedef Events::EventTemplate<Events::Int2Type<33>, AlienNestClearedData, Events::LinearEventDispatcher, GCEventContainer, Events::NullEventClass, Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> AlienNestClearedEvent;

class CvAliens
{
public:
	static void Init();
	static void Uninit();
	static void NewGameInit();
	static void DoTurn();
	static void CreateNest(CvPlot&, bool);
	static void RemoveNest(CvPlot&, PlayerTypes);
	static void SpawnNormalUnitFromNest(CvPlot*, bool, bool);
	static void SpawnNormalSeaUnit(bool, bool);
	static bool AttemptHiddenSpawn(UnitTypes);
	static bool AttemptWildAreaSpawn(UnitTypes);
	static void DoAlienKillCivilian(const CvUnit&, CvUnit&);
	static void DoCityThumperStrike(const CvCity&, int, int, int);
	static void AddRepelEffectToPlotRange(PlayerTypes, const CvPlot&, int);
	static void MarkRepulsorPlotsInRange(PlayerTypes, int, int, int);
	static void AddAttractorPlot(PlayerTypes, const CvPlot&, int);
	static void ClearAttractorPlot(PlayerTypes, const CvPlot&);
	static bool IsPlotValidForAlienNest(const CvPlot&);
	static bool IsPlotValidForAlienUnit(const CvPlot&, const CvUnit&, bool);
	static AIAlienOpinion GetOpinionForPlayer(PlayerTypes);
	static float GetOpinionValueForPlayer(PlayerTypes);
	static void SetOpinionForPlayer(PlayerTypes, AIAlienOpinion);
	static void SetOpinionValueForPlayer(PlayerTypes, float);
	static AIAlienOpinion GetGlobalOpinion();
	static void SetHostilityFlagForPlayer(PlayerTypes, bool);
	static bool IsHostileToPlayer(PlayerTypes);
	static int GetDangerValueAtPlot(int);
	static int GetRepelChanceAtPlot(int);
	static void OnAlienUnitSetXY(CvUnit&, CvPlot&);
	static void OnOrbitalAlienAttractionChanged(PlayerTypes, const CvPlot&, int, bool);
	static int GetAlienMiasmaHealRate();
	static bool PlotHasNonsentient(const CvPlot&);
	static std::vector<CvUnit*> GetAllActiveThumperUnitsForCity(const CvCity&);
	static void Read(FDataStream&, unsigned int);
	static void Write(FDataStream&);
	static int GetTotalPlayerUnitsKilled() { return m_totalPlayerUnitsKilled; }
	static int GetTotalLandUnitsLost() { return m_totalLandUnitsLost; }
	static int GetTotalSeaUnitsLost() { return m_totalSeaUnitsLost; }
	static int GetTotalLandDamageDealt() { return m_totalLandDamageDealt; }
	static int GetTotalSeaDamageDealt() { return m_totalSeaDamageDealt; }
	static int GetTotalLandDamageReceived() { return m_totalLandDamageReceived; }
	static int GetTotalSeaDamageReceived() { return m_totalSeaDamageReceived; }
	static const std::vector<int>& GetActiveNestPlotIndices() { return m_nestSites; }
	static void OnNestAttacked(AlienNestAttackedEvent&);
	static void OnNestDestroyed(AlienNestClearedEvent&);
	static void OnUnitCreated(UnitCreatedEvent&);
	static void OnUnitAttacked(UnitAttackedEvent&);
	static void OnUnitKilled(UnitKilledEvent&);
	static void OnOutpostFounded(OutpostFoundedEvent&);
	static void OnCityMoved(CityMovedEvent&);
	static void OnCityKilled(CityKilledEvent&);
	static void OnBuildFinished(BuildFinishedEvent&);
	static void LogStory(CvString);
	static void DoNests();
	static bool IsPlotValidForAnyAlienSpawn(const CvPlot&, bool);
	static bool CreateNewAlienUnitAtPlot(CvPlot&, bool);
	static void LogData(CvString);
	static void UpdateDangerPlots();
	static void UpdateThumperPlots();
	static void UpdateRepulsorPlots();
	static void UpdateAggroLevels();
	static void UpdateOpinionLevels();
	static void UpdateAggressionLevels();
	static void DoUnits();
	static void UpdateNestSpawnCounter(CvPlot*);
	static int GetNestRespawnRate();
	static void ChangePlayerOpinionValue(PlayerTypes, float);
	static bool IsPlotValidForAlienUnitSpawn(const CvPlot&, UnitTypes);
	static bool IsTargetValidForAlienAttack(const CvPlot&, const CvUnit&);
	static bool IsTargetValidForAlienPlunder(const CvPlot&, const CvUnit&);
	static int ScoreAlienWanderPlot(const CvPlot&, const CvUnit&);
	static std::vector<CvUnit*> GetAllAlienUnits();
	static std::vector<CvUnit*> GetAllNormalAlienUnits(DomainTypes);
	static std::vector<CvUnit*> GetAllColossalAlienUnits(DomainTypes);
	static std::vector<CvUnit*> GetAllNonsentientAlienUnits();
	static bool IsUnitTypeRevealed(UnitTypes, TeamTypes);
	static void SetUnitTypeRevealed(UnitTypes, TeamTypes, bool);
	static bool CanUnitPillageAlienNest(const CvUnit&, const CvPlot&);
	static int GetFlagColorForPlayer(CvUnit&, PlayerTypes);
	static void OnPlayerOpinionChanged(PlayerTypes);
	static bool HasPlotActiveAlienRepel(const CvPlot&);
	static void AddAlienUnitData(CvUnit&, CvPlot&);
	static void AddDangerToPlotArea(CvPlot&, int);
	static bool ShouldSpawnAlienFromNest(CvPlot*);
	static void UpdateColossalUnitDisappearance(AlienUnitData&);
	static void DoColossalAlienDisappearance(CvUnit&);
	static bool IsAttractorPlot(const CvPlot&, int&);
	static int GetAggroForTarget(IDInfo);
	static bool GetHostilityFlagForPlayer(PlayerTypes);

private:
	static short* m_aiPlotAlienNestSpawnCounter;
	static short* m_aiPlotAlienNestNumUnitsSpawned;
	static int m_globalAggressionLevel;
	static int m_totalPlayerUnitsKilled;
	static int m_totalLandUnitsLost;
	static int m_totalSeaUnitsLost;
	static int m_totalLandDamageDealt;
	static int m_totalSeaDamageDealt;
	static int m_totalLandDamageReceived;
	static int m_totalSeaDamageReceived;
	static std::map<IDInfo, AlienUnitData> m_alienUnitData;
	static std::vector<int> m_nestSites;
	static std::map<PlayerTypes, float> m_playerOpinionLevels;
	static std::map<PlayerTypes, bool> m_playerHostilityFlags;
	static std::map<IDInfo, int> m_aggroAttackTargets;
	static std::map<int, int> m_dangerPlots;
	static std::map<int, int> m_thumperPlots;
	static std::map<int, int> m_repulsorPlots;
	static std::map<int, int> m_attractorPlots;
	static std::map<UnitTypes, std::map<TeamTypes, bool> > m_unitTypesRevealedToTeam;
	static std::vector<IDInfo> m_activeThumperUnits;
	static std::vector<DirectionTypes> m_aeValidAlienSpawnDirections;
	static void* m_luaContext;
};
