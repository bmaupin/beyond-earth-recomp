#pragma once

#include "CvDllInterfaces.h"

class CvDiplomacyAI;

class CvDllDiplomacyAI : public ICvDiplomacyAI1
{
public:
	// TODO: Phase1 CvDllDiplomacyAI::CvDllDiplomacyAI — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvDllDiplomacyAI(CvDiplomacyAI* pDiplomacyAI);
	~CvDllDiplomacyAI();
	// TODO: Phase1 CvDllDiplomacyAI::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
	void* QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	// TODO: Phase1 CvDllDiplomacyAI::DecrementReference — UNVERIFIED: Full operand and relocation-target comparison not established.
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();
	// TODO: Phase1 CvDllDiplomacyAI::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
	static void operator delete(void* p);
	// TODO: Phase1 CvDllDiplomacyAI::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
	static void* operator new(size_t bytes);
	CvDiplomacyAI* GetInstance();
	// TODO: Phase1 CvDllDiplomacyAI::DoBeginDiploWithHuman — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DoBeginDiploWithHuman();
	// TODO: Phase1 CvDllDiplomacyAI::GetDiploStringForMessage — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	std::string GetDiploStringForMessage(DiploMessageTypes eMessage, PlayerTypes ePlayer, const char* szOptionalKey = NULL);
	// TODO: Phase1 CvDllDiplomacyAI::TestUIDiploStatement — UNVERIFIED: Full operand and relocation-target comparison not established.
	void TestUIDiploStatement(PlayerTypes ePlayer, DiploStatementTypes eStatement, int iData);

private:
	// TODO: Phase1 CvDllDiplomacyAI::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
	void Destroy();
	unsigned int m_uiRefCount;
	CvDiplomacyAI* m_pDiplomacyAI;
};
