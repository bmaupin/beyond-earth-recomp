/*	-------------------------------------------------------------------------------------------------------
	� 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.
	All other marks and trademarks are the property of their respective owners.
	All rights reserved.
	------------------------------------------------------------------------------------------------------- */
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string.h>
#include "CvGameCoreDLLUtil_Win32Headers.h"
#include "CvGameCoreDLLUtil/CvDLLUtilDefines.h"
#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvGameCoreEnums.h"
#include "CvAssert.h"
#include "CvString.h"
#include "FDefNew.h"
#include "FMemHooks.h"
#include "FFireTypes.h"
#include "FFastVector.h"
#include "FDataStream.h"
#include "CvGameCoreEnumSerialization.h"
#include <hash_map>
#include "FFreeListArrayBase.h"
#include "CvGameCoreDLLUtil/include/CvStructs.h"
#include "CvGameCoreDLLUtil/include/ICvDLLUtility.h"
#include "CvGameDatabase/include/DatabaseResults.h"
class CvPlot;
class CvUnit;
#include "CvGlobals.h"
#include "CvInfos.h"
#include "CvBeliefClasses.h"
#include "CvDatabaseUtility.h"
#include "CvGameCoreDLLUtil.h"

// Authentic exported dependencies not yet declared in the shared headers.
// TODO: Phase1 audit GetResultFloat(Database::Results *,const char *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern float GetResultFloat(Database::Results*, const char*)
	__asm__("_ZN8Database7Results8GetFloatEPKc");
// TODO: Phase1 audit CopyBeliefList(BeliefList *,const BeliefList &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern BeliefList& CopyBeliefList(BeliefList*, const BeliefList&)
	__asm__("_ZN13FStaticVectorIiLj5ELb0ELj1256ELj0EEaSERKS0_");
// TODO: Phase1 audit operator >>(FDataStream &,EraTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, EraTypes&);
// TODO: Phase1 audit operator <<(FDataStream &,const EraTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const EraTypes&);
// TODO: Phase1 audit operator >>(FDataStream &,ResourceTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, ResourceTypes&);
// TODO: Phase1 audit operator >>(FDataStream &,TechTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator>>(FDataStream&, TechTypes&);
// TODO: Phase1 audit operator <<(FDataStream &,const ResourceTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const ResourceTypes&);
// TODO: Phase1 audit operator <<(FDataStream &,const TechTypes &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
FDataStream& operator<<(FDataStream&, const TechTypes&);
// TODO: Phase1 audit GetGameBeliefs(const CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern CvBeliefXMLEntries* GetGameBeliefs(const CvGlobals*)
	__asm__("_ZNK9CvGlobals14GetGameBeliefsEv");
namespace CvInfosSerializationHelper
{
	// TODO: Phase1 audit CvInfosSerializationHelper::WriteHashed(FDataStream &,BeliefTypes): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	bool WriteHashed(FDataStream&, BeliefTypes);
}
namespace BuildingClassArrayHelpers
{
	// TODO: Phase1 audit BuildingClassArrayHelpers::Read(FDataStream &,int *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	void Read(FDataStream&, int*);
	// TODO: Phase1 audit BuildingClassArrayHelpers::Write(FDataStream &,int *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	void Write(FDataStream&, int*, int);
}
#include "CvInfosSerializationHelper.h"

#include "LintFree.h"

//======================================================================================================
//					CvBeliefEntry
//======================================================================================================
// TODO: Phase1 audit CvBeliefEntry::CvBeliefEntry(): UNVERIFIED; BE/object instructions 31/31; Civ5 changed/new UNVERIFIED.
CvBeliefEntry::CvBeliefEntry() :
	m_iMinPopulation(0),
	m_iMinFollowers(0),
	m_iMaxDistance(0),
	m_iCityGrowthModifier(0),
	m_iFaithFromKills(0),
	m_iFaithFromDyingUnits(0),
	m_iHealthNextToRiver(0),
	m_iHealthPerCanyon(0),
	m_iHealthPerCity(0),
	m_iHealthPerXPeacefulForeignFollowers(0),
	m_iPlotCultureCostModifier(0),
	m_iCityRangeStrikeModifier(0),
	m_iCombatModifierEnemyCities(0),
	m_iCombatModifierFriendlyCities(0),
	m_iFriendlyHealChange(0),
	m_iCityStateFriendshipModifier(0),
	m_iLandBarbarianConversionPercent(0),
	m_iWonderProductionModifier(0),
	m_iPlayerHealth(0),
	m_iPlayerCultureModifier(0),
	m_fHealthPerFollowingCity(0),
	m_iGoldPerFollowingCity(0),
	m_iGoldPerXFollowers(0),
	m_iGoldWhenCityAdopts(0),
	m_iSciencePerOtherReligionFollower(0),
	m_iSpreadDistanceModifier(0),
	m_iSpreadStrengthModifier(0),
	m_iProphetStrengthModifier(0),
	m_iProphetCostModifier(0),
	m_iMissionaryStrengthModifier(0),
	m_iMissionaryCostModifier(0),
	m_iFriendlyCityStateSpreadModifier(0),
	m_iCityStateMinimumInfluence(0),
	m_iCityStateInfluenceModifier(0),
	m_iOtherReligionPressureErosion(0),
	m_iSpyPressure(0),
	m_iInquisitorPressureRetention(0),
	m_iFaithBuildingTourism(0),

	m_iFaithCost(0),
	m_bCreatesCreed(false),
	m_iCreatesDogma(-1),
	m_bRequiresPeace(false),
	m_bConvertsBarbarians(false),

	m_eObsoleteEra(NO_ERA),
	m_eResourceRevealed(NO_RESOURCE),
	m_eSpreadModifierDoublingTech(NO_TECH),

	m_paiCityYieldChange(NULL),
	m_paiHolyCityYieldChange(NULL),
	m_paiYieldChangePerForeignCity(NULL),
	m_paiYieldChangePerXForeignFollowers(NULL),
	m_piResourceQuantityModifiers(NULL),
	m_ppiImprovementYieldChanges(NULL),
	m_ppiBuildingClassYieldChanges(NULL),
	m_paiBuildingClassHealth(NULL),
	m_paiBuildingClassTourism(NULL),
	m_ppaiFeatureYieldChange(NULL),
	m_ppaiResourceYieldChange(NULL),
	m_ppaiTerrainYieldChange(NULL),
	m_piResourceHealth(NULL),
	m_piYieldChangeAnySpecialist(NULL),
	m_piYieldChangeTradeRoute(NULL),
	m_piYieldChangeWorldWonder(NULL),
	m_piMaxYieldModifierPerFollower(NULL),
	m_pbFaithPurchaseUnitEraEnabled(NULL),
	m_pbBuildingClassEnabled(NULL)
{
}

