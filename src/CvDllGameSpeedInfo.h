/*	-------------------------------------------------------------------------------------------------------
	© 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#pragma once
#include "CvDllInterfaces.h"

class CvGameSpeedInfo;

class CvDllGameSpeedInfo : public ICvGameSpeedInfo1
{
public:
	CvDllGameSpeedInfo(_In_ CvGameSpeedInfo* pGameSpeedInfo);
	~CvDllGameSpeedInfo();

	void* DLLCALL QueryInterface(GUID guidInterface);

	unsigned int IncrementReference();
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();

	static void operator delete(void* p);
	static void* operator new(size_t bytes);

	CvGameSpeedInfo* GetInstance();

	const char* DLLCALL GetType();
	const char* DLLCALL GetDescription();
	// NOTE: GetBarbPercent does not exist in Beyond Earth game core.
	// int DLLCALL GetBarbPercent();
	int DLLCALL GetMidGameTurn();
	int DLLCALL GetLateGameTurn();

private:
	void DLLCALL Destroy();

	unsigned int m_uiRefCount;
	CvGameSpeedInfo* m_pGameSpeedInfo;
};