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
// TODO(Phase1 audit): AlienUnitData::AlienUnitData UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	AlienUnitData() : m_eOwner(NO_PLAYER), m_iUnitID(-1), m_iTurnsSinceSpawn(0), m_iLastPlotIndex(-1), m_bActive(true) {}
// TODO(Phase1 audit): AlienUnitData::IsColossal UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=29; Civ5 changed/new=UNVERIFIED.
	bool IsColossal() const;
	PlayerTypes m_eOwner;
	int m_iUnitID;
	int m_iTurnsSinceSpawn;
	int m_iLastPlotIndex;
	bool m_bActive;
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
// TODO(Phase1 audit): CvAliens::Init MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=318; Civ5 changed/new=UNVERIFIED.
	static void Init();
// TODO(Phase1 audit): CvAliens::Uninit MISMATCH: Instruction 4 differs before first target reference: object [sub    $0x10,%esp] vs BE [sub    $0x20,%esp]; BE instructions=171; Civ5 changed/new=UNVERIFIED.
	static void Uninit();
// TODO(Phase1 audit): CvAliens::NewGameInit MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=367; Civ5 changed/new=UNVERIFIED.
	static void NewGameInit();
// TODO(Phase1 audit): CvAliens::DoTurn MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=72; Civ5 changed/new=UNVERIFIED.
	static void DoTurn();
// TODO(Phase1 audit): CvAliens::CreateNest MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=159; Civ5 changed/new=UNVERIFIED.
	static void CreateNest(CvPlot&, bool);
// TODO(Phase1 audit): CvAliens::RemoveNest MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x1c,%esp] vs BE [sub    $0x2c,%esp]; BE instructions=101; Civ5 changed/new=UNVERIFIED.
	static void RemoveNest(CvPlot&, PlayerTypes);
// TODO(Phase1 audit): CvAliens::SpawnNormalUnitFromNest MISMATCH: First instruction opcode differs: object call, BE push; BE instructions=404; Civ5 changed/new=UNVERIFIED.
	static void SpawnNormalUnitFromNest(CvPlot*, bool, bool);
// TODO(Phase1 audit): CvAliens::SpawnNormalSeaUnit UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static void SpawnNormalSeaUnit(bool, bool);
// TODO(Phase1 audit): CvAliens::AttemptHiddenSpawn MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=332; Civ5 changed/new=UNVERIFIED.
	static bool AttemptHiddenSpawn(UnitTypes);
// TODO(Phase1 audit): CvAliens::AttemptWildAreaSpawn MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=75; Civ5 changed/new=UNVERIFIED.
	static bool AttemptWildAreaSpawn(UnitTypes);
// TODO(Phase1 audit): CvAliens::DoAlienKillCivilian MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=119; Civ5 changed/new=UNVERIFIED.
	static void DoAlienKillCivilian(const CvUnit&, CvUnit&);
// TODO(Phase1 audit): CvAliens::DoCityThumperStrike MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=383; Civ5 changed/new=UNVERIFIED.
	static void DoCityThumperStrike(const CvCity&, int, int, int);
// TODO(Phase1 audit): CvAliens::AddRepelEffectToPlotRange MISMATCH: Instruction 1 differs before first target reference: object [push   %ebp] vs BE [push   %ebx]; BE instructions=20; Civ5 changed/new=UNVERIFIED.
	static void AddRepelEffectToPlotRange(PlayerTypes, const CvPlot&, int);
// TODO(Phase1 audit): CvAliens::MarkRepulsorPlotsInRange MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x2c,%esp] vs BE [sub    $0x3c,%esp]; BE instructions=213; Civ5 changed/new=UNVERIFIED.
	static void MarkRepulsorPlotsInRange(PlayerTypes, int, int, int);
// TODO(Phase1 audit): CvAliens::AddAttractorPlot MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=35; Civ5 changed/new=UNVERIFIED.
	static void AddAttractorPlot(PlayerTypes, const CvPlot&, int);
