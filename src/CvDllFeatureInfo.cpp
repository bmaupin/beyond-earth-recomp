/*	-------------------------------------------------------------------------------------------------------
	© 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#include "CvGameCoreDLLPCH.h"
#include "CvDllFeatureInfo.h"
#include "CvDllContext.h"

CvDllFeatureInfo::CvDllFeatureInfo(CvFeatureInfo* pFeatureInfo)
	: m_pFeatureInfo(pFeatureInfo)
	, m_uiRefCount(1)
{
	FAssertMsg(pFeatureInfo != NULL, "SHOULD NOT HAPPEN");
}
//------------------------------------------------------------------------------
CvDllFeatureInfo::~CvDllFeatureInfo()
{
}
//------------------------------------------------------------------------------
void* CvDllFeatureInfo::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
	        guidInterface == ICvFeatureInfo1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}

	return NULL;
}
//------------------------------------------------------------------------------
unsigned int CvDllFeatureInfo::IncrementReference()
{
	++m_uiRefCount;
	return m_uiRefCount;
}
//------------------------------------------------------------------------------
unsigned int CvDllFeatureInfo::DecrementReference()
{
	if(m_uiRefCount == 1)
	{
		delete this;
		return 0;
	}
	else
	{
		--m_uiRefCount;
		return m_uiRefCount;
	}
}
//------------------------------------------------------------------------------
unsigned int CvDllFeatureInfo::GetReferenceCount()
{
	return m_uiRefCount;
}
//------------------------------------------------------------------------------
void CvDllFeatureInfo::Destroy()
{
	DecrementReference();
}
//------------------------------------------------------------------------------
void CvDllFeatureInfo::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}
//------------------------------------------------------------------------------
void* CvDllFeatureInfo::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}
//------------------------------------------------------------------------------
CvFeatureInfo* CvDllFeatureInfo::GetInstance()
{
	return m_pFeatureInfo;
}
//------------------------------------------------------------------------------
const char* CvDllFeatureInfo::GetType()
{
	return m_pFeatureInfo->GetType();
}
//------------------------------------------------------------------------------
const char* CvDllFeatureInfo::GetDescription()
{
	return m_pFeatureInfo->GetDescription();
}
//------------------------------------------------------------------------------
// Beyond Earth renames the native placement predicates to Requires* methods.
bool CvDllFeatureInfo::IsNoCoast()
{
	return m_pFeatureInfo->RequiresNoCoast();
}
//------------------------------------------------------------------------------
bool CvDllFeatureInfo::IsNoRiver()
{
	return m_pFeatureInfo->RequiresNoRiver();
}
//------------------------------------------------------------------------------
bool CvDllFeatureInfo::IsNoAdjacent()
{
	return m_pFeatureInfo->RequiresNoAdjacentSameFeature();
}
//------------------------------------------------------------------------------
bool CvDllFeatureInfo::IsRequiresFlatlands()
{
	return m_pFeatureInfo->RequiresFlatTerrain();
}
//------------------------------------------------------------------------------
bool CvDllFeatureInfo::IsRequiresRiver()
{
	return m_pFeatureInfo->RequiresRiver();
}
//------------------------------------------------------------------------------
// NOTE: IsNaturalWonder does not exist in the Beyond Earth wrapper.
// bool CvDllFeatureInfo::IsNaturalWonder()
// {
// 	return m_pFeatureInfo->IsNaturalWonder();
// }
//------------------------------------------------------------------------------
const char* CvDllFeatureInfo::GetArtDefineTag()
{
	return m_pFeatureInfo->getArtDefineTag();
}
//------------------------------------------------------------------------------
int CvDllFeatureInfo::GetWorldSoundscapeScriptId()
{
	return m_pFeatureInfo->getWorldSoundscapeScriptId();
}
//------------------------------------------------------------------------------
// Beyond Earth refreshes the cached soundscape script ID.
void CvDllFeatureInfo::RefreshWorldSoundscapeID()
{
	m_pFeatureInfo->RefreshWorldSoundscapeID();
}
//------------------------------------------------------------------------------
const char* CvDllFeatureInfo::GetEffectTypeTag()
{
	return m_pFeatureInfo->getEffectTypeTag();
}
//------------------------------------------------------------------------------
bool CvDllFeatureInfo::IsTerrain(int i)
{
	return m_pFeatureInfo->RequiresTerrainType(i);
}
//------------------------------------------------------------------------------