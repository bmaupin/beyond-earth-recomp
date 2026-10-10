#pragma once

#include <vector>

class CvRandom;
class CvGameSpeedInfo;
class CvHandicapInfo;
class CvGameDeals;
class CvTacticalAnalysisMap
{
public:
	void Init(int iNumPlots);
};
class CvUnit;
class CvPlot;
class CvCity;
class CvGameMinorPowers;
class CvGameTrade;
class CvPartnerApp;
class CvGameInitialItemsOverrides
{
public:
	bool GrantInitialFreeTechsPerTeam[REALLY_MAX_TEAMS];
	bool GrantInitialGoldPerPlayer[MAX_MAJOR_CIVS];
	bool GrantInitialCulturePerPlayer[MAX_MAJOR_CIVS];
	bool ClearResearchQueuePerPlayer[MAX_MAJOR_CIVS];
	bool GrantInitialUnitsPerPlayer[MAX_MAJOR_CIVS];
};

class CvGame
{
public:
	int getElapsedGameTurns() const;
	int countMajorCivsAlive() const;
	int countCivPlayersAlive() const;
	int countHumanPlayersAlive() const;
	int countNumHumanGameTurnActive();
	int getJonRandNum(int iNum, const char* pszLog);
	int getGameRandNum(int iNum, const char* pszLog);
	int GetNumMinorCivsEver();
	CvRandom& getMapRand();
	int getMapRandNum(int iNum, const char* pszLog);
	CvRandom& getJonRand();
	PlayerTypes getActivePlayer() const;
	TeamTypes getActiveTeam();
	int getGameTurn() const;
	GameSpeedTypes getGameSpeedType() const;
	CvGameSpeedInfo& getGameSpeedInfo() const;
	CvHandicapInfo& getHandicapInfo() const;
	GameStateTypes getGameState();
	bool hasGameEverBeenExtended();
	HandicapTypes getHandicapType() const;
	int IsAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl);
	int GetAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl);
	bool isDebugMode() const;
	bool isFinalInitialized() const;
	bool isGameMultiPlayer() const;
	bool getFOW();
	bool isHotSeat() const;
	bool isMPOption(MultiplayerOptionTypes eIndex) const;
	bool isNetworkMultiPlayer() const;
	bool isOption(GameOptionTypes eIndex) const;
	bool isPaused();
	bool isPbem() const;
	bool isTeamGame() const;
	bool TunerEverConnected() const;
	void InitFromLoad();
	void changeNumGameTurnActive(int iChange, const std::string& why);
	bool cyclePlotUnits(CvPlot* pPlot, bool bForward, bool bAuto, int iCount);
	void cycleUnits(bool bClear, bool bForward, bool bWorkers);
	void DoGameStarted();
	void endTurnTimerReset();
	void endTurnTimerSemaphoreDecrement();
	void endTurnTimerSemaphoreIncrement();
	CvGameDeals* GetGameDeals();
	int getMaxTurns() const;
	int getNumGameTurnActive();
	PlayerTypes getPausePlayer();
	bool getPbemTurnSent() const;
	CvUnit* getPlotUnit(CvPlot* pPlot, int iIndex);
	VictoryTypes getVictory() const;
	int GetVotesNeededForDiploVictory() const;
	TeamTypes getWinner() const;
	int GetWinningTurn() const;
	void handleAction(int iAction);
	bool hasTurnTimerExpired(PlayerTypes playerID);
	void TurnTimerSync(float fCurTurnTime, float fTurnStartTime);
	void GetTurnTimerData(float& fCurTurnTime, float& fTurnStartTime);
	void init(HandicapTypes eHandicap);
	bool init2();
	void initScoreCalculation();
	CvTacticalAnalysisMap* GetTacticalAnalysisMap();
	bool IsCityScreenBlocked();
	bool CanOpenCityScreen(PlayerTypes eOpener, CvCity* pCity);
	void LogGameState(bool bLogHeaders);
	void resetTurnTimer(bool bResetGameTurn = false);
	void selectAll(CvPlot* pPlot);
	void selectGroup(CvUnit* pUnit, bool bShift, bool bCtrl, bool bAlt);
	bool selectionListIgnoreBuildingDefense();
	void selectionListMove(CvPlot* pPlot, bool bShift);
	void selectPlot(CvPlot* pPlot);
	void SelectSettler();
	void selectUnit(CvUnit* pUnit, bool bClear, bool bToggle, bool bSound);
	void sendPlayerOptions(bool bForce);
	void setDebugMode(bool bDebugMode);
	void setFinalInitialized(bool bNewValue);
	void setInitialTime(unsigned int uiNewValue);
	void setMPOption(MultiplayerOptionTypes eIndex, bool bEnabled);
	void setPausePlayer(PlayerTypes eNewValue);
	CalendarTypes getCalendar() const;
	int getStartYear() const;
	void uninit();
	void unitIsMoving();
	void update(float fDeltaTime);
	void updateSelectionList();
	void updateTestEndTurn();
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream) const;
	void ReadSupportingClassData(FDataStream& kStream);
	void WriteSupportingClassData(FDataStream& kStream) const;
	void writeReplay(FDataStream& kStream) const;
	void NetMessageStaticsReset();
	void SetInitialAICivsFinished();
	void SetNextSequentialPlayerTurnActive(PlayerTypes ePlayer);
	bool IsQueueGameCoreMessageFrame();
	int GetTurnOrder(PlayerTypes ePlayer) const;
	PlayerTypes GetPlayerIDForTurnOrder(int iTurnOrder) const;
	bool GetUnitEntryBasedOnUpgrades(const char* szUnitType, int iUnitTier, UnitUpgradeTypes eUpgrade, CvString& strUnitEntry);
	void setAIAutoPlay(int iNumTurns, PlayerTypes ePlayer);
	CvGameMinorPowers* GetGameMinorPowers() const;
	CvGameTrade* GetGameTrade();
	CvPartnerApp* GetPartnerApp();
};