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

// TODO: Phase1 CvDllGame::CvDllGame — UNVERIFIED: Full operand and relocation-target comparison not established.
CvDllGame::CvDllGame(CvGame* pGame) : m_uiRefCount(1), m_pGame(pGame)
{
	if(gDLL)
		gDLL->GetGameCoreLock();
}
// TODO: Phase1 CvDllGame::~CvDllGame — MISMATCH: Non-padding instruction mnemonic sequence differs.
CvDllGame::~CvDllGame()
{
	if(gDLL)
		gDLL->ReleaseGameCoreLock();
}

// TODO: Phase1 CvDllGame::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
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
// TODO: Phase1 CvDllGame::DecrementReference — MISMATCH: Non-padding instruction mnemonic sequence differs.
unsigned int CvDllGame::DecrementReference()
{
	if(m_uiRefCount == 1) { delete this; return 0; }
	return --m_uiRefCount;
}
unsigned int CvDllGame::GetReferenceCount() { return m_uiRefCount; }
// TODO: Phase1 CvDllGame::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::Destroy() { DecrementReference(); }
// TODO: Phase1 CvDllGame::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllGame::operator delete(void* p) { CvDllGameContext::Free(p); }
// TODO: Phase1 CvDllGame::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllGame::operator new(size_t bytes) { return CvDllGameContext::Allocate(bytes); }