// TODO: Phase1 audit CvBeliefEntry::~CvBeliefEntry(): MISMATCH; BE/object instructions 101/89; Civ5 changed/new UNVERIFIED.
CvBeliefEntry::~CvBeliefEntry()
{
	CvDatabaseUtility::SafeDelete2DArray(m_ppiImprovementYieldChanges);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiBuildingClassYieldChanges);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiFeatureYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiResourceYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiTerrainYieldChange);
	SAFE_DELETE_ARRAY(m_piMaxYieldModifierPerFollower);
	SAFE_DELETE_ARRAY(m_piResourceHealth);
	SAFE_DELETE_ARRAY(m_piResourceQuantityModifiers);
	SAFE_DELETE_ARRAY(m_paiBuildingClassHealth);
	SAFE_DELETE_ARRAY(m_paiBuildingClassTourism);
	SAFE_DELETE_ARRAY(m_paiYieldChangePerForeignCity);
	SAFE_DELETE_ARRAY(m_paiYieldChangePerXForeignFollowers);
	SAFE_DELETE_ARRAY(m_pbFaithPurchaseUnitEraEnabled);
	SAFE_DELETE_ARRAY(m_pbBuildingClassEnabled);
}

int CvBeliefEntry::GetMinPopulation() const
{
	return m_iMinPopulation;
}

int CvBeliefEntry::GetMinFollowers() const
{
	return m_iMinFollowers;
}

int CvBeliefEntry::GetMaxDistance() const
{
	return m_iMaxDistance;
}

int CvBeliefEntry::GetCityGrowthModifier() const
{
	return m_iCityGrowthModifier;
}

int CvBeliefEntry::GetFaithFromKills() const
{
	return m_iFaithFromKills;
}

int CvBeliefEntry::GetFaithFromDyingUnits() const
{
	return m_iFaithFromDyingUnits;
}

int CvBeliefEntry::GetHealthNextToRiver() const
{
	return m_iHealthNextToRiver;
}

int CvBeliefEntry::GetHealthPerCanyon() const
{
	return m_iHealthPerCanyon;
}

int CvBeliefEntry::GetFaithCost() const
{
	return m_iFaithCost;
}

bool CvBeliefEntry::IsCreateCreed() const
{
	return m_bCreatesCreed;
}

// TODO: Phase1 audit CvBeliefEntry::IsCreateDogma() const: UNVERIFIED; BE/object instructions 5/5; Civ5 changed/new UNVERIFIED.
bool CvBeliefEntry::IsCreateDogma() const
{
	return m_iCreatesDogma != -1;
}

int CvBeliefEntry::GetCreateDogma() const
{
	return m_iCreatesDogma;
}

int CvBeliefEntry::GetHealthPerCity() const
{
	return m_iHealthPerCity;
}

int CvBeliefEntry::GetHealthPerXPeacefulForeignFollowers() const
{
	return m_iHealthPerXPeacefulForeignFollowers;
}

int CvBeliefEntry::GetPlotCultureCostModifier() const
{
	return m_iPlotCultureCostModifier;
}

int CvBeliefEntry::GetCityRangeStrikeModifier() const
{
	return m_iCityRangeStrikeModifier;
}

int CvBeliefEntry::GetCombatModifierEnemyCities() const
{
	return m_iCombatModifierEnemyCities;
}

int CvBeliefEntry::GetCombatModifierFriendlyCities() const
{
	return m_iCombatModifierFriendlyCities;
}

int CvBeliefEntry::GetFriendlyHealChange() const
{
	return m_iFriendlyHealChange;
}

int CvBeliefEntry::GetCityStateFriendshipModifier() const
{
	return m_iCityStateFriendshipModifier;
}

int CvBeliefEntry::GetLandBarbarianConversionPercent() const
{
	return m_iLandBarbarianConversionPercent;
}

int CvBeliefEntry::GetWonderProductionModifier() const
{
	return m_iWonderProductionModifier;
}

int CvBeliefEntry::GetPlayerHealth() const
{
	return m_iPlayerHealth;
}

int CvBeliefEntry::GetPlayerCultureModifier() const
{
	return m_iPlayerCultureModifier;
}

float CvBeliefEntry::GetHealthPerFollowingCity() const
{
	return m_fHealthPerFollowingCity;
}

int CvBeliefEntry::GetGoldPerFollowingCity() const
{
	return m_iGoldPerFollowingCity;
}

int CvBeliefEntry::GetGoldPerXFollowers() const
{
	return m_iGoldPerXFollowers;
}

int CvBeliefEntry::GetGoldWhenCityAdopts() const
{
	return m_iGoldWhenCityAdopts;
}

int CvBeliefEntry::GetSciencePerOtherReligionFollower() const
{
	return m_iSciencePerOtherReligionFollower;
}

int CvBeliefEntry::GetSpreadDistanceModifier() const
{
	return m_iSpreadDistanceModifier;
}

int CvBeliefEntry::GetSpreadStrengthModifier() const
{
	return m_iSpreadStrengthModifier;
}

int CvBeliefEntry::GetProphetStrengthModifier() const
{
	return m_iProphetStrengthModifier;
}

int CvBeliefEntry::GetProphetCostModifier() const
{
	return m_iProphetCostModifier;
}

int CvBeliefEntry::GetMissionaryStrengthModifier() const
{
	return m_iMissionaryStrengthModifier;
}

int CvBeliefEntry::GetMissionaryCostModifier() const
{
	return m_iMissionaryCostModifier;
}

int CvBeliefEntry::GetFriendlyCityStateSpreadModifier() const
{
	return m_iFriendlyCityStateSpreadModifier;
}


int CvBeliefEntry::GetCityStateMinimumInfluence() const
{
	return m_iCityStateMinimumInfluence;
}

int CvBeliefEntry::GetCityStateInfluenceModifier() const
{
	return m_iCityStateInfluenceModifier;
}

int CvBeliefEntry::GetOtherReligionPressureErosion() const
{
	return m_iOtherReligionPressureErosion;
}

int CvBeliefEntry::GetSpyPressure() const
{
	return m_iSpyPressure;
}

int CvBeliefEntry::GetInquisitorPressureRetention() const
{
	return m_iInquisitorPressureRetention;
}

int CvBeliefEntry::GetFaithBuildingTourism() const
{
	return m_iFaithBuildingTourism;
}






