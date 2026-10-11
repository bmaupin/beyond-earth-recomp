#pragma once

#include "CvDllInterfaces.h"

class CvMinorCivInfo;

class CvDllMinorCivInfo : public ICvMinorCivInfo1
{
public:
	// TODO: Phase1 CvDllMinorCivInfo::CvDllMinorCivInfo — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvDllMinorCivInfo(CvMinorCivInfo* pMinorCivInfo);
	~CvDllMinorCivInfo();

	// TODO: Phase1 CvDllMinorCivInfo::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
	void* DLLCALL QueryInterface(GUID guidInterface);

	unsigned int IncrementReference();
	// TODO: Phase1 CvDllMinorCivInfo::DecrementReference — UNVERIFIED: Full operand and relocation-target comparison not established.
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();

	// TODO: Phase1 CvDllMinorCivInfo::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
	static void operator delete(void* p);
	// TODO: Phase1 CvDllMinorCivInfo::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
	static void* operator new(size_t bytes);

	CvMinorCivInfo* GetInstance();

	// TODO: Phase1 CvDllMinorCivInfo::GetType — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* DLLCALL GetType();
	// TODO: Phase1 CvDllMinorCivInfo::GetDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* DLLCALL GetDescription();
	// TODO: Phase1 CvDllMinorCivInfo::GetDefaultPlayerColor — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetDefaultPlayerColor() const;
	// TODO: Phase1 CvDllMinorCivInfo::GetArtStyleType — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetArtStyleType() const;
	// TODO: Phase1 CvDllMinorCivInfo::GetNumCityNames — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL GetNumCityNames() const;
	// TODO: Phase1 CvDllMinorCivInfo::GetArtStylePrefix — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* DLLCALL GetArtStylePrefix() const;
	// TODO: Phase1 CvDllMinorCivInfo::GetArtStyleSuffix — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* DLLCALL GetArtStyleSuffix() const;
	// TODO: Phase1 CvDllMinorCivInfo::GetCityNames — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* DLLCALL GetCityNames(int i) const;

private:
	// TODO: Phase1 CvDllMinorCivInfo::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Destroy();

	unsigned int m_uiRefCount;
	CvMinorCivInfo* m_pMinorCivInfo;
};
