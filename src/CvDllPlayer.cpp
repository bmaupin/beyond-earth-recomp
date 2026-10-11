#include "CvGameCoreDLLPCH.h"
#include "CvDllPlayer.h"
#include "CvDllContext.h"
#include "CvDllCity.h"
#include "CvDllOutpost.h"
#include "CvDllPlot.h"
#include "CvDllUnit.h"
#include "CvDllDealAI.h"
#include "CvDllDiplomacyAI.h"
#include "CvDllCovertAgent.h"
#include "CvDiplomacyRequests.h"
#include "CvPlayerUnitUpgrades.h"
#include "CvTreasury.h"
#include "CvMinorCivAI.h"

namespace
{
// Target i386 fields whose owning class layouts are not yet reconstructed.
// TODO: Phase1 PlayerField<T> — raw byte offsets are prohibited; reconstruct authentic owning members before relying on this helper.
template<class T> const T& PlayerField(const void* object, size_t offset)
{
	return *reinterpret_cast<const T*>(static_cast<const char*>(object) + offset);
}
// TODO: Phase1 CovertAgents — PlayerField at 0x10 substitutes an incomplete CvPlayerCovertOps layout; reconstruct the actual member.
const std::vector<CvCovertAgent*>& CovertAgents(CvPlayerCovertOps* covertOps)
{
	return PlayerField<std::vector<CvCovertAgent*> >(covertOps, 0x10);
}
}