bool CvBeliefEntry::RequiresPeace() const
{
	return m_bRequiresPeace;
}

bool CvBeliefEntry::ConvertsBarbarians() const
{
	return m_bConvertsBarbarians;
}


EraTypes CvBeliefEntry::GetObsoleteEra() const
{
	return m_eObsoleteEra;
}

ResourceTypes CvBeliefEntry::GetResourceRevealed() const
{
	return m_eResourceRevealed;
}

TechTypes CvBeliefEntry::GetSpreadModifierDoublingTech() const
{
	return m_eSpreadModifierDoublingTech;
}

const char* CvBeliefEntry::getShortDescription() const
{
	return m_strShortDescription;
}

// TODO: Phase1 audit CvBeliefEntry::setShortDescription(char const*): UNVERIFIED; BE/object instructions 14/14; Civ5 changed/new UNVERIFIED.
void CvBeliefEntry::setShortDescription(const char* szVal)
{
	m_strShortDescription = szVal;
}

// TODO: Phase1 audit CvBeliefEntry::GetCityYieldChange(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetCityYieldChange(int i) const
{
	return m_paiCityYieldChange ? m_paiCityYieldChange[i] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetHolyCityYieldChange(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetHolyCityYieldChange(int i) const
{
	return m_paiHolyCityYieldChange ? m_paiHolyCityYieldChange[i] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetYieldChangePerForeignCity(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetYieldChangePerForeignCity(int i) const
{
	return m_paiYieldChangePerForeignCity ? m_paiYieldChangePerForeignCity[i] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetYieldChangePerXForeignFollowers(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetYieldChangePerXForeignFollowers(int i) const
{
	return m_paiYieldChangePerXForeignFollowers ? m_paiYieldChangePerXForeignFollowers[i] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetResourceQuantityModifier(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetResourceQuantityModifier(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceQuantityModifiers ? m_piResourceQuantityModifiers[i] : -1;
}

int CvBeliefEntry::GetImprovementYieldChange(ImprovementTypes eIndex1, YieldTypes eIndex2) const
{
	CvAssertMsg(eIndex1 < GC.getNumImprovementInfos(), "Index out of bounds");
	CvAssertMsg(eIndex1 > -1, "Index out of bounds");
	CvAssertMsg(eIndex2 < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(eIndex2 > -1, "Index out of bounds");
	return m_ppiImprovementYieldChanges ? m_ppiImprovementYieldChanges[eIndex1][eIndex2] : 0;
}

int CvBeliefEntry::GetBuildingClassYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiBuildingClassYieldChanges[i][j];
}

// TODO: Phase1 audit CvBeliefEntry::GetBuildingClassHealth(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetBuildingClassHealth(int i) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_paiBuildingClassHealth ? m_paiBuildingClassHealth[i] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetBuildingClassTourism(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetBuildingClassTourism(int i) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_paiBuildingClassTourism ? m_paiBuildingClassTourism[i] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetFeatureYieldChange(int, int) const: UNVERIFIED; BE/object instructions 10/10; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetFeatureYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiFeatureYieldChange ? m_ppaiFeatureYieldChange[i][j] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetResourceYieldChange(int, int) const: UNVERIFIED; BE/object instructions 10/10; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetResourceYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiResourceYieldChange ? m_ppaiResourceYieldChange[i][j] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetTerrainYieldChange(int, int) const: UNVERIFIED; BE/object instructions 10/10; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetTerrainYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiTerrainYieldChange ? m_ppaiTerrainYieldChange[i][j] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetResourceHealth(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetResourceHealth(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceHealth ? m_piResourceHealth[i] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetYieldChangeAnySpecialist(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetYieldChangeAnySpecialist(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeAnySpecialist ? m_piYieldChangeAnySpecialist[i] : -1;
}

// TODO: Phase1 audit CvBeliefEntry::GetYieldChangeTradeRoute(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetYieldChangeTradeRoute(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeTradeRoute ? m_piYieldChangeTradeRoute[i] : -1;
}


// TODO: Phase1 audit CvBeliefEntry::GetYieldChangeWorldWonder(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetYieldChangeWorldWonder(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeWorldWonder ? m_piYieldChangeWorldWonder[i] : -1;
}


// TODO: Phase1 audit CvBeliefEntry::GetMaxYieldModifierPerFollower(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvBeliefEntry::GetMaxYieldModifierPerFollower(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piMaxYieldModifierPerFollower ? m_piMaxYieldModifierPerFollower[i] : -1;
}

bool CvBeliefEntry::IsFaithUnitPurchaseEra(int i) const
{
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(i < GC.getNumEraInfos(), "Index out of bounds");
	return m_pbFaithPurchaseUnitEraEnabled ? m_pbFaithPurchaseUnitEraEnabled[i] : false;
}

bool CvBeliefEntry::IsBuildingClassEnabled(int i) const
{
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	return m_pbBuildingClassEnabled ? m_pbBuildingClassEnabled[i] : false;
}

// TODO: Phase1 audit CvBeliefEntry::CacheResults(Database::Results&, CvDatabaseUtility&): MISMATCH; BE/object instructions 850/807; Civ5 changed/new UNVERIFIED.
bool CvBeliefEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults, kUtility))
		return false;

	//Basic Properties
	setShortDescription(kResults.GetText("ShortDescription"));

	m_iMinPopulation                  = kResults.GetInt("MinPopulation");
	m_iMinFollowers                   = kResults.GetInt("MinFollowers");
	m_iMaxDistance					  = kResults.GetInt("MaxDistance");
	m_iCityGrowthModifier		      = kResults.GetInt("CityGrowthModifier");
	m_iFaithFromKills				  = kResults.GetInt("FaithFromKills");
	m_iFaithFromDyingUnits			  = kResults.GetInt("FaithFromDyingUnits");
	m_iHealthNextToRiver				  = kResults.GetInt("HealthNextToRiver");
	m_iHealthPerCanyon = kResults.GetInt("HealthPerCanyon");
	m_iHealthPerCity = kResults.GetInt("HealthPerCity");
	m_iHealthPerXPeacefulForeignFollowers  = kResults.GetInt("HealthPerXPeacefulForeignFollowers");
	m_iPlotCultureCostModifier	      = kResults.GetInt("PlotCultureCostModifier");
	m_iCityRangeStrikeModifier	      = kResults.GetInt("CityRangeStrikeModifier");
	m_iCombatModifierEnemyCities      = kResults.GetInt("CombatModifierEnemyCities");
	m_iCombatModifierFriendlyCities   = kResults.GetInt("CombatModifierFriendlyCities");
	m_iFriendlyHealChange	          = kResults.GetInt("FriendlyHealChange");
	m_iCityStateFriendshipModifier    = kResults.GetInt("CityStateFriendshipModifier");
	m_iLandBarbarianConversionPercent = kResults.GetInt("LandBarbarianConversionPercent");
	m_iWonderProductionModifier       = kResults.GetInt("WonderProductionModifier");
	m_iPlayerHealth			      = kResults.GetInt("PlayerHealth");
	m_iPlayerCultureModifier          = kResults.GetInt("PlayerCultureModifier");
	m_fHealthPerFollowingCity = GetResultFloat(&kResults, "HealthPerFollowingCity");
	m_iGoldPerFollowingCity           = kResults.GetInt("GoldPerFollowingCity");
	m_iGoldPerXFollowers              = kResults.GetInt("GoldPerXFollowers");
	m_iGoldWhenCityAdopts             = kResults.GetInt("GoldPerFirstCityConversion");
	m_iSciencePerOtherReligionFollower= kResults.GetInt("SciencePerOtherReligionFollower");
	m_iSpreadDistanceModifier         = kResults.GetInt("SpreadDistanceModifier");
	m_iSpreadStrengthModifier		  = kResults.GetInt("SpreadStrengthModifier");
	m_iProphetStrengthModifier        = kResults.GetInt("ProphetStrengthModifier");
	m_iProphetCostModifier            = kResults.GetInt("ProphetCostModifier");
	m_iMissionaryStrengthModifier     = kResults.GetInt("MissionaryStrengthModifier");
	m_iMissionaryCostModifier         = kResults.GetInt("MissionaryCostModifier");
	m_iFriendlyCityStateSpreadModifier= kResults.GetInt("FriendlyCityStateSpreadModifier");
	m_iCityStateMinimumInfluence      = kResults.GetInt("CityStateMinimumInfluence");
	m_iCityStateInfluenceModifier     = kResults.GetInt("CityStateInfluenceModifier");
	m_iOtherReligionPressureErosion   = kResults.GetInt("OtherReligionPressureErosion");
	m_iSpyPressure					  = kResults.GetInt("SpyPressure");
	m_iInquisitorPressureRetention    = kResults.GetInt("InquisitorPressureRetention");
	m_iFaithBuildingTourism           = kResults.GetInt("FaithBuildingTourism");

	m_iFaithCost = kResults.GetInt("FaithCost");
	m_bCreatesCreed = kResults.GetBool("CreatesCreed");
	m_iCreatesDogma = GC.getInfoTypeForString(kResults.GetText("CreatesDogma"), true);
	m_bRequiresPeace = kResults.GetBool("RequiresPeace");
	m_bConvertsBarbarians			  = kResults.GetBool("ConvertsBarbarians");

	//References
	const char* szTextVal;
	szTextVal						  = kResults.GetText("ObsoleteEra");
	m_eObsoleteEra					  = (EraTypes)GC.getInfoTypeForString(szTextVal, true);
	szTextVal						  = kResults.GetText("ResourceRevealed");
	m_eResourceRevealed				  = (ResourceTypes)GC.getInfoTypeForString(szTextVal, true);
	szTextVal						  = kResults.GetText("SpreadModifierDoublingTech");
	m_eSpreadModifierDoublingTech     = (TechTypes)GC.getInfoTypeForString(szTextVal, true);

	//Arrays
	const char* szBeliefType = GetType();
	kUtility.SetYields(m_paiCityYieldChange, "Belief_CityYieldChanges", "BeliefType", szBeliefType);
	kUtility.SetYields(m_paiHolyCityYieldChange, "Belief_HolyCityYieldChanges", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldChangeAnySpecialist, "Belief_YieldChangeAnySpecialist", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldChangeTradeRoute, "Belief_YieldChangeTradeRoute", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldChangeWorldWonder, "Belief_YieldChangeWorldWonder", "BeliefType", szBeliefType);
	kUtility.PopulateArrayByValue(m_piMaxYieldModifierPerFollower, "Yields", "Belief_MaxYieldModifierPerFollower", "YieldType", "BeliefType", szBeliefType, "Max");
	kUtility.PopulateArrayByValue(m_piResourceHealth, "Resources", "Belief_ResourceHealth", "ResourceType", "BeliefType", szBeliefType, "HealthChange");
	kUtility.PopulateArrayByValue(m_piResourceQuantityModifiers, "Resources", "Belief_ResourceQuantityModifiers", "ResourceType", "BeliefType", szBeliefType, "ResourceQuantityModifier");
	kUtility.PopulateArrayByValue(m_paiBuildingClassHealth, "BuildingClasses", "Belief_BuildingClassHealth", "BuildingClassType", "BeliefType", szBeliefType, "Health");
	kUtility.PopulateArrayByValue(m_paiBuildingClassTourism, "BuildingClasses", "Belief_BuildingClassTourism", "BuildingClassType", "BeliefType", szBeliefType, "Tourism");
	kUtility.PopulateArrayByValue(m_paiYieldChangePerForeignCity, "Yields", "Belief_YieldChangePerForeignCity", "YieldType", "BeliefType", szBeliefType, "Yield");
	kUtility.PopulateArrayByValue(m_paiYieldChangePerXForeignFollowers, "Yields", "Belief_YieldChangePerXForeignFollowers", "YieldType", "BeliefType", szBeliefType, "ForeignFollowers");
	kUtility.PopulateArrayByExistence(m_pbFaithPurchaseUnitEraEnabled, "Eras", "Belief_EraFaithUnitPurchase", "EraType", "BeliefType", szBeliefType);
	kUtility.PopulateArrayByExistence(m_pbBuildingClassEnabled, "BuildingClasses", "Belief_BuildingClassFaithPurchase", "BuildingClassType", "BeliefType", szBeliefType);

	//ImprovementYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiImprovementYieldChanges, "Improvements", "Yields");

		std::string strKey("Belief_ImprovementYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Improvements.ID as ImprovementID, Yields.ID as YieldID, Yield from Belief_ImprovementYieldChanges inner join Improvements on Improvements.Type = ImprovementType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int ImprovementID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiImprovementYieldChanges[ImprovementID][YieldID] = yield;
		}
	}

	//BuildingClassYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiBuildingClassYieldChanges, "BuildingClasses", "Yields");

		std::string strKey("Belief_BuildingClassYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select BuildingClasses.ID as BuildingClassID, Yields.ID as YieldID, YieldChange from Belief_BuildingClassYieldChanges inner join BuildingClasses on BuildingClasses.Type = BuildingClassType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int BuildingClassID = pResults->GetInt(0);
			const int iYieldID = pResults->GetInt(1);
			const int iYieldChange = pResults->GetInt(2);

			m_ppiBuildingClassYieldChanges[BuildingClassID][iYieldID] = iYieldChange;
		}
	}

	//FeatureYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiFeatureYieldChange, "Features", "Yields");

		std::string strKey("Belief_FeatureYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Belief_FeatureYieldChanges inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiFeatureYieldChange[FeatureID][YieldID] = yield;
		}
	}

	//ResourceYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiResourceYieldChange, "Resources", "Yields");

		std::string strKey("Belief_ResourceYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Resources.ID as ResourceID, Yields.ID as YieldID, Yield from Belief_ResourceYieldChanges inner join Resources on Resources.Type = ResourceType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int ResourceID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiResourceYieldChange[ResourceID][YieldID] = yield;
		}
	}

	//TerrainYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiTerrainYieldChange, "Terrains", "Yields");

		std::string strKey("Belief_TerrainYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Terrains.ID as TerrainID, Yields.ID as YieldID, Yield from Belief_TerrainYieldChanges inner join Terrains on Terrains.Type = TerrainType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int TerrainID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiTerrainYieldChange[TerrainID][YieldID] = yield;
		}
	}

	return true;
}