// TODO(Phase1 audit): CvAliens::ClearAttractorPlot MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x18,%esp] vs BE [push   %esi]; BE instructions=34; Civ5 changed/new=UNVERIFIED.
	static void ClearAttractorPlot(PlayerTypes, const CvPlot&);
// TODO(Phase1 audit): CvAliens::IsPlotValidForAlienNest MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=220; Civ5 changed/new=UNVERIFIED.
	static bool IsPlotValidForAlienNest(const CvPlot&);
// TODO(Phase1 audit): CvAliens::IsPlotValidForAlienUnit MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=101; Civ5 changed/new=UNVERIFIED.
	static bool IsPlotValidForAlienUnit(const CvPlot&, const CvUnit&, bool);
// TODO(Phase1 audit): CvAliens::GetOpinionForPlayer MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=43; Civ5 changed/new=UNVERIFIED.
	static AIAlienOpinion GetOpinionForPlayer(PlayerTypes);
// TODO(Phase1 audit): CvAliens::GetOpinionValueForPlayer MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [sub    $0x18,%esp]; BE instructions=16; Civ5 changed/new=UNVERIFIED.
	static float GetOpinionValueForPlayer(PlayerTypes);
// TODO(Phase1 audit): CvAliens::SetOpinionForPlayer MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x18,%esp] vs BE [push   %edi]; BE instructions=55; Civ5 changed/new=UNVERIFIED.
	static void SetOpinionForPlayer(PlayerTypes, AIAlienOpinion);
// TODO(Phase1 audit): CvAliens::SetOpinionValueForPlayer MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x18,%esp] vs BE [push   %edi]; BE instructions=39; Civ5 changed/new=UNVERIFIED.
	static void SetOpinionValueForPlayer(PlayerTypes, float);
// TODO(Phase1 audit): CvAliens::GetGlobalOpinion MISMATCH: First instruction opcode differs: object push, BE call; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	static AIAlienOpinion GetGlobalOpinion();
// TODO(Phase1 audit): CvAliens::SetHostilityFlagForPlayer UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	static void SetHostilityFlagForPlayer(PlayerTypes, bool);
// TODO(Phase1 audit): CvAliens::IsHostileToPlayer MISMATCH: Instruction 3 differs before first target reference: object [sub    $0x14,%esp] vs BE [push   %eax]; BE instructions=27; Civ5 changed/new=UNVERIFIED.
	static bool IsHostileToPlayer(PlayerTypes);
// TODO(Phase1 audit): CvAliens::GetDangerValueAtPlot MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=50; Civ5 changed/new=UNVERIFIED.
	static int GetDangerValueAtPlot(int);
// TODO(Phase1 audit): CvAliens::GetRepelChanceAtPlot MISMATCH: Instruction 3 differs before first target reference: object [sub    $0x24,%esp] vs BE [push   %eax]; BE instructions=25; Civ5 changed/new=UNVERIFIED.
	static int GetRepelChanceAtPlot(int);
// TODO(Phase1 audit): CvAliens::OnAlienUnitSetXY MISMATCH: First instruction opcode differs: object call, BE push; BE instructions=39; Civ5 changed/new=UNVERIFIED.
	static void OnAlienUnitSetXY(CvUnit&, CvPlot&);
// TODO(Phase1 audit): CvAliens::OnOrbitalAlienAttractionChanged MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [sub    $0x18,%esp]; BE instructions=19; Civ5 changed/new=UNVERIFIED.
	static void OnOrbitalAlienAttractionChanged(PlayerTypes, const CvPlot&, int, bool);
// TODO(Phase1 audit): CvAliens::GetAlienMiasmaHealRate MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=33; Civ5 changed/new=UNVERIFIED.
	static int GetAlienMiasmaHealRate();
// TODO(Phase1 audit): CvAliens::PlotHasNonsentient MISMATCH: Instruction 2 differs before first target reference: object [push   %edi] vs BE [sub    $0x8,%esp]; BE instructions=33; Civ5 changed/new=UNVERIFIED.
	static bool PlotHasNonsentient(const CvPlot&);
