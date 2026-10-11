#include <string>
#include <vector>
#include <algorithm>
#include "CvGameCoreDLLUtil_Win32Headers.h"
#include "CvGameCoreDLLUtil/CvDLLUtilDefines.h"
#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvGameCoreEnums.h"
#include "CvGameCoreDLLUtil/CvAssert.h"
#include "CvGameCoreDLLUtil/include/CvString.h"
#include "Fireworks/FFreeListArrayBase.h"
#include "CvGameCoreDLLUtil/include/CvStructs.h"
#include "CvStructs.h"
#include "Fireworks/FDefNew.h"
#include "Fireworks/FMemHooks.h"
#include "Fireworks/FFireTypes.h"
#include "Fireworks/FAssert.h"
#include "Fireworks/FDataStream.h"
#include <hash_map>
#include "CvGameCoreDLLUtil/include/ICvDLLUtility.h"
#include "CvGameDatabase/include/Database.h"
#include "CvGameDatabase/include/DatabaseResults.h"
#include "CvGlobals.h"
#include "CvInfos.h"
#include "CvImprovementClasses.h"

#include "CvDatabaseUtility.h"
#include "CvInfosSerializationHelper.h"
#include "Fireworks/FString.h"


// TODO: Phase1 audit operator delete(void *,size_t): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
void operator delete(void*, size_t) noexcept;
// TODO: Phase1 audit operator delete[](void *,size_t): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
void operator delete[](void*, size_t) noexcept;
// TODO: Phase1 audit ImprovementBind(Database::Results *,int,const char *,int,bool): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern bool ImprovementBind(Database::Results*, int, const char*, int, bool) asm("_ZN8Database7Results4BindEiPKcib");
// TODO: Phase1 audit ImprovementCount(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int ImprovementCount(CvGlobals*) asm("_ZN9CvGlobals22getNumImprovementInfosEv");
// TODO: Phase1 audit ImprovementInfo(CvGlobals *,ImprovementTypes): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern CvImprovementEntry* ImprovementInfo(CvGlobals*, ImprovementTypes) asm("_ZN9CvGlobals18getImprovementInfoE16ImprovementTypes");
// TODO: Phase1 audit ImprovementTypeForHash(const CvGlobals *,unsigned int,bool): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int ImprovementTypeForHash(const CvGlobals*, unsigned int, bool) asm("_ZNK9CvGlobals18getInfoTypeForHashEjb");
// TODO: Phase1 audit ImprovementStringCopy(FStringA *,int,const char *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern void ImprovementStringCopy(FStringA*, int, const char*, int) asm("_ZN8FStringA4CopyEiPKci");
// TODO: Phase1 audit _strupr(char *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern "C" char* _strupr(char*);
static_assert(sizeof(CvBaseInfo) == 0x74, "Beyond Earth base layout");
static_assert(sizeof(CvImprovementResourceInfo) == 12, "Beyond Earth resource layout");
static_assert(sizeof(CvImprovementEntry) == 0x154, "Beyond Earth entry layout");
static_assert(sizeof(CvImprovementXMLEntries) == 12, "Beyond Earth collection layout");
CvImprovementResourceInfo::CvImprovementResourceInfo() :
	m_iDiscoverRand(0),
	m_bResourceMakesValid(false),
	m_bResourceTrade(false),
	m_piYieldChange(NULL)
{
}
//------------------------------------------------------------------------------
// TODO: Phase1 audit CvImprovementResourceInfo::~CvImprovementResourceInfo(): UNVERIFIED; BE/object instructions 17/17; Civ5 changed/new UNVERIFIED.
CvImprovementResourceInfo::~CvImprovementResourceInfo()
{
	delete[] m_piYieldChange; m_piYieldChange = NULL;
}
//------------------------------------------------------------------------------
int CvImprovementResourceInfo::getDiscoverRand() const
{
	return m_iDiscoverRand;
}
//------------------------------------------------------------------------------
bool CvImprovementResourceInfo::isResourceMakesValid() const
{
	return m_bResourceMakesValid;
}
//------------------------------------------------------------------------------
bool CvImprovementResourceInfo::isResourceTrade() const
{
	return m_bResourceTrade;
}
//------------------------------------------------------------------------------
// TODO: Phase1 audit CvImprovementResourceInfo::getYieldChange(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvImprovementResourceInfo::getYieldChange(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChange ? m_piYieldChange[i] : -1;
}
//------------------------------------------------------------------------------

