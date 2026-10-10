#pragma once

#include "CvDllInterfaces.h"

class CvStation;

class CvDllStation : public ICvStation1
{
public:
	CvDllStation(CvStation* pStation);
	void* DLLCALL QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();
	static void operator delete(void* p);
	static void* operator new(size_t bytes);
	CvStation* GetInstance();

private:
	void DLLCALL Destroy();
	unsigned int m_uiRefCount;
	CvStation* m_pStation;
};
