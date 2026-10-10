#pragma once

#include "CvDllInterfaces.h"

class CvGame;
class CvStation;

class CvDllGame : public ICvGame1
{
public:
	CvDllGame(CvGame* pGame);
	~CvDllGame();

	void* DLLCALL QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();
	static void operator delete(void* p);
	static void* operator new(size_t bytes);

	ICvPlayer1* DLLCALL GetPlayer(PlayerTypes ePlayer);
	CvGame* GetInstance();
	void DLLCALL InitFromLoad();
	PlayerTypes DLLCALL GetActivePlayer();
	TeamTypes DLLCALL GetActiveTeam();
	int DLLCALL GetGameTurn() const;
	void DLLCALL ChangeNumGameTurnActive(int iChange, const char* why);
	int DLLCALL CountHumanPlayersAlive() const;
	int DLLCALL CountNumHumanGameTurnActive();
	bool DLLCALL CyclePlotUnits(ICvPlot1* pPlot, bool bForward = true, bool bAuto = false, int iCount = -1);
	void DLLCALL CycleUnits(bool bClear, bool bForward = true, bool bWorkers = false);
	void DLLCALL DoGameStarted();
	void DLLCALL EndTurnTimerReset();
	void DLLCALL EndTurnTimerSemaphoreDecrement();
	void DLLCALL EndTurnTimerSemaphoreIncrement();
	int DLLCALL GetAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl);
	int DLLCALL IsAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl);
	int DLLCALL GetElapsedGameTurns() const;
	bool DLLCALL GetFOW();
	ICvGameDeals1* DLLCALL GetGameDeals();
	GameSpeedTypes DLLCALL GetGameSpeedType() const;
	GameStateTypes DLLCALL GetGameState();
	bool DLLCALL HasGameEverBeenExtended();
	HandicapTypes DLLCALL GetHandicapType() const;
	ICvRandom1* DLLCALL GetRandomNumberGenerator();
	int DLLCALL GetJonRandNum(int iNum, const char* pszLog);
	int DLLCALL GetMaxTurns() const;
	int DLLCALL GetNumGameTurnActive();
	PlayerTypes DLLCALL GetPausePlayer();
	bool DLLCALL GetPbemTurnSent() const;
	ICvUnit1* DLLCALL GetPlotUnit(ICvPlot1* pPlot, int iIndex);
	VictoryTypes DLLCALL GetVictory() const;
	int DLLCALL GetVotesNeededForDiploVictory() const;
	TeamTypes DLLCALL GetWinner() const;
	int DLLCALL GetWinningTurn() const;
	void DLLCALL HandleAction(int iAction);
	bool DLLCALL HasTurnTimerExpired();
	bool DLLCALL HasTurnTimerExpired(PlayerTypes playerID);
	void DLLCALL TurnTimerSync(float fCurTurnTime, float fTurnStartTime);
	void DLLCALL GetTurnTimerData(float& fCurTurnTime, float& fTurnStartTime);
	void DLLCALL Init(HandicapTypes eHandicap);
	bool DLLCALL Init2();
	void DLLCALL InitScoreCalculation();
	void DLLCALL InitTacticalAnalysisMap(int iNumPlots);
	bool DLLCALL IsCityScreenBlocked();
	bool DLLCALL CanOpenCityScreen(PlayerTypes eOpener, ICvCity1* pCity);
	bool DLLCALL IsDebugMode() const;
	bool DLLCALL IsFinalInitialized() const;
	bool DLLCALL IsGameMultiPlayer() const;
	bool DLLCALL IsHotSeat() const;
	bool DLLCALL IsMPOption(MultiplayerOptionTypes eIndex) const;
	bool DLLCALL IsNetworkMultiPlayer() const;
	bool DLLCALL IsOption(GameOptionTypes eIndex) const;
	bool DLLCALL IsPaused();
	bool DLLCALL IsPbem() const;
	bool DLLCALL IsTeamGame() const;
	void DLLCALL LogGameState(bool bLogHeaders = false);
	void DLLCALL ResetTurnTimer();
	void DLLCALL SelectAll(ICvPlot1* pPlot);
	void DLLCALL SelectGroup(ICvUnit1* pUnit, bool bShift, bool bCtrl, bool bAlt);
	bool DLLCALL SelectionListIgnoreBuildingDefense();
	void DLLCALL SelectionListMove(ICvPlot1* pPlot, bool bShift);
	void DLLCALL SelectPlot(ICvPlot1* pPlot);
	void DLLCALL SelectSettler();
	void DLLCALL SelectUnit(ICvUnit1* pUnit, bool bClear, bool bToggle = false, bool bSound = false);
	void DLLCALL SendPlayerOptions(bool bForce = false);
	void DLLCALL SetDebugMode(bool bDebugMode);
	void DLLCALL SetFinalInitialized(bool bNewValue);
	void DLLCALL SetInitialTime(unsigned int uiNewValue);
	void DLLCALL SetMPOption(MultiplayerOptionTypes eIndex, bool bEnabled);
	void DLLCALL SetPausePlayer(PlayerTypes eNewValue);
	void DLLCALL SetTimeStr(char* szString, int iGameTurn, bool bSave);
	bool DLLCALL TunerEverConnected() const;
	void DLLCALL Uninit();
	void DLLCALL UnitIsMoving();
	void DLLCALL Update(float fDeltaTime);
	void DLLCALL UpdateSelectionList();
	void DLLCALL UpdateTestEndTurn();
	void DLLCALL Read(FDataStream& kStream);
	void DLLCALL Write(FDataStream& kStream) const;
	void DLLCALL ReadSupportingClassData(FDataStream& kStream);
	void DLLCALL WriteSupportingClassData(FDataStream& kStream) const;
	void DLLCALL WriteReplay(FDataStream& kStream) const;
	bool DLLCALL CanMoveUnitTo(ICvUnit1* pUnit, ICvPlot1* pPlot) const;
	void DLLCALL NetMessageStaticsReset();
	void DLLCALL SetLastTurnAICivsProcessed();
	void DLLCALL SetNextSequentialPlayerTurnActive(PlayerTypes ePlayer);
	bool DLLCALL IsQueueGameCoreMessageFrame();
	ICvStation1* DLLCALL GetStationByID(int iID);
	ICvStation1* DLLCALL GetStationByPlot(ICvPlot1* pPlot);
	ICvStation1* DLLCALL FirstStation(int* pIndex, bool bRevive = false);
	ICvStation1* DLLCALL NextStation(int* pIndex, bool bRevive = false);
	int DLLCALL GetNumStations() const;
	int DLLCALL GetTurnOrder(PlayerTypes ePlayer) const;
	PlayerTypes DLLCALL GetPlayerIDForTurnOrder(int iTurnOrder) const;
	void DLLCALL SendSaveDataToPartnerApp() const;
	std::vector<int> DLLCALL GetCovertOpsVisibleTradeRouteIDs(PlayerTypes ePlayer) const;
	bool DLLCALL GetUnitEntryBasedOnUpgrades(const char* szUnitType, int iUnitTier, UnitUpgradeTypes eUpgrade, CvString& strUnitEntry);
	void DLLCALL SetAIAutoPlay(int iNumTurns, PlayerTypes ePlayer);

private:
	void DLLCALL Destroy();
	unsigned int m_uiRefCount;
	CvGame* m_pGame;
};
