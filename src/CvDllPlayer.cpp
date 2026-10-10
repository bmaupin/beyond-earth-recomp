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
template<class T> const T& PlayerField(const void* object, size_t offset)
{
	return *reinterpret_cast<const T*>(static_cast<const char*>(object) + offset);
}
const std::vector<CvCovertAgent*>& CovertAgents(CvPlayerCovertOps* covertOps)
{
	return PlayerField<std::vector<CvCovertAgent*> >(covertOps, 0x10);
}
}

CvDllPlayer::CvDllPlayer(CvPlayerAI* pPlayer) : m_uiRefCount(1), m_pPlayer(pPlayer)
{
	if(gDLL) gDLL->GetGameCoreLock();
}
CvDllPlayer::~CvDllPlayer()
{
	if(gDLL) gDLL->ReleaseGameCoreLock();
}
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
unsigned int CvDllPlayer::DecrementReference()
{
	if(m_uiRefCount == 1) { delete this; return 0; }
	return --m_uiRefCount;
}
unsigned int CvDllPlayer::GetReferenceCount() { return m_uiRefCount; }
void CvDllPlayer::Destroy() { DecrementReference(); }
void CvDllPlayer::operator delete(void* p) { CvDllGameContext::Free(p); }
void* CvDllPlayer::operator new(size_t bytes) { return CvDllGameContext::Allocate(bytes); }
CvPlayerAI* CvDllPlayer::GetInstance() { return m_pPlayer; }
void CvDllPlayer::Init(PlayerTypes eID) { m_pPlayer->init(eID); }
void CvDllPlayer::SetupGraphical() { m_pPlayer->setupGraphical(); }
void CvDllPlayer::InitAffinityValues() { m_pPlayer->InitAffinityValues(); }
void CvDllPlayer::LaterInit() { m_pPlayer->gameStartInit(); }
void CvDllPlayer::Uninit() { m_pPlayer->uninit(); }
bool CvDllPlayer::IsHuman() const { return m_pPlayer->isHuman(); }
bool CvDllPlayer::IsAlien() const { return m_pPlayer->isAlien(); }
bool CvDllPlayer::IsObserver() const { return m_pPlayer->isObserver(); }
const char* CvDllPlayer::GetName() const { return m_pPlayer->getName(); }
const char* CvDllPlayer::GetNickName() const { return m_pPlayer->getNickName(); }
ArtStyleTypes CvDllPlayer::GetArtStyleType() const { return m_pPlayer->getArtStyleType(); }
ICvUnit1* CvDllPlayer::GetFirstReadyUnit()
{
	CvUnit* unit = m_pPlayer->GetFirstReadyUnit();
	return unit ? new CvDllUnit(unit) : NULL;
}
bool CvDllPlayer::HasBusyUnit() const { return m_pPlayer->hasBusyUnit(); }
bool CvDllPlayer::HasBusyUnitOrCity() const { return m_pPlayer->hasBusyUnitOrCity(); }
int CvDllPlayer::GetScore(bool bFinal, bool bVictory) const { return m_pPlayer->GetScore(bFinal, bVictory); }
ICvPlot1* CvDllPlayer::GetStartingPlot() const
{
	CvPlot* plot = m_pPlayer->getStartingPlot();
	return plot ? new CvDllPlot(plot) : NULL;
}
ICvCity1* CvDllPlayer::GetCapitalCity()
{
	CvCity* city = m_pPlayer->getCapitalCity();
	return city ? new CvDllCity(city) : NULL;
}
bool CvDllPlayer::IsHasLostCapital() const { return m_pPlayer->IsHasLostCapital(); }
void CvDllPlayer::SetStartTime(unsigned int uiStartTime) { m_pPlayer->setStartTime(uiStartTime); }
bool CvDllPlayer::IsMinorCiv() const { return m_pPlayer->isMinorCiv(); }
bool CvDllPlayer::IsAlive() const { return PlayerField<bool>(m_pPlayer, 0x858); }
bool CvDllPlayer::IsEverAlive() const { return PlayerField<bool>(m_pPlayer, 0x864); }
bool CvDllPlayer::IsTurnActive() const { return m_pPlayer->isTurnActive(); }
void CvDllPlayer::SetTurnActive(bool bNewValue, bool bDoTurn) { m_pPlayer->setTurnActive(bNewValue, bDoTurn); }
PlayerTypes CvDllPlayer::GetID() const { return PlayerField<PlayerTypes>(m_pPlayer, 0x28); }
HandicapTypes CvDllPlayer::GetHandicapType() const { return m_pPlayer->getHandicapType(); }
CivilizationTypes CvDllPlayer::GetCivilizationType() const { return m_pPlayer->getCivilizationType(); }
LeaderHeadTypes CvDllPlayer::GetLeaderType() const { return m_pPlayer->getLeaderType(); }
const char* CvDllPlayer::GetLeaderTypeKey() const { return m_pPlayer->getLeaderTypeKey(); }
EraTypes CvDllPlayer::GetCurrentEra() const { return m_pPlayer->GetCurrentEra(); }
TeamTypes CvDllPlayer::GetTeam() const
{
	PlayerTypes player = PlayerField<PlayerTypes>(m_pPlayer, 0x28);
	return static_cast<unsigned int>(player) < 64 ? (*CvPreGame::sr_TeamTypes)[player] : NO_TEAM;
}
PlayerColorTypes CvDllPlayer::GetPlayerColor() const { return m_pPlayer->getPlayerColor(); }
bool CvDllPlayer::IsOption(PlayerOptionTypes eOption) const { return m_pPlayer->isOption(eOption); }
bool CvDllPlayer::IsOptionKey(PlayerOptionTypes eOption) const { return m_pPlayer->isOption(eOption); }
ICvCity1* CvDllPlayer::FirstCity(int* pIterIdx, bool bRev)
{
	CvCity* city = m_pPlayer->firstCity(pIterIdx, bRev);
	return city ? new CvDllCity(city) : NULL;
}
ICvCity1* CvDllPlayer::NextCity(int* pIterIdx, bool bRev)
{
	CvCity* city = m_pPlayer->nextCity(pIterIdx, bRev);
	return city ? new CvDllCity(city) : NULL;
}
int CvDllPlayer::GetNumCities() const { return m_pPlayer->getNumCities(); }
ICvOutpost1* CvDllPlayer::FirstOutpost(int* pIterIdx, bool bRev)
{
	CvOutpost* outpost = m_pPlayer->FirstOutpost(pIterIdx, bRev);
	return outpost ? new CvDllOutpost(outpost) : NULL;
}
ICvOutpost1* CvDllPlayer::NextOutpost(int* pIterIdx, bool bRev)
{
	CvOutpost* outpost = m_pPlayer->NextOutpost(pIterIdx, bRev);
	return outpost ? new CvDllOutpost(outpost) : NULL;
}
int CvDllPlayer::GetNumOutposts() const { return m_pPlayer->GetNumOutposts(); }
ICvOutpost1* CvDllPlayer::GetOutpost(int iID)
{
	CvOutpost* outpost = m_pPlayer->GetOutpost(iID);
	return outpost ? new CvDllOutpost(outpost) : NULL;
}
ICvCity1* CvDllPlayer::GetCity(int iID)
{
	CvCity* city = m_pPlayer->getCity(iID);
	return city ? new CvDllCity(city) : NULL;
}
ICvUnit1* CvDllPlayer::FirstUnit(int* pIterIdx, bool bRev)
{
	CvUnit* unit = m_pPlayer->firstUnit(pIterIdx, bRev);
	return unit ? new CvDllUnit(unit) : NULL;
}
ICvUnit1* CvDllPlayer::NextUnit(int* pIterIdx, bool bRev)
{
	CvUnit* unit = m_pPlayer->nextUnit(pIterIdx, bRev);
	return unit ? new CvDllUnit(unit) : NULL;
}
ICvUnit1* CvDllPlayer::GetUnit(int iID)
{
	CvUnit* unit = m_pPlayer->getUnit(iID);
	return unit ? new CvDllUnit(unit) : NULL;
}
int CvDllPlayer::GetPlotDanger(ICvPlot1* pPlot) const { return m_pPlayer->GetPlotDanger(*static_cast<CvDllPlot*>(pPlot)->GetInstance()); }
int CvDllPlayer::GetCityDistanceHighwaterMark() const { return m_pPlayer->GetCityDistanceHighwaterMark(); }
void CvDllPlayer::Disconnected() { m_pPlayer->disconnected(); }
void CvDllPlayer::Reconnected() { m_pPlayer->reconnected(); }
void CvDllPlayer::SetBusyUnitUpdatesRemaining(int iUpdateCount) { m_pPlayer->setBusyUnitUpdatesRemaining(iUpdateCount); }
bool CvDllPlayer::HasUnitsThatNeedAIUpdate() const { return m_pPlayer->hasUnitsThatNeedAIUpdate(); }
AffinityType CvDllPlayer::GetDominantAffinity() const { return PlayerField<CvPlayerAffinities*>(m_pPlayer, 0xf4b4)->GetDominantAffinityType(); }
int CvDllPlayer::GetAffinityLevel(AffinityType eAffinity) const { return PlayerField<CvPlayerAffinities*>(m_pPlayer, 0xf4b4)->GetAffinityLevel(eAffinity); }
int CvDllPlayer::GetAffinityPercentTowardsMaxLevel(AffinityType eAffinity) const { return PlayerField<CvPlayerAffinities*>(m_pPlayer, 0xf4b4)->GetAffinityPercentTowardsMaxLevel(eAffinity); }
int CvDllPlayer::GetNumPolicyBranchesFinished() const { return m_pPlayer->GetPlayerPolicies()->GetNumPolicyBranchesFinished(); }
void CvDllPlayer::Read(FDataStream& kStream) { m_pPlayer->Read(kStream); }
void CvDllPlayer::Write(FDataStream& kStream) const { m_pPlayer->Write(kStream); }
int CvDllPlayer::GetEnergy() const { return m_pPlayer->GetTreasury()->GetTotalAccumulatedEnergy(); }
int CvDllPlayer::CalculateBaseNetGold() { return m_pPlayer->GetTreasury()->GetTotalNetEnergyPerTurn(); }
const char* CvDllPlayer::GetEmbarkedGraphicOverride() { return PlayerField<CvString>(m_pPlayer, 0xb6c).c_str(); }
FAutoArchive& CvDllPlayer::GetSyncArchive() { return m_pPlayer->getSyncArchive(); }
MinorCivTypes CvDllPlayer::GetMinorCivType() const
{
	CvMinorCivAI* minorAI = m_pPlayer->GetMinorCivAI();
	return minorAI ? static_cast<MinorCivTypes>(minorAI->GetMinorCivType()) : NO_MINORCIV;
}
ICvDiplomacyAI1* CvDllPlayer::GetDiplomacyAI()
{
	CvDiplomacyAI* ai = m_pPlayer->GetDiplomacyAI();
	return ai ? new CvDllDiplomacyAI(ai) : NULL;
}
ICvDealAI1* CvDllPlayer::GetDealAI()
{
	CvDealAI* ai = m_pPlayer->GetDealAI();
	return ai ? new CvDllDealAI(ai) : NULL;
}
bool CvDllPlayer::MayNotAnnex() { return PlayerField<bool>(m_pPlayer->GetPlayerTraits(), 0x112); }
bool CvDllPlayer::HasCompletedLoadout() const
{
	return PlayerField<bool>(m_pPlayer->GetPlayerLoadout(), 0x10) && PlayerField<bool>(m_pPlayer->GetPlayerLoadout(), 0x11);
}
bool CvDllPlayer::AddDiplomacyRequest(PlayerTypes ePlayer, DiploUIStateTypes eState, const char* message, LeaderheadAnimationTypes eAnimation, int iExtraGameData)
{
	return m_pPlayer->GetDiplomacyRequests()->Add(ePlayer, eState, message, eAnimation, iExtraGameData);
}
void CvDllPlayer::ActiveDiplomacyRequestComplete() { m_pPlayer->GetDiplomacyRequests()->ActiveRequestComplete(); }
int CvDllPlayer::AddNotification(NotificationTypes eType, const char* message, const char* summary, int iX, int iY, int iGameDataIndex, int iExtraGameData)
{
	return m_pPlayer->GetNotifications()->Add(eType, message, summary, iX, iY, iGameDataIndex, iExtraGameData);
}
void CvDllPlayer::ActivateNotification(int iLookupIndex) { m_pPlayer->GetNotifications()->Activate(iLookupIndex); }
void CvDllPlayer::DismissNotification(int iLookupIndex, bool bUserInvoked) { m_pPlayer->GetNotifications()->Dismiss(iLookupIndex, bUserInvoked); }
bool CvDllPlayer::MayUserDismissNotification(int iLookupIndex) { return m_pPlayer->GetNotifications()->MayUserDismiss(iLookupIndex); }
void CvDllPlayer::RebroadcastNotifications() { m_pPlayer->GetNotifications()->Rebroadcast(); }
bool CvDllPlayer::GetCurrentResearchTech(TechTypes* pTech, int* pTurnsLeft) const
{
	CvPlayerTechs* techs = m_pPlayer->GetPlayerTechs();
	if(!techs) return false;
	if(pTech) *pTech = techs->GetCurrentResearch();
	if(pTurnsLeft) *pTurnsLeft = techs->GetResearchTurnsLeft(techs->GetCurrentResearch(), false);
	return true;
}
bool CvDllPlayer::IsSimultaneousTurns() const { return m_pPlayer->isSimultaneousTurns(); }
bool CvDllPlayer::HasTurnTimerExpired() { return m_pPlayer->hasTurnTimerExpired(); }
void CvDllPlayer::GetBestUnitUpgrade(UnitTypes eUnit, UnitUpgradeTypes& eUpgrade, UnitPerkTypes& ePerk)
{
	PlayerField<CvPlayerUnitUpgrades*>(m_pPlayer, 0xf4b8)->GetBestUnitUpgrade(eUnit, eUpgrade, ePerk);
}
void CvDllPlayer::WaitForEffect(bool bWait) { m_pPlayer->WaitForEffect(bWait); }
std::vector<std::unique_ptr<ICvCovertAgent1> > CvDllPlayer::GetCovertAgents() const
{
	const std::vector<CvCovertAgent*>& agents = CovertAgents(m_pPlayer->GetPlayerCovertOps());
	// The target sizes the vector before appending, retaining leading null entries.
	std::vector<std::unique_ptr<ICvCovertAgent1> > result(agents.size());
	for(std::vector<CvCovertAgent*>::const_iterator it = agents.begin(); it != agents.end(); ++it)
		result.push_back(std::unique_ptr<ICvCovertAgent1>(new CvDllCovertAgent(*it)));
	return result;
}
std::unique_ptr<ICvCovertAgent1> CvDllPlayer::GetCovertAgentByIndex(int iIndex) const
{
	const std::vector<CvCovertAgent*>& agents = CovertAgents(m_pPlayer->GetPlayerCovertOps());
	if(iIndex > 0 && iIndex < static_cast<int>(agents.size()))
		return std::unique_ptr<ICvCovertAgent1>(new CvDllCovertAgent(agents[iIndex]));
	return std::unique_ptr<ICvCovertAgent1>();
}
bool CvDllPlayer::HasMadePlanetfall() const { return m_pPlayer->hasMadePlanetfall(); }