// TODO: Phase1 CvDllPlayer::CvDllPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
CvDllPlayer::CvDllPlayer(CvPlayerAI* pPlayer) : m_uiRefCount(1), m_pPlayer(pPlayer)
{
	if(gDLL) gDLL->GetGameCoreLock();
}
// TODO: Phase1 CvDllPlayer::~CvDllPlayer — MISMATCH: Non-padding instruction mnemonic sequence differs.
CvDllPlayer::~CvDllPlayer()
{
	if(gDLL) gDLL->ReleaseGameCoreLock();
}
// TODO: Phase1 CvDllPlayer::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllPlayer::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() || guidInterface == ICvPlayer1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}
	return NULL;
}
unsigned int CvDllPlayer::IncrementReference() { return ++m_uiRefCount; }
// TODO: Phase1 CvDllPlayer::DecrementReference — MISMATCH: Non-padding instruction mnemonic sequence differs.
unsigned int CvDllPlayer::DecrementReference()
{
	if(m_uiRefCount == 1) { delete this; return 0; }
	return --m_uiRefCount;
}
unsigned int CvDllPlayer::GetReferenceCount() { return m_uiRefCount; }
// TODO: Phase1 CvDllPlayer::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::Destroy() { DecrementReference(); }
// TODO: Phase1 CvDllPlayer::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllPlayer::operator delete(void* p) { CvDllGameContext::Free(p); }
// TODO: Phase1 CvDllPlayer::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllPlayer::operator new(size_t bytes) { return CvDllGameContext::Allocate(bytes); }
CvPlayerAI* CvDllPlayer::GetInstance() { return m_pPlayer; }
// TODO: Phase1 CvDllPlayer::Init — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::Init(PlayerTypes eID) { m_pPlayer->init(eID); }
// TODO: Phase1 CvDllPlayer::SetupGraphical — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::SetupGraphical() { m_pPlayer->setupGraphical(); }
// TODO: Phase1 CvDllPlayer::InitAffinityValues — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::InitAffinityValues() { m_pPlayer->InitAffinityValues(); }
// TODO: Phase1 CvDllPlayer::LaterInit — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::LaterInit() { m_pPlayer->gameStartInit(); }
// TODO: Phase1 CvDllPlayer::Uninit — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::Uninit() { m_pPlayer->uninit(); }
// TODO: Phase1 CvDllPlayer::IsHuman — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsHuman() const { return m_pPlayer->isHuman(); }
// TODO: Phase1 CvDllPlayer::IsAlien — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsAlien() const { return m_pPlayer->isAlien(); }
// TODO: Phase1 CvDllPlayer::IsObserver — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsObserver() const { return m_pPlayer->isObserver(); }
// TODO: Phase1 CvDllPlayer::GetName — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllPlayer::GetName() const { return m_pPlayer->getName(); }
// TODO: Phase1 CvDllPlayer::GetNickName — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllPlayer::GetNickName() const { return m_pPlayer->getNickName(); }
// TODO: Phase1 CvDllPlayer::GetArtStyleType — UNVERIFIED: Full operand and relocation-target comparison not established.
ArtStyleTypes CvDllPlayer::GetArtStyleType() const { return m_pPlayer->getArtStyleType(); }
// TODO: Phase1 CvDllPlayer::GetFirstReadyUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvUnit1* CvDllPlayer::GetFirstReadyUnit()
{
	CvUnit* unit = m_pPlayer->GetFirstReadyUnit();
	return unit ? new CvDllUnit(unit) : NULL;
}
// TODO: Phase1 CvDllPlayer::HasBusyUnit — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::HasBusyUnit() const { return m_pPlayer->hasBusyUnit(); }
// TODO: Phase1 CvDllPlayer::HasBusyUnitOrCity — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::HasBusyUnitOrCity() const { return m_pPlayer->hasBusyUnitOrCity(); }
// TODO: Phase1 CvDllPlayer::GetScore — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPlayer::GetScore(bool bFinal, bool bVictory) const { return m_pPlayer->GetScore(bFinal, bVictory); }
// TODO: Phase1 CvDllPlayer::GetStartingPlot — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvPlot1* CvDllPlayer::GetStartingPlot() const
{
	CvPlot* plot = m_pPlayer->getStartingPlot();
	return plot ? new CvDllPlot(plot) : NULL;
}
// TODO: Phase1 CvDllPlayer::GetCapitalCity — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvCity1* CvDllPlayer::GetCapitalCity()
{
	CvCity* city = m_pPlayer->getCapitalCity();
	return city ? new CvDllCity(city) : NULL;
}
// TODO: Phase1 CvDllPlayer::IsHasLostCapital — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsHasLostCapital() const { return m_pPlayer->IsHasLostCapital(); }
// TODO: Phase1 CvDllPlayer::SetStartTime — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::SetStartTime(unsigned int uiStartTime) { m_pPlayer->setStartTime(uiStartTime); }
// TODO: Phase1 CvDllPlayer::IsMinorCiv — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsMinorCiv() const { return m_pPlayer->isMinorCiv(); }
// TODO: Phase1 CvDllPlayer::IsAlive — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
bool CvDllPlayer::IsAlive() const { return PlayerField<bool>(m_pPlayer, 0x858); }
// TODO: Phase1 CvDllPlayer::IsEverAlive — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
bool CvDllPlayer::IsEverAlive() const { return PlayerField<bool>(m_pPlayer, 0x864); }
// TODO: Phase1 CvDllPlayer::IsTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsTurnActive() const { return m_pPlayer->isTurnActive(); }
// TODO: Phase1 CvDllPlayer::SetTurnActive — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::SetTurnActive(bool bNewValue, bool bDoTurn) { m_pPlayer->setTurnActive(bNewValue, bDoTurn); }
// TODO: Phase1 CvDllPlayer::GetID — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
PlayerTypes CvDllPlayer::GetID() const { return PlayerField<PlayerTypes>(m_pPlayer, 0x28); }
// TODO: Phase1 CvDllPlayer::GetHandicapType — UNVERIFIED: Full operand and relocation-target comparison not established.
HandicapTypes CvDllPlayer::GetHandicapType() const { return m_pPlayer->getHandicapType(); }
// TODO: Phase1 CvDllPlayer::GetCivilizationType — UNVERIFIED: Full operand and relocation-target comparison not established.
CivilizationTypes CvDllPlayer::GetCivilizationType() const { return m_pPlayer->getCivilizationType(); }
// TODO: Phase1 CvDllPlayer::GetLeaderType — UNVERIFIED: Full operand and relocation-target comparison not established.
LeaderHeadTypes CvDllPlayer::GetLeaderType() const { return m_pPlayer->getLeaderType(); }
// TODO: Phase1 CvDllPlayer::GetLeaderTypeKey — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllPlayer::GetLeaderTypeKey() const { return m_pPlayer->getLeaderTypeKey(); }
// TODO: Phase1 CvDllPlayer::GetCurrentEra — UNVERIFIED: Full operand and relocation-target comparison not established.
EraTypes CvDllPlayer::GetCurrentEra() const { return m_pPlayer->GetCurrentEra(); }
// TODO: Phase1 CvDllPlayer::GetTeam — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
TeamTypes CvDllPlayer::GetTeam() const
{
	PlayerTypes player = PlayerField<PlayerTypes>(m_pPlayer, 0x28);
	return static_cast<unsigned int>(player) < 64 ? (*CvPreGame::sr_TeamTypes)[player] : NO_TEAM;
}
// TODO: Phase1 CvDllPlayer::GetPlayerColor — UNVERIFIED: Full operand and relocation-target comparison not established.
PlayerColorTypes CvDllPlayer::GetPlayerColor() const { return m_pPlayer->getPlayerColor(); }
// TODO: Phase1 CvDllPlayer::IsOption — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsOption(PlayerOptionTypes eOption) const { return m_pPlayer->isOption(eOption); }
// TODO: Phase1 CvDllPlayer::IsOptionKey — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsOptionKey(PlayerOptionTypes eOption) const { return m_pPlayer->isOption(eOption); }
// TODO: Phase1 CvDllPlayer::FirstCity — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvCity1* CvDllPlayer::FirstCity(int* pIterIdx, bool bRev)
{
	CvCity* city = m_pPlayer->firstCity(pIterIdx, bRev);
	return city ? new CvDllCity(city) : NULL;
}
// TODO: Phase1 CvDllPlayer::NextCity — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvCity1* CvDllPlayer::NextCity(int* pIterIdx, bool bRev)
{
	CvCity* city = m_pPlayer->nextCity(pIterIdx, bRev);
	return city ? new CvDllCity(city) : NULL;
}
// TODO: Phase1 CvDllPlayer::GetNumCities — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPlayer::GetNumCities() const { return m_pPlayer->getNumCities(); }
// TODO: Phase1 CvDllPlayer::FirstOutpost — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvOutpost1* CvDllPlayer::FirstOutpost(int* pIterIdx, bool bRev)
{
	CvOutpost* outpost = m_pPlayer->FirstOutpost(pIterIdx, bRev);
	return outpost ? new CvDllOutpost(outpost) : NULL;
}
// TODO: Phase1 CvDllPlayer::NextOutpost — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvOutpost1* CvDllPlayer::NextOutpost(int* pIterIdx, bool bRev)
{
	CvOutpost* outpost = m_pPlayer->NextOutpost(pIterIdx, bRev);
	return outpost ? new CvDllOutpost(outpost) : NULL;
}
// TODO: Phase1 CvDllPlayer::GetNumOutposts — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPlayer::GetNumOutposts() const { return m_pPlayer->GetNumOutposts(); }
// TODO: Phase1 CvDllPlayer::GetOutpost — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvOutpost1* CvDllPlayer::GetOutpost(int iID)
{
	CvOutpost* outpost = m_pPlayer->GetOutpost(iID);
	return outpost ? new CvDllOutpost(outpost) : NULL;
}
// TODO: Phase1 CvDllPlayer::GetCity — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvCity1* CvDllPlayer::GetCity(int iID)
{
	CvCity* city = m_pPlayer->getCity(iID);
	return city ? new CvDllCity(city) : NULL;
}
// TODO: Phase1 CvDllPlayer::FirstUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvUnit1* CvDllPlayer::FirstUnit(int* pIterIdx, bool bRev)
{
	CvUnit* unit = m_pPlayer->firstUnit(pIterIdx, bRev);
	return unit ? new CvDllUnit(unit) : NULL;
}
// TODO: Phase1 CvDllPlayer::NextUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvUnit1* CvDllPlayer::NextUnit(int* pIterIdx, bool bRev)
{
	CvUnit* unit = m_pPlayer->nextUnit(pIterIdx, bRev);
	return unit ? new CvDllUnit(unit) : NULL;
}
// TODO: Phase1 CvDllPlayer::GetUnit — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvUnit1* CvDllPlayer::GetUnit(int iID)
{
	CvUnit* unit = m_pPlayer->getUnit(iID);
	return unit ? new CvDllUnit(unit) : NULL;
}
// TODO: Phase1 CvDllPlayer::GetPlotDanger — MISMATCH: Non-padding instruction mnemonic sequence differs.
int CvDllPlayer::GetPlotDanger(ICvPlot1* pPlot) const { return m_pPlayer->GetPlotDanger(*static_cast<CvDllPlot*>(pPlot)->GetInstance()); }
// TODO: Phase1 CvDllPlayer::GetCityDistanceHighwaterMark — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPlayer::GetCityDistanceHighwaterMark() const { return m_pPlayer->GetCityDistanceHighwaterMark(); }
// TODO: Phase1 CvDllPlayer::Disconnected — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::Disconnected() { m_pPlayer->disconnected(); }
// TODO: Phase1 CvDllPlayer::Reconnected — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::Reconnected() { m_pPlayer->reconnected(); }
// TODO: Phase1 CvDllPlayer::SetBusyUnitUpdatesRemaining — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::SetBusyUnitUpdatesRemaining(int iUpdateCount) { m_pPlayer->setBusyUnitUpdatesRemaining(iUpdateCount); }
// TODO: Phase1 CvDllPlayer::HasUnitsThatNeedAIUpdate — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::HasUnitsThatNeedAIUpdate() const { return m_pPlayer->hasUnitsThatNeedAIUpdate(); }
// TODO: Phase1 CvDllPlayer::GetDominantAffinity — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
AffinityType CvDllPlayer::GetDominantAffinity() const { return PlayerField<CvPlayerAffinities*>(m_pPlayer, 0xf4b4)->GetDominantAffinityType(); }
// TODO: Phase1 CvDllPlayer::GetAffinityLevel — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
int CvDllPlayer::GetAffinityLevel(AffinityType eAffinity) const { return PlayerField<CvPlayerAffinities*>(m_pPlayer, 0xf4b4)->GetAffinityLevel(eAffinity); }
// TODO: Phase1 CvDllPlayer::GetAffinityPercentTowardsMaxLevel — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
int CvDllPlayer::GetAffinityPercentTowardsMaxLevel(AffinityType eAffinity) const { return PlayerField<CvPlayerAffinities*>(m_pPlayer, 0xf4b4)->GetAffinityPercentTowardsMaxLevel(eAffinity); }
// TODO: Phase1 CvDllPlayer::GetNumPolicyBranchesFinished — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPlayer::GetNumPolicyBranchesFinished() const { return m_pPlayer->GetPlayerPolicies()->GetNumPolicyBranchesFinished(); }
// TODO: Phase1 CvDllPlayer::Read — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::Read(FDataStream& kStream) { m_pPlayer->Read(kStream); }
// TODO: Phase1 CvDllPlayer::Write — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::Write(FDataStream& kStream) const { m_pPlayer->Write(kStream); }
// TODO: Phase1 CvDllPlayer::GetEnergy — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPlayer::GetEnergy() const { return m_pPlayer->GetTreasury()->GetTotalAccumulatedEnergy(); }
// TODO: Phase1 CvDllPlayer::CalculateBaseNetGold — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPlayer::CalculateBaseNetGold() { return m_pPlayer->GetTreasury()->GetTotalNetEnergyPerTurn(); }
// TODO: Phase1 CvDllPlayer::GetEmbarkedGraphicOverride — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
const char* CvDllPlayer::GetEmbarkedGraphicOverride() { return PlayerField<CvString>(m_pPlayer, 0xb6c).c_str(); }
// TODO: Phase1 CvDllPlayer::GetSyncArchive — UNVERIFIED: Full operand and relocation-target comparison not established.
FAutoArchive& CvDllPlayer::GetSyncArchive() { return m_pPlayer->getSyncArchive(); }
// TODO: Phase1 CvDllPlayer::GetMinorCivType — UNVERIFIED: Full operand and relocation-target comparison not established.
MinorCivTypes CvDllPlayer::GetMinorCivType() const
{
	CvMinorCivAI* minorAI = m_pPlayer->GetMinorCivAI();
	return minorAI ? static_cast<MinorCivTypes>(minorAI->GetMinorCivType()) : NO_MINORCIV;
}
// TODO: Phase1 CvDllPlayer::GetDiplomacyAI — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvDiplomacyAI1* CvDllPlayer::GetDiplomacyAI()
{
	CvDiplomacyAI* ai = m_pPlayer->GetDiplomacyAI();
	return ai ? new CvDllDiplomacyAI(ai) : NULL;
}
// TODO: Phase1 CvDllPlayer::GetDealAI — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvDealAI1* CvDllPlayer::GetDealAI()
{
	CvDealAI* ai = m_pPlayer->GetDealAI();
	return ai ? new CvDllDealAI(ai) : NULL;
}
// TODO: Phase1 CvDllPlayer::MayNotAnnex — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
bool CvDllPlayer::MayNotAnnex() { return PlayerField<bool>(m_pPlayer->GetPlayerTraits(), 0x112); }
// TODO: Phase1 CvDllPlayer::HasCompletedLoadout — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
bool CvDllPlayer::HasCompletedLoadout() const
{
	return PlayerField<bool>(m_pPlayer->GetPlayerLoadout(), 0x10) && PlayerField<bool>(m_pPlayer->GetPlayerLoadout(), 0x11);
}
// TODO: Phase1 CvDllPlayer::AddDiplomacyRequest — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::AddDiplomacyRequest(PlayerTypes ePlayer, DiploUIStateTypes eState, const char* message, LeaderheadAnimationTypes eAnimation, int iExtraGameData)
{
	return m_pPlayer->GetDiplomacyRequests()->Add(ePlayer, eState, message, eAnimation, iExtraGameData);
}
// TODO: Phase1 CvDllPlayer::ActiveDiplomacyRequestComplete — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::ActiveDiplomacyRequestComplete() { m_pPlayer->GetDiplomacyRequests()->ActiveRequestComplete(); }
// TODO: Phase1 CvDllPlayer::AddNotification — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPlayer::AddNotification(NotificationTypes eType, const char* message, const char* summary, int iX, int iY, int iGameDataIndex, int iExtraGameData)
{
	return m_pPlayer->GetNotifications()->Add(eType, message, summary, iX, iY, iGameDataIndex, iExtraGameData);
}
// TODO: Phase1 CvDllPlayer::ActivateNotification — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::ActivateNotification(int iLookupIndex) { m_pPlayer->GetNotifications()->Activate(iLookupIndex); }
// TODO: Phase1 CvDllPlayer::DismissNotification — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::DismissNotification(int iLookupIndex, bool bUserInvoked) { m_pPlayer->GetNotifications()->Dismiss(iLookupIndex, bUserInvoked); }
// TODO: Phase1 CvDllPlayer::MayUserDismissNotification — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::MayUserDismissNotification(int iLookupIndex) { return m_pPlayer->GetNotifications()->MayUserDismiss(iLookupIndex); }
// TODO: Phase1 CvDllPlayer::RebroadcastNotifications — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::RebroadcastNotifications() { m_pPlayer->GetNotifications()->Rebroadcast(); }
// TODO: Phase1 CvDllPlayer::GetCurrentResearchTech — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::GetCurrentResearchTech(TechTypes* pTech, int* pTurnsLeft) const
{
	CvPlayerTechs* techs = m_pPlayer->GetPlayerTechs();
	if(!techs) return false;
	if(pTech) *pTech = techs->GetCurrentResearch();
	if(pTurnsLeft) *pTurnsLeft = techs->GetResearchTurnsLeft(techs->GetCurrentResearch(), false);
	return true;
}
// TODO: Phase1 CvDllPlayer::IsSimultaneousTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::IsSimultaneousTurns() const { return m_pPlayer->isSimultaneousTurns(); }
// TODO: Phase1 CvDllPlayer::HasTurnTimerExpired — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::HasTurnTimerExpired() { return m_pPlayer->hasTurnTimerExpired(); }
// TODO: Phase1 CvDllPlayer::GetBestUnitUpgrade — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
void CvDllPlayer::GetBestUnitUpgrade(UnitTypes eUnit, UnitUpgradeTypes& eUpgrade, UnitPerkTypes& ePerk)
{
	PlayerField<CvPlayerUnitUpgrades*>(m_pPlayer, 0xf4b8)->GetBestUnitUpgrade(eUnit, eUpgrade, ePerk);
}
// TODO: Phase1 CvDllPlayer::WaitForEffect — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPlayer::WaitForEffect(bool bWait) { m_pPlayer->WaitForEffect(bWait); }
// TODO: Phase1 CvDllPlayer::GetCovertAgents — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
std::vector<std::unique_ptr<ICvCovertAgent1> > CvDllPlayer::GetCovertAgents() const
{
	const std::vector<CvCovertAgent*>& agents = CovertAgents(m_pPlayer->GetPlayerCovertOps());
	// The target sizes the vector before appending, retaining leading null entries.
	std::vector<std::unique_ptr<ICvCovertAgent1> > result(agents.size());
	for(std::vector<CvCovertAgent*>::const_iterator it = agents.begin(); it != agents.end(); ++it)
		result.push_back(std::unique_ptr<ICvCovertAgent1>(new CvDllCovertAgent(*it)));
	return result;
}
// TODO: Phase1 CvDllPlayer::GetCovertAgentByIndex — MISMATCH: Phase1 prohibits PlayerField/CovertAgents raw-offset layout shortcut; preserve body pending authentic layout reconstruction.
std::unique_ptr<ICvCovertAgent1> CvDllPlayer::GetCovertAgentByIndex(int iIndex) const
{
	const std::vector<CvCovertAgent*>& agents = CovertAgents(m_pPlayer->GetPlayerCovertOps());
	if(iIndex > 0 && iIndex < static_cast<int>(agents.size()))
		return std::unique_ptr<ICvCovertAgent1>(new CvDllCovertAgent(agents[iIndex]));
	return std::unique_ptr<ICvCovertAgent1>();
}
// TODO: Phase1 CvDllPlayer::HasMadePlanetfall — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPlayer::HasMadePlanetfall() const { return m_pPlayer->hasMadePlanetfall(); }