// TODO(Phase1 audit): CvAliens::GetAllActiveThumperUnitsForCity MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=72; Civ5 changed/new=UNVERIFIED.
	static std::vector<CvUnit*> GetAllActiveThumperUnitsForCity(const CvCity&);
// TODO(Phase1 audit): CvAliens::Read MISMATCH: First instruction opcode differs: object call, BE push; BE instructions=150; Civ5 changed/new=UNVERIFIED.
	static void Read(FDataStream&, unsigned int);
// TODO(Phase1 audit): CvAliens::Write MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=120; Civ5 changed/new=UNVERIFIED.
	static void Write(FDataStream&);
// TODO(Phase1 audit): CvAliens::GetTotalPlayerUnitsKilled UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static int GetTotalPlayerUnitsKilled() { return m_totalPlayerUnitsKilled; }
// TODO(Phase1 audit): CvAliens::GetTotalLandUnitsLost UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static int GetTotalLandUnitsLost() { return m_totalLandUnitsLost; }
// TODO(Phase1 audit): CvAliens::GetTotalSeaUnitsLost UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static int GetTotalSeaUnitsLost() { return m_totalSeaUnitsLost; }
// TODO(Phase1 audit): CvAliens::GetTotalLandDamageDealt UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static int GetTotalLandDamageDealt() { return m_totalLandDamageDealt; }
// TODO(Phase1 audit): CvAliens::GetTotalSeaDamageDealt UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static int GetTotalSeaDamageDealt() { return m_totalSeaDamageDealt; }
// TODO(Phase1 audit): CvAliens::GetTotalLandDamageReceived UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static int GetTotalLandDamageReceived() { return m_totalLandDamageReceived; }
// TODO(Phase1 audit): CvAliens::GetTotalSeaDamageReceived UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static int GetTotalSeaDamageReceived() { return m_totalSeaDamageReceived; }
// TODO(Phase1 audit): CvAliens::GetActiveNestPlotIndices UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	static const std::vector<int>& GetActiveNestPlotIndices() { return m_nestSites; }
// TODO(Phase1 audit): CvAliens::OnNestAttacked MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=93; Civ5 changed/new=UNVERIFIED.
	static void OnNestAttacked(AlienNestAttackedEvent&);
// TODO(Phase1 audit): CvAliens::OnNestDestroyed MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=199; Civ5 changed/new=UNVERIFIED.
	static void OnNestDestroyed(AlienNestClearedEvent&);
// TODO(Phase1 audit): CvAliens::OnUnitCreated MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=22; Civ5 changed/new=UNVERIFIED.
	static void OnUnitCreated(UnitCreatedEvent&);
// TODO(Phase1 audit): CvAliens::OnUnitAttacked MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=533; Civ5 changed/new=UNVERIFIED.
	static void OnUnitAttacked(UnitAttackedEvent&);
// TODO(Phase1 audit): CvAliens::OnUnitKilled MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=308; Civ5 changed/new=UNVERIFIED.
	static void OnUnitKilled(UnitKilledEvent&);
// TODO(Phase1 audit): CvAliens::OnOutpostFounded MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=136; Civ5 changed/new=UNVERIFIED.
	static void OnOutpostFounded(OutpostFoundedEvent&);
// TODO(Phase1 audit): CvAliens::OnCityMoved MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=46; Civ5 changed/new=UNVERIFIED.
	static void OnCityMoved(CityMovedEvent&);
// TODO(Phase1 audit): CvAliens::OnCityKilled MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=50; Civ5 changed/new=UNVERIFIED.
	static void OnCityKilled(CityKilledEvent&);
// TODO(Phase1 audit): CvAliens::OnBuildFinished MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=38; Civ5 changed/new=UNVERIFIED.
	static void OnBuildFinished(BuildFinishedEvent&);
