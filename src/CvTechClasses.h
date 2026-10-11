#pragma once
#include "CvInfos.h"
#include "CvFlavorManager.h"
#include "CvGameCoreDLLUtil/include/CvWeightedVector.h"
#include <vector>

class CvTeam;
class CvPlayer;
class CvPlayerAI;
class CvPlayerTechs;
class FDataStream;

class CvTechEntry : public CvBaseInfo
{
public:
 CvTechEntry();
 ~CvTechEntry();
 virtual bool CacheResults(Database::Results&, CvDatabaseUtility&);
 int GetAIWeight() const;
 int GetAITradeModifier() const;
 int GetResearchCost() const;
 int GetAdvancedStartCost() const;
 int GetEra() const;
 int GetFeatureProductionModifier() const;
 int GetUnitFortificationModifier() const;
 int GetUnitBaseHealModifier() const;
 int GetUnitBaseMiasmaHeal() const;
 int GetWorkerSpeedModifier() const;
 int GetFirstFreeUnitClass() const;
 int GetFirstFreeTechs() const;
 int GetEmbarkedMoveChange() const;
 int GetNumInternationalTradeRoutesChange() const;
 int GetInfluenceSpreadModifier() const;
 int GetExtraVotesPerDiplomat() const;
 float GetGridRadius() const;
 int GetGridDegrees() const;
 bool IsLeafTech() const;
 bool IsEndsGame() const;
 bool IsAllowsEmbarking() const;
 bool IsAllowsDeepWaterCityMove() const;
 bool IsRepeat() const;
 bool IsTrade() const;
 bool IsDisable() const;
 bool IsGoodyTech() const;
 bool IsExtraWaterSeeFrom() const;
 bool IsMapCentering() const;
 bool IsMapVisible() const;
 bool IsMapTrading() const;
 bool IsTechTrading() const;
 bool IsGoldTrading() const;
 bool IsBridgeBuilding() const;
 bool IsWaterWork() const;
 bool IsTriggersArchaeologicalSites() const;
 bool IsAllowsMiasmaImmunity() const;
 int IsFreePromotion(int) const;
 bool IsFreePlayerPerk(int) const;
 const char* GetQuote();
 void SetQuoteKey(const char*);
 const char* GetSound() const;
 void SetSound(const char*);
 const char* GetSoundMP() const;
 void SetSoundMP(const char*);
 int GetAffinityValue(AffinityType) const;
 int GetDomainExtraMoves(int) const;
 int GetTradeRouteDomainExtraRange(int) const;
 int GetFlavorValue(int) const;
 int GetNumConnectedTechs() const;
 TechTypes GetConnectedTechs(int) const;
private:
 int m_iAIWeight, m_iAITradeModifier, m_iResearchCost, m_iAdvancedStartCost, m_iEra;
 int m_iFeatureProductionModifier, m_iUnitFortificationModifier, m_iUnitBaseHealModifier, m_iUnitBaseMiasmaHeal;
 int m_iWorkerSpeedModifier, m_iFirstFreeUnitClass, m_iFirstFreeTechs, m_iEmbarkedMoveChange;
 int m_iInternationalTradeRoutesChange, m_iInfluenceSpreadModifier, m_iExtraVotesPerDiplomat;
 float m_gridRadius;
 int m_gridDegrees;
 bool m_leafTech, m_bEndsGame, m_bAllowsEmbarking, m_bAllowsAmphibiousTraders, m_bAllowsDeepWaterCityMove;
 bool m_bRepeat, m_bTrade, m_bDisable, m_bGoodyTech, m_bExtraWaterSeeFrom, m_bMapCentering, m_bMapVisible;
 bool m_bMapTrading, m_bTechTrading, m_bGoldTrading, m_bBridgeBuilding, m_bWaterWork;
 bool m_bTriggersArchaeologicalSites, m_bAllowsMiasmaImmunity;
 CvString m_strQuoteKey, m_wstrQuote, m_strSound, m_strSoundMP;
 int *m_piAffinities, *m_piDomainExtraMoves, *m_piTradeRouteDomainExtraRange, *m_piFlavorValue;
 int *m_piPrereqOrTechs, *m_piPrereqAndTechs;
 bool *m_pabFreePlayerPerks, *m_pabFreePromotion;
 std::vector<int> m_ConnectedTechs;
};

