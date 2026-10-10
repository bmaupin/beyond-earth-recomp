#pragma once

#include "CvDllInterfaces.h"

class CvPlayerAI;

class CvDllPlayer : public ICvPlayer1
{
public:
	CvDllPlayer(_In_ CvPlayerAI* pPlayer);
	~CvDllPlayer();
	void* DLLCALL QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();
	static void operator delete(void* p);
	static void* operator new(size_t bytes);
	CvPlayerAI* GetInstance();

	void Init(PlayerTypes eID);
	void SetupGraphical();
	void InitAffinityValues();
	void LaterInit();
	void Uninit();
	bool IsHuman() const;
	bool IsAlien() const;
	bool IsObserver() const;
	const char* GetName() const;
	const char* GetNickName() const;
	ArtStyleTypes GetArtStyleType() const;
	ICvUnit1* GetFirstReadyUnit();
	bool HasBusyUnit() const;
	bool HasBusyUnitOrCity() const;
	int GetScore(bool bFinal = false, bool bVictory = false) const;
	ICvPlot1* GetStartingPlot() const;
	ICvCity1* GetCapitalCity();
	bool IsHasLostCapital() const;
	void SetStartTime(unsigned int uiStartTime);
	bool IsMinorCiv() const;
	bool IsAlive() const;
	bool IsEverAlive() const;
	bool IsTurnActive() const;
	PlayerTypes GetID() const;
	HandicapTypes GetHandicapType() const;
	CivilizationTypes GetCivilizationType() const;
	LeaderHeadTypes GetLeaderType() const;
	const char* GetLeaderTypeKey() const;
	EraTypes GetCurrentEra() const;
	TeamTypes GetTeam() const;
	PlayerColorTypes GetPlayerColor() const;
	bool IsOption(PlayerOptionTypes eOption) const;
	ICvCity1* FirstCity(int* pIterIdx, bool bRev = false);
	ICvCity1* NextCity(int* pIterIdx, bool bRev = false);
	int GetNumCities() const;
	ICvOutpost1* FirstOutpost(int* pIterIdx, bool bRev = false);
	ICvOutpost1* NextOutpost(int* pIterIdx, bool bRev = false);
	int GetNumOutposts() const;
	ICvCity1* GetCity(int iID);
	ICvUnit1* FirstUnit(int* pIterIdx, bool bRev = false);
	ICvUnit1* NextUnit(int* pIterIdx, bool bRev = false);
	ICvUnit1* GetUnit(int iID);
	int GetPlotDanger(ICvPlot1* pPlot) const;
	int GetCityDistanceHighwaterMark() const;
	void Disconnected();
	void Reconnected();
	void SetBusyUnitUpdatesRemaining(int iUpdateCount);
	bool HasUnitsThatNeedAIUpdate() const;
	AffinityType GetDominantAffinity() const;
	int GetAffinityLevel(AffinityType eAffinity) const;
	int GetAffinityPercentTowardsMaxLevel(AffinityType eAffinity) const;
	int GetNumPolicyBranchesFinished() const;
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream) const;
	int GetEnergy() const;
	int CalculateBaseNetGold();
	const char* GetEmbarkedGraphicOverride();
	FAutoArchive& GetSyncArchive();
	MinorCivTypes GetMinorCivType() const;
	ICvDiplomacyAI1* GetDiplomacyAI();
	ICvDealAI1* GetDealAI();
	bool AddDiplomacyRequest(PlayerTypes ePlayer, DiploUIStateTypes eState, const char* message, LeaderheadAnimationTypes eAnimation, int iExtraGameData = -1);
	void ActiveDiplomacyRequestComplete();
	int AddNotification(NotificationTypes eType, const char* message, const char* summary, int iX, int iY, int iGameDataIndex, int iExtraGameData = -1);
	void ActivateNotification(int iLookupIndex);
	void DismissNotification(int iLookupIndex, bool bUserInvoked);
	bool MayUserDismissNotification(int iLookupIndex);
	void RebroadcastNotifications();
	bool GetCurrentResearchTech(TechTypes* pTech, int* pTurnsLeft) const;
	bool IsSimultaneousTurns() const;
	bool HasTurnTimerExpired();
	bool IsOptionKey(PlayerOptionTypes eOption) const;
	bool MayNotAnnex();
	bool HasCompletedLoadout() const;
	void GetBestUnitUpgrade(UnitTypes eUnit, UnitUpgradeTypes& eUpgrade, UnitPerkTypes& ePerk);
	void WaitForEffect(bool bWait);
	std::vector<std::unique_ptr<ICvCovertAgent1> > GetCovertAgents() const;
	std::unique_ptr<ICvCovertAgent1> GetCovertAgentByIndex(int iIndex) const;
	bool HasMadePlanetfall() const;

	ICvOutpost1* GetOutpost(int iID);
	void SetTurnActive(bool bNewValue, bool bDoTurn = true);

private:
	void DLLCALL Destroy();
	unsigned int m_uiRefCount;
	CvPlayerAI* m_pPlayer;
};
