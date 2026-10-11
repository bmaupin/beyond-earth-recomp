#include "CvGameCoreDLLPCH.h"
#include "CvDllMinorCivInfo.h"
#include "CvDllContext.h"

// TODO: Phase1 CvDllMinorCivInfo::CvDllMinorCivInfo — UNVERIFIED: Full operand and relocation-target comparison not established.
CvDllMinorCivInfo::CvDllMinorCivInfo(CvMinorCivInfo* pMinorCivInfo)
	: m_pMinorCivInfo(pMinorCivInfo)
	, m_uiRefCount(1)
{
	FAssertMsg(pMinorCivInfo != NULL, "SHOULD NOT HAPPEN");
}

CvDllMinorCivInfo::~CvDllMinorCivInfo()
{
}

// TODO: Phase1 CvDllMinorCivInfo::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
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

// TODO: Phase1 CvDllMinorCivInfo::DecrementReference — UNVERIFIED: Full operand and relocation-target comparison not established.
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

// TODO: Phase1 CvDllMinorCivInfo::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllMinorCivInfo::Destroy()
{
	DecrementReference();
}

// TODO: Phase1 CvDllMinorCivInfo::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllMinorCivInfo::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}

// TODO: Phase1 CvDllMinorCivInfo::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllMinorCivInfo::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}

CvMinorCivInfo* CvDllMinorCivInfo::GetInstance()
{
	return m_pMinorCivInfo;
}

// TODO: Phase1 CvDllMinorCivInfo::GetType — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllMinorCivInfo::GetType()
{
	return m_pMinorCivInfo->GetType();
}

// TODO: Phase1 CvDllMinorCivInfo::GetDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllMinorCivInfo::GetDescription()
{
	return m_pMinorCivInfo->GetDescription();
}

// TODO: Phase1 CvDllMinorCivInfo::GetDefaultPlayerColor — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllMinorCivInfo::GetDefaultPlayerColor() const
{
	return m_pMinorCivInfo->getDefaultPlayerColor();
}

// TODO: Phase1 CvDllMinorCivInfo::GetArtStyleType — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllMinorCivInfo::GetArtStyleType() const
{
	return m_pMinorCivInfo->getArtStyleType();
}

// TODO: Phase1 CvDllMinorCivInfo::GetNumCityNames — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllMinorCivInfo::GetNumCityNames() const
{
	return m_pMinorCivInfo->getNumCityNames();
}

// TODO: Phase1 CvDllMinorCivInfo::GetArtStylePrefix — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllMinorCivInfo::GetArtStylePrefix() const
{
	return m_pMinorCivInfo->getArtStylePrefix();
}

// TODO: Phase1 CvDllMinorCivInfo::GetArtStyleSuffix — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllMinorCivInfo::GetArtStyleSuffix() const
{
	return m_pMinorCivInfo->getArtStyleSuffix();
}

// TODO: Phase1 CvDllMinorCivInfo::GetCityNames — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllMinorCivInfo::GetCityNames(int i) const
{
	return m_pMinorCivInfo->getCityNames(i).c_str();
}
