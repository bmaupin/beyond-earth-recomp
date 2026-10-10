#include "CvGameCoreDLLPCH.h"
#include "CvDllStrategicSite.h"
#include "CvDllContext.h"
#include "CvDllPlot.h"
#include "CvCityStrategicSite.h"

CvDllStrategicSite::CvDllStrategicSite(CvStrategicSite* pStrategicSite)
	: m_pStrategicSite(pStrategicSite)
	, m_uiRefCount(1)
{
}

CvDllStrategicSite::~CvDllStrategicSite()
{
}

void* CvDllStrategicSite::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
		guidInterface == ICvStrategicSite1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}

	return NULL;
}

unsigned int CvDllStrategicSite::IncrementReference()
{
	++m_uiRefCount;
	return m_uiRefCount;
}

unsigned int CvDllStrategicSite::DecrementReference()
{
	if(m_uiRefCount == 1)
	{
		delete this;
		return 0;
	}

	--m_uiRefCount;
	return m_uiRefCount;
}

unsigned int CvDllStrategicSite::GetReferenceCount()
{
	return m_uiRefCount;
}

void CvDllStrategicSite::Destroy()
{
	DecrementReference();
}

void CvDllStrategicSite::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}

void* CvDllStrategicSite::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}

CvStrategicSite* CvDllStrategicSite::GetInstance()
{
	return m_pStrategicSite;
}

int CvDllStrategicSite::GetID() const
{
	return m_pStrategicSite->GetID();
}

PlayerTypes CvDllStrategicSite::GetOwner() const
{
	return m_pStrategicSite->GetOwner();
}

const char* CvDllStrategicSite::GetName() const
{
	return m_pStrategicSite->GetName();
}

TeamTypes CvDllStrategicSite::GetTeam() const
{
	return m_pStrategicSite->GetTeam();
}

int CvDllStrategicSite::GetX() const
{
	return m_pStrategicSite->GetX();
}

int CvDllStrategicSite::GetY() const
{
	return m_pStrategicSite->GetY();
}

void CvDllStrategicSite::GetPosition(int& iX, int& iY) const
{
	iX = m_pStrategicSite->GetX();
	iY = m_pStrategicSite->GetY();
}

ICvPlot1* CvDllStrategicSite::GetPlot() const
{
	CvPlot* pkPlot = m_pStrategicSite->GetPlot();
	return (NULL != pkPlot) ? new CvDllPlot(pkPlot) : NULL;
}

IDInfo CvDllStrategicSite::GetIDInfo() const
{
	return m_pStrategicSite->GetIDInfo();
}

int CvDllStrategicSite::GetMaxHitPoints() const
{
	return m_pStrategicSite->GetMaxHitPoints();
}

const char* CvDllStrategicSite::GetBombardEffectTag() const
{
	return m_pStrategicSite->GetBombardEffectTag();
}