// TODO: Phase1 audit CvImprovementEntry::CvImprovementEntry(): UNVERIFIED; BE/object instructions 56/56; Civ5 changed/new UNVERIFIED.
CvImprovementEntry::CvImprovementEntry() :
	m_iCityHP(0),
	m_iCoastalLandUpgradeMod(0),
	m_iCultureAdjacentSameType(0),
	m_iDefenseModifier(0),
	m_iEnergyMaintenance(0),
	m_iUnhealth(0),
	m_iFreshWaterUpgradeMod(0),
	m_iGoodyRange(0),
	m_iHealth(0),
	m_iHillsUpgradeMod(0),
	m_iImprovementPillage(-1),
	m_iImprovementUpgrade(-1),
	m_iMinRangeToCity(0),
	m_iNearbyEnemyDamage(0),
	m_iNearbyFriendlyHeal(0),
	m_iPillageEnergy(0),
	m_iRequiresXAdjacentLand(-1),
	m_iResourceExtractionMod(0),
	m_iRiverSideUpgradeMod(0),
	m_iTilesPerGoody(0),
	m_iUpgradeTime(0),
	m_iOrbitalCoverageForCity(0),
	m_bAllowsWalkWater(false),
	m_bBuildableOnAnyResource(false),
	m_bCoastal(false),
	m_bDestroyedWhenPillaged(false),
	m_bDisplacePillager(false),
	m_bFreshWaterMakesValid(false),
	m_bGoody(false),
	m_bHillsMakesValid(false),
	m_bIgnoreOwnership(false),
	m_bImpassable(false),
	m_bInAdjacentFriendly(false),
	m_bNoFreshWater(false),
	m_bNoMiasma(false),
	m_bNoTwoAdjacent(false),
	m_bOutsideBorders(false),
	m_bOverrideYield(false),
	m_bPermanent(false),
	m_bPromptWhenComplete(false),
	m_bRemovesAnyResource(false),
	m_bRemovesArtifactResource(false),
	m_bRequiresFeature(false),
	m_bRequiresFlatlands(false),
	m_bRequiresFlatlandsOrFreshWater(false),
	m_bRequiresImprovement(false),
	m_bResourceStaysVisible(false),
	m_bRiverSideMakesValid(false),
	m_bWater(false),
	m_bSelectable(false),
	m_bCannotPillage(false),
	m_eImprovementUsageType(IMPROVEMENTUSAGE_BASIC),
	m_eRequiredCivilization(NO_CIVILIZATION),
	m_iWorldSoundscapeScriptId(0),
	m_uiWorldSoundscapeScriptHash(0),
	m_piResourceQuantityRequirements(NULL),
	m_piPrereqNatureYield(NULL),
	m_piYieldChange(NULL),
	m_piYieldPerEra(NULL),
	m_piRiverSideYieldChange(NULL),
	m_piCoastalLandYieldChange(NULL),
	m_piHillsYieldChange(NULL),
	m_piFreshWaterChange(NULL),
	m_piAdjacentCityYieldChange(NULL),
	m_piAdjacentMountainYieldChange(NULL),
	m_piFlavorValue(NULL),
	m_pbTerrainMakesValid(NULL),
	m_pbFeatureMakesValid(NULL),
	m_pbImprovementMakesValid(NULL),
	m_ppiTechYieldChanges(NULL),
	m_ppiTechNoFreshWaterYieldChanges(NULL),
	m_ppiTechFreshWaterYieldChanges(NULL),
	m_ppiRouteYieldChanges(NULL),
	m_paImprovementResource(NULL)
{}
// TODO: Phase1 audit CvImprovementEntry::~CvImprovementEntry(): MISMATCH; BE/object instructions 161/151; Civ5 changed/new UNVERIFIED.
CvImprovementEntry::~CvImprovementEntry()
{
	delete[] m_piResourceQuantityRequirements; m_piResourceQuantityRequirements = NULL;
	delete[] m_piPrereqNatureYield; m_piPrereqNatureYield = NULL;
	delete[] m_piYieldChange; m_piYieldChange = NULL;
	delete[] m_piYieldPerEra; m_piYieldPerEra = NULL;
	delete[] m_piRiverSideYieldChange; m_piRiverSideYieldChange = NULL;
	delete[] m_piCoastalLandYieldChange; m_piCoastalLandYieldChange = NULL;
	delete[] m_piHillsYieldChange; m_piHillsYieldChange = NULL;
	delete[] m_piFreshWaterChange; m_piFreshWaterChange = NULL;
	delete[] m_piAdjacentCityYieldChange; m_piAdjacentCityYieldChange = NULL;
	delete[] m_piAdjacentMountainYieldChange; m_piAdjacentMountainYieldChange = NULL;
	delete[] m_piFlavorValue; m_piFlavorValue = NULL;
	delete[] m_pbTerrainMakesValid; m_pbTerrainMakesValid = NULL;
	delete[] m_pbFeatureMakesValid; m_pbFeatureMakesValid = NULL;
	delete[] m_pbImprovementMakesValid; m_pbImprovementMakesValid = NULL;
	if(m_paImprovementResource)
	{
		// The target passes the array cookie's allocation size to sized delete[].
		CvImprovementResourceInfo* first = m_paImprovementResource;
		size_t* cookie = reinterpret_cast<size_t*>(first) - 1;
		const size_t count = *cookie;
		CvImprovementResourceInfo* end = first + count;
		while(end != first)
			(--end)->~CvImprovementResourceInfo();
		::operator delete[](cookie, count * sizeof(CvImprovementResourceInfo) + sizeof(size_t));
		m_paImprovementResource = NULL;
	}
	if(m_ppiTechYieldChanges) CvDatabaseUtility::SafeDelete2DArray(m_ppiTechYieldChanges);
	if(m_ppiTechNoFreshWaterYieldChanges) CvDatabaseUtility::SafeDelete2DArray(m_ppiTechNoFreshWaterYieldChanges);
	if(m_ppiTechFreshWaterYieldChanges) CvDatabaseUtility::SafeDelete2DArray(m_ppiTechFreshWaterYieldChanges);
	if(m_ppiRouteYieldChanges) CvDatabaseUtility::SafeDelete2DArray(m_ppiRouteYieldChanges);
}
// TODO: Phase1 audit CvImprovementEntry::CacheResults(Database::Results&, CvDatabaseUtility&): MISMATCH; BE/object instructions 1127/1050; Civ5 changed/new UNVERIFIED.
bool CvImprovementEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults,kUtility)) return false;
	SetArtDefineTag(kResults.GetText("ArtDefineTag"));
	m_iCityHP = kResults.GetInt("CityHP");
	m_iCoastalLandUpgradeMod = kResults.GetInt("CoastalLandUpgradeMod");
	m_iCultureAdjacentSameType = kResults.GetInt("CultureAdjacentSameType");
	m_iDefenseModifier = kResults.GetInt("DefenseModifier");
	m_iEnergyMaintenance = kResults.GetInt("EnergyMaintenance");
	m_iUnhealth = kResults.GetInt("Unhealth");
	m_iFreshWaterUpgradeMod = kResults.GetInt("FreshWaterUpgradeMod");
	m_iGoodyRange = kResults.GetInt("GoodyRange");
	m_iHealth = kResults.GetInt("Health");
	m_iHillsUpgradeMod = kResults.GetInt("HillsUpgradeMod");
	m_iMinRangeToCity = kResults.GetInt("MinRangeToCity");
	m_iNearbyEnemyDamage = kResults.GetInt("NearbyEnemyDamage");
	m_iNearbyFriendlyHeal = kResults.GetInt("NearbyFriendlyHeal");
	m_iPillageEnergy = kResults.GetInt("PillageEnergy");
	m_iRequiresXAdjacentLand = kResults.GetInt("RequiresXAdjacentLand");
	m_iResourceExtractionMod = kResults.GetInt("ResourceExtractionMod");
	m_iRiverSideUpgradeMod = kResults.GetInt("RiverSideUpgradeMod");
	m_iTilesPerGoody = kResults.GetInt("TilesPerGoody");
	m_iUpgradeTime = kResults.GetInt("UpgradeTime");
	m_iOrbitalCoverageForCity = kResults.GetInt("OrbitalCoverageForCity");
	m_bAllowsWalkWater = kResults.GetBool("AllowsWalkWater");
	m_bBuildableOnAnyResource = kResults.GetBool("BuildableOnAnyResource");
	m_bCoastal = kResults.GetBool("Coastal");
	m_bDestroyedWhenPillaged = kResults.GetBool("DestroyedWhenPillaged");
	m_bDisplacePillager = kResults.GetBool("DisplacePillager");
	m_bFreshWaterMakesValid = kResults.GetBool("FreshWaterMakesValid");
	m_bGoody = kResults.GetBool("Goody");
	m_bHillsMakesValid = kResults.GetBool("HillsMakesValid");
	m_bIgnoreOwnership = kResults.GetBool("IgnoreOwnership");
	m_bImpassable = kResults.GetBool("Impassable");
	m_bInAdjacentFriendly = kResults.GetBool("InAdjacentFriendly");
	m_bNoFreshWater = kResults.GetBool("NoFreshWater");
	m_bNoMiasma = kResults.GetBool("NoMiasma");
	m_bNoTwoAdjacent = kResults.GetBool("NoTwoAdjacent");
	m_bOutsideBorders = kResults.GetBool("OutsideBorders");
	m_bOverrideYield = kResults.GetBool("OverrideYield");
	m_bPermanent = kResults.GetBool("Permanent");
	m_bPromptWhenComplete = kResults.GetBool("PromptWhenComplete");
	m_bRemovesAnyResource = kResults.GetBool("RemovesAnyResource");
	m_bRemovesArtifactResource = kResults.GetBool("RemovesArtifactResource");
	m_bRequiresFeature = kResults.GetBool("RequiresFeature");
	m_bRequiresFlatlands = kResults.GetBool("RequiresFlatlands");
	m_bRequiresFlatlandsOrFreshWater = kResults.GetBool("RequiresFlatlandsOrFreshWater");
	m_bRequiresImprovement = kResults.GetBool("RequiresImprovement");
	m_bResourceStaysVisible = kResults.GetBool("ResourceStaysVisible");
	m_bRiverSideMakesValid = kResults.GetBool("RiverSideMakesValid");
	m_bWater = kResults.GetBool("Water");
	m_bSelectable = kResults.GetBool("Selectable");
	m_bCannotPillage = kResults.GetBool("CannotPillage");
	m_eImprovementUsageType = m_bBuildableOnAnyResource ? IMPROVEMENTUSAGE_LANDMARK : IMPROVEMENTUSAGE_BASIC;
	m_eRequiredCivilization = (CivilizationTypes)GC.getInfoTypeForString(kResults.GetText("CivilizationType"), true);
	const char* soundscape = kResults.GetText("WorldSoundscapeAudioScript");
	if(soundscape)
	{
		FString upper;
		FStringA::FStringAFixedBuffer<512> upperBuffer(upper);
		ImprovementStringCopy(&upper, strlen(soundscape), soundscape, 0);
		_strupr(const_cast<char*>(upper.c_str()));
		const FStringAData* data = reinterpret_cast<const FStringAData*>(upper.c_str()) - 1;
		m_uiWorldSoundscapeScriptHash = g_CRC32.Calc(upper.c_str(), data->m_iDataLength);
		m_iWorldSoundscapeScriptId = gDLL->GetAudioTagIndex(soundscape, 5);
	}
	else
	{
		m_uiWorldSoundscapeScriptHash = 0;
		m_iWorldSoundscapeScriptId = -1;
	}
	m_iImprovementPillage = GC.getInfoTypeForString(kResults.GetText("ImprovementPillage"), true);
	m_iImprovementUpgrade = GC.getInfoTypeForString(kResults.GetText("ImprovementUpgrade"), true);
	//Arrays
	const char* szImprovementType = GetType();
	const size_t lenImprovementType = strlen(szImprovementType);

	kUtility.PopulateArrayByExistence(m_pbTerrainMakesValid,
	                                  "Terrains",
	                                  "Improvement_ValidTerrains",
	                                  "TerrainType",
	                                  "ImprovementType",
	                                  szImprovementType);

	kUtility.PopulateArrayByExistence(m_pbFeatureMakesValid,
	                                  "Features",
	                                  "Improvement_ValidFeatures",
	                                  "FeatureType",
	                                  "ImprovementType",
	                                  szImprovementType);

	kUtility.PopulateArrayByExistence(m_pbImprovementMakesValid,
									  "Improvements",
									  "Improvement_ValidImprovements",
									  "PrereqImprovement",
									  "ImprovementType",
							          szImprovementType);

	kUtility.SetYields(m_piYieldChange, "Improvement_Yields", "ImprovementType", szImprovementType);
	kUtility.SetYields(m_piYieldPerEra, "Improvement_YieldPerEra", "ImprovementType", szImprovementType);
	kUtility.SetYields(m_piAdjacentCityYieldChange, "Improvement_AdjacentCityYields", "ImprovementType", szImprovementType);
	kUtility.SetYields(m_piAdjacentMountainYieldChange, "Improvement_AdjacentMountainYieldChanges", "ImprovementType", szImprovementType);
	kUtility.SetYields(m_piCoastalLandYieldChange, "Improvement_CoastalLandYields", "ImprovementType", szImprovementType);
	kUtility.SetYields(m_piFreshWaterChange, "Improvement_FreshWaterYields", "ImprovementType", szImprovementType);
	kUtility.SetYields(m_piHillsYieldChange, "Improvement_HillsYields", "ImprovementType", szImprovementType);
	kUtility.SetYields(m_piRiverSideYieldChange, "Improvement_RiverSideYields", "ImprovementType", szImprovementType);
	kUtility.SetYields(m_piPrereqNatureYield, "Improvement_PrereqNatureYields", "ImprovementType", szImprovementType);

	kUtility.SetFlavors(m_piFlavorValue, "Improvement_Flavors", "ImprovementType", szImprovementType);

	{
		//Initialize Improvement Resource Types to number of Resources
		const int iNumResources = kUtility.MaxRows("Resources");
		#line 321 "../../../Civ5/Src/App/CvGameCoreDLL_Expansion1/CvImprovementClasses.cpp"
		m_paImprovementResource = FNEW(CvImprovementResourceInfo[iNumResources], c_eCiv5GameplayDLL, 0);

		kUtility.InitializeArray(m_piResourceQuantityRequirements, iNumResources);


		std::string strResourceTypesKey = "Improvements - ResourceTypes";
		Database::Results* pResourceTypes = kUtility.GetResults(strResourceTypesKey);
		if(pResourceTypes == NULL)
		{
			pResourceTypes = kUtility.PrepareResults(strResourceTypesKey, "select Resources.ID, ResourceType, ResourceMakesValid, ResourceTrade, DiscoveryRand from Improvement_ResourceTypes inner join Resources on ResourceType = Resources.Type where ImprovementType = ?");
		}

		std::string strYieldResultsKey = "Improvements - YieldResults";
		Database::Results* pYieldResults = kUtility.GetResults(strYieldResultsKey);
		if(pYieldResults == NULL)
		{
			pYieldResults = kUtility.PrepareResults(strYieldResultsKey, "select Yields.ID, Yield from Improvement_ResourceType_Yields inner join Yields on YieldType = Yields.Type where ImprovementType = ? and ResourceType = ?");
		}

		ImprovementBind(pResourceTypes, 1, szImprovementType, lenImprovementType, false);

		while(pResourceTypes->Step())
		{
			const int idx = pResourceTypes->GetInt("ID");
			CvImprovementResourceInfo& pResourceInfo = m_paImprovementResource[idx];

			const char* szResourceType = pResourceTypes->GetText("ResourceType");
			pResourceInfo.m_bResourceMakesValid = pResourceTypes->GetBool("ResourceMakesValid");
			pResourceInfo.m_bResourceTrade = pResourceTypes->GetBool("ResourceTrade");
			pResourceInfo.m_iDiscoverRand = pResourceTypes->GetInt("DiscoveryRand");
			m_piResourceQuantityRequirements[idx] = pResourceTypes->GetInt("QuantityRequirement");

			//Populate Yields for structure
			kUtility.InitializeArray(pResourceInfo.m_piYieldChange, "Yields");

			ImprovementBind(pYieldResults, 1, szImprovementType, lenImprovementType, false);
			ImprovementBind(pYieldResults, 2, szResourceType, -1, false);
			while(pYieldResults->Step())
			{
				const int yieldIdx = pYieldResults->GetInt("ID");
				const int yield = pYieldResults->GetInt("Yield");
				pResourceInfo.m_piYieldChange[yieldIdx] = yield;
			}

			pYieldResults->Reset();
		}

		pResourceTypes->Reset();
	}


	const int iNumYields = kUtility.MaxRows("Yields");
	const int iNumTechs = GC.getNumTechInfos();
	CvAssertMsg(iNumTechs > 0, "Num Tech Infos <= 0");


	//TechYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiTechYieldChanges, iNumTechs, iNumYields);

		std::string strKey = "Improvements - TechYieldChanges";
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Yields.ID as YieldID, Technologies.ID as TechID, Yield from Improvement_TechYieldChanges inner join Yields on YieldType = Yields.Type inner join Technologies on TechType = Technologies.Type where ImprovementType = ?");
		}

		ImprovementBind(pResults, 1, szImprovementType, lenImprovementType, false);

		while(pResults->Step())
		{
			const int yield_idx = pResults->GetInt(0);
			CvAssert(yield_idx > -1);

			const int tech_idx = pResults->GetInt(1);
			CvAssert(tech_idx > -1);

			const int yield = pResults->GetInt(2);

			m_ppiTechYieldChanges[tech_idx][yield_idx] = yield;
		}
	}

	//TechNoFreshWaterYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiTechNoFreshWaterYieldChanges, iNumTechs, iNumYields);

		std::string strKey = "Improvements - TechNoFreshWaterYieldChanges";
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Yields.ID as YieldID, Technologies.ID as TechID, Yield from Improvement_TechNoFreshWaterYieldChanges inner join Yields on YieldType = Yields.Type inner join Technologies on TechType = Technologies.Type where ImprovementType = ?");
		}

		ImprovementBind(pResults, 1, szImprovementType, lenImprovementType, false);

		while(pResults->Step())
		{
			const int yield_idx = pResults->GetInt(0);
			CvAssert(yield_idx > -1);

			const int tech_idx = pResults->GetInt(1);
			CvAssert(tech_idx > -1);

			const int yield = pResults->GetInt(2);

			m_ppiTechNoFreshWaterYieldChanges[tech_idx][yield_idx] = yield;
		}

		pResults->Reset();

	}

	//TechFreshWaterYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiTechFreshWaterYieldChanges, iNumTechs, iNumYields);

		std::string strKey = "Improvements - TechFreshWaterYieldChanges";
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Yields.ID as YieldID, Technologies.ID as TechID, Yield from Improvement_TechFreshWaterYieldChanges inner join Yields on YieldType = Yields.Type inner join Technologies on TechType = Technologies.Type where ImprovementType = ?");
		}

		ImprovementBind(pResults, 1, szImprovementType, lenImprovementType, false);

		while(pResults->Step())
		{
			const int yield_idx = pResults->GetInt(0);
			CvAssert(yield_idx > -1);

			const int tech_idx = pResults->GetInt(1);
			CvAssert(tech_idx > -1);

			const int yield = pResults->GetInt(2);

			m_ppiTechFreshWaterYieldChanges[tech_idx][yield_idx] = yield;
		}

		pResults->Reset();

	}

	//RouteYieldChanges
	{
		const int iNumRoutes = kUtility.MaxRows("Routes");
		kUtility.Initialize2DArray(m_ppiRouteYieldChanges, iNumRoutes, iNumYields);

		std::string strKey = "Improvements - RouteYieldChanges";
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Yields.ID as YieldID, Routes.ID as RouteID, Yield from Improvement_RouteYieldChanges inner join Yields on YieldType = Yields.Type inner join Routes on RouteType = Routes.Type where ImprovementType = ?;");
		}

		ImprovementBind(pResults, 1, szImprovementType, lenImprovementType, false);

		while(pResults->Step())
		{
			const int yield_idx = pResults->GetInt(0);
			CvAssert(yield_idx > -1);

			const int route_idx = pResults->GetInt(1);
			CvAssert(route_idx > -1);

			const int yield = pResults->GetInt(2);

			m_ppiRouteYieldChanges[route_idx][yield_idx] = yield;
		}

		pResults->Reset();

	}

	return true;
}