class CvTechXMLEntries
{
public:
 CvTechXMLEntries();
 ~CvTechXMLEntries();
 std::vector<CvTechEntry*>& GetTechEntries();
 const std::vector<CvTechEntry*>& GetTechEntries() const;
 int GetNumTechs();
 CvTechEntry* GetEntry(int);
 void DeleteArray();
private:
 std::vector<CvTechEntry*> m_paTechEntries;
};
class CvTechAI
{
public:
	CvTechAI(CvPlayerTechs* currentTechs);
// TODO(Phase1 audit): CvTechAI::~CvTechAI UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	~CvTechAI();
// TODO(Phase1 audit): CvTechAI::Reset UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=41; Civ5 changed/new=UNVERIFIED.
	void Reset();
// TODO(Phase1 audit): CvTechAI::Read UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=73; Civ5 changed/new=UNVERIFIED.
	void Read(FDataStream& kStream);
// TODO(Phase1 audit): CvTechAI::Write UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=47; Civ5 changed/new=UNVERIFIED.
	void Write(FDataStream& kStream) const;
// TODO(Phase1 audit): CvTechAI::GetQuestSpecificWeight UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=95; Civ5 changed/new=UNVERIFIED.
	int GetQuestSpecificWeight(TechTypes eTech, int& iWeight, int& iPropagationPercent) const;
// TODO(Phase1 audit): CvTechAI::AddQuestWeights MISMATCH: Instruction 2 differs before first target reference: object [push   %ebx] vs BE [mov    %esp,%ebp]; BE instructions=133; Civ5 changed/new=UNVERIFIED.
	void AddQuestWeights(int iWeight);
// TODO(Phase1 audit): CvTechAI::WeightConnections MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x5c,%esp] vs BE [sub    $0xac,%esp]; BE instructions=256; Civ5 changed/new=UNVERIFIED.
	void WeightConnections(int iTech, int iWeight, int iPropagationPercent, int iPropagationLevel);
// TODO(Phase1 audit): CvTechAI::AddFlavorWeights MISMATCH: Instruction 2 differs before first target reference: object [push   %ebx] vs BE [mov    %esp,%ebp]; BE instructions=127; Civ5 changed/new=UNVERIFIED.
	void AddFlavorWeights(FlavorTypes eFlavor, int iWeight, int iPropagationPercent);
// TODO(Phase1 audit): CvTechAI::ChooseNextTech UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=120; Civ5 changed/new=UNVERIFIED.
	TechTypes ChooseNextTech(bool bFreeTech = false);
// TODO(Phase1 audit): CvTechAI::ReweightByAffinity UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=84; Civ5 changed/new=UNVERIFIED.
	void ReweightByAffinity();
// TODO(Phase1 audit): CvTechAI::ReweightByCost MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x3c,%esp] vs BE [sub    $0x1c,%esp]; BE instructions=46; Civ5 changed/new=UNVERIFIED.
	void ReweightByCost();
// TODO(Phase1 audit): CvTechAI::ReweightByStrategy UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=75; Civ5 changed/new=UNVERIFIED.
	void ReweightByStrategy();
// TODO(Phase1 audit): CvTechAI::LogPossibleResearch MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x4c,%esp] vs BE [sub    $0x9c,%esp]; BE instructions=295; Civ5 changed/new=UNVERIFIED.
	void LogPossibleResearch();
// TODO(Phase1 audit): CvTechAI::LogResearchChoice MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x3c,%esp] vs BE [sub    $0x8c,%esp]; BE instructions=210; Civ5 changed/new=UNVERIFIED.
	void LogResearchChoice(TechTypes eTech);
// TODO(Phase1 audit): CvTechAI::RecommendNextTech MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x2c,%esp] vs BE [sub    $0x1c,%esp]; BE instructions=85; Civ5 changed/new=UNVERIFIED.
	TechTypes RecommendNextTech(TechTypes eIgnoreTech = NO_TECH);
// TODO(Phase1 audit): CvTechAI::GetTechRatio MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x3c,%esp] vs BE [sub    $0x5c,%esp]; BE instructions=151; Civ5 changed/new=UNVERIFIED.
	float GetTechRatio();
// TODO(Phase1 audit): CvTechAI::IsAffinityMatch MISMATCH: Instruction 2 differs before first target reference: object [push   %edi] vs BE [push   %esi]; BE instructions=29; Civ5 changed/new=UNVERIFIED.
	bool IsAffinityMatch(const CvPlayerAI& kPlayer, TechTypes eTech);
// TODO(Phase1 audit): CvTechAI::HasLeafAffinityMatch UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=67; Civ5 changed/new=UNVERIFIED.
	bool HasLeafAffinityMatch(AffinityType eAffinity, TechTypes eTech, int* piWeight);
// TODO(Phase1 audit): CvTechAI::IsAffinityBooster UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=51; Civ5 changed/new=UNVERIFIED.
	bool IsAffinityBooster(TechTypes eTech, AffinityType* peAffinity, int* piWeight);
// TODO(Phase1 audit): CvTechAI::ShouldBoostNonChosenAffinity MISMATCH: Instruction 2 differs before first target reference: object [push   %edi] vs BE [sub    $0x8,%esp]; BE instructions=24; Civ5 changed/new=UNVERIFIED.
	bool ShouldBoostNonChosenAffinity(const CvPlayerAI& kPlayer) const;
// TODO(Phase1 audit): CvTechAI::GetLogFileName MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=83; Civ5 changed/new=UNVERIFIED.
	CvString GetLogFileName(CvString& playerName) const;
// TODO(Phase1 audit): CvTechAI::GetWeight MISMATCH: First instruction opcode differs: object push, BE mov; BE instructions=5; Civ5 changed/new=UNVERIFIED.
	int GetWeight(TechTypes eTech);

private:
	CvPlayerTechs* m_pCurrentTechs;
	CvWeightedVector<int, 80, true> m_TechAIWeights;
	CvWeightedVector<int, 80, true> m_ResearchableTechs;
};

