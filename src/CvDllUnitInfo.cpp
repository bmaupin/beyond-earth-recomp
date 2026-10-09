/*	-------------------------------------------------------------------------------------------------------
	© 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#include "CvGameCoreDLLPCH.h"
#include "CvDllUnitInfo.h"
#include "CvDllContext.h"

CvDllUnitInfo::CvDllUnitInfo(CvUnitEntry* pUnitInfo)
	: m_pUnitInfo(pUnitInfo)
	, m_uiRefCount(1)
{
}
//------------------------------------------------------------------------------
CvDllUnitInfo::~CvDllUnitInfo()
{
}
//------------------------------------------------------------------------------
void* CvDllUnitInfo::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
	        guidInterface == ICvUnitInfo1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}

	return NULL;
}
//------------------------------------------------------------------------------
unsigned int CvDllUnitInfo::IncrementReference()
{
	++m_uiRefCount;
	return m_uiRefCount;
}
//------------------------------------------------------------------------------
unsigned int CvDllUnitInfo::DecrementReference()
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
unsigned int CvDllUnitInfo::GetReferenceCount()
{
	return m_uiRefCount;
}
//------------------------------------------------------------------------------
void CvDllUnitInfo::Destroy()
{
	DecrementReference();
}
//------------------------------------------------------------------------------
void CvDllUnitInfo::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}
//------------------------------------------------------------------------------
void* CvDllUnitInfo::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}
//------------------------------------------------------------------------------
int CvDllUnitInfo::GetCombat() const
{
	return m_pUnitInfo->GetCombat();
}
//------------------------------------------------------------------------------
int CvDllUnitInfo::GetDomainType() const
{
	return m_pUnitInfo->GetDomainType();
}
//------------------------------------------------------------------------------
const char* CvDllUnitInfo::GetType() const
{
	return m_pUnitInfo->GetType();
}
//------------------------------------------------------------------------------
const char* CvDllUnitInfo::GetText() const
{
	return m_pUnitInfo->GetText();
}
//------------------------------------------------------------------------------
// Beyond Earth also exposes the untranslated text key.
const char* CvDllUnitInfo::GetTextKey() const
{
	return m_pUnitInfo->GetTextKey();
}
//------------------------------------------------------------------------------
UnitMoveRate CvDllUnitInfo::GetMoveRate(int numHexes) const
{
	return m_pUnitInfo->GetMoveRate(numHexes);
}
//------------------------------------------------------------------------------
const char* CvDllUnitInfo::GetUnitArtInfoTag() const
{
	return m_pUnitInfo->GetUnitArtInfoTag();
}
//------------------------------------------------------------------------------
bool CvDllUnitInfo::GetUnitArtInfoCulturalVariation() const
{
	return m_pUnitInfo->GetUnitArtInfoCulturalVariation();
}
//------------------------------------------------------------------------------
bool CvDllUnitInfo::GetUnitArtInfoEraVariation() const
{
	return m_pUnitInfo->GetUnitArtInfoEraVariation();
}
//------------------------------------------------------------------------------
// Beyond Earth adds art variations and orbital unit types.
bool CvDllUnitInfo::GetUnitArtInfoUpgradeVariation() const
{
	return m_pUnitInfo->GetUnitArtInfoUpgradeVariation();
}
//------------------------------------------------------------------------------
int CvDllUnitInfo::GetUnitArtInfoVariationStart() const
{
	return m_pUnitInfo->GetUnitArtInfoVariationStart();
}
//------------------------------------------------------------------------------
bool CvDllUnitInfo::GetUnitArtInfoAmphibiousVariation() const
{
	return m_pUnitInfo->GetUnitArtInfoAmphibiousVariation();
}
//------------------------------------------------------------------------------
int CvDllUnitInfo::GetOrbitalUnitType() const
{
	return m_pUnitInfo->GetOrbitalUnitType();
}
//------------------------------------------------------------------------------
// NOTE: GetUnitFlagIconOffset does not exist in Beyond Earth game core.
// int CvDllUnitInfo::GetUnitFlagIconOffset() const
// {
// 	return m_pUnitInfo->GetUnitFlagIconOffset();
// }
//------------------------------------------------------------------------------