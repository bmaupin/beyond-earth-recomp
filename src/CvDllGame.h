#pragma once

#include "CvDllInterfaces.h"

class CvGame;
class CvStation;

class CvDllGame : public ICvGame1
{
public:
	// TODO: Phase1 CvDllGame::CvDllGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvDllGame(CvGame* pGame);
	// TODO: Phase1 CvDllGame::~CvDllGame — MISMATCH: Non-padding instruction mnemonic sequence differs.
	~CvDllGame();

	// TODO: Phase1 CvDllGame::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
	void* DLLCALL QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	// TODO: Phase1 CvDllGame::DecrementReference — MISMATCH: Non-padding instruction mnemonic sequence differs.
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();
	// TODO: Phase1 CvDllGame::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
	static void operator delete(void* p);
	// TODO: Phase1 CvDllGame::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
	static void* operator new(size_t bytes);

	// TODO: Phase1 CvDllGame::GetPlayer — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvPlayer1* DLLCALL GetPlayer(PlayerTypes ePlayer);
	CvGame* GetInstance();
	// TODO: Phase1 CvDllGame::InitFromLoad — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL InitFromLoad();
	// TODO: Phase1 CvDllGame::GetActivePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	PlayerTypes DLLCALL GetActivePlayer();
	// TODO: Phase1 CvDllGame::GetActiveTeam — UNVERIFIED: Full operand and relocation-target comparison not established.
	TeamTypes DLLCALL GetActiveTeam();
	// TODO: Phase1 CvDllGame::GetGameTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetGameTurn() const;
	// TODO: Phase1 CvDllGame::ChangeNumGameTurnActive — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	void DLLCALL ChangeNumGameTurnActive(int iChange, const char* why);
	// TODO: Phase1 CvDllGame::CountHumanPlayersAlive — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL CountHumanPlayersAlive() const;
	// TODO: Phase1 CvDllGame::CountNumHumanGameTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL CountNumHumanGameTurnActive();
	// TODO: Phase1 CvDllGame::CyclePlotUnits — MISMATCH: Non-padding instruction mnemonic sequence differs.
	bool DLLCALL CyclePlotUnits(ICvPlot1* pPlot, bool bForward = true, bool bAuto = false, int iCount = -1);
	// TODO: Phase1 CvDllGame::CycleUnits — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL CycleUnits(bool bClear, bool bForward = true, bool bWorkers = false);
	// TODO: Phase1 CvDllGame::DoGameStarted — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL DoGameStarted();
	// TODO: Phase1 CvDllGame::EndTurnTimerReset — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL EndTurnTimerReset();
	// TODO: Phase1 CvDllGame::EndTurnTimerSemaphoreDecrement — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL EndTurnTimerSemaphoreDecrement();
	// TODO: Phase1 CvDllGame::EndTurnTimerSemaphoreIncrement — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL EndTurnTimerSemaphoreIncrement();
	// TODO: Phase1 CvDllGame::GetAction — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl);
	// TODO: Phase1 CvDllGame::IsAction — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL IsAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl);
	// TODO: Phase1 CvDllGame::GetElapsedGameTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetElapsedGameTurns() const;
	// TODO: Phase1 CvDllGame::GetFOW — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL GetFOW();
	// TODO: Phase1 CvDllGame::GetGameDeals — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvGameDeals1* DLLCALL GetGameDeals();
	// TODO: Phase1 CvDllGame::GetGameSpeedType — UNVERIFIED: Full operand and relocation-target comparison not established.
	GameSpeedTypes DLLCALL GetGameSpeedType() const;
	// TODO: Phase1 CvDllGame::GetGameState — UNVERIFIED: Full operand and relocation-target comparison not established.
	GameStateTypes DLLCALL GetGameState();
	// TODO: Phase1 CvDllGame::HasGameEverBeenExtended — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL HasGameEverBeenExtended();
	// TODO: Phase1 CvDllGame::GetHandicapType — UNVERIFIED: Full operand and relocation-target comparison not established.
	HandicapTypes DLLCALL GetHandicapType() const;
	// TODO: Phase1 CvDllGame::GetRandomNumberGenerator — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvRandom1* DLLCALL GetRandomNumberGenerator();
	// TODO: Phase1 CvDllGame::GetJonRandNum — MISMATCH: Current relocations reference target-absent imports: _ZN6CvGame13getJonRandNumEiPKc.
	int DLLCALL GetJonRandNum(int iNum, const char* pszLog);
	// TODO: Phase1 CvDllGame::GetMaxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetMaxTurns() const;
	// TODO: Phase1 CvDllGame::GetNumGameTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetNumGameTurnActive();
	// TODO: Phase1 CvDllGame::GetPausePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	PlayerTypes DLLCALL GetPausePlayer();
	// TODO: Phase1 CvDllGame::GetPbemTurnSent — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL GetPbemTurnSent() const;
	// TODO: Phase1 CvDllGame::GetPlotUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvUnit1* DLLCALL GetPlotUnit(ICvPlot1* pPlot, int iIndex);
	// TODO: Phase1 CvDllGame::GetVictory — UNVERIFIED: Full operand and relocation-target comparison not established.
	VictoryTypes DLLCALL GetVictory() const;
	// TODO: Phase1 CvDllGame::GetVotesNeededForDiploVictory — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetVotesNeededForDiploVictory() const;
	// TODO: Phase1 CvDllGame::GetWinner — UNVERIFIED: Full operand and relocation-target comparison not established.
	TeamTypes DLLCALL GetWinner() const;
	// TODO: Phase1 CvDllGame::GetWinningTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetWinningTurn() const;
	// TODO: Phase1 CvDllGame::HandleAction — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL HandleAction(int iAction);
	bool DLLCALL HasTurnTimerExpired();
	// TODO: Phase1 CvDllGame::HasTurnTimerExpired — UNVERIFIED: Overloads have differing audit results; complete signature-specific comparison remains necessary.
	bool DLLCALL HasTurnTimerExpired(PlayerTypes playerID);
	// TODO: Phase1 CvDllGame::TurnTimerSync — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL TurnTimerSync(float fCurTurnTime, float fTurnStartTime);
	// TODO: Phase1 CvDllGame::GetTurnTimerData — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL GetTurnTimerData(float& fCurTurnTime, float& fTurnStartTime);
	// TODO: Phase1 CvDllGame::Init — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Init(HandicapTypes eHandicap);
	// TODO: Phase1 CvDllGame::Init2 — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL Init2();
	// TODO: Phase1 CvDllGame::InitScoreCalculation — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL InitScoreCalculation();
	// TODO: Phase1 CvDllGame::InitTacticalAnalysisMap — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL InitTacticalAnalysisMap(int iNumPlots);
	// TODO: Phase1 CvDllGame::IsCityScreenBlocked — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsCityScreenBlocked();
	// TODO: Phase1 CvDllGame::CanOpenCityScreen — MISMATCH: Non-padding instruction mnemonic sequence differs.
	bool DLLCALL CanOpenCityScreen(PlayerTypes eOpener, ICvCity1* pCity);
	// TODO: Phase1 CvDllGame::IsDebugMode — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsDebugMode() const;
	// TODO: Phase1 CvDllGame::IsFinalInitialized — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsFinalInitialized() const;
	// TODO: Phase1 CvDllGame::IsGameMultiPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsGameMultiPlayer() const;
	// TODO: Phase1 CvDllGame::IsHotSeat — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsHotSeat() const;
	// TODO: Phase1 CvDllGame::IsMPOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsMPOption(MultiplayerOptionTypes eIndex) const;
	// TODO: Phase1 CvDllGame::IsNetworkMultiPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsNetworkMultiPlayer() const;
	// TODO: Phase1 CvDllGame::IsOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsOption(GameOptionTypes eIndex) const;
	// TODO: Phase1 CvDllGame::IsPaused — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsPaused();
	// TODO: Phase1 CvDllGame::IsPbem — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsPbem() const;
	// TODO: Phase1 CvDllGame::IsTeamGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL IsTeamGame() const;
	// TODO: Phase1 CvDllGame::LogGameState — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL LogGameState(bool bLogHeaders = false);
	// TODO: Phase1 CvDllGame::ResetTurnTimer — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL ResetTurnTimer();
	// TODO: Phase1 CvDllGame::SelectAll — MISMATCH: Non-padding instruction mnemonic sequence differs.
	void DLLCALL SelectAll(ICvPlot1* pPlot);
	// TODO: Phase1 CvDllGame::SelectGroup — MISMATCH: Non-padding instruction mnemonic sequence differs.
	void DLLCALL SelectGroup(ICvUnit1* pUnit, bool bShift, bool bCtrl, bool bAlt);
	// TODO: Phase1 CvDllGame::SelectionListIgnoreBuildingDefense — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL SelectionListIgnoreBuildingDefense();
	// TODO: Phase1 CvDllGame::SelectionListMove — MISMATCH: Non-padding instruction mnemonic sequence differs.
	void DLLCALL SelectionListMove(ICvPlot1* pPlot, bool bShift);
	// TODO: Phase1 CvDllGame::SelectPlot — MISMATCH: Non-padding instruction mnemonic sequence differs.
	void DLLCALL SelectPlot(ICvPlot1* pPlot);
	// TODO: Phase1 CvDllGame::SelectSettler — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SelectSettler();
	// TODO: Phase1 CvDllGame::SelectUnit — MISMATCH: Non-padding instruction mnemonic sequence differs.
	void DLLCALL SelectUnit(ICvUnit1* pUnit, bool bClear, bool bToggle = false, bool bSound = false);
	// TODO: Phase1 CvDllGame::SendPlayerOptions — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SendPlayerOptions(bool bForce = false);
	// TODO: Phase1 CvDllGame::SetDebugMode — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetDebugMode(bool bDebugMode);
	// TODO: Phase1 CvDllGame::SetFinalInitialized — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetFinalInitialized(bool bNewValue);
	// TODO: Phase1 CvDllGame::SetInitialTime — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetInitialTime(unsigned int uiNewValue);
	// TODO: Phase1 CvDllGame::SetMPOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetMPOption(MultiplayerOptionTypes eIndex, bool bEnabled);
	// TODO: Phase1 CvDllGame::SetPausePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetPausePlayer(PlayerTypes eNewValue);
	// TODO: Phase1 CvDllGame::SetTimeStr — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	void DLLCALL SetTimeStr(char* szString, int iGameTurn, bool bSave);
	// TODO: Phase1 CvDllGame::TunerEverConnected — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL TunerEverConnected() const;
	// TODO: Phase1 CvDllGame::Uninit — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Uninit();
	// TODO: Phase1 CvDllGame::UnitIsMoving — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL UnitIsMoving();
	// TODO: Phase1 CvDllGame::Update — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Update(float fDeltaTime);
	// TODO: Phase1 CvDllGame::UpdateSelectionList — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL UpdateSelectionList();
	// TODO: Phase1 CvDllGame::UpdateTestEndTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL UpdateTestEndTurn();
	// TODO: Phase1 CvDllGame::Read — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Read(FDataStream& kStream);
	// TODO: Phase1 CvDllGame::Write — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Write(FDataStream& kStream) const;
	// TODO: Phase1 CvDllGame::ReadSupportingClassData — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL ReadSupportingClassData(FDataStream& kStream);
	// TODO: Phase1 CvDllGame::WriteSupportingClassData — MISMATCH: Current relocations reference target-absent imports: _ZNK6CvGame24WriteSupportingClassDataER11FDataStream.
	void DLLCALL WriteSupportingClassData(FDataStream& kStream) const;
	// TODO: Phase1 CvDllGame::WriteReplay — MISMATCH: Current relocations reference target-absent imports: _ZNK6CvGame11writeReplayER11FDataStream.
	void DLLCALL WriteReplay(FDataStream& kStream) const;
	// TODO: Phase1 CvDllGame::CanMoveUnitTo — MISMATCH: Non-padding instruction mnemonic sequence differs.
	bool DLLCALL CanMoveUnitTo(ICvUnit1* pUnit, ICvPlot1* pPlot) const;
	// TODO: Phase1 CvDllGame::NetMessageStaticsReset — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL NetMessageStaticsReset();
	// TODO: Phase1 CvDllGame::SetLastTurnAICivsProcessed — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetLastTurnAICivsProcessed();
	// TODO: Phase1 CvDllGame::SetNextSequentialPlayerTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetNextSequentialPlayerTurnActive(PlayerTypes ePlayer);
	// TODO: Phase1 CvDllGame::IsQueueGameCoreMessageFrame — MISMATCH: Current relocations reference target-absent imports: _ZN6CvGame27IsQueueGameCoreMessageFrameEv.
	bool DLLCALL IsQueueGameCoreMessageFrame();
	// TODO: Phase1 CvDllGame::GetStationByID — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvStation1* DLLCALL GetStationByID(int iID);
	// TODO: Phase1 CvDllGame::GetStationByPlot — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvStation1* DLLCALL GetStationByPlot(ICvPlot1* pPlot);
	// TODO: Phase1 CvDllGame::FirstStation — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvStation1* DLLCALL FirstStation(int* pIndex, bool bRevive = false);
	// TODO: Phase1 CvDllGame::NextStation — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvStation1* DLLCALL NextStation(int* pIndex, bool bRevive = false);
	// TODO: Phase1 CvDllGame::GetNumStations — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetNumStations() const;
	// TODO: Phase1 CvDllGame::GetTurnOrder — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetTurnOrder(PlayerTypes ePlayer) const;
	// TODO: Phase1 CvDllGame::GetPlayerIDForTurnOrder — UNVERIFIED: Full operand and relocation-target comparison not established.
	PlayerTypes DLLCALL GetPlayerIDForTurnOrder(int iTurnOrder) const;
	// TODO: Phase1 CvDllGame::SendSaveDataToPartnerApp — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SendSaveDataToPartnerApp() const;
	// TODO: Phase1 CvDllGame::GetCovertOpsVisibleTradeRouteIDs — MISMATCH: Phase1 prohibits dependent TradeConnection::m_padding[0x1dc] fabricated array stride.
	std::vector<int> DLLCALL GetCovertOpsVisibleTradeRouteIDs(PlayerTypes ePlayer) const;
	// TODO: Phase1 CvDllGame::GetUnitEntryBasedOnUpgrades — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL GetUnitEntryBasedOnUpgrades(const char* szUnitType, int iUnitTier, UnitUpgradeTypes eUpgrade, CvString& strUnitEntry);
	// TODO: Phase1 CvDllGame::SetAIAutoPlay — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetAIAutoPlay(int iNumTurns, PlayerTypes ePlayer);

private:
	// TODO: Phase1 CvDllGame::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Destroy();
	unsigned int m_uiRefCount;
	CvGame* m_pGame;
};