const char* CvImprovementEntry::GetArtDefineTag() const { return m_strArtDefineTag.c_str(); }
int CvImprovementEntry::GetEnergyMaintenance() const { return m_iEnergyMaintenance; }
int CvImprovementEntry::GetRequiresXAdjacentLand() const { return m_iRequiresXAdjacentLand; }
int CvImprovementEntry::GetMinRangeToCity() const { return m_iMinRangeToCity; }
int CvImprovementEntry::GetCultureAdjacentSameType() const { return m_iCultureAdjacentSameType; }
int CvImprovementEntry::GetTilesPerGoody() const { return m_iTilesPerGoody; }
int CvImprovementEntry::GetGoodyUniqueRange() const { return m_iGoodyRange; }
int CvImprovementEntry::GetUpgradeTime() const { return m_iUpgradeTime; }
int CvImprovementEntry::GetRiverSideUpgradeMod() const { return m_iRiverSideUpgradeMod; }
int CvImprovementEntry::GetCoastalLandUpgradeMod() const { return m_iCoastalLandUpgradeMod; }
int CvImprovementEntry::GetHillsUpgradeMod() const { return m_iHillsUpgradeMod; }
int CvImprovementEntry::GetFreshWaterUpgradeMod() const { return m_iFreshWaterUpgradeMod; }
int CvImprovementEntry::GetDefenseModifier() const { return m_iDefenseModifier; }
int CvImprovementEntry::GetNearbyEnemyDamage() const { return m_iNearbyEnemyDamage; }
int CvImprovementEntry::GetNearbyFriendlyHeal() const { return m_iNearbyFriendlyHeal; }
int CvImprovementEntry::GetHealth() const { return m_iHealth; }
int CvImprovementEntry::GetUnhealth() const { return m_iUnhealth; }
int CvImprovementEntry::GetCityHP() const { return m_iCityHP; }
int CvImprovementEntry::GetPillageEnergy() const { return m_iPillageEnergy; }
int CvImprovementEntry::GetResourceExtractionMod() const { return m_iResourceExtractionMod; }
int CvImprovementEntry::GetOrbitalCoverageForCity() const { return m_iOrbitalCoverageForCity; }
int CvImprovementEntry::GetImprovementPillage() const { return m_iImprovementPillage; }
int CvImprovementEntry::GetImprovementUpgrade() const { return m_iImprovementUpgrade; }
bool CvImprovementEntry::IsHillsMakesValid() const { return m_bHillsMakesValid; }
bool CvImprovementEntry::IsFreshWaterMakesValid() const { return m_bFreshWaterMakesValid; }
bool CvImprovementEntry::IsRiverSideMakesValid() const { return m_bRiverSideMakesValid; }
bool CvImprovementEntry::IsNoFreshWater() const { return m_bNoFreshWater; }
bool CvImprovementEntry::IsNoMiasma() const { return m_bNoMiasma; }
bool CvImprovementEntry::IsRequiresFlatlands() const { return m_bRequiresFlatlands; }
bool CvImprovementEntry::IsRequiresFlatlandsOrFreshWater() const { return m_bRequiresFlatlandsOrFreshWater; }
bool CvImprovementEntry::IsRequiresFeature() const { return m_bRequiresFeature; }
bool CvImprovementEntry::IsRequiresImprovement() const { return m_bRequiresImprovement; }
bool CvImprovementEntry::IsRemovesAnyResource() const { return m_bRemovesAnyResource; }
bool CvImprovementEntry::IsRemovesArtifactResource() const { return m_bRemovesArtifactResource; }
bool CvImprovementEntry::IsPromptWhenComplete() const { return m_bPromptWhenComplete; }
bool CvImprovementEntry::IsWater() const { return m_bWater; }
bool CvImprovementEntry::IsCoastal() const { return m_bCoastal; }
bool CvImprovementEntry::IsSelectable() const { return m_bSelectable; }
bool CvImprovementEntry::IsCannotPillage() const { return m_bCannotPillage; }
bool CvImprovementEntry::IsDestroyedWhenPillaged() const { return m_bDestroyedWhenPillaged; }
bool CvImprovementEntry::IsDisplacePillager() const { return m_bDisplacePillager; }
bool CvImprovementEntry::IsBuildableOnAnyResource() const { return m_bBuildableOnAnyResource; }
bool CvImprovementEntry::IsGoody() const { return m_bGoody; }
bool CvImprovementEntry::IsPermanent() const { return m_bPermanent; }
bool CvImprovementEntry::IsImpassable() const { return m_bImpassable; }
bool CvImprovementEntry::IsOutsideBorders() const { return m_bOutsideBorders; }
bool CvImprovementEntry::IsOverrideYield() const { return m_bOverrideYield; }
bool CvImprovementEntry::IsIgnoreOwnership() const { return m_bIgnoreOwnership; }
bool CvImprovementEntry::IsNoTwoAdjacent() const { return m_bNoTwoAdjacent; }
bool CvImprovementEntry::IsAllowsWalkWater() const { return m_bAllowsWalkWater; }
bool CvImprovementEntry::IsInAdjacentFriendly() const { return m_bInAdjacentFriendly; }
CivilizationTypes CvImprovementEntry::GetRequiredCivilization() const { return m_eRequiredCivilization; }
bool CvImprovementEntry::ResourceStaysVisible() const { return m_bResourceStaysVisible; }
ImprovementUsageTypes CvImprovementEntry::GetImprovementUsage() const { return m_eImprovementUsageType; }
int CvImprovementEntry::GetWorldSoundscapeScriptId() const { return m_iWorldSoundscapeScriptId; }
// TODO: Phase1 audit CvImprovementEntry::GetResourceQuantityRequirement(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvImprovementEntry::GetResourceQuantityRequirement(int i) const { return m_piResourceQuantityRequirements ? m_piResourceQuantityRequirements[i] : -1; }
// TODO: Phase1 audit CvImprovementEntry::GetPrereqNatureYield(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvImprovementEntry::GetPrereqNatureYield(int i) const { return m_piPrereqNatureYield ? m_piPrereqNatureYield[i] : -1; }
int* CvImprovementEntry::GetPrereqNatureYieldArray() { return m_piPrereqNatureYield; }
int CvImprovementEntry::GetYieldChange(int i) const { return m_piYieldChange ? m_piYieldChange[i] : 0; }
int* CvImprovementEntry::GetYieldChangeArray() { return m_piYieldChange; }
int CvImprovementEntry::GetYieldChangePerEra(int i) const { return m_piYieldPerEra ? m_piYieldPerEra[i] : 0; }
int CvImprovementEntry::GetRiverSideYieldChange(int i) const { return m_piRiverSideYieldChange ? m_piRiverSideYieldChange[i] : 0; }
int* CvImprovementEntry::GetRiverSideYieldChangeArray() { return m_piRiverSideYieldChange; }
int CvImprovementEntry::GetCoastalLandYieldChange(int i) const { return m_piCoastalLandYieldChange ? m_piCoastalLandYieldChange[i] : 0; }
int* CvImprovementEntry::GetCoastalLandYieldChangeArray() { return m_piCoastalLandYieldChange; }
int CvImprovementEntry::GetHillsYieldChange(int i) const { return m_piHillsYieldChange ? m_piHillsYieldChange[i] : 0; }
int* CvImprovementEntry::GetHillsYieldChangeArray() { return m_piHillsYieldChange; }
int CvImprovementEntry::GetFreshWaterYieldChange(int i) const { return m_piFreshWaterChange ? m_piFreshWaterChange[i] : 0; }
int* CvImprovementEntry::GetFreshWaterYieldChangeArray() { return m_piFreshWaterChange; }
int CvImprovementEntry::GetAdjacentCityYieldChange(int i) const { return m_piAdjacentCityYieldChange ? m_piAdjacentCityYieldChange[i] : 0; }
int* CvImprovementEntry::GetAdjacentCityYieldChangeArray() { return m_piAdjacentCityYieldChange; }
int CvImprovementEntry::GetAdjacentMountainYieldChange(int i) const { return m_piAdjacentMountainYieldChange ? m_piAdjacentMountainYieldChange[i] : 0; }
int* CvImprovementEntry::GetAdjacentMountainYieldChangeArray() { return m_piAdjacentMountainYieldChange; }
bool CvImprovementEntry::GetTerrainMakesValid(int i) const { return m_pbTerrainMakesValid ? m_pbTerrainMakesValid[i] : false; }
bool CvImprovementEntry::GetFeatureMakesValid(int i) const { return m_pbFeatureMakesValid ? m_pbFeatureMakesValid[i] : false; }
bool CvImprovementEntry::GetImprovementMakesValid(int i) const { return m_pbImprovementMakesValid ? m_pbImprovementMakesValid[i] : false; }
int CvImprovementEntry::GetTechYieldChanges(int i, int j) const { return m_ppiTechYieldChanges[i][j]; }
int* CvImprovementEntry::GetTechYieldChangesArray(int i) { return m_ppiTechYieldChanges[i]; }
int CvImprovementEntry::GetTechNoFreshWaterYieldChanges(int i, int j) const { return m_ppiTechNoFreshWaterYieldChanges[i][j]; }
int* CvImprovementEntry::GetTechNoFreshWaterYieldChangesArray(int i) { return m_ppiTechNoFreshWaterYieldChanges[i]; }
int CvImprovementEntry::GetTechFreshWaterYieldChanges(int i, int j) const { return m_ppiTechFreshWaterYieldChanges[i][j]; }
int* CvImprovementEntry::GetTechFreshWaterYieldChangesArray(int i) { return m_ppiTechFreshWaterYieldChanges[i]; }
int CvImprovementEntry::GetRouteYieldChanges(int i, int j) const { return m_ppiRouteYieldChanges[i][j]; }
int* CvImprovementEntry::GetRouteYieldChangesArray(int i) { return m_ppiRouteYieldChanges[i]; }
int CvImprovementEntry::GetImprovementResourceYield(int i, int j) const { return m_paImprovementResource[i].m_piYieldChange ? m_paImprovementResource[i].m_piYieldChange[j] : 0; }
bool CvImprovementEntry::IsImprovementResourceMakesValid(int i) const { return m_paImprovementResource[i].m_bResourceMakesValid; }
bool CvImprovementEntry::IsImprovementResourceTrade(int i) const { return m_paImprovementResource[i].m_bResourceTrade; }
int CvImprovementEntry::GetImprovementResourceDiscoverRand(int i) const { return m_paImprovementResource[i].m_iDiscoverRand; }
int CvImprovementEntry::GetFlavorValue(int i) const { return m_piFlavorValue[i]; }

