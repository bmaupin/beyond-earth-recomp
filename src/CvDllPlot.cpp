#include "CvGameCoreDLLPCH.h"
#include "CvDllPlot.h"
#include "CvDllContext.h"
#include "CvDllCity.h"
#include "CvDllOutpost.h"
#include "CvDllStrategicSite.h"
#include "CvDllUnit.h"
#include "CvPlot.h"
#include "CvUnit.h"

#if !defined(__EXCEPTIONS)
#error CvDllPlot requires exceptions to reproduce native allocation cleanup.
#endif

CvDllPlot::CvDllPlot(CvPlot* pPlot) : m_uiRefCount(1), m_pPlot(pPlot) {}
CvDllPlot::~CvDllPlot() {}
void* CvDllPlot::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() || guidInterface == ICvPlot1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}
	return NULL;
}
unsigned int CvDllPlot::IncrementReference() { return ++m_uiRefCount; }
unsigned int CvDllPlot::DecrementReference()
{
	if(m_uiRefCount == 1) { delete this; return 0; }
	return --m_uiRefCount;
}
unsigned int CvDllPlot::GetReferenceCount() { return m_uiRefCount; }
void CvDllPlot::Destroy() { DecrementReference(); }
void CvDllPlot::operator delete(void* p) { CvDllGameContext::Free(p); }
void* CvDllPlot::operator new(size_t bytes) { return CvDllGameContext::Allocate(bytes); }
CvPlot* CvDllPlot::GetInstance() { return m_pPlot; }

TeamTypes CvDllPlot::GetTeam() const { return m_pPlot->getTeam(); }
FogOfWarModeTypes CvDllPlot::GetActiveFogOfWarMode() const { return m_pPlot->GetActiveFogOfWarMode(); }
void CvDllPlot::UpdateCenterUnit() { m_pPlot->updateCenterUnit(); }
bool CvDllPlot::IsAdjacent(ICvPlot1* pPlot) const
{
	CvPlot* pNativePlot = pPlot ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL;
	return m_pPlot->isAdjacent(pNativePlot);
}
bool CvDllPlot::IsRiver() const { return m_pPlot->isRiver(); }
ICvPlot1* CvDllPlot::GetNeighboringPlot(DirectionTypes eDirection) const { CvPlot* pPlot = m_pPlot->getNeighboringPlot(eDirection); return pPlot ? new CvDllPlot(pPlot) : NULL; }
// Beyond Earth adds adjacent-direction lookup; its native contract requires a plot.
DirectionTypes CvDllPlot::GetAdjacentPlotDirection(ICvPlot1* pPlot) const { return m_pPlot->getAdjacentPlotDirection(static_cast<CvDllPlot*>(pPlot)->GetInstance()); }
int CvDllPlot::GetBuildTime(BuildTypes eBuild, PlayerTypes ePlayer) const { return m_pPlot->getBuildTime(eBuild, ePlayer); }
// Beyond Earth exposes walk-water, strategic sites, outposts, miasma and bubbles.
bool CvDllPlot::IsAllowsWalkWater() const { return m_pPlot->IsAllowsWalkWater(); }
bool CvDllPlot::IsVisible(TeamTypes eTeam, bool bDebug) const { return m_pPlot->isVisible(eTeam, bDebug); }
bool CvDllPlot::IsStrategicSite() const { return m_pPlot->getPlotStrategicSite() != NULL; }
bool CvDllPlot::IsEnemyStrategicSite(ICvUnit1* pUnit) const { CvUnit* pNativeUnit = pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL; return pNativeUnit ? m_pPlot->isEnemyStrategicSite(*pNativeUnit) : false; }
bool CvDllPlot::IsCity() const { return m_pPlot->isCity(); }
bool CvDllPlot::IsEnemyCity(ICvUnit1* pUnit) const { CvUnit* pNativeUnit = pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL; return pNativeUnit ? m_pPlot->isEnemyCity(*pNativeUnit) : false; }
bool CvDllPlot::IsOutpost() const { return m_pPlot->isOutpost(); }
bool CvDllPlot::IsEnemyOutpost(ICvUnit1* pUnit) const { CvUnit* pNativeUnit = pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL; return pNativeUnit ? m_pPlot->isEnemyOutpost(*pNativeUnit) : false; }
bool CvDllPlot::IsFighting() const { return m_pPlot->isFighting(); }
bool CvDllPlot::IsTradeRoute(PlayerTypes ePlayer) const { return m_pPlot->IsTradeRoute(ePlayer); }
bool CvDllPlot::IsImpassable() const { return m_pPlot->isImpassable(); }
bool CvDllPlot::HasMiasma() const { return m_pPlot->HasMiasma(); }
bool CvDllPlot::HasBubbles() const { return m_pPlot->HasBubbles(); }
void CvDllPlot::GetPosition(int& iX, int& iY) const { iX = m_pPlot->getX(); iY = m_pPlot->getY(); }
bool CvDllPlot::IsNEOfRiver() const { return m_pPlot->isNEOfRiver(); }
bool CvDllPlot::IsWOfRiver() const { return m_pPlot->isWOfRiver(); }
bool CvDllPlot::IsNWOfRiver() const { return m_pPlot->isNWOfRiver(); }
FlowDirectionTypes CvDllPlot::GetRiverEFlowDirection() const { return m_pPlot->getRiverEFlowDirection(); }
FlowDirectionTypes CvDllPlot::GetRiverSEFlowDirection() const { return m_pPlot->getRiverSEFlowDirection(); }
FlowDirectionTypes CvDllPlot::GetRiverSWFlowDirection() const { return m_pPlot->getRiverSWFlowDirection(); }
PlayerTypes CvDllPlot::GetOwner() const { return m_pPlot->getOwner(); }
PlotTypes CvDllPlot::GetPlotType() const { return m_pPlot->getPlotType(); }
bool CvDllPlot::IsWater() const { return m_pPlot->isWater(); }
bool CvDllPlot::IsHills() const { return m_pPlot->isHills(); }
bool CvDllPlot::IsOpenGround() const { return m_pPlot->isOpenGround(); }
bool CvDllPlot::IsMountain() const { return m_pPlot->isMountain(); }
bool CvDllPlot::IsCanyon() const { return m_pPlot->isCanyon(); }
TerrainTypes CvDllPlot::GetTerrainType() const { return m_pPlot->getTerrainType(); }
FeatureTypes CvDllPlot::GetFeatureType() const { return m_pPlot->getFeatureType(); }
// Beyond Earth adds the hero-landmark queries.
HeroLandmarkTypes CvDllPlot::GetHeroLandmarkType() const { return m_pPlot->getHeroLandmark(); }
int CvDllPlot::GetHeroLandmarkPiece() const { return m_pPlot->getHeroLandmarkPiece(); }
int CvDllPlot::GetHeroLandmarkOrientation() const { return m_pPlot->getHeroLandmarkOrientation(); }
ResourceTypes CvDllPlot::GetResourceType(TeamTypes eTeam) const { return m_pPlot->getResourceType(eTeam); }
int CvDllPlot::GetNumResource() const { return m_pPlot->getNumResource(); }
ImprovementTypes CvDllPlot::GetImprovementType() const { return m_pPlot->getImprovementType(); }
bool CvDllPlot::IsImprovementPillaged() const { return m_pPlot->IsImprovementPillaged(); }
// Beyond Earth additionally exposes improvement activation.
bool CvDllPlot::IsImprovementActivated() const { return m_pPlot->IsImprovementActivated(); }
GenericWorldAnchorTypes CvDllPlot::GetWorldAnchor() const { return m_pPlot->GetWorldAnchor(); }
int CvDllPlot::GetWorldAnchorData() const { return m_pPlot->GetWorldAnchorData(); }
RouteTypes CvDllPlot::GetRouteType() const { return m_pPlot->getRouteType(); }
bool CvDllPlot::IsRoutePillaged() const { return m_pPlot->IsRoutePillaged(); }
ICvCity1* CvDllPlot::GetPlotCity() const { CvCity* pCity = m_pPlot->getPlotCity(); return pCity ? new CvDllCity(pCity) : NULL; }
ICvCity1* CvDllPlot::GetWorkingCity() const { CvCity* pCity = m_pPlot->getWorkingCity(); return pCity ? new CvDllCity(pCity) : NULL; }
ICvOutpost1* CvDllPlot::GetPlotOutpost() const { CvOutpost* pOutpost = m_pPlot->getPlotOutpost(); return pOutpost ? new CvDllOutpost(pOutpost) : NULL; }
ICvStrategicSite1* CvDllPlot::GetPlotStrategicSite() const { CvStrategicSite* pSite = m_pPlot->getPlotStrategicSite(); return pSite ? new CvDllStrategicSite(pSite) : NULL; }
bool CvDllPlot::IsRevealed(TeamTypes eTeam, bool bDebug) const { return m_pPlot->isRevealed(eTeam, bDebug); }
// Beyond Earth exposes revealing a plot with the native default source team.
void CvDllPlot::SetRevealed(TeamTypes eTeam) { m_pPlot->setRevealed(eTeam, true, false, NO_TEAM); }
ImprovementTypes CvDllPlot::GetRevealedImprovementType(TeamTypes eTeam, bool bDebug) const { return m_pPlot->getRevealedImprovementType(eTeam, bDebug); }
int CvDllPlot::GetBuildProgress(BuildTypes eBuild) const { return m_pPlot->getBuildProgress(eBuild); }
bool CvDllPlot::GetAnyBuildProgress() const { return m_pPlot->getAnyBuildProgress(); }
void CvDllPlot::UpdateLayout(bool bDebug) { m_pPlot->updateLayout(bDebug); }
ICvUnit1* CvDllPlot::GetCenterUnit() { CvUnit* pUnit = m_pPlot->getCenterUnit().pointer(); return pUnit ? new CvDllUnit(pUnit) : NULL; }
int CvDllPlot::GetNumUnits() const { return m_pPlot->getNumUnits(); }
ICvUnit1* CvDllPlot::GetUnitByIndex(int iIndex) const { CvUnit* pUnit = m_pPlot->getUnitByIndex(iIndex); return pUnit ? new CvDllUnit(pUnit) : NULL; }
void CvDllPlot::AddUnit(ICvUnit1* pUnit, bool bUpdate)
{
	CvUnit* pNativeUnit = pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL;
	m_pPlot->addUnit(pNativeUnit, bUpdate);
}
void CvDllPlot::RemoveUnit(ICvUnit1* pUnit, bool bUpdate)
{
	CvUnit* pNativeUnit = pUnit ? static_cast<CvDllUnit*>(pUnit)->GetInstance() : NULL;
	m_pPlot->removeUnit(pNativeUnit, bUpdate);
}
const IDInfo* CvDllPlot::NextUnitNode(const IDInfo* pNode) const { return m_pPlot->nextUnitNode(pNode); }
IDInfo* CvDllPlot::NextUnitNode(IDInfo* pNode) { return m_pPlot->nextUnitNode(pNode); }
IDInfo* CvDllPlot::HeadUnitNode() { return m_pPlot->headUnitNode(); }
int CvDllPlot::GetPlotIndex() const { return m_pPlot->GetPlotIndex(); }
char CvDllPlot::GetContinentType() const { return m_pPlot->GetContinentType(); }
// Beyond Earth exposes refreshing the cached impassability flag.
void CvDllPlot::UpdateImpassable() { m_pPlot->updateImpassable(); }
FAutoArchive& CvDllPlot::GetSyncArchive() { return m_pPlot->getSyncArchive(); }