//=====================================
// CvBeliefXMLEntries
//=====================================
CvBeliefXMLEntries::CvBeliefXMLEntries(void)
{

}

// TODO: Phase1 audit CvBeliefXMLEntries::~CvBeliefXMLEntries(): UNVERIFIED; BE/object instructions 12/12; Civ5 changed/new UNVERIFIED.
CvBeliefXMLEntries::~CvBeliefXMLEntries(void)
{
	DeleteArray();
}

std::vector<CvBeliefEntry*>& CvBeliefXMLEntries::GetBeliefEntries()
{
	return m_paBeliefEntries;
}

int CvBeliefXMLEntries::GetNumBeliefs()
{
	return m_paBeliefEntries.size();
}

// TODO: Phase1 audit CvBeliefXMLEntries::DeleteArray(): MISMATCH; BE/object instructions 39/40; Civ5 changed/new UNVERIFIED.
void CvBeliefXMLEntries::DeleteArray()
{
	for(std::vector<CvBeliefEntry*>::iterator it = m_paBeliefEntries.begin(); it != m_paBeliefEntries.end(); ++it)
	{
		if(*it)
		{
			delete *it;
			*it = NULL;
		}
	}

	m_paBeliefEntries.clear();
}

CvBeliefEntry* CvBeliefXMLEntries::GetEntry(int index)
{
	return m_paBeliefEntries[index];
}

