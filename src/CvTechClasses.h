#pragma once
#include "CvGameCoreDLLUtil/CvEnums.h"

class CvTechXMLEntries;
class CvTeam;
class FDataStream;

class CvTechEntry: public CvBaseInfo
{
public:
	CvTechEntry(void);
	~CvTechEntry(void);

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	int GetFlavorValue(int i) const;
	int GetEra() const;
	const char* GetSound() const;
	const char* GetSoundMP() const;

	// Beyond Earth uses polar coordinates for the technology web.
	int GetGridRadius() const;
	int GetGridDegrees() const;
	int GetAffinityValue(AffinityType eAffinity) const;
	bool IsLeafTech() const;
	int GetNumConnectedTechs() const;
	TechTypes GetConnectedTechs(int iIndex) const;
	// TODO: CvTechEntry (remaining SDK methods and Beyond Earth members).
};

class CvTechXMLEntries
{
public:
	int GetNumTechs() const;
	CvTechEntry* GetEntry(int iIndex);
};

class CvTechAI
{
public:
	CvTechAI(CvPlayerTechs* currentTechs);
	~CvTechAI();
	void Reset();
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream) const;
	int GetQuestSpecificWeight(TechTypes eTech, int& iWeight, int& iPropagationPercent) const;
	void AddQuestWeights(int iWeight);
	void WeightConnections(int iTech, int iWeight, int iPropagationPercent, int iPropagationLevel);
	void AddFlavorWeights(FlavorTypes eFlavor, int iWeight, int iPropagationPercent);
	TechTypes ChooseNextTech(bool bFreeTech = false);
	void ReweightByAffinity();
	void ReweightByCost();
	void ReweightByStrategy();
	void LogPossibleResearch();
	void LogResearchChoice(TechTypes eTech);
	TechTypes RecommendNextTech(TechTypes eIgnoreTech = NO_TECH);
	float GetTechRatio();
	bool IsAffinityMatch(const CvPlayerAI& kPlayer, TechTypes eTech);
	bool HasLeafAffinityMatch(AffinityType eAffinity, TechTypes eTech, int* piWeight);
	bool IsAffinityBooster(TechTypes eTech, AffinityType* peAffinity, int* piWeight);
	bool ShouldBoostNonChosenAffinity(const CvPlayerAI& kPlayer) const;
	CvString GetLogFileName(CvString& playerName) const;
	int GetWeight(TechTypes eTech);

private:
	CvPlayerTechs* m_pCurrentTechs;
	CvWeightedVector<int, 80, true> m_TechAIWeights;
	CvWeightedVector<int, 80, true> m_ResearchableTechs;
};

class CvPlayerTechs
{
public:
	TechTypes GetCurrentResearch() const;
	CvTechXMLEntries* GetTechs() const;
	CvTechAI* GetTechAI() const;
	CvPlayer* GetPlayer();
	bool CanResearch(TechTypes eTech, bool bTrade = false) const;
	bool CanResearchForFree(TechTypes eTech) const;
	bool IsResearched(TechTypes eTech) const;
	int GetResearchTurnsLeft(TechTypes eTech, bool bOverflow) const;
	int GetNumTechsKnown() const;
};

class CvTeamTechs
{
public:
	CvTeamTechs(void);
	~CvTeamTechs(void);
	void Init(CvTechXMLEntries* pTechs, CvTeam* pTeam);
	void Uninit();
	void Reset();
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream);

	void SetHasTech(TechTypes eIndex, bool bNewValue);
	bool HasTech(TechTypes eIndex) const;
	TechTypes GetLastTechAcquired() const;
	void SetLastTechAcquired(TechTypes eTech);
	int GetNumTechsKnown() const;
	bool HasResearchedAllTechs() const;
	void SetNoTradeTech(TechTypes eIndex, bool bNewValue);
	bool IsNoTradeTech(TechTypes eIndex) const;
	void IncrementTechCount(TechTypes eIndex);
	int GetTechCount(TechTypes eIndex) const;
	void SetResearchProgress(TechTypes eIndex, int iNewValue, PlayerTypes ePlayer);
	void SetResearchProgressTimes100(TechTypes eIndex, int iNewValue, PlayerTypes ePlayer);
	int GetResearchProgress(TechTypes eIndex) const;
	int GetResearchProgressTimes100(TechTypes eIndex) const;
	void ChangeResearchProgress(TechTypes eIndex, int iChange, PlayerTypes ePlayer);
	void ChangeResearchProgressTimes100(TechTypes eIndex, int iChange, PlayerTypes ePlayer);
	int ChangeResearchProgressPercent(TechTypes eIndex, int iPercent, PlayerTypes ePlayer);
	int GetResearchCost(TechTypes eTech) const;
	int GetResearchLeft(TechTypes eTech) const;
	CvTechXMLEntries* GetTechs() const;

private:
	int GetMaxResearchOverflow(TechTypes eTech, PlayerTypes ePlayer) const;
	TechTypes m_eLastTechAcquired;
	bool* m_pabHasTech;
	bool* m_pabNoTradeTech;
	int* m_paiResearchProgress; // Stored in hundredths
	int* m_paiTechCount;
	CvTechXMLEntries* m_pTechs;
	CvTeam* m_pTeam;
};
