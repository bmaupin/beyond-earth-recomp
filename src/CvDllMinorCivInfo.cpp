#include "CvGameCoreDLLPCH.h"
#include "CvDllMinorCivInfo.h"
#include "CvDllContext.h"

CvDllMinorCivInfo::CvDllMinorCivInfo(CvMinorCivInfo* pMinorCivInfo)
	: m_pMinorCivInfo(pMinorCivInfo)
	, m_uiRefCount(1)
{
	FAssertMsg(pMinorCivInfo != NULL, "SHOULD NOT HAPPEN");
}

CvDllMinorCivInfo::~CvDllMinorCivInfo()
{
}

void* CvDllMinorCivInfo::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
		guidInterface == ICvMinorCivInfo1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}

	return NULL;
}

unsigned int CvDllMinorCivInfo::IncrementReference()
{
	++m_uiRefCount;
	return m_uiRefCount;
}

unsigned int CvDllMinorCivInfo::DecrementReference()
{
	if(m_uiRefCount == 1)
	{
		delete this;
		return 0;
	}

	--m_uiRefCount;
	return m_uiRefCount;
}

unsigned int CvDllMinorCivInfo::GetReferenceCount()
{
	return m_uiRefCount;
}

void CvDllMinorCivInfo::Destroy()
{
	DecrementReference();
}

void CvDllMinorCivInfo::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}

void* CvDllMinorCivInfo::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}

CvMinorCivInfo* CvDllMinorCivInfo::GetInstance()
{
	return m_pMinorCivInfo;
}

const char* CvDllMinorCivInfo::GetType()
{
	return m_pMinorCivInfo->GetType();
}

const char* CvDllMinorCivInfo::GetDescription()
{
	return m_pMinorCivInfo->GetDescription();
}

int CvDllMinorCivInfo::GetDefaultPlayerColor() const
{
	return m_pMinorCivInfo->getDefaultPlayerColor();
}

int CvDllMinorCivInfo::GetArtStyleType() const
{
	return m_pMinorCivInfo->getArtStyleType();
}

int CvDllMinorCivInfo::GetNumCityNames() const
{
	return m_pMinorCivInfo->getNumCityNames();
}

const char* CvDllMinorCivInfo::GetArtStylePrefix() const
{
	return m_pMinorCivInfo->getArtStylePrefix();
}

const char* CvDllMinorCivInfo::GetArtStyleSuffix() const
{
	return m_pMinorCivInfo->getArtStyleSuffix();
}

const char* CvDllMinorCivInfo::GetCityNames(int i) const
{
	return m_pMinorCivInfo->getCityNames(i).c_str();
}