//=====================================
// CvReligionBeliefs
//=====================================
// TODO: Phase1 audit CvReligionBeliefs::CvReligionBeliefs(CvReligionBeliefs const&): MISMATCH; BE/object instructions 123/78; Civ5 changed/new UNVERIFIED.
// TODO: Phase1 audit CvReligionBeliefs::CvReligionBeliefs(): MISMATCH; BE/object instructions 26/11; Civ5 changed/new UNVERIFIED.
CvReligionBeliefs::CvReligionBeliefs():
	m_paiBuildingClassEnabled(NULL)
{
	Reset();
}

// TODO: Phase1 audit CvReligionBeliefs::~CvReligionBeliefs(): UNVERIFIED; BE/object instructions 20/20; Civ5 changed/new UNVERIFIED.
CvReligionBeliefs::~CvReligionBeliefs(void)
{
	Uninit();
}

// TODO: Phase1 audit CvReligionBeliefs::CvReligionBeliefs(CvReligionBeliefs const&): MISMATCH; BE/object instructions 123/78; Civ5 changed/new UNVERIFIED.
// TODO: Phase1 audit CvReligionBeliefs::CvReligionBeliefs(): MISMATCH; BE/object instructions 26/11; Civ5 changed/new UNVERIFIED.
CvReligionBeliefs::CvReligionBeliefs(const CvReligionBeliefs& source)
{
	m_iFaithFromDyingUnits = source.m_iFaithFromDyingUnits;
	m_iHealthNextToRiver = source.m_iHealthNextToRiver;
	m_iHealthPerCanyon = source.m_iHealthPerCanyon;
	m_iPlotCultureCostModifier = source.m_iPlotCultureCostModifier;
	m_iCityRangeStrikeModifier = source.m_iCityRangeStrikeModifier;
	m_iCombatModifierEnemyCities = source.m_iCombatModifierEnemyCities;
	m_iCombatModifierFriendlyCities = source.m_iCombatModifierFriendlyCities;
	m_iFriendlyHealChange = source.m_iFriendlyHealChange;
	m_iCityStateFriendshipModifier = source.m_iCityStateFriendshipModifier;
	m_iLandBarbarianConversionPercent = source.m_iLandBarbarianConversionPercent;
	m_iSpreadDistanceModifier = source.m_iSpreadDistanceModifier;
	m_iSpreadStrengthModifier = source.m_iSpreadStrengthModifier;
	m_iProphetStrengthModifier = source.m_iProphetStrengthModifier;
	m_iProphetCostModifier = source.m_iProphetCostModifier;
	m_iMissionaryStrengthModifier = source.m_iMissionaryStrengthModifier;
	m_iMissionaryCostModifier = source.m_iMissionaryCostModifier;
	m_iFriendlyCityStateSpreadModifier = source.m_iFriendlyCityStateSpreadModifier;
	m_iCityStateMinimumInfluence = source.m_iCityStateMinimumInfluence;
	m_iCityStateInfluenceModifier = source.m_iCityStateInfluenceModifier;
	m_iOtherReligionPressureErosion = source.m_iOtherReligionPressureErosion;
	m_iSpyPressure = source.m_iSpyPressure;
	m_iInquisitorPressureRetention = source.m_iInquisitorPressureRetention;
	m_iFaithBuildingTourism = source.m_iFaithBuildingTourism;

	m_eObsoleteEra = source.m_eObsoleteEra;
	m_eResourceRevealed = source.m_eResourceRevealed;
	m_eSpreadModifierDoublingTech = source.m_eSpreadModifierDoublingTech;

	CopyBeliefList(&m_ReligionBeliefs, source.m_ReligionBeliefs);

	m_paiBuildingClassEnabled = FNEW(int[GC.getNumBuildingClassInfos()], c_eCiv5GameplayDLL, 0);
	for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		CvBuildingClassInfo* pkBuildingClassInfo = GC.getBuildingClassInfo((BuildingClassTypes)iI);
		if(!pkBuildingClassInfo)
		{
			continue;
		}

		m_paiBuildingClassEnabled[iI] = source.m_paiBuildingClassEnabled[iI];
	}
}

