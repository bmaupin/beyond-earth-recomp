#include "CvGameCoreDLLPCH.h"
#include "CvDllDiplomacyAI.h"
#include "CvDiplomacyAI.h"
#include "CvDllContext.h"
#include "CvLocalization.h"

// TODO: Phase1 CvDllDiplomacyAI::CvDllDiplomacyAI — UNVERIFIED: Full operand and relocation-target comparison not established.
CvDllDiplomacyAI::CvDllDiplomacyAI(CvDiplomacyAI* diplomacyAI)
	: m_uiRefCount(1), m_pDiplomacyAI(diplomacyAI)
{
}

CvDllDiplomacyAI::~CvDllDiplomacyAI()
{
}

// TODO: Phase1 CvDllDiplomacyAI::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllDiplomacyAI::QueryInterface(GUID interfaceId)
{
	if(interfaceId == ICvUnknown::GetInterfaceId() || interfaceId == ICvDiplomacyAI1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}
	return NULL;
}

unsigned int CvDllDiplomacyAI::IncrementReference()
{
	return ++m_uiRefCount;
}

// TODO: Phase1 CvDllDiplomacyAI::DecrementReference — UNVERIFIED: Full operand and relocation-target comparison not established.
unsigned int CvDllDiplomacyAI::DecrementReference()
{
	if(m_uiRefCount == 1)
	{
		delete this;
		return 0;
	}
	return --m_uiRefCount;
}

unsigned int CvDllDiplomacyAI::GetReferenceCount()
{
	return m_uiRefCount;
}

// TODO: Phase1 CvDllDiplomacyAI::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllDiplomacyAI::Destroy()
{
	DecrementReference();
}

// TODO: Phase1 CvDllDiplomacyAI::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllDiplomacyAI::operator delete(void* pointer)
{
	CvDllGameContext::Free(pointer);
}

// TODO: Phase1 CvDllDiplomacyAI::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllDiplomacyAI::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}

CvDiplomacyAI* CvDllDiplomacyAI::GetInstance()
{
	return m_pDiplomacyAI;
}

// TODO: Phase1 CvDllDiplomacyAI::DoBeginDiploWithHuman — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllDiplomacyAI::DoBeginDiploWithHuman()
{
	m_pDiplomacyAI->DoBeginDiploWithHuman();
}

// TODO: Phase1 CvDllDiplomacyAI::GetDiploStringForMessage — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
std::string CvDllDiplomacyAI::GetDiploStringForMessage(DiploMessageTypes message, PlayerTypes player, const char* optionalKey)
{
	return m_pDiplomacyAI->GetDiploStringForMessage(message, player, Localization::String(optionalKey));
}

// TODO: Phase1 CvDllDiplomacyAI::TestUIDiploStatement — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllDiplomacyAI::TestUIDiploStatement(PlayerTypes player, DiploStatementTypes statement, int data)
{
	m_pDiplomacyAI->TestUIDiploStatement(player, statement, data);
}