class CvPlayerTechs : public CvFlavorRecipient
{
public:
 CvPlayerTechs();
 ~CvPlayerTechs();
 void Init(CvTechXMLEntries*, CvPlayer*, bool);
 virtual void Uninit();
 void Reset();
 void Read(FDataStream&);
 void Write(FDataStream&);
 virtual void FlavorUpdate();
 CvPlayer* GetPlayer();
 CvTechAI* GetTechAI();
 void SetResearchingTech(TechTypes, bool);
 bool IsResearchingTech(TechTypes) const;
 void SetCivTechPriority(TechTypes, int);
 int GetCivTechPriority(TechTypes) const;
 void SetLocaleTechPriority(TechTypes, int);
 int GetLocaleTechPriority(TechTypes) const;
 ResourceTypes GetLocaleTechResource(TechTypes) const;
 UnitTypes GetCivTechUniqueUnit(TechTypes) const;
 BuildingTypes GetCivTechUniqueBuilding(TechTypes) const;
 ImprovementTypes GetCivTechUniqueImprovement(TechTypes) const;
 void SetLocalePriorities();
 bool IsResearch() const;
 bool IsResearched(TechTypes) const;
 bool CanEverResearch(TechTypes) const;
 bool CanResearch(TechTypes, bool = false) const;
 bool CanResearchForFree(TechTypes) const;
 TechTypes GetCurrentResearch() const;
 bool IsCurrentResearchRepeat() const;
 bool IsNoResearchAvailable() const;
 void CheckForTechAchievement() const;
 int GetResearchTurnsLeft(TechTypes, bool) const;
 int GetResearchTurnsLeftTimes100(TechTypes, bool) const;
 int GetNumTechsCanBeResearched() const;
 CvTechXMLEntries* GetTechs() const;
 int GetResearchCost(TechTypes) const;
 int GetResearchProgress(TechTypes) const;
 int GetMedianTechResearch() const;
 int GetNumTechsKnown() const;
 std::vector<TechTypes> GetAllAvailableTechs() const;
 std::vector<const CvTechEntry*> GetPathToTech(const CvTechEntry*, const CvTechEntry*) const;
 void AddFlavorAsStrategies(int);
protected:
 virtual void LogFlavors(FlavorTypes = NO_FLAVOR);
private:
 bool* m_pabResearchingTech;
 int *m_piCivTechPriority, *m_piLocaleTechPriority;
 ResourceTypes* m_peLocaleTechResources;
 UnitTypes* m_peCivTechUniqueUnits;
 BuildingTypes* m_peCivTechUniqueBuildings;
 ImprovementTypes* m_peCivTechUniqueImprovements;
 CvTechXMLEntries* m_pTechs;
 CvPlayer* m_pPlayer;
 CvTechAI* m_pTechAI;
};