// TODO: Phase1 audit CvReligionBeliefs::Uninit(): UNVERIFIED; BE/object instructions 17/17; Civ5 changed/new UNVERIFIED.
void CvReligionBeliefs::Uninit()
{
	SAFE_DELETE_ARRAY(m_paiBuildingClassEnabled);
}

// TODO: Phase1 audit CvReligionBeliefs::Reset(): MISMATCH; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
void CvReligionBeliefs::Reset()
{
	m_iFaithFromDyingUnits = 0;
	m_iHealthNextToRiver = 0;
	m_iHealthPerCanyon = 0;
	m_iPlotCultureCostModifier = 0;
	m_iCityRangeStrikeModifier = 0;
	m_iCombatModifierEnemyCities = 0;
	m_iCombatModifierFriendlyCities = 0;
	m_iFriendlyHealChange = 0;
	m_iCityStateFriendshipModifier = 0;
	m_iLandBarbarianConversionPercent = 0;
	m_iSpreadDistanceModifier = 0;
	m_iSpreadStrengthModifier = 0;
	m_iProphetStrengthModifier = 0;
	m_iProphetCostModifier = 0;
	m_iMissionaryStrengthModifier = 0;
	m_iMissionaryCostModifier = 0;
	m_iFriendlyCityStateSpreadModifier = 0;
	m_iCityStateMinimumInfluence = 0;
	m_iCityStateInfluenceModifier = 0;
	m_iOtherReligionPressureErosion = 0;
	m_iSpyPressure = 0;
	m_iInquisitorPressureRetention = 0;
	m_iFaithBuildingTourism = 0;

	m_eObsoleteEra = NO_ERA;
	m_eResourceRevealed = NO_RESOURCE;
	m_eSpreadModifierDoublingTech = NO_TECH;

	m_ReligionBeliefs.clear();

	m_paiBuildingClassEnabled = FNEW(int[GC.getNumBuildingClassInfos()], c_eCiv5GameplayDLL, 0);
	for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		CvBuildingClassInfo* pkBuildingClassInfo = GC.getBuildingClassInfo((BuildingClassTypes)iI);
		if(!pkBuildingClassInfo)
		{
			continue;
		}

		m_paiBuildingClassEnabled[iI] = 0;
	}
}

// TODO: Phase1 audit CvReligionBeliefs::AddBelief(BeliefTypes): MISMATCH; BE/object instructions 106/98; Civ5 changed/new UNVERIFIED.
void CvReligionBeliefs::AddBelief(BeliefTypes eBelief)
{
	CvAssert(eBelief != NO_BELIEF);
	if(eBelief == NO_BELIEF)
		return;

	CvBeliefEntry* belief = GetGameBeliefs(&GC)->GetEntry(eBelief);
	CvAssert(belief != NULL);
	if(belief == NULL)
		return;

	m_iFaithFromDyingUnits += belief->GetFaithFromDyingUnits();
	m_iHealthNextToRiver += belief->GetHealthNextToRiver();
	m_iHealthPerCanyon += belief->GetHealthPerCanyon();
	m_iPlotCultureCostModifier += belief->GetPlotCultureCostModifier();
	m_iCityRangeStrikeModifier += belief->GetCityRangeStrikeModifier();
	m_iCombatModifierEnemyCities += belief->GetCombatModifierEnemyCities();
	m_iCombatModifierFriendlyCities += belief->GetCombatModifierFriendlyCities();
	m_iFriendlyHealChange += belief->GetFriendlyHealChange();
	m_iCityStateFriendshipModifier += belief->GetCityStateFriendshipModifier();
	m_iLandBarbarianConversionPercent += belief->GetLandBarbarianConversionPercent();
	m_iSpreadDistanceModifier += belief->GetSpreadDistanceModifier();
	m_iSpreadStrengthModifier += belief->GetSpreadStrengthModifier();
	m_iProphetStrengthModifier += belief->GetProphetStrengthModifier();
	m_iProphetCostModifier += belief->GetProphetCostModifier();
	m_iMissionaryStrengthModifier += belief->GetMissionaryStrengthModifier();
	m_iMissionaryCostModifier += belief->GetMissionaryCostModifier();
	m_iFriendlyCityStateSpreadModifier += belief->GetFriendlyCityStateSpreadModifier();
	m_iCityStateMinimumInfluence += belief->GetCityStateMinimumInfluence();
	m_iCityStateInfluenceModifier += belief->GetCityStateInfluenceModifier();
	m_iOtherReligionPressureErosion += belief->GetOtherReligionPressureErosion();
	m_iSpyPressure += belief->GetSpyPressure();
	m_iInquisitorPressureRetention += belief->GetInquisitorPressureRetention();
	m_iFaithBuildingTourism += belief->GetFaithBuildingTourism();

	m_eObsoleteEra = belief->GetObsoleteEra();
	m_eResourceRevealed = belief->GetResourceRevealed();

	for (int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		if (belief->IsBuildingClassEnabled(iI))
		{
			m_paiBuildingClassEnabled[iI]++;
		}
	}

	if(belief->GetSpreadModifierDoublingTech() != NO_TECH)
	{
		m_eSpreadModifierDoublingTech = belief->GetSpreadModifierDoublingTech();
	}

	m_ReligionBeliefs.push_back((int)eBelief);
}

// TODO: Phase1 audit CvReligionBeliefs::HasBelief(BeliefTypes) const: UNVERIFIED; BE/object instructions 20/20; Civ5 changed/new UNVERIFIED.
bool CvReligionBeliefs::HasBelief(BeliefTypes eBelief) const
{
	return (find(m_ReligionBeliefs.begin(), m_ReligionBeliefs.end(), (int)eBelief) != m_ReligionBeliefs.end());
}

BeliefTypes CvReligionBeliefs::GetBelief(int iIndex) const
{
	return (BeliefTypes)m_ReligionBeliefs[iIndex];
}

int CvReligionBeliefs::GetNumBeliefs() const
{
	return m_ReligionBeliefs.size();
}