// TODO: Phase1 audit CvImprovementEntry::SetArtDefineTag(char const*): UNVERIFIED; BE/object instructions 14/14; Civ5 changed/new UNVERIFIED.
void CvImprovementEntry::SetArtDefineTag(const char* szTag) { m_strArtDefineTag = szTag; }
void CvImprovementEntry::SetImprovementPillage(int i) { m_iImprovementPillage = i; }
void CvImprovementEntry::SetImprovementUpgrade(int i) { m_iImprovementUpgrade = i; }
void CvImprovementEntry::SetImprovementUsage(ImprovementUsageTypes eType) { m_eImprovementUsageType = eType; }
// TODO: Phase1 audit CvImprovementEntry::RefreshWorldSoundscapeID(): UNVERIFIED; BE/object instructions 22/22; Civ5 changed/new UNVERIFIED.
void CvImprovementEntry::RefreshWorldSoundscapeID() {
 if(m_uiWorldSoundscapeScriptHash) m_iWorldSoundscapeScriptId = gDLL->GetAudioTagIndex(m_uiWorldSoundscapeScriptHash, 5);
}
CvImprovementXMLEntries::CvImprovementXMLEntries(void)
{

}

// TODO: Phase1 audit CvImprovementXMLEntries::~CvImprovementXMLEntries(): UNVERIFIED; BE/object instructions 12/12; Civ5 changed/new UNVERIFIED.
CvImprovementXMLEntries::~CvImprovementXMLEntries(void)
{
	DeleteArray();
}