// TODO: Phase1 CvDllGame::GetPlayer — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvPlayer1* CvDllGame::GetPlayer(PlayerTypes ePlayer) { return new CvDllPlayer(&CvPlayerAI::getPlayer(ePlayer)); }
CvGame* CvDllGame::GetInstance() { return m_pGame; }
// TODO: Phase1 CvDllGame::InitFromLoad — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::InitFromLoad() { m_pGame->InitFromLoad(); }
// TODO: Phase1 CvDllGame::GetActivePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
PlayerTypes CvDllGame::GetActivePlayer() { return m_pGame->getActivePlayer(); }
// TODO: Phase1 CvDllGame::GetActiveTeam — UNVERIFIED: Full operand and relocation-target comparison not established.
TeamTypes CvDllGame::GetActiveTeam() { return m_pGame->getActiveTeam(); }
// TODO: Phase1 CvDllGame::GetGameTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetGameTurn() const { return m_pGame->getGameTurn(); }
// TODO: Phase1 CvDllGame::ChangeNumGameTurnActive — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
void CvDllGame::ChangeNumGameTurnActive(int iChange, const char* why)
{
	m_pGame->changeNumGameTurnActive(iChange, why && *why ? std::string(why) : std::string());
}
// TODO: Phase1 CvDllGame::CountHumanPlayersAlive — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::CountHumanPlayersAlive() const { return m_pGame->countHumanPlayersAlive(); }
// TODO: Phase1 CvDllGame::CountNumHumanGameTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::CountNumHumanGameTurnActive() { return m_pGame->countNumHumanGameTurnActive(); }
// TODO: Phase1 CvDllGame::CyclePlotUnits — MISMATCH: Non-padding instruction mnemonic sequence differs.
bool CvDllGame::CyclePlotUnits(ICvPlot1* pPlot, bool bForward, bool bAuto, int iCount)
{
	return m_pGame->cyclePlotUnits(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL, bForward, bAuto, iCount);
}
// TODO: Phase1 CvDllGame::CycleUnits — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::CycleUnits(bool bClear, bool bForward, bool bWorkers) { m_pGame->cycleUnits(bClear, bForward, bWorkers); }
// TODO: Phase1 CvDllGame::DoGameStarted — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::DoGameStarted() { m_pGame->DoGameStarted(); }
// TODO: Phase1 CvDllGame::EndTurnTimerReset — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::EndTurnTimerReset() { m_pGame->endTurnTimerReset(); }
// TODO: Phase1 CvDllGame::EndTurnTimerSemaphoreDecrement — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::EndTurnTimerSemaphoreDecrement() { m_pGame->endTurnTimerSemaphoreDecrement(); }
// TODO: Phase1 CvDllGame::EndTurnTimerSemaphoreIncrement — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::EndTurnTimerSemaphoreIncrement() { m_pGame->endTurnTimerSemaphoreIncrement(); }
// TODO: Phase1 CvDllGame::GetAction — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl) { return m_pGame->GetAction(iKeyStroke, bAlt, bShift, bCtrl); }
// TODO: Phase1 CvDllGame::IsAction — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::IsAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl) { return m_pGame->IsAction(iKeyStroke, bAlt, bShift, bCtrl); }
// TODO: Phase1 CvDllGame::GetElapsedGameTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetElapsedGameTurns() const { return m_pGame->getElapsedGameTurns(); }
// TODO: Phase1 CvDllGame::GetFOW — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::GetFOW() { return m_pGame->getFOW(); }
// TODO: Phase1 CvDllGame::GetGameDeals — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvGameDeals1* CvDllGame::GetGameDeals()
{
	CvGameDeals* pDeals = m_pGame->GetGameDeals();
	return pDeals ? new CvDllGameDeals(pDeals) : NULL;
}
// TODO: Phase1 CvDllGame::GetGameSpeedType — UNVERIFIED: Full operand and relocation-target comparison not established.
GameSpeedTypes CvDllGame::GetGameSpeedType() const { return m_pGame->getGameSpeedType(); }
// TODO: Phase1 CvDllGame::GetGameState — UNVERIFIED: Full operand and relocation-target comparison not established.
GameStateTypes CvDllGame::GetGameState() { return m_pGame->getGameState(); }
// TODO: Phase1 CvDllGame::HasGameEverBeenExtended — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::HasGameEverBeenExtended() { return m_pGame->hasGameEverBeenExtended(); }
// TODO: Phase1 CvDllGame::GetHandicapType — UNVERIFIED: Full operand and relocation-target comparison not established.
HandicapTypes CvDllGame::GetHandicapType() const { return m_pGame->getHandicapType(); }
// TODO: Phase1 CvDllGame::GetRandomNumberGenerator — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvRandom1* CvDllGame::GetRandomNumberGenerator() { return new CvDllRandom(&m_pGame->getJonRand()); }
// TODO: Phase1 CvDllGame::GetJonRandNum — MISMATCH: Current relocations reference target-absent imports: _ZN6CvGame13getJonRandNumEiPKc.
int CvDllGame::GetJonRandNum(int iNum, const char* pszLog) { return m_pGame->getJonRandNum(iNum, pszLog); }
// TODO: Phase1 CvDllGame::GetMaxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetMaxTurns() const { return m_pGame->getMaxTurns(); }
// TODO: Phase1 CvDllGame::GetNumGameTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetNumGameTurnActive() { return m_pGame->getNumGameTurnActive(); }
// TODO: Phase1 CvDllGame::GetPausePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
PlayerTypes CvDllGame::GetPausePlayer() { return m_pGame->getPausePlayer(); }
// TODO: Phase1 CvDllGame::GetPbemTurnSent — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::GetPbemTurnSent() const { return m_pGame->getPbemTurnSent(); }
// TODO: Phase1 CvDllGame::GetPlotUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvUnit1* CvDllGame::GetPlotUnit(ICvPlot1* pPlot, int iIndex)
{
	CvUnit* pUnit = m_pGame->getPlotUnit(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL, iIndex);
	return pUnit ? new CvDllUnit(pUnit) : NULL;
}
// TODO: Phase1 CvDllGame::GetVictory — UNVERIFIED: Full operand and relocation-target comparison not established.
VictoryTypes CvDllGame::GetVictory() const { return m_pGame->getVictory(); }
// TODO: Phase1 CvDllGame::GetVotesNeededForDiploVictory — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetVotesNeededForDiploVictory() const { return m_pGame->GetVotesNeededForDiploVictory(); }
// TODO: Phase1 CvDllGame::GetWinner — UNVERIFIED: Full operand and relocation-target comparison not established.
TeamTypes CvDllGame::GetWinner() const { return m_pGame->getWinner(); }
// TODO: Phase1 CvDllGame::GetWinningTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetWinningTurn() const { return m_pGame->GetWinningTurn(); }
// TODO: Phase1 CvDllGame::HandleAction — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::HandleAction(int iAction) { m_pGame->handleAction(iAction); }
bool CvDllGame::HasTurnTimerExpired() { return false; }
// TODO: Phase1 CvDllGame::HasTurnTimerExpired — UNVERIFIED: Overloads have differing audit results; complete signature-specific comparison remains necessary.
bool CvDllGame::HasTurnTimerExpired(PlayerTypes playerID) { return m_pGame->hasTurnTimerExpired(playerID); }
// TODO: Phase1 CvDllGame::TurnTimerSync — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::TurnTimerSync(float fCurTurnTime, float fTurnStartTime) { m_pGame->TurnTimerSync(fCurTurnTime, fTurnStartTime); }
// TODO: Phase1 CvDllGame::GetTurnTimerData — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::GetTurnTimerData(float& fCurTurnTime, float& fTurnStartTime) { m_pGame->GetTurnTimerData(fCurTurnTime, fTurnStartTime); }
// TODO: Phase1 CvDllGame::Init — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::Init(HandicapTypes eHandicap) { m_pGame->init(eHandicap); }
// TODO: Phase1 CvDllGame::Init2 — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::Init2() { return m_pGame->init2(); }
// TODO: Phase1 CvDllGame::InitScoreCalculation — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::InitScoreCalculation() { m_pGame->initScoreCalculation(); }
// TODO: Phase1 CvDllGame::InitTacticalAnalysisMap — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::InitTacticalAnalysisMap(int iNumPlots) { m_pGame->GetTacticalAnalysisMap()->Init(iNumPlots); }
// TODO: Phase1 CvDllGame::IsCityScreenBlocked — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsCityScreenBlocked() { return m_pGame->IsCityScreenBlocked(); }
// TODO: Phase1 CvDllGame::CanOpenCityScreen — MISMATCH: Non-padding instruction mnemonic sequence differs.
bool CvDllGame::CanOpenCityScreen(PlayerTypes eOpener, ICvCity1* pCity) { return m_pGame->CanOpenCityScreen(eOpener, pCity ? static_cast<CvDllCity*>(pCity)->GetInstance() : NULL); }
// TODO: Phase1 CvDllGame::IsDebugMode — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsDebugMode() const { return m_pGame->isDebugMode(); }
// TODO: Phase1 CvDllGame::IsFinalInitialized — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsFinalInitialized() const { return m_pGame->isFinalInitialized(); }
// TODO: Phase1 CvDllGame::IsGameMultiPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsGameMultiPlayer() const { return m_pGame->isGameMultiPlayer(); }
// TODO: Phase1 CvDllGame::IsHotSeat — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsHotSeat() const { return m_pGame->isHotSeat(); }
// TODO: Phase1 CvDllGame::IsMPOption — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsMPOption(MultiplayerOptionTypes eIndex) const { return m_pGame->isMPOption(eIndex); }
// TODO: Phase1 CvDllGame::IsNetworkMultiPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsNetworkMultiPlayer() const { return m_pGame->isNetworkMultiPlayer(); }
// TODO: Phase1 CvDllGame::IsOption — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsOption(GameOptionTypes eIndex) const { return m_pGame->isOption(eIndex); }
// TODO: Phase1 CvDllGame::IsPaused — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsPaused() { return m_pGame->isPaused(); }
// TODO: Phase1 CvDllGame::IsPbem — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsPbem() const { return m_pGame->isPbem(); }
// TODO: Phase1 CvDllGame::IsTeamGame — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::IsTeamGame() const { return m_pGame->isTeamGame(); }
// TODO: Phase1 CvDllGame::LogGameState — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::LogGameState(bool bLogHeaders) { m_pGame->LogGameState(bLogHeaders); }
// TODO: Phase1 CvDllGame::ResetTurnTimer — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::ResetTurnTimer() { m_pGame->resetTurnTimer(); }
// TODO: Phase1 CvDllGame::SelectAll — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllGame::SelectAll(ICvPlot1* pPlot) { m_pGame->selectAll(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL); }
// TODO: Phase1 CvDllGame::SelectGroup — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllGame::SelectGroup(ICvUnit1* pUnit, bool bShift, bool bCtrl, bool bAlt) { m_pGame->selectGroup(pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL, bShift, bCtrl, bAlt); }
// TODO: Phase1 CvDllGame::SelectionListIgnoreBuildingDefense — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::SelectionListIgnoreBuildingDefense() { return m_pGame->selectionListIgnoreBuildingDefense(); }
// TODO: Phase1 CvDllGame::SelectionListMove — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllGame::SelectionListMove(ICvPlot1* pPlot, bool bShift) { m_pGame->selectionListMove(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL, bShift); }
// TODO: Phase1 CvDllGame::SelectPlot — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllGame::SelectPlot(ICvPlot1* pPlot) { m_pGame->selectPlot(pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL); }
// TODO: Phase1 CvDllGame::SelectSettler — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SelectSettler() { m_pGame->SelectSettler(); }
// TODO: Phase1 CvDllGame::SelectUnit — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllGame::SelectUnit(ICvUnit1* pUnit, bool bClear, bool bToggle, bool bSound) { m_pGame->selectUnit(pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL, bClear, bToggle, bSound); }
// TODO: Phase1 CvDllGame::SendPlayerOptions — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SendPlayerOptions(bool bForce) { m_pGame->sendPlayerOptions(bForce); }
// TODO: Phase1 CvDllGame::SetDebugMode — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SetDebugMode(bool bDebugMode) { m_pGame->setDebugMode(bDebugMode); }
// TODO: Phase1 CvDllGame::SetFinalInitialized — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SetFinalInitialized(bool bNewValue) { m_pGame->setFinalInitialized(bNewValue); }
// TODO: Phase1 CvDllGame::SetInitialTime — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SetInitialTime(unsigned int uiNewValue) { m_pGame->setInitialTime(uiNewValue); }
// TODO: Phase1 CvDllGame::SetMPOption — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SetMPOption(MultiplayerOptionTypes eIndex, bool bEnabled) { m_pGame->setMPOption(eIndex, bEnabled); }
// TODO: Phase1 CvDllGame::SetPausePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SetPausePlayer(PlayerTypes eNewValue) { m_pGame->setPausePlayer(eNewValue); }
// TODO: Phase1 CvDllGame::SetTimeStr — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
void CvDllGame::SetTimeStr(char* szString, int iGameTurn, bool bSave)
{
	if(szString)
	{
		CvString strString;
		CvGameTextMgr::setDateStr(strString, iGameTurn, bSave, m_pGame->getCalendar(), m_pGame->getStartYear(), m_pGame->getGameSpeedType());
		strcpy(szString, strString.c_str());
	}
}
// TODO: Phase1 CvDllGame::TunerEverConnected — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::TunerEverConnected() const { return m_pGame->TunerEverConnected(); }
// TODO: Phase1 CvDllGame::Uninit — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::Uninit() { m_pGame->uninit(); }
// TODO: Phase1 CvDllGame::UnitIsMoving — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::UnitIsMoving() { m_pGame->unitIsMoving(); }
// TODO: Phase1 CvDllGame::Update — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::Update(float fDeltaTime) { m_pGame->update(fDeltaTime); }
// TODO: Phase1 CvDllGame::UpdateSelectionList — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::UpdateSelectionList() { m_pGame->updateSelectionList(); }
// TODO: Phase1 CvDllGame::UpdateTestEndTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::UpdateTestEndTurn() { m_pGame->updateTestEndTurn(); }
// TODO: Phase1 CvDllGame::Read — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::Read(FDataStream& kStream) { m_pGame->Read(kStream); }
// TODO: Phase1 CvDllGame::Write — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::Write(FDataStream& kStream) const { m_pGame->Write(kStream); }
// TODO: Phase1 CvDllGame::ReadSupportingClassData — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::ReadSupportingClassData(FDataStream& kStream) { m_pGame->ReadSupportingClassData(kStream); }
// TODO: Phase1 CvDllGame::WriteSupportingClassData — MISMATCH: Current relocations reference target-absent imports: _ZNK6CvGame24WriteSupportingClassDataER11FDataStream.
void CvDllGame::WriteSupportingClassData(FDataStream& kStream) const { m_pGame->WriteSupportingClassData(kStream); }
// TODO: Phase1 CvDllGame::WriteReplay — MISMATCH: Current relocations reference target-absent imports: _ZNK6CvGame11writeReplayER11FDataStream.
void CvDllGame::WriteReplay(FDataStream& kStream) const { m_pGame->writeReplay(kStream); }
// TODO: Phase1 CvDllGame::CanMoveUnitTo — MISMATCH: Non-padding instruction mnemonic sequence differs.
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
// TODO: Phase1 CvDllGame::NetMessageStaticsReset — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::NetMessageStaticsReset() { m_pGame->NetMessageStaticsReset(); }
// TODO: Phase1 CvDllGame::SetLastTurnAICivsProcessed — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SetLastTurnAICivsProcessed() { m_pGame->SetInitialAICivsFinished(); }
// TODO: Phase1 CvDllGame::SetNextSequentialPlayerTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SetNextSequentialPlayerTurnActive(PlayerTypes ePlayer) { m_pGame->SetNextSequentialPlayerTurnActive(ePlayer); }
// TODO: Phase1 CvDllGame::IsQueueGameCoreMessageFrame — MISMATCH: Current relocations reference target-absent imports: _ZN6CvGame27IsQueueGameCoreMessageFrameEv.
bool CvDllGame::IsQueueGameCoreMessageFrame() { return m_pGame->IsQueueGameCoreMessageFrame(); }