// TODO(Phase1 audit): CvAliens::LogStory MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=97; Civ5 changed/new=UNVERIFIED.
	static void LogStory(CvString);
// TODO(Phase1 audit): CvAliens::DoNests MISMATCH: Instruction 1 differs before first target reference: object [push   %esi] vs BE [push   %ebp]; BE instructions=145; Civ5 changed/new=UNVERIFIED.
	static void DoNests();
// TODO(Phase1 audit): CvAliens::IsPlotValidForAnyAlienSpawn MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=61; Civ5 changed/new=UNVERIFIED.
	static bool IsPlotValidForAnyAlienSpawn(const CvPlot&, bool);
// TODO(Phase1 audit): CvAliens::CreateNewAlienUnitAtPlot MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=181; Civ5 changed/new=UNVERIFIED.
	static bool CreateNewAlienUnitAtPlot(CvPlot&, bool);
// TODO(Phase1 audit): CvAliens::LogData MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=198; Civ5 changed/new=UNVERIFIED.
	static void LogData(CvString);
// TODO(Phase1 audit): CvAliens::UpdateDangerPlots UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=52; Civ5 changed/new=UNVERIFIED.
	static void UpdateDangerPlots();
// TODO(Phase1 audit): CvAliens::UpdateThumperPlots MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=52; Civ5 changed/new=UNVERIFIED.
	static void UpdateThumperPlots();
// TODO(Phase1 audit): CvAliens::UpdateRepulsorPlots MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=79; Civ5 changed/new=UNVERIFIED.
	static void UpdateRepulsorPlots();
// TODO(Phase1 audit): CvAliens::UpdateAggroLevels MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x1c,%esp] vs BE [sub    $0x2c,%esp]; BE instructions=52; Civ5 changed/new=UNVERIFIED.
	static void UpdateAggroLevels();
// TODO(Phase1 audit): CvAliens::UpdateOpinionLevels MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=84; Civ5 changed/new=UNVERIFIED.
	static void UpdateOpinionLevels();
// TODO(Phase1 audit): CvAliens::UpdateAggressionLevels MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=41; Civ5 changed/new=UNVERIFIED.
	static void UpdateAggressionLevels();
// TODO(Phase1 audit): CvAliens::DoUnits MISMATCH: First instruction opcode differs: object call, BE push; BE instructions=240; Civ5 changed/new=UNVERIFIED.
	static void DoUnits();
// TODO(Phase1 audit): CvAliens::UpdateNestSpawnCounter MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=165; Civ5 changed/new=UNVERIFIED.
	static void UpdateNestSpawnCounter(CvPlot*);
// TODO(Phase1 audit): CvAliens::GetNestRespawnRate MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=33; Civ5 changed/new=UNVERIFIED.
	static int GetNestRespawnRate();
// TODO(Phase1 audit): CvAliens::ChangePlayerOpinionValue MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=111; Civ5 changed/new=UNVERIFIED.
	static void ChangePlayerOpinionValue(PlayerTypes, float);
// TODO(Phase1 audit): CvAliens::IsPlotValidForAlienUnitSpawn MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x8,%esp] vs BE [push   %edi]; BE instructions=57; Civ5 changed/new=UNVERIFIED.
	static bool IsPlotValidForAlienUnitSpawn(const CvPlot&, UnitTypes);
// TODO(Phase1 audit): CvAliens::IsTargetValidForAlienAttack MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=108; Civ5 changed/new=UNVERIFIED.
	static bool IsTargetValidForAlienAttack(const CvPlot&, const CvUnit&);
// TODO(Phase1 audit): CvAliens::IsTargetValidForAlienPlunder MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=96; Civ5 changed/new=UNVERIFIED.
	static bool IsTargetValidForAlienPlunder(const CvPlot&, const CvUnit&);
// TODO(Phase1 audit): CvAliens::ScoreAlienWanderPlot MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=254; Civ5 changed/new=UNVERIFIED.
	static int ScoreAlienWanderPlot(const CvPlot&, const CvUnit&);
