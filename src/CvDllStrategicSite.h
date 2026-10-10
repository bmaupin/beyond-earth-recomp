#pragma once

#include "CvDllInterfaces.h"

class CvStrategicSite;

class CvDllStrategicSite : public ICvStrategicSite1
{
public:
	CvDllStrategicSite(CvStrategicSite* pStrategicSite);
	~CvDllStrategicSite();

	void* DLLCALL QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();

	static void operator delete(void* p);
	static void* operator new(size_t bytes);

	CvStrategicSite* GetInstance();
	int DLLCALL GetID() const;
	PlayerTypes DLLCALL GetOwner() const;
	const char* DLLCALL GetName() const;
	TeamTypes DLLCALL GetTeam() const;
	int DLLCALL GetX() const;
	int DLLCALL GetY() const;
	void DLLCALL GetPosition(int& iX, int& iY) const;
	ICvPlot1* DLLCALL GetPlot() const;
	IDInfo DLLCALL GetIDInfo() const;
	int DLLCALL GetMaxHitPoints() const;
	const char* DLLCALL GetBombardEffectTag() const;

private:
	void DLLCALL Destroy();

	unsigned int m_uiRefCount;
	CvStrategicSite* m_pStrategicSite;
};