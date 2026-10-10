#include "CvGameCoreDLLPCH.h"
#include "CvDllOutpost.h"
#include "CvDllContext.h"
#include "CvDllPlot.h"
#include "CvOutpost.h"
#include "CvCityStrategicSite.h"

CvDllOutpost::CvDllOutpost(CvOutpost* pOutpost) : m_uiRefCount(1), m_pOutpost(pOutpost) {}
CvDllOutpost::~CvDllOutpost() {}
void* CvDllOutpost::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() || guidInterface == ICvOutpost1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}
	return NULL;
}
unsigned int CvDllOutpost::IncrementReference() { return ++m_uiRefCount; }
unsigned int CvDllOutpost::DecrementReference()
{
	if(m_uiRefCount == 1) { delete this; return 0; }
	return --m_uiRefCount;
}
unsigned int CvDllOutpost::GetReferenceCount() { return m_uiRefCount; }
void CvDllOutpost::Destroy() { DecrementReference(); }
void CvDllOutpost::operator delete(void* p) { CvDllGameContext::Free(p); }
void* CvDllOutpost::operator new(size_t bytes) { return CvDllGameContext::Allocate(bytes); }
CvOutpost* CvDllOutpost::GetInstance() { return m_pOutpost; }
int CvDllOutpost::GetID() const { return m_pOutpost->GetIDInfo().iID; }
PlayerTypes CvDllOutpost::GetOwner() const { return m_pOutpost->GetIDInfo().eOwner; }
const char* CvDllOutpost::GetName() const { return m_pOutpost->GetName(); }
TeamTypes CvDllOutpost::GetTeam() const { return m_pOutpost->GetTeam(); }
int CvDllOutpost::GetX() const { CvPlot* pPlot = m_pOutpost->GetPlot(); return pPlot ? pPlot->getX() : -1; }
int CvDllOutpost::GetY() const { CvPlot* pPlot = m_pOutpost->GetPlot(); return pPlot ? pPlot->getY() : -1; }
void CvDllOutpost::GetPosition(int& iX, int& iY) const { iX = GetX(); iY = GetY(); }
ICvPlot1* CvDllOutpost::GetPlot() const { CvPlot* pPlot = m_pOutpost->GetPlot(); return pPlot ? new CvDllPlot(pPlot) : NULL; }
IDInfo CvDllOutpost::GetIDInfo() const { return m_pOutpost->GetIDInfo(); }
void CvDllOutpost::InitFromLoad() const { const_cast<CvOutpost*>(m_pOutpost)->InitFromLoad(); }
int CvDllOutpost::GetCombatStrength(bool bForRangedAttack) const { return m_pOutpost->GetStrategicSite()->GetCombatStrength(bForRangedAttack); }
int CvDllOutpost::GetMaxHitPoints() const { return m_pOutpost->GetStrategicSite()->GetMaxHitPoints(); }
const char* CvDllOutpost::GetBombardEffectTag() const { return m_pOutpost->GetBombardEffectTag(); }
