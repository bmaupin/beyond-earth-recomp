#include "CvGameCoreDLLPCH.h"
#include "CvDllUnit.h"
#include "CvDllContext.h"
#include "CvDllMissionData.h"
#include "CvDllPlot.h"
#include "CvDllUnitInfo.h"
#include "CvUnit.h"

// The native wrappers retain constructor-failure cleanup and terminating delete handlers.
#ifndef __EXCEPTIONS
#error CvDllUnit.cpp requires exception handling to match the Beyond Earth binary.
#endif

CvDllUnit::CvDllUnit(CvUnit* pUnit)
	: m_uiRefCount(1)
	, m_pUnit(pUnit)
{
}

CvDllUnit::~CvDllUnit()
{
}

void* CvDllUnit::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
		guidInterface == ICvUnit1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}

	return NULL;
}

unsigned int CvDllUnit::IncrementReference()
{
	return ++m_uiRefCount;
}

unsigned int CvDllUnit::DecrementReference()
{
	if(m_uiRefCount == 1)
	{
		delete this;
		return 0;
	}

	return --m_uiRefCount;
}

unsigned int CvDllUnit::GetReferenceCount()
{
	return m_uiRefCount;
}

void CvDllUnit::Destroy()
{
	DecrementReference();
}

void CvDllUnit::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}

void* CvDllUnit::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}

CvUnit* CvDllUnit::GetInstance()
{
	return m_pUnit;
}

int CvDllUnit::GetID() const { return m_pUnit->GetID(); }
PlayerTypes CvDllUnit::GetOwner() const { return m_pUnit->getOwner(); }
int CvDllUnit::GetDamage() const { return m_pUnit->getDamage(); }
int CvDllUnit::GetMoves() const { return m_pUnit->getMoves(); }
bool CvDllUnit::IsSelected() const { return m_pUnit->IsSelected(); }
int CvDllUnit::GetMaxHitPoints() const { return m_pUnit->GetMaxHitPoints(); }
CivilizationTypes CvDllUnit::GetCivilizationType() const { return m_pUnit->getCivilizationType(); }
TeamTypes CvDllUnit::GetTeam() const { return m_pUnit->getTeam(); }
DomainTypes CvDllUnit::GetDomainType() const { return m_pUnit->getDomainType(); }
bool CvDllUnit::IsCombatUnit() const { return m_pUnit->IsCombatUnit(); }
// Beyond Earth replaces barbarian classification with alien classification.
bool CvDllUnit::IsAlien() const { return m_pUnit->isAlien(); }
bool CvDllUnit::IsHoveringUnit() const { return m_pUnit->IsHoveringUnit(); }
bool CvDllUnit::IsAmphibiousUnit() const { return m_pUnit->IsAmphibiousUnit(); }

bool CvDllUnit::IsInvisible(TeamTypes eTeam, bool bDebug) const
{
	return m_pUnit->isInvisible(eTeam, bDebug, true);
}

// Beyond Earth adds amphibious and orbital classification to the unit interface.
bool CvDllUnit::IsOrbitalUnit() const { return m_pUnit->IsOrbitalUnit(); }
bool CvDllUnit::IsInOrbit() const { return m_pUnit->IsInOrbit(); }
bool CvDllUnit::CanMoveImpassable() const { return m_pUnit->canMoveImpassable(); }
DirectionTypes CvDllUnit::GetFacingDirection(bool bCheckLineOfSightProperty) const { return m_pUnit->getFacingDirection(bCheckLineOfSightProperty); }

ICvPlot1* CvDllUnit::GetPlot() const
{
	CvPlot* pPlot = m_pUnit->plot();
	return pPlot != NULL ? new CvDllPlot(pPlot) : NULL;
}

ICvUnitInfo1* CvDllUnit::GetUnitInfo() const
{
	return new CvDllUnitInfo(&m_pUnit->getUnitInfo());
}

bool CvDllUnit::IsEmbarked() const
{
	return m_pUnit->isEmbarked();
}

bool CvDllUnit::IsGarrisoned() const { return m_pUnit->IsGarrisoned(); }

ICvMissionData1* CvDllUnit::GetHeadMissionData() const
{
	const MissionData* pData = const_cast<CvUnit*>(m_pUnit)->GetHeadMissionData();
	return pData != NULL ? new CvDllMissionData(pData) : NULL;
}

UnitCombatTypes CvDllUnit::GetUnitCombatType() { return m_pUnit->getUnitCombatType(); }
int CvDllUnit::GetX() const { return m_pUnit->getX(); }
int CvDllUnit::GetY() const { return m_pUnit->getY(); }