// TODO: Phase1 CvDllGame::GetStationByID — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvStation1* CvDllGame::GetStationByID(int iID)
{
	CvStation* pStation = m_pGame->GetGameMinorPowers()->GetStation(iID);
	return pStation ? new CvDllStation(pStation) : NULL;
}
// TODO: Phase1 CvDllGame::GetStationByPlot — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvStation1* CvDllGame::GetStationByPlot(ICvPlot1* pPlot)
{
	CvStation* pStation = m_pGame->GetGameMinorPowers()->GetStationByPlot(pPlot->GetPlotIndex());
	return pStation ? new CvDllStation(pStation) : NULL;
}
// TODO: Phase1 CvDllGame::FirstStation — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvStation1* CvDllGame::FirstStation(int* pIndex, bool bRevive)
{
	CvStation* pStation = m_pGame->GetGameMinorPowers()->FirstStation(pIndex, bRevive);
	return pStation ? new CvDllStation(pStation) : NULL;
}
// TODO: Phase1 CvDllGame::NextStation — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvStation1* CvDllGame::NextStation(int* pIndex, bool bRevive)
{
	CvStation* pStation = m_pGame->GetGameMinorPowers()->NextStation(pIndex, bRevive);
	return pStation ? new CvDllStation(pStation) : NULL;
}
// TODO: Phase1 CvDllGame::GetNumStations — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetNumStations() const { return m_pGame->GetGameMinorPowers()->GetNumStations(); }
// TODO: Phase1 CvDllGame::GetTurnOrder — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllGame::GetTurnOrder(PlayerTypes ePlayer) const { return m_pGame->GetTurnOrder(ePlayer); }
// TODO: Phase1 CvDllGame::GetPlayerIDForTurnOrder — UNVERIFIED: Full operand and relocation-target comparison not established.
PlayerTypes CvDllGame::GetPlayerIDForTurnOrder(int iTurnOrder) const { return m_pGame->GetPlayerIDForTurnOrder(iTurnOrder); }
// TODO: Phase1 CvDllGame::SendSaveDataToPartnerApp — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SendSaveDataToPartnerApp() const { m_pGame->GetPartnerApp()->PushCurrentGameToPartnerApp(); }
// TODO: Phase1 CvDllGame::GetCovertOpsVisibleTradeRouteIDs — MISMATCH: Phase1 prohibits dependent TradeConnection::m_padding[0x1dc] fabricated array stride.
std::vector<int> CvDllGame::GetCovertOpsVisibleTradeRouteIDs(PlayerTypes ePlayer) const
{
	std::vector<TradeConnection> routes = m_pGame->GetGameTrade()->GetCovertOpsVisibleTradeRoutes(ePlayer);
	std::vector<int> routeIDs(routes.size());
	for(size_t i = 0; i < routes.size(); ++i)
		routeIDs[i] = routes[i].m_iID;
	return routeIDs;
}
// TODO: Phase1 CvDllGame::GetUnitEntryBasedOnUpgrades — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllGame::GetUnitEntryBasedOnUpgrades(const char* szUnitType, int iUnitTier, UnitUpgradeTypes eUpgrade, CvString& strUnitEntry) { return m_pGame->GetUnitEntryBasedOnUpgrades(szUnitType, iUnitTier, eUpgrade, strUnitEntry); }
// TODO: Phase1 CvDllGame::SetAIAutoPlay — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllGame::SetAIAutoPlay(int iNumTurns, PlayerTypes ePlayer) { m_pGame->setAIAutoPlay(iNumTurns, ePlayer); }
