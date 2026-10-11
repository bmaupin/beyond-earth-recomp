#pragma once

#include "CvDllInterfaces.h"

class CvPlayerAI;

class CvDllPlayer : public ICvPlayer1
{
public:
	// TODO: Phase1 CvDllPlayer::CvDllPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvDllPlayer(_In_ CvPlayerAI* pPlayer);
	// TODO: Phase1 CvDllPlayer::~CvDllPlayer — MISMATCH: Non-padding instruction mnemonic sequence differs.
	~CvDllPlayer();
	// TODO: Phase1 CvDllPlayer::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
	void* DLLCALL QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	// TODO: Phase1 CvDllPlayer::DecrementReference — MISMATCH: Non-padding instruction mnemonic sequence differs.
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();
	// TODO: Phase1 CvDllPlayer::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
	static void operator delete(void* p);
	// TODO: Phase1 CvDllPlayer::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
	static void* operator new(size_t bytes);
	CvPlayerAI* GetInstance();

	// TODO: Phase1 CvDllPlayer::Init — UNVERIFIED: Full operand and relocation-target comparison not established.
	void Init(PlayerTypes eID);
	// TODO: Phase1 CvDllPlayer::SetupGraphical — UNVERIFIED: Full operand and relocation-target comparison not established.
	void SetupGraphical();
	// TODO: Phase1 CvDllPlayer::InitAffinityValues — UNVERIFIED: Full operand and relocation-target comparison not established.
	void InitAffinityValues();
	// TODO: Phase1 CvDllPlayer::LaterInit — UNVERIFIED: Full operand and relocation-target comparison not established.
	void LaterInit();
	// TODO: Phase1 CvDllPlayer::Uninit — UNVERIFIED: Full operand and relocation-target comparison not established.
	void Uninit();
	// TODO: Phase1 CvDllPlayer::IsHuman — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsHuman() const;
	// TODO: Phase1 CvDllPlayer::IsAlien — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsAlien() const;
	// TODO: Phase1 CvDllPlayer::IsObserver — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsObserver() const;
	// TODO: Phase1 CvDllPlayer::GetName — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* GetName() const;
	// TODO: Phase1 CvDllPlayer::GetNickName — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* GetNickName() const;
	// TODO: Phase1 CvDllPlayer::GetArtStyleType — UNVERIFIED: Full operand and relocation-target comparison not established.
	ArtStyleTypes GetArtStyleType() const;
	// TODO: Phase1 CvDllPlayer::GetFirstReadyUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvUnit1* GetFirstReadyUnit();
	// TODO: Phase1 CvDllPlayer::HasBusyUnit — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool HasBusyUnit() const;
	// TODO: Phase1 CvDllPlayer::HasBusyUnitOrCity — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool HasBusyUnitOrCity() const;
	// TODO: Phase1 CvDllPlayer::GetScore — UNVERIFIED: Full operand and relocation-target comparison not established.
	int GetScore(bool bFinal = false, bool bVictory = false) const;
	// TODO: Phase1 CvDllPlayer::GetStartingPlot — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvPlot1* GetStartingPlot() const;
	// TODO: Phase1 CvDllPlayer::GetCapitalCity — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvCity1* GetCapitalCity();
	// TODO: Phase1 CvDllPlayer::IsHasLostCapital — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsHasLostCapital() const;
	// TODO: Phase1 CvDllPlayer::SetStartTime — UNVERIFIED: Full operand and relocation-target comparison not established.
	void SetStartTime(unsigned int uiStartTime);
	// TODO: Phase1 CvDllPlayer::IsMinorCiv — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsMinorCiv() const;
	// TODO: Phase1 CvDllPlayer::IsAlive — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	bool IsAlive() const;
	// TODO: Phase1 CvDllPlayer::IsEverAlive — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	bool IsEverAlive() const;
	// TODO: Phase1 CvDllPlayer::IsTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsTurnActive() const;
	// TODO: Phase1 CvDllPlayer::GetID — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	PlayerTypes GetID() const;
	// TODO: Phase1 CvDllPlayer::GetHandicapType — UNVERIFIED: Full operand and relocation-target comparison not established.
	HandicapTypes GetHandicapType() const;
	// TODO: Phase1 CvDllPlayer::GetCivilizationType — UNVERIFIED: Full operand and relocation-target comparison not established.
	CivilizationTypes GetCivilizationType() const;
	// TODO: Phase1 CvDllPlayer::GetLeaderType — UNVERIFIED: Full operand and relocation-target comparison not established.
	LeaderHeadTypes GetLeaderType() const;
	// TODO: Phase1 CvDllPlayer::GetLeaderTypeKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* GetLeaderTypeKey() const;
	// TODO: Phase1 CvDllPlayer::GetCurrentEra — UNVERIFIED: Full operand and relocation-target comparison not established.
	EraTypes GetCurrentEra() const;
	// TODO: Phase1 CvDllPlayer::GetTeam — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	TeamTypes GetTeam() const;
	// TODO: Phase1 CvDllPlayer::GetPlayerColor — UNVERIFIED: Full operand and relocation-target comparison not established.
	PlayerColorTypes GetPlayerColor() const;
	// TODO: Phase1 CvDllPlayer::IsOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsOption(PlayerOptionTypes eOption) const;
	// TODO: Phase1 CvDllPlayer::FirstCity — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvCity1* FirstCity(int* pIterIdx, bool bRev = false);
	// TODO: Phase1 CvDllPlayer::NextCity — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvCity1* NextCity(int* pIterIdx, bool bRev = false);
	// TODO: Phase1 CvDllPlayer::GetNumCities — UNVERIFIED: Full operand and relocation-target comparison not established.
	int GetNumCities() const;
	// TODO: Phase1 CvDllPlayer::FirstOutpost — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvOutpost1* FirstOutpost(int* pIterIdx, bool bRev = false);
	// TODO: Phase1 CvDllPlayer::NextOutpost — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvOutpost1* NextOutpost(int* pIterIdx, bool bRev = false);
	// TODO: Phase1 CvDllPlayer::GetNumOutposts — UNVERIFIED: Full operand and relocation-target comparison not established.
	int GetNumOutposts() const;
	// TODO: Phase1 CvDllPlayer::GetCity — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvCity1* GetCity(int iID);
	// TODO: Phase1 CvDllPlayer::FirstUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvUnit1* FirstUnit(int* pIterIdx, bool bRev = false);
	// TODO: Phase1 CvDllPlayer::NextUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvUnit1* NextUnit(int* pIterIdx, bool bRev = false);
	// TODO: Phase1 CvDllPlayer::GetUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvUnit1* GetUnit(int iID);
	// TODO: Phase1 CvDllPlayer::GetPlotDanger — MISMATCH: Non-padding instruction mnemonic sequence differs.
	int GetPlotDanger(ICvPlot1* pPlot) const;
	// TODO: Phase1 CvDllPlayer::GetCityDistanceHighwaterMark — UNVERIFIED: Full operand and relocation-target comparison not established.
	int GetCityDistanceHighwaterMark() const;
	// TODO: Phase1 CvDllPlayer::Disconnected — UNVERIFIED: Full operand and relocation-target comparison not established.
	void Disconnected();
	// TODO: Phase1 CvDllPlayer::Reconnected — UNVERIFIED: Full operand and relocation-target comparison not established.
	void Reconnected();
	// TODO: Phase1 CvDllPlayer::SetBusyUnitUpdatesRemaining — UNVERIFIED: Full operand and relocation-target comparison not established.
	void SetBusyUnitUpdatesRemaining(int iUpdateCount);
	// TODO: Phase1 CvDllPlayer::HasUnitsThatNeedAIUpdate — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool HasUnitsThatNeedAIUpdate() const;
	// TODO: Phase1 CvDllPlayer::GetDominantAffinity — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	AffinityType GetDominantAffinity() const;
	// TODO: Phase1 CvDllPlayer::GetAffinityLevel — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	int GetAffinityLevel(AffinityType eAffinity) const;
	// TODO: Phase1 CvDllPlayer::GetAffinityPercentTowardsMaxLevel — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	int GetAffinityPercentTowardsMaxLevel(AffinityType eAffinity) const;
	// TODO: Phase1 CvDllPlayer::GetNumPolicyBranchesFinished — UNVERIFIED: Full operand and relocation-target comparison not established.
	int GetNumPolicyBranchesFinished() const;
	// TODO: Phase1 CvDllPlayer::Read — UNVERIFIED: Full operand and relocation-target comparison not established.
	void Read(FDataStream& kStream);
	// TODO: Phase1 CvDllPlayer::Write — UNVERIFIED: Full operand and relocation-target comparison not established.
	void Write(FDataStream& kStream) const;
	// TODO: Phase1 CvDllPlayer::GetEnergy — UNVERIFIED: Full operand and relocation-target comparison not established.
	int GetEnergy() const;
	// TODO: Phase1 CvDllPlayer::CalculateBaseNetGold — UNVERIFIED: Full operand and relocation-target comparison not established.
	int CalculateBaseNetGold();
	// TODO: Phase1 CvDllPlayer::GetEmbarkedGraphicOverride — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	const char* GetEmbarkedGraphicOverride();
	// TODO: Phase1 CvDllPlayer::GetSyncArchive — UNVERIFIED: Full operand and relocation-target comparison not established.
	FAutoArchive& GetSyncArchive();
	// TODO: Phase1 CvDllPlayer::GetMinorCivType — UNVERIFIED: Full operand and relocation-target comparison not established.
	MinorCivTypes GetMinorCivType() const;
	// TODO: Phase1 CvDllPlayer::GetDiplomacyAI — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvDiplomacyAI1* GetDiplomacyAI();
	// TODO: Phase1 CvDllPlayer::GetDealAI — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvDealAI1* GetDealAI();
	// TODO: Phase1 CvDllPlayer::AddDiplomacyRequest — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool AddDiplomacyRequest(PlayerTypes ePlayer, DiploUIStateTypes eState, const char* message, LeaderheadAnimationTypes eAnimation, int iExtraGameData = -1);
	// TODO: Phase1 CvDllPlayer::ActiveDiplomacyRequestComplete — UNVERIFIED: Full operand and relocation-target comparison not established.
	void ActiveDiplomacyRequestComplete();
	// TODO: Phase1 CvDllPlayer::AddNotification — UNVERIFIED: Full operand and relocation-target comparison not established.
	int AddNotification(NotificationTypes eType, const char* message, const char* summary, int iX, int iY, int iGameDataIndex, int iExtraGameData = -1);
	// TODO: Phase1 CvDllPlayer::ActivateNotification — UNVERIFIED: Full operand and relocation-target comparison not established.
	void ActivateNotification(int iLookupIndex);
	// TODO: Phase1 CvDllPlayer::DismissNotification — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DismissNotification(int iLookupIndex, bool bUserInvoked);
	// TODO: Phase1 CvDllPlayer::MayUserDismissNotification — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool MayUserDismissNotification(int iLookupIndex);
	// TODO: Phase1 CvDllPlayer::RebroadcastNotifications — UNVERIFIED: Full operand and relocation-target comparison not established.
	void RebroadcastNotifications();
	// TODO: Phase1 CvDllPlayer::GetCurrentResearchTech — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool GetCurrentResearchTech(TechTypes* pTech, int* pTurnsLeft) const;
	// TODO: Phase1 CvDllPlayer::IsSimultaneousTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsSimultaneousTurns() const;
	// TODO: Phase1 CvDllPlayer::HasTurnTimerExpired — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool HasTurnTimerExpired();
	// TODO: Phase1 CvDllPlayer::IsOptionKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool IsOptionKey(PlayerOptionTypes eOption) const;
	// TODO: Phase1 CvDllPlayer::MayNotAnnex — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	bool MayNotAnnex();
	// TODO: Phase1 CvDllPlayer::HasCompletedLoadout — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	bool HasCompletedLoadout() const;
	// TODO: Phase1 CvDllPlayer::GetBestUnitUpgrade — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	void GetBestUnitUpgrade(UnitTypes eUnit, UnitUpgradeTypes& eUpgrade, UnitPerkTypes& ePerk);
	// TODO: Phase1 CvDllPlayer::WaitForEffect — UNVERIFIED: Full operand and relocation-target comparison not established.
	void WaitForEffect(bool bWait);
	// TODO: Phase1 CvDllPlayer::GetCovertAgents — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	std::vector<std::unique_ptr<ICvCovertAgent1> > GetCovertAgents() const;
	// TODO: Phase1 CvDllPlayer::GetCovertAgentByIndex — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
	std::unique_ptr<ICvCovertAgent1> GetCovertAgentByIndex(int iIndex) const;
	// TODO: Phase1 CvDllPlayer::HasMadePlanetfall — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool HasMadePlanetfall() const;

	// TODO: Phase1 CvDllPlayer::GetOutpost — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvOutpost1* GetOutpost(int iID);
	// TODO: Phase1 CvDllPlayer::SetTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
	void SetTurnActive(bool bNewValue, bool bDoTurn = true);

private:
	// TODO: Phase1 CvDllPlayer::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Destroy();
	unsigned int m_uiRefCount;
	CvPlayerAI* m_pPlayer;
};