// TODO(Phase1 audit): CvAliens::GetAllAlienUnits MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=56; Civ5 changed/new=UNVERIFIED.
	static std::vector<CvUnit*> GetAllAlienUnits();
// TODO(Phase1 audit): CvAliens::GetAllNormalAlienUnits MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=71; Civ5 changed/new=UNVERIFIED.
	static std::vector<CvUnit*> GetAllNormalAlienUnits(DomainTypes);
// TODO(Phase1 audit): CvAliens::GetAllColossalAlienUnits MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=71; Civ5 changed/new=UNVERIFIED.
	static std::vector<CvUnit*> GetAllColossalAlienUnits(DomainTypes);
// TODO(Phase1 audit): CvAliens::GetAllNonsentientAlienUnits MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=65; Civ5 changed/new=UNVERIFIED.
	static std::vector<CvUnit*> GetAllNonsentientAlienUnits();
// TODO(Phase1 audit): CvAliens::IsUnitTypeRevealed MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=65; Civ5 changed/new=UNVERIFIED.
	static bool IsUnitTypeRevealed(UnitTypes, TeamTypes);
// TODO(Phase1 audit): CvAliens::SetUnitTypeRevealed MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=94; Civ5 changed/new=UNVERIFIED.
	static void SetUnitTypeRevealed(UnitTypes, TeamTypes, bool);
// TODO(Phase1 audit): CvAliens::CanUnitPillageAlienNest MISMATCH: Instruction 2 differs before first target reference: object [sub    $0x8,%esp] vs BE [push   %esi]; BE instructions=50; Civ5 changed/new=UNVERIFIED.
	static bool CanUnitPillageAlienNest(const CvUnit&, const CvPlot&);
// TODO(Phase1 audit): CvAliens::GetFlagColorForPlayer UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=26; Civ5 changed/new=UNVERIFIED.
	static int GetFlagColorForPlayer(CvUnit&, PlayerTypes);
// TODO(Phase1 audit): CvAliens::OnPlayerOpinionChanged MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=110; Civ5 changed/new=UNVERIFIED.
	static void OnPlayerOpinionChanged(PlayerTypes);
// TODO(Phase1 audit): CvAliens::HasPlotActiveAlienRepel MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=72; Civ5 changed/new=UNVERIFIED.
	static bool HasPlotActiveAlienRepel(const CvPlot&);
// TODO(Phase1 audit): CvAliens::AddAlienUnitData UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=48; Civ5 changed/new=UNVERIFIED.
	static void AddAlienUnitData(CvUnit&, CvPlot&);
// TODO(Phase1 audit): CvAliens::AddDangerToPlotArea MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=252; Civ5 changed/new=UNVERIFIED.
	static void AddDangerToPlotArea(CvPlot&, int);
// TODO(Phase1 audit): CvAliens::ShouldSpawnAlienFromNest UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=16; Civ5 changed/new=UNVERIFIED.
	static bool ShouldSpawnAlienFromNest(CvPlot*);
// TODO(Phase1 audit): CvAliens::UpdateColossalUnitDisappearance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=275; Civ5 changed/new=UNVERIFIED.
	static void UpdateColossalUnitDisappearance(AlienUnitData&);
// TODO(Phase1 audit): CvAliens::DoColossalAlienDisappearance MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=86; Civ5 changed/new=UNVERIFIED.
	static void DoColossalAlienDisappearance(CvUnit&);
// TODO(Phase1 audit): CvAliens::IsAttractorPlot MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=47; Civ5 changed/new=UNVERIFIED.
	static bool IsAttractorPlot(const CvPlot&, int&);
// TODO(Phase1 audit): CvAliens::GetAggroForTarget MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=28; Civ5 changed/new=UNVERIFIED.
	static int GetAggroForTarget(IDInfo);
// TODO(Phase1 audit): CvAliens::GetHostilityFlagForPlayer MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=33; Civ5 changed/new=UNVERIFIED.
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
