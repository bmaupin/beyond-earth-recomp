#pragma once

#include "CvDllInterfaces.h"

class CvDiplomacyAI;

class CvDllDiplomacyAI : public ICvDiplomacyAI1
{
public:
	CvDllDiplomacyAI(CvDiplomacyAI* pDiplomacyAI);
	~CvDllDiplomacyAI();
	void* QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();
	static void operator delete(void* p);
	static void* operator new(size_t bytes);
	CvDiplomacyAI* GetInstance();
	void DoBeginDiploWithHuman();
	const char* GetDiploStringForMessage(DiploMessageTypes eMessage, PlayerTypes ePlayer, const char* szOptionalKey = NULL);
	void TestUIDiploStatement(PlayerTypes ePlayer, DiploStatementTypes eStatement, int iData);

private:
	void Destroy();
	unsigned int m_uiRefCount;
	CvDiplomacyAI* m_pDiplomacyAI;
};
