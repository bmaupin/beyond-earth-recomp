#include "CvGameCoreDLLPCH.h"
#include "CvDllGame.h"
#include "CvDllContext.h"
#include "CvDllGameDeals.h"
#include "CvDllPlayer.h"
#include "CvDllPlot.h"
#include "CvDllRandom.h"
#include "CvDllUnit.h"
#include "CvUnit.h"
#include "CvDllCity.h"
#include "CvDllStation.h"
#include "CvStation.h"
#include "CvAStar.h"
#include "CvPartnerApp.h"
#include "CvTradeClasses.h"
#include "CvGameTextMgr.h"

CvDllGame::CvDllGame(CvGame* pGame) : m_uiRefCount(1), m_pGame(pGame)
{
	if(gDLL)
		gDLL->GetGameCoreLock();
}
CvDllGame::~CvDllGame()
{
	if(gDLL)
		gDLL->ReleaseGameCoreLock();
}

void* CvDllGame::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() || guidInterface == ICvGame1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}
	return NULL;
}

unsigned int CvDllGame::IncrementReference() { return ++m_uiRefCount; }
unsigned int CvDllGame::DecrementReference()
{
	if(m_uiRefCount == 1) { delete this; return 0; }
	return --m_uiRefCount;
}
unsigned int CvDllGame::GetReferenceCount() { return m_uiRefCount; }
void CvDllGame::Destroy() { DecrementReference(); }
void CvDllGame::operator delete(void* p) { CvDllGameContext::Free(p); }
void* CvDllGame::operator new(size_t bytes) { return CvDllGameContext::Allocate(bytes); }