std::vector<CvImprovementEntry*>& CvImprovementXMLEntries::GetImprovementEntries()
{
	return m_paImprovementEntries;
}

int CvImprovementXMLEntries::GetNumImprovements()
{
	return m_paImprovementEntries.size();
}

CvImprovementEntry* CvImprovementXMLEntries::GetEntry(int index)
{
	return m_paImprovementEntries[index];
}

// TODO: Phase1 audit CvImprovementXMLEntries::GetImprovementForResource(int): MISMATCH; BE/object instructions 28/27; Civ5 changed/new UNVERIFIED.
CvImprovementEntry* CvImprovementXMLEntries::GetImprovementForResource(int eResource)
{
	for(unsigned int iImprovement = 0; iImprovement < m_paImprovementEntries.size(); ++iImprovement)
	{
		CvImprovementEntry* pImprovement = GetEntry((ImprovementTypes)iImprovement);
		if(pImprovement && pImprovement->IsImprovementResourceMakesValid(eResource))
		{
			return pImprovement;
		}
	}

	return NULL;
}

// TODO: Phase1 audit CvImprovementXMLEntries::DeleteArray(): UNVERIFIED; BE/object instructions 39/39; Civ5 changed/new UNVERIFIED.
void CvImprovementXMLEntries::DeleteArray()
{
	for(std::vector<CvImprovementEntry*>::iterator it = m_paImprovementEntries.begin(); it != m_paImprovementEntries.end(); ++it)
	{
		CvImprovementEntry* entry = *it;
		if(entry) { entry->~CvImprovementEntry(); ::operator delete(entry, sizeof(CvImprovementEntry)); }
		*it = NULL;
	}

	m_paImprovementEntries.clear();
}

// TODO: Phase1 audit ImprovementArrayHelpers::Read(FDataStream&, int*): MISMATCH; BE/object instructions 83/75; Civ5 changed/new UNVERIFIED.
void ImprovementArrayHelpers::Read(FDataStream& kStream, int* paiImprovementArray)
{
	int iNumEntries;

	kStream >> iNumEntries;

	int iArraySize = ImprovementCount(&GC);
	for(int iI = 0; iI < iNumEntries; iI++)
	{
		uint uiHash;
		kStream >> uiHash;
		if (uiHash != 0 && uiHash != (uint)NO_IMPROVEMENT)
		{
			int iType = ImprovementTypeForHash(&GC, uiHash, false);
			if(iType != -1 && iType < iArraySize)
			{
				kStream >> paiImprovementArray[iType];
			}
			else
			{
				CvString szError;
				szError.Format("LOAD ERROR: Improvement Type not found");
				GC.LogMessage(szError.GetCString());
				CvAssertMsg(false, szError);

				int iDummy;
				kStream >> iDummy;
			}
		}
	}
}

// TODO: Phase1 audit ImprovementArrayHelpers::Write(FDataStream&, int*, int): UNVERIFIED; BE/object instructions 47/47; Civ5 changed/new UNVERIFIED.
void ImprovementArrayHelpers::Write(FDataStream& kStream, int* paiImprovementArray, int iArraySize)
{
	kStream << iArraySize;

	for(int iI = 0; iI < iArraySize; iI++)
	{
		const ImprovementTypes eImprovement = static_cast<ImprovementTypes>(iI);
		CvImprovementEntry* pkImprovementInfo = ImprovementInfo(&GC, eImprovement);
		if(pkImprovementInfo)
		{
			CvInfosSerializationHelper::WriteHashed(kStream, pkImprovementInfo);
			kStream << paiImprovementArray[iI];
		}
		else
		{
			kStream << (int)NO_IMPROVEMENT;
		}
	}
}

