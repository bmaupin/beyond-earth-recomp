#pragma once

#include "CvDllInterfaces.h"

class CvOutpost;

class CvDllOutpost : public ICvOutpost1
{
public:
	CvDllOutpost(CvOutpost* pOutpost);
	virtual ~CvDllOutpost();

	void* QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();
	static void operator delete(void* p);
	static void* operator new(size_t bytes);

	CvOutpost* GetInstance();
	int GetID() const;
	PlayerTypes GetOwner() const;
	const char* GetName() const;
	TeamTypes GetTeam() const;
	int GetX() const;
	int GetY() const;
	void GetPosition(int& iX, int& iY) const;
	ICvPlot1* GetPlot() const;
	IDInfo GetIDInfo() const;
	void InitFromLoad() const;
	int GetCombatStrength(bool bForRangedAttack) const;
	int GetMaxHitPoints() const;
	const char* GetBombardEffectTag() const;

private:
	void Destroy();
	unsigned int m_uiRefCount;
	CvOutpost* m_pOutpost;
};