void CvDllUnit::GetPosition(int& iX, int& iY) const
{
	iX = m_pUnit->getX();
	iY = m_pUnit->getY();
}

bool CvDllUnit::CanSwapWithUnitHere(ICvPlot1* pPlot) const
{
	CvPlot* pNativePlot = pPlot != NULL ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL;
	return pNativePlot != NULL && m_pUnit->CanSwapWithUnitHere(*pNativePlot);
}

bool CvDllUnit::CanEmbarkOnto(ICvPlot1* pOriginPlot, ICvPlot1* pTargetPlot, bool bOverrideEmbarkedCheck) const
{
	CvPlot* pOrigin = pOriginPlot != NULL ? static_cast<CvDllPlot*>(pOriginPlot)->GetInstance() : NULL;
	CvPlot* pTarget = pTargetPlot != NULL ? static_cast<CvDllPlot*>(pTargetPlot)->GetInstance() : NULL;
	return pOrigin != NULL && pTarget != NULL && m_pUnit->canEmbarkOnto(*pOrigin, *pTarget, bOverrideEmbarkedCheck, false);
}

bool CvDllUnit::CanDisembarkOnto(ICvPlot1* pOriginPlot, ICvPlot1* pTargetPlot, bool bOverrideEmbarkedCheck) const
{
	CvPlot* pOrigin = pOriginPlot != NULL ? static_cast<CvDllPlot*>(pOriginPlot)->GetInstance() : NULL;
	CvPlot* pTarget = pTargetPlot != NULL ? static_cast<CvDllPlot*>(pTargetPlot)->GetInstance() : NULL;
	return pOrigin != NULL && pTarget != NULL && m_pUnit->canDisembarkOnto(*pOrigin, *pTarget, bOverrideEmbarkedCheck, false);
}

bool CvDllUnit::IsFirstTimeSelected() const { return m_pUnit->IsFirstTimeSelected(); }
UnitTypes CvDllUnit::GetUnitType() const { return m_pUnit->getUnitType(); }
bool CvDllUnit::IsDelayedDeathExported() const { return m_pUnit->isDelayedDeathExported(); }
bool CvDllUnit::IsBusy() const { return m_pUnit->IsBusy(); }

// Beyond Earth supplies the additional graphical setup arguments.
void CvDllUnit::SetupGraphical()
{
	m_pUnit->setupGraphical(false, -1);
}

// Beyond Earth adds an exported graphical-state reset.
void CvDllUnit::ResetGraphical(int iState)
{
	m_pUnit->resetGraphical(iState);
}

CvString CvDllUnit::GetName() const { return m_pUnit->getName(); }

// Beyond Earth also exports the untranslated name key.
CvString CvDllUnit::GetNameTextKey() const
{
	const char* szNameKey = m_pUnit->getNameKey();
	return CvString(szNameKey != NULL ? szNameKey : "");
}

void CvDllUnit::DoCommand(CommandTypes eCommand, int iData1, int iData2)
{
	m_pUnit->doCommand(eCommand, iData1, iData2);
}

bool CvDllUnit::CanDoInterfaceMode(InterfaceModeTypes eInterfaceMode, bool bTestVisibility)
{
	return m_pUnit->CanDoInterfaceMode(eInterfaceMode, bTestVisibility);
}

IDInfo CvDllUnit::GetIDInfo() const { return m_pUnit->GetIDInfo(); }
int CvDllUnit::MovesLeft() const { return m_pUnit->movesLeft(); }

bool CvDllUnit::CanMoveInto(ICvPlot1* pPlot, byte bMoveFlags) const
{
	CvPlot* pNativePlot = pPlot != NULL ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL;
	return pNativePlot != NULL && m_pUnit->canMoveInto(*pNativePlot, bMoveFlags);
}

TeamTypes CvDllUnit::GetDeclareWarMove(ICvPlot1* pPlot) const
{
	CvPlot* pNativePlot = pPlot != NULL ? static_cast<CvDllPlot*>(pPlot)->GetInstance() : NULL;
	return pNativePlot != NULL ? m_pUnit->GetDeclareWarMove(*pNativePlot) : NO_TEAM;
}

bool CvDllUnit::ReadyToSelect() const { return m_pUnit->ReadyToSelect(); }
bool CvDllUnit::CanWork() const { return m_pUnit->IsWork(); }
bool CvDllUnit::CanFound() const { return m_pUnit->isFound(); }
FAutoArchive& CvDllUnit::GetSyncArchive() { return m_pUnit->getSyncArchive(); }
bool CvDllUnit::IsTrade() const { return m_pUnit->isTrade(); }
bool CvDllUnit::IsWorker() const { return m_pUnit->isWorker(); }