ICvPlayer1* CvDllGame::GetPlayer(PlayerTypes ePlayer) { return new CvDllPlayer(&CvPlayerAI::getPlayer(ePlayer)); }
CvGame* CvDllGame::GetInstance() { return m_pGame; }
void CvDllGame::InitFromLoad() { m_pGame->InitFromLoad(); }
PlayerTypes CvDllGame::GetActivePlayer() { return m_pGame->getActivePlayer(); }
TeamTypes CvDllGame::GetActiveTeam() { return m_pGame->getActiveTeam(); }
int CvDllGame::GetGameTurn() const { return m_pGame->getGameTurn(); }
void CvDllGame::ChangeNumGameTurnActive(int iChange, const char* why)
{
	m_pGame->changeNumGameTurnActive(iChange, why && *why ? std::string(why) : std::string());
}
int CvDllGame::CountHumanPlayersAlive() const { return m_pGame->countHumanPlayersAlive(); }
int CvDllGame::CountNumHumanGameTurnActive() { return m_pGame->countNumHumanGameTurnActive(); }
bool CvDllGame::CyclePlotUnits(ICvPlot1* pPlot, bool bForward, bool bAuto, int iCount)
{
	return m_pGame->cyclePlotUnits(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL, bForward, bAuto, iCount);
}
void CvDllGame::CycleUnits(bool bClear, bool bForward, bool bWorkers) { m_pGame->cycleUnits(bClear, bForward, bWorkers); }
void CvDllGame::DoGameStarted() { m_pGame->DoGameStarted(); }
void CvDllGame::EndTurnTimerReset() { m_pGame->endTurnTimerReset(); }
void CvDllGame::EndTurnTimerSemaphoreDecrement() { m_pGame->endTurnTimerSemaphoreDecrement(); }
void CvDllGame::EndTurnTimerSemaphoreIncrement() { m_pGame->endTurnTimerSemaphoreIncrement(); }
int CvDllGame::GetAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl) { return m_pGame->GetAction(iKeyStroke, bAlt, bShift, bCtrl); }
int CvDllGame::IsAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl) { return m_pGame->IsAction(iKeyStroke, bAlt, bShift, bCtrl); }
int CvDllGame::GetElapsedGameTurns() const { return m_pGame->getElapsedGameTurns(); }
bool CvDllGame::GetFOW() { return m_pGame->getFOW(); }
ICvGameDeals1* CvDllGame::GetGameDeals()
{
	CvGameDeals* pDeals = m_pGame->GetGameDeals();
	return pDeals ? new CvDllGameDeals(pDeals) : NULL;
}
GameSpeedTypes CvDllGame::GetGameSpeedType() const { return m_pGame->getGameSpeedType(); }
GameStateTypes CvDllGame::GetGameState() { return m_pGame->getGameState(); }
bool CvDllGame::HasGameEverBeenExtended() { return m_pGame->hasGameEverBeenExtended(); }
HandicapTypes CvDllGame::GetHandicapType() const { return m_pGame->getHandicapType(); }
ICvRandom1* CvDllGame::GetRandomNumberGenerator() { return new CvDllRandom(&m_pGame->getJonRand()); }
int CvDllGame::GetJonRandNum(int iNum, const char* pszLog) { return m_pGame->getJonRandNum(iNum, pszLog); }
int CvDllGame::GetMaxTurns() const { return m_pGame->getMaxTurns(); }
int CvDllGame::GetNumGameTurnActive() { return m_pGame->getNumGameTurnActive(); }
PlayerTypes CvDllGame::GetPausePlayer() { return m_pGame->getPausePlayer(); }
bool CvDllGame::GetPbemTurnSent() const { return m_pGame->getPbemTurnSent(); }
ICvUnit1* CvDllGame::GetPlotUnit(ICvPlot1* pPlot, int iIndex)
{
	CvUnit* pUnit = m_pGame->getPlotUnit(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL, iIndex);
	return pUnit ? new CvDllUnit(pUnit) : NULL;
}
VictoryTypes CvDllGame::GetVictory() const { return m_pGame->getVictory(); }
int CvDllGame::GetVotesNeededForDiploVictory() const { return m_pGame->GetVotesNeededForDiploVictory(); }
TeamTypes CvDllGame::GetWinner() const { return m_pGame->getWinner(); }
int CvDllGame::GetWinningTurn() const { return m_pGame->GetWinningTurn(); }
void CvDllGame::HandleAction(int iAction) { m_pGame->handleAction(iAction); }
bool CvDllGame::HasTurnTimerExpired() { return false; }
bool CvDllGame::HasTurnTimerExpired(PlayerTypes playerID) { return m_pGame->hasTurnTimerExpired(playerID); }
void CvDllGame::TurnTimerSync(float fCurTurnTime, float fTurnStartTime) { m_pGame->TurnTimerSync(fCurTurnTime, fTurnStartTime); }
void CvDllGame::GetTurnTimerData(float& fCurTurnTime, float& fTurnStartTime) { m_pGame->GetTurnTimerData(fCurTurnTime, fTurnStartTime); }
void CvDllGame::Init(HandicapTypes eHandicap) { m_pGame->init(eHandicap); }
bool CvDllGame::Init2() { return m_pGame->init2(); }
void CvDllGame::InitScoreCalculation() { m_pGame->initScoreCalculation(); }
void CvDllGame::InitTacticalAnalysisMap(int iNumPlots) { m_pGame->GetTacticalAnalysisMap()->Init(iNumPlots); }
bool CvDllGame::IsCityScreenBlocked() { return m_pGame->IsCityScreenBlocked(); }
bool CvDllGame::CanOpenCityScreen(PlayerTypes eOpener, ICvCity1* pCity) { return m_pGame->CanOpenCityScreen(eOpener, pCity ? static_cast<CvDllCity*>(pCity)->GetInstance() : NULL); }
bool CvDllGame::IsDebugMode() const { return m_pGame->isDebugMode(); }
bool CvDllGame::IsFinalInitialized() const { return m_pGame->isFinalInitialized(); }
bool CvDllGame::IsGameMultiPlayer() const { return m_pGame->isGameMultiPlayer(); }
bool CvDllGame::IsHotSeat() const { return m_pGame->isHotSeat(); }
bool CvDllGame::IsMPOption(MultiplayerOptionTypes eIndex) const { return m_pGame->isMPOption(eIndex); }
bool CvDllGame::IsNetworkMultiPlayer() const { return m_pGame->isNetworkMultiPlayer(); }
bool CvDllGame::IsOption(GameOptionTypes eIndex) const { return m_pGame->isOption(eIndex); }
bool CvDllGame::IsPaused() { return m_pGame->isPaused(); }
bool CvDllGame::IsPbem() const { return m_pGame->isPbem(); }
bool CvDllGame::IsTeamGame() const { return m_pGame->isTeamGame(); }
void CvDllGame::LogGameState(bool bLogHeaders) { m_pGame->LogGameState(bLogHeaders); }
void CvDllGame::ResetTurnTimer() { m_pGame->resetTurnTimer(); }
void CvDllGame::SelectAll(ICvPlot1* pPlot) { m_pGame->selectAll(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL); }
void CvDllGame::SelectGroup(ICvUnit1* pUnit, bool bShift, bool bCtrl, bool bAlt) { m_pGame->selectGroup(pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL, bShift, bCtrl, bAlt); }
bool CvDllGame::SelectionListIgnoreBuildingDefense() { return m_pGame->selectionListIgnoreBuildingDefense(); }
void CvDllGame::SelectionListMove(ICvPlot1* pPlot, bool bShift) { m_pGame->selectionListMove(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL, bShift); }
void CvDllGame::SelectPlot(ICvPlot1* pPlot) { m_pGame->selectPlot(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL); }
void CvDllGame::SelectSettler() { m_pGame->SelectSettler(); }
void CvDllGame::SelectUnit(ICvUnit1* pUnit, bool bClear, bool bToggle, bool bSound) { m_pGame->selectUnit(pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL, bClear, bToggle, bSound); }
void CvDllGame::SendPlayerOptions(bool bForce) { m_pGame->sendPlayerOptions(bForce); }
void CvDllGame::SetDebugMode(bool bDebugMode) { m_pGame->setDebugMode(bDebugMode); }
void CvDllGame::SetFinalInitialized(bool bNewValue) { m_pGame->setFinalInitialized(bNewValue); }
void CvDllGame::SetInitialTime(unsigned int uiNewValue) { m_pGame->setInitialTime(uiNewValue); }
void CvDllGame::SetMPOption(MultiplayerOptionTypes eIndex, bool bEnabled) { m_pGame->setMPOption(eIndex, bEnabled); }
void CvDllGame::SetPausePlayer(PlayerTypes eNewValue) { m_pGame->setPausePlayer(eNewValue); }
void CvDllGame::SetTimeStr(char* szString, int iGameTurn, bool bSave)
{
	if(szString)
	{
		CvString strString;
		CvGameTextMgr::setDateStr(strString, iGameTurn, bSave, m_pGame->getCalendar(), m_pGame->getStartYear(), m_pGame->getGameSpeedType());
		strcpy(szString, strString.c_str());
	}
}
bool CvDllGame::TunerEverConnected() const { return m_pGame->TunerEverConnected(); }
void CvDllGame::Uninit() { m_pGame->uninit(); }
void CvDllGame::UnitIsMoving() { m_pGame->unitIsMoving(); }
void CvDllGame::Update(float fDeltaTime) { m_pGame->update(fDeltaTime); }
void CvDllGame::UpdateSelectionList() { m_pGame->updateSelectionList(); }
void CvDllGame::UpdateTestEndTurn() { m_pGame->updateTestEndTurn(); }
void CvDllGame::Read(FDataStream& kStream) { m_pGame->Read(kStream); }
void CvDllGame::Write(FDataStream& kStream) const { m_pGame->Write(kStream); }
void CvDllGame::ReadSupportingClassData(FDataStream& kStream) { m_pGame->ReadSupportingClassData(kStream); }
void CvDllGame::WriteSupportingClassData(FDataStream& kStream) const { m_pGame->WriteSupportingClassData(kStream); }
void CvDllGame::WriteReplay(FDataStream& kStream) const { m_pGame->writeReplay(kStream); }
bool CvDllGame::CanMoveUnitTo(ICvUnit1* pUnit, ICvPlot1* pPlot) const
{
	if(!pUnit || !pPlot)
		return false;

	CvUnit* pUnitInstance = GC.UnwrapUnitPointer(pUnit);
	CvPlot* pPlotInstance = GC.UnwrapPlotPointer(pPlot);
	GC.getInterfacePathFinder().SetData(pUnitInstance);
	if(!GC.getInterfacePathFinder().GeneratePath(pUnitInstance->getX(), pUnitInstance->getY(), pPlotInstance->getX(), pPlotInstance->getY(), MOVE_UNITS_IGNORE_DANGER | MOVE_UNITS_THROUGH_ENEMY, true))
		return false;

	CvAStarNode* pNode = GC.getInterfacePathFinder().GetLastNode();
	return pNode && pNode->m_iData2 < 2;
}
void CvDllGame::NetMessageStaticsReset() { m_pGame->NetMessageStaticsReset(); }
void CvDllGame::SetLastTurnAICivsProcessed() { m_pGame->SetInitialAICivsFinished(); }
void CvDllGame::SetNextSequentialPlayerTurnActive(PlayerTypes ePlayer) { m_pGame->SetNextSequentialPlayerTurnActive(ePlayer); }
bool CvDllGame::IsQueueGameCoreMessageFrame() { return m_pGame->IsQueueGameCoreMessageFrame(); }