// TODO: Phase1 audit CvReligionBeliefs::GetFaithFromKills(int) const: UNVERIFIED; BE/object instructions 59/59; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetFaithFromKills(int iDistance) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;
	int iRequiredDistance;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			iRequiredDistance = pBeliefs->GetEntry(i)->GetMaxDistance();
			if(iRequiredDistance == 0 || iDistance <= iRequiredDistance)
			{
				rtnValue += pBeliefs->GetEntry(i)->GetFaithFromKills();
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetHealthPerCity(int) const: UNVERIFIED; BE/object instructions 57/57; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetHealthPerCity(int iPopulation) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if(iPopulation >= pBeliefs->GetEntry(i)->GetMinPopulation())
			{
				rtnValue += pBeliefs->GetEntry(i)->GetHealthPerCity();
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetHealthPerXPeacefulForeignFollowers() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetHealthPerXPeacefulForeignFollowers() const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i) && pBeliefs->GetEntry(i)->GetHealthPerXPeacefulForeignFollowers() > 0)
		{
			return pBeliefs->GetEntry(i)->GetHealthPerXPeacefulForeignFollowers();
		}
	}

	return 0;
}

// TODO: Phase1 audit CvReligionBeliefs::GetWonderProductionModifier(EraTypes) const: UNVERIFIED; BE/object instructions 57/57; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs:: GetWonderProductionModifier(EraTypes eWonderEra) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if((int)eWonderEra < (int)pBeliefs->GetEntry(i)->GetObsoleteEra())
			{
				rtnValue += pBeliefs->GetEntry(i)->GetWonderProductionModifier();
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetPlayerHealth(bool) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs:: GetPlayerHealth(bool bAtPeace) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if(bAtPeace || !pBeliefs->GetEntry(i)->RequiresPeace())
			{
				rtnValue += pBeliefs->GetEntry(i)->GetPlayerHealth();
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetPlayerCultureModifier(bool) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs:: GetPlayerCultureModifier(bool bAtPeace) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if(bAtPeace || !pBeliefs->GetEntry(i)->RequiresPeace())
			{
				rtnValue += pBeliefs->GetEntry(i)->GetPlayerCultureModifier();
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetHealthPerFollowingCity() const: UNVERIFIED; BE/object instructions 53/53; Civ5 changed/new UNVERIFIED.
float CvReligionBeliefs:: GetHealthPerFollowingCity() const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	float rtnValue = 0.0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetHealthPerFollowingCity();
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetGoldPerFollowingCity() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs:: GetGoldPerFollowingCity() const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetGoldPerFollowingCity();
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetGoldPerXFollowers() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs:: GetGoldPerXFollowers() const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetGoldPerXFollowers();
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetGoldWhenCityAdopts() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs:: GetGoldWhenCityAdopts() const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetGoldWhenCityAdopts();
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetSciencePerOtherReligionFollower() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs:: GetSciencePerOtherReligionFollower() const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetSciencePerOtherReligionFollower();
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetCityGrowthModifier(bool) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetCityGrowthModifier(bool bAtPeace) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if(bAtPeace || !pBeliefs->GetEntry(i)->RequiresPeace())
			{
				rtnValue += pBeliefs->GetEntry(i)->GetCityGrowthModifier();
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetCityYieldChange(int, YieldTypes) const: UNVERIFIED; BE/object instructions 61/61; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetCityYieldChange(int iPopulation, YieldTypes eYield) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if(iPopulation >= pBeliefs->GetEntry(i)->GetMinPopulation())
			{
				rtnValue += pBeliefs->GetEntry(i)->GetCityYieldChange(eYield);
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetHolyCityYieldChange(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetHolyCityYieldChange (YieldTypes eYield) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
				rtnValue += pBeliefs->GetEntry(i)->GetHolyCityYieldChange(eYield);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangePerForeignCity(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetYieldChangePerForeignCity(YieldTypes eYield) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetYieldChangePerForeignCity(eYield);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangePerXForeignFollowers(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetYieldChangePerXForeignFollowers(YieldTypes eYield) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetYieldChangePerXForeignFollowers(eYield);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetResourceQuantityModifier(ResourceTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetResourceQuantityModifier(ResourceTypes eResource) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetResourceQuantityModifier(eResource);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetImprovementYieldChange(ImprovementTypes, YieldTypes) const: UNVERIFIED; BE/object instructions 60/60; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetImprovementYieldChange(ImprovementTypes eImprovement, YieldTypes eYield) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetImprovementYieldChange(eImprovement, eYield);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetBuildingClassYieldChange(BuildingClassTypes, YieldTypes, int) const: UNVERIFIED; BE/object instructions 64/64; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetBuildingClassYieldChange(BuildingClassTypes eBuildingClass, YieldTypes eYieldType, int iFollowers) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if(iFollowers >= pBeliefs->GetEntry(i)->GetMinFollowers())
			{
				rtnValue += pBeliefs->GetEntry(i)->GetBuildingClassYieldChange(eBuildingClass, eYieldType);
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetBuildingClassHealth(BuildingClassTypes, int) const: UNVERIFIED; BE/object instructions 61/61; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetBuildingClassHealth(BuildingClassTypes eBuildingClass, int iFollowers) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if(iFollowers >= pBeliefs->GetEntry(i)->GetMinFollowers())
			{
				rtnValue += pBeliefs->GetEntry(i)->GetBuildingClassHealth(eBuildingClass);
			}
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetBuildingClassTourism(BuildingClassTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetBuildingClassTourism(BuildingClassTypes eBuildingClass) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetBuildingClassTourism(eBuildingClass);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetFeatureYieldChange(FeatureTypes, YieldTypes) const: UNVERIFIED; BE/object instructions 60/60; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetFeatureYieldChange(FeatureTypes eFeature, YieldTypes eYieldType) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetFeatureYieldChange(eFeature, eYieldType);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetResourceYieldChange(ResourceTypes, YieldTypes) const: UNVERIFIED; BE/object instructions 60/60; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetResourceYieldChange(ResourceTypes eResource, YieldTypes eYieldType) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetResourceYieldChange(eResource, eYieldType);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetTerrainYieldChange(TerrainTypes, YieldTypes) const: UNVERIFIED; BE/object instructions 60/60; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetTerrainYieldChange(TerrainTypes eTerrain, YieldTypes eYieldType) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetTerrainYieldChange(eTerrain, eYieldType);
		}
	}

	return rtnValue;
}

// Get happiness boost from a resource
// TODO: Phase1 audit CvReligionBeliefs::GetResourceHealth(ResourceTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetResourceHealth(ResourceTypes eResource) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetResourceHealth(eResource);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangeAnySpecialist(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetYieldChangeAnySpecialist(YieldTypes eYieldType) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetYieldChangeAnySpecialist(eYieldType);
		}
	}

	return rtnValue;
}

// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangeTradeRoute(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetYieldChangeTradeRoute(YieldTypes eYieldType) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetYieldChangeTradeRoute(eYieldType);
		}
	}

	return rtnValue;
}


// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangeWorldWonder(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetYieldChangeWorldWonder(YieldTypes eYieldType) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetYieldChangeWorldWonder(eYieldType);
		}
	}

	return rtnValue;
}