class CvTeamTechs
{
public:
 CvTeamTechs();
 ~CvTeamTechs();
 void Init(CvTechXMLEntries*, CvTeam*);
 void Uninit();
 void Reset();
 void Read(FDataStream&);
 void Write(FDataStream&);
 void SetHasTech(TechTypes, bool);
 bool HasTech(TechTypes) const;
 TechTypes GetLastTechAcquired() const;
 void SetLastTechAcquired(TechTypes);
 int GetNumTechsKnown() const;
 bool HasResearchedAllTechs() const;
 void SetNoTradeTech(TechTypes, bool);
 bool IsNoTradeTech(TechTypes) const;
 void IncrementTechCount(TechTypes);
 int GetTechCount(TechTypes) const;
 void SetResearchProgress(TechTypes, int, PlayerTypes);
 void SetResearchProgressTimes100(TechTypes, int, PlayerTypes);
 int GetResearchProgress(TechTypes) const;
 int GetResearchProgressTimes100(TechTypes) const;
 void ChangeResearchProgress(TechTypes, int, PlayerTypes);
 void ChangeResearchProgressTimes100(TechTypes, int, PlayerTypes);
 int ChangeResearchProgressPercent(TechTypes, int, PlayerTypes);
 int GetResearchCost(TechTypes) const;
 int GetResearchLeft(TechTypes) const;
 CvTechXMLEntries* GetTechs() const;
private:
 TechTypes m_eLastTechAcquired;
 bool *m_pabHasTech, *m_pabNoTradeTech;
 int *m_paiResearchProgress, *m_paiTechCount;
 CvTechXMLEntries* m_pTechs;
 CvTeam* m_pTeam;
};

template<class T, unsigned int Alignment, unsigned int Tag, unsigned int SubTag> class FSTL_Tagged_Allocator;
template<class T, class U> struct CvGraphPolicyBase
{
 typedef T NodeType;
 typedef U ExtraDataType;
};
template<class T, class U, class A> struct CvGraphTraversalPolicy : CvGraphPolicyBase<T, U>
{
 virtual const T* GetConnectedNode(const T&, int, const U*) const = 0;
 virtual int GetNumConnectedNodes(const T&, const U*) const = 0;
 virtual bool Compare(const T&, const T&, const U*) const = 0;
};
template<class T, class U> struct CvGraphHeuristicPolicy : CvGraphPolicyBase<T, U>
{
 virtual float GetH(const T&, const T&, const U*) const = 0;
};
template<class T, class U> struct CvGraphCostPolicy : CvGraphPolicyBase<T, U>
{
 virtual float GetCost(const T&, const T&, const U*) const = 0;
};
class CvTechGraphTraversalPolicy : public CvGraphTraversalPolicy<CvTechEntry, CvPlayer, FSTL_Tagged_Allocator<CvTechEntry, 32, 19, 4> >
{
public:
 virtual const CvTechEntry* GetConnectedNode(const CvTechEntry&, int, const CvPlayer*) const;
 virtual int GetNumConnectedNodes(const CvTechEntry&, const CvPlayer*) const;
 virtual bool Compare(const CvTechEntry&, const CvTechEntry&, const CvPlayer*) const;
 const CvPlayer* m_player;
};
class CvTechGraphHeuristicPolicy : public CvGraphHeuristicPolicy<CvTechEntry, CvPlayer>
{
public:
 virtual float GetH(const CvTechEntry&, const CvTechEntry&, const CvPlayer*) const;
 const CvPlayer* m_player;
};
class CvTechGraphResearchCostPolicy : public CvGraphCostPolicy<CvTechEntry, CvPlayer>
{
public:
 virtual float GetCost(const CvTechEntry&, const CvTechEntry&, const CvPlayer*) const;
 const CvPlayer* m_player;
};
class CvTechGraphFlatCostPolicy : public CvGraphCostPolicy<CvTechEntry, CvPlayer>
{
public:
 virtual float GetCost(const CvTechEntry&, const CvTechEntry&, const CvPlayer*) const;
};
template<class Traversal, class Heuristic, class Cost>
class CvGraphSearch : public Traversal, public Heuristic, public Cost
{
public:
 typedef typename Traversal::NodeType NodeType;
 typedef typename Traversal::ExtraDataType ExtraDataType;
 explicit CvGraphSearch(const ExtraDataType* data) : m_ExtraData(data) {}
 std::vector<const NodeType*> GetPath(const NodeType&, const NodeType&, float&) const;
 const ExtraDataType* m_ExtraData;
};