ICvStation1* CvDllGame::GetStationByID(int iID)
{
	CvStation* pStation = m_pGame->GetGameMinorPowers()->GetStation(iID);
	return pStation ? new CvDllStation(pStation) : NULL;
}
ICvStation1* CvDllGame::GetStationByPlot(ICvPlot1* pPlot)
{
	CvStation* pStation = m_pGame->GetGameMinorPowers()->GetStationByPlot(pPlot->GetPlotIndex());
	return pStation ? new CvDllStation(pStation) : NULL;
}
ICvStation1* CvDllGame::FirstStation(int* pIndex, bool bRevive)
{
	CvStation* pStation = m_pGame->GetGameMinorPowers()->FirstStation(pIndex, bRevive);
	return pStation ? new CvDllStation(pStation) : NULL;
}
ICvStation1* CvDllGame::NextStation(int* pIndex, bool bRevive)
{
	CvStation* pStation = m_pGame->GetGameMinorPowers()->NextStation(pIndex, bRevive);
	return pStation ? new CvDllStation(pStation) : NULL;
}
int CvDllGame::GetNumStations() const { return m_pGame->GetGameMinorPowers()->GetNumStations(); }
int CvDllGame::GetTurnOrder(PlayerTypes ePlayer) const { return m_pGame->GetTurnOrder(ePlayer); }
PlayerTypes CvDllGame::GetPlayerIDForTurnOrder(int iTurnOrder) const { return m_pGame->GetPlayerIDForTurnOrder(iTurnOrder); }
void CvDllGame::SendSaveDataToPartnerApp() const { m_pGame->GetPartnerApp()->PushCurrentGameToPartnerApp(); }
std::vector<int> CvDllGame::GetCovertOpsVisibleTradeRouteIDs(PlayerTypes ePlayer) const
{
	std::vector<TradeConnection> routes = m_pGame->GetGameTrade()->GetCovertOpsVisibleTradeRoutes(ePlayer);
	std::vector<int> routeIDs(routes.size());
	for(size_t i = 0; i < routes.size(); ++i)
		routeIDs[i] = routes[i].m_iID;
	return routeIDs;
}
bool CvDllGame::GetUnitEntryBasedOnUpgrades(const char* szUnitType, int iUnitTier, UnitUpgradeTypes eUpgrade, CvString& strUnitEntry) { return m_pGame->GetUnitEntryBasedOnUpgrades(szUnitType, iUnitTier, eUpgrade, strUnitEntry); }
void CvDllGame::SetAIAutoPlay(int iNumTurns, PlayerTypes ePlayer) { m_pGame->setAIAutoPlay(iNumTurns, ePlayer); }