// TODO: Phase1 audit CvReligionBeliefs::GetMaxYieldModifierPerFollower(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
int CvReligionBeliefs::GetMaxYieldModifierPerFollower(YieldTypes eYieldType) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	int rtnValue = 0;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			rtnValue += pBeliefs->GetEntry(i)->GetMaxYieldModifierPerFollower(eYieldType);
		}
	}

	return rtnValue;
}

bool CvReligionBeliefs::IsBuildingClassEnabled(BuildingClassTypes eType) const
{
	return m_paiBuildingClassEnabled[(int)eType];
}

// TODO: Phase1 audit CvReligionBeliefs::IsFaithBuyingEnabled(EraTypes) const: UNVERIFIED; BE/object instructions 62/62; Civ5 changed/new UNVERIFIED.
bool CvReligionBeliefs::IsFaithBuyingEnabled(EraTypes eEra) const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);
	if(eEra == NO_ERA)
		return false;

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if (pBeliefs->GetEntry(i)->IsFaithUnitPurchaseEra((int)eEra))
			{
				return true;
			}
		}
	}

	return false;
}

// TODO: Phase1 audit CvReligionBeliefs::IsConvertsBarbarians() const: UNVERIFIED; BE/object instructions 56/56; Civ5 changed/new UNVERIFIED.
bool CvReligionBeliefs::IsConvertsBarbarians() const
{
	CvBeliefXMLEntries* pBeliefs = GetGameBeliefs(&GC);

	for(int i = 0; i < pBeliefs->GetNumBeliefs(); i++)
	{
		if(HasBelief((BeliefTypes)i))
		{
			if (pBeliefs->GetEntry(i)->ConvertsBarbarians())
			{
				return true;
			}
		}
	}

	return false;
}


// TODO: Phase1 audit CvReligionBeliefs::Read(FDataStream&): UNVERIFIED; BE/object instructions 153/153; Civ5 changed/new UNVERIFIED.
void CvReligionBeliefs::Read(FDataStream& kStream)
{
	// Version number to maintain backwards compatibility
	int uiVersion;
	kStream >> uiVersion;

	kStream >> m_iFaithFromDyingUnits;
	kStream >> m_iHealthNextToRiver;
	kStream >> m_iHealthPerCanyon;
	kStream >> m_iPlotCultureCostModifier;
	kStream >> m_iCityRangeStrikeModifier;
	kStream >> m_iCombatModifierEnemyCities;
	kStream >> m_iCombatModifierFriendlyCities;
	kStream >> m_iFriendlyHealChange;
	kStream >> m_iCityStateFriendshipModifier;
	kStream >> m_iLandBarbarianConversionPercent;
	kStream >> m_iSpreadStrengthModifier;
	kStream >> m_iSpreadDistanceModifier;
	kStream >> m_iProphetStrengthModifier;
	kStream >> m_iProphetCostModifier;
	kStream >> m_iMissionaryStrengthModifier;
	kStream >> m_iMissionaryCostModifier;
	kStream >> m_iFriendlyCityStateSpreadModifier;
	kStream >> m_iCityStateMinimumInfluence;
	kStream >> m_iCityStateInfluenceModifier;
	kStream >> m_iOtherReligionPressureErosion;
	kStream >> m_iSpyPressure;
	kStream >> m_iInquisitorPressureRetention;
	kStream >> m_iFaithBuildingTourism;

	kStream >> m_eObsoleteEra;
	kStream >> m_eResourceRevealed;
	kStream >> m_eSpreadModifierDoublingTech;

	m_ReligionBeliefs.clear();
	uint uiBeliefCount;
	kStream >> uiBeliefCount;
	while(uiBeliefCount--)
	{
		int iBeliefIndex = CvInfosSerializationHelper::ReadHashed(kStream);
		m_ReligionBeliefs.push_back(iBeliefIndex);
	}

	BuildingClassArrayHelpers::Read(kStream, m_paiBuildingClassEnabled);
}

// TODO: Phase1 audit CvReligionBeliefs::Write(FDataStream&) const: UNVERIFIED; BE/object instructions 149/149; Civ5 changed/new UNVERIFIED.
void CvReligionBeliefs::Write(FDataStream& kStream) const
{
	// Current version number
	int uiVersion = 1;
	kStream << uiVersion;

	kStream << m_iFaithFromDyingUnits;
	kStream << m_iHealthNextToRiver;
	kStream << m_iHealthPerCanyon;
	kStream << m_iPlotCultureCostModifier;
	kStream << m_iCityRangeStrikeModifier;
	kStream << m_iCombatModifierEnemyCities;
	kStream << m_iCombatModifierFriendlyCities;
	kStream << m_iFriendlyHealChange;
	kStream << m_iCityStateFriendshipModifier;
	kStream << m_iLandBarbarianConversionPercent;
	kStream << m_iSpreadStrengthModifier;
	kStream << m_iSpreadDistanceModifier;
	kStream << m_iProphetStrengthModifier;
	kStream << m_iProphetCostModifier;
	kStream << m_iMissionaryStrengthModifier;
	kStream << m_iMissionaryCostModifier;
	kStream << m_iFriendlyCityStateSpreadModifier;
	kStream << m_iCityStateMinimumInfluence;
	kStream << m_iCityStateInfluenceModifier;
	kStream << m_iOtherReligionPressureErosion;
	kStream << m_iSpyPressure;
	kStream << m_iInquisitorPressureRetention;
	kStream << m_iFaithBuildingTourism;

	kStream << m_eObsoleteEra;
	kStream << m_eResourceRevealed;
	kStream << m_eSpreadModifierDoublingTech;

	// m_ReligionBeliefs contains the BeliefTypes, which are indices into the religion info table (GC.getBeliefInfo).  Write out the info hashes
	kStream << m_ReligionBeliefs.size();
	for (uint i = 0; i < m_ReligionBeliefs.size(); ++i)
	{
		CvInfosSerializationHelper::WriteHashed(kStream, (BeliefTypes)m_ReligionBeliefs[i]);
	}

	BuildingClassArrayHelpers::Write(kStream, m_paiBuildingClassEnabled, GC.getNumBuildingClassInfos());

}
