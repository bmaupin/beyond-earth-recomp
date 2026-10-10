#include "CvGameCoreDLLPCH.h"
#include "CvDllCombatInfo.h"
#include "CvDllContext.h"
#include "CvDllPlot.h"
#include "CvDllStrategicSite.h"
#include "CvDllUnit.h"

CvDllCombatInfo::CvDllCombatInfo(CvCombatInfo* pCombatInfo)
	: m_pCombatInfo(pCombatInfo)
	, m_uiRefCount(1)
{
}

CvDllCombatInfo::~CvDllCombatInfo()
{
}

void* CvDllCombatInfo::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
		guidInterface == ICvCombatInfo1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}

	return NULL;
}

unsigned int CvDllCombatInfo::IncrementReference()
{
	++m_uiRefCount;
	return m_uiRefCount;
}

unsigned int CvDllCombatInfo::DecrementReference()
{
	if(m_uiRefCount == 1)
	{
		delete this;
		return 0;
	}

	--m_uiRefCount;
	return m_uiRefCount;
}

unsigned int CvDllCombatInfo::GetReferenceCount()
{
	return m_uiRefCount;
}

void CvDllCombatInfo::Destroy()
{
	DecrementReference();
}

void CvDllCombatInfo::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}

void* CvDllCombatInfo::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}

ICvUnit1* CvDllCombatInfo::GetUnit(BattleUnitTypes unitType) const
{
	CvUnit* pkUnit = m_pCombatInfo->getUnit(unitType);
	return (NULL != pkUnit) ? new CvDllUnit(pkUnit) : NULL;
}

ICvStrategicSite1* CvDllCombatInfo::GetStrategicSite(BattleUnitTypes unitType) const
{
	CvStrategicSite* pkStrategicSite = m_pCombatInfo->getStrategicSite(unitType);
	return (NULL != pkStrategicSite) ? new CvDllStrategicSite(pkStrategicSite) : NULL;
}

ICvPlot1* CvDllCombatInfo::GetPlot() const
{
	CvPlot* pkPlot = m_pCombatInfo->getPlot();
	return (NULL != pkPlot) ? new CvDllPlot(pkPlot) : NULL;
}

bool CvDllCombatInfo::GetAttackerAdvances() const
{
	return m_pCombatInfo->getAttackerAdvances();
}

bool CvDllCombatInfo::GetVisualizeCombat() const
{
	return m_pCombatInfo->getVisualizeCombat();
}

int CvDllCombatInfo::GetDamageInflicted(BattleUnitTypes unitType) const
{
	return m_pCombatInfo->getDamageInflicted(unitType);
}

int CvDllCombatInfo::GetFinalDamage(BattleUnitTypes unitType) const
{
	return m_pCombatInfo->getFinalDamage(unitType);
}

void* CvDllCombatInfo::TEMPGetRawCombatInfo() const
{
	return m_pCombatInfo;
}

const CvCombatMemberEntry* CvDllCombatInfo::GetDamageMember(int iIndex) const
{
	if(iIndex < m_pCombatInfo->getMaxDamageMemberCount())
		return &m_pCombatInfo->getDamageMembers()[iIndex];
	return NULL;
}

int CvDllCombatInfo::GetDamageMemberCount() const
{
	return m_pCombatInfo->getDamageMemberCount();
}

int CvDllCombatInfo::GetMaxDamageMemberCount() const
{
	return m_pCombatInfo->getMaxDamageMemberCount();
}

bool CvDllCombatInfo::GetDefenderRetaliates() const
{
	return m_pCombatInfo->getDefenderRetaliates();
}

int CvDllCombatInfo::GetNuclearDamageLevel() const
{
	return m_pCombatInfo->getAttackNuclearLevel();
}

bool CvDllCombatInfo::GetAttackIsRanged() const
{
	return m_pCombatInfo->getAttackIsRanged();
}

bool CvDllCombatInfo::GetAttackIsBombingMission() const
{
	return m_pCombatInfo->getAttackIsBombingMission();
}

bool CvDllCombatInfo::GetAttackIsAirSweep() const
{
	return m_pCombatInfo->getAttackIsAirSweep();
}

bool CvDllCombatInfo::GetDefenderCaptured() const
{
	return m_pCombatInfo->getDefenderCaptured();
}

bool CvDllCombatInfo::GetAttackIsAgainstOrbital() const
{
	return m_pCombatInfo->getAttackIsAttackOrbital();
}

unsigned int CvDllCombatInfo::GetVisFXHash() const
{
	return m_pCombatInfo->getVisFXHash();
}