// TODO: Phase1 audit ImprovementArrayHelpers::ReadYieldArray(FDataStream&, int**, int): MISMATCH; BE/object instructions 116/106; Civ5 changed/new UNVERIFIED.
void ImprovementArrayHelpers::ReadYieldArray(FDataStream& kStream, int** ppaaiImprovementYieldArray, int iNumYields)
{
	int iNumEntries;

	kStream >> iNumEntries;

	for(int iI = 0; iI < iNumEntries; iI++)
	{
		int iHash;
		kStream >> iHash;
		if(iHash != (int)0)
		{
			int iType = ImprovementTypeForHash(&GC, iHash, false);
			if(iType != -1)
			{
				for(int jJ = 0; jJ < iNumYields; jJ++)
				{
					kStream >> ppaaiImprovementYieldArray[iType][jJ];
				}
			}
			else
			{
				CvString szError;
				szError.Format("LOAD ERROR: Improvement Type not found: %08x", iHash);
				GC.LogMessage(szError.GetCString());
				CvAssertMsg(false, szError);

				for(int jJ = 0; jJ < iNumYields; jJ++)
				{
					int iDummy;
					kStream >> iDummy;
				}
			}
		}
	}
}

// TODO: Phase1 audit ImprovementArrayHelpers::WriteYieldArray(FDataStream&, int**, int): UNVERIFIED; BE/object instructions 59/59; Civ5 changed/new UNVERIFIED.
void ImprovementArrayHelpers::WriteYieldArray(FDataStream& kStream, int** ppaaiImprovementYieldArray, int iArraySize)
{
	kStream << iArraySize;

	for(int iI = 0; iI < iArraySize; iI++)
	{
		const ImprovementTypes eImprovement = static_cast<ImprovementTypes>(iI);
		CvImprovementEntry* pkImprovementInfo = ImprovementInfo(&GC, eImprovement);
		if(pkImprovementInfo)
		{
			CvInfosSerializationHelper::WriteHashed(kStream, pkImprovementInfo);
			for(int jJ = 0; jJ < NUM_YIELD_TYPES; jJ++)
			{
				kStream << ppaaiImprovementYieldArray[iI][jJ];
			}
		}
		else
		{
			kStream << (int)0;
		}
	}
}
