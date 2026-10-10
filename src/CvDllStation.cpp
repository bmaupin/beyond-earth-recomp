#include "CvGameCoreDLLPCH.h"
#include "CvDllStation.h"
#include "CvDllContext.h"

CvDllStation::CvDllStation(CvStation* pStation) : m_uiRefCount(1), m_pStation(pStation) {}
void* CvDllStation::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() || guidInterface == ICvStation1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}
	return NULL;
}
unsigned int CvDllStation::IncrementReference() { return ++m_uiRefCount; }
unsigned int CvDllStation::DecrementReference()
{
	if(m_uiRefCount == 1) { delete this; return 0; }
	return --m_uiRefCount;
}
unsigned int CvDllStation::GetReferenceCount() { return m_uiRefCount; }
void CvDllStation::Destroy() { DecrementReference(); }
void CvDllStation::operator delete(void* p) { CvDllGameContext::Free(p); }
void* CvDllStation::operator new(size_t bytes) { return CvDllGameContext::Allocate(bytes); }
CvStation* CvDllStation::GetInstance() { return m_pStation; }
