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
#include "CvUnitClasses.h"
#include "CvPromotionClasses.h"
#include "CvDatabaseUtility.h"
#include "CvInfosSerializationHelper.h"
#include <cmath>

// TODO: Phase1 audit operator delete(void *,size_t): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
void operator delete(void*, size_t) noexcept;

// Native entry points pending shared database, global and promotion declarations.
// TODO: Phase1 audit UnitClassesBind(Database::Results *,int,const char *,int,bool): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern bool UnitClassesBind(Database::Results*, int, const char*, int, bool) asm("_ZN8Database7Results4BindEiPKcib");
// TODO: Phase1 audit UnitClassesText(Database::Results *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern const char* UnitClassesText(Database::Results*, int) asm("_ZN8Database7Results7GetTextEi");
// TODO: Phase1 audit UnitClassesFloat(Database::Results *,const char *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern float UnitClassesFloat(Database::Results*, const char*) asm("_ZN8Database7Results8GetFloatEPKc");
// TODO: Phase1 audit UnitClassesNumPromotion(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesNumPromotion(CvGlobals*) asm("_ZN9CvGlobals20getNumPromotionInfosEv");
// TODO: Phase1 audit UnitClassesNumTerrain(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesNumTerrain(CvGlobals*) asm("_ZN9CvGlobals18getNumTerrainInfosEv");
// TODO: Phase1 audit UnitClassesNumFeature(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesNumFeature(CvGlobals*) asm("_ZN9CvGlobals18getNumFeatureInfosEv");
// TODO: Phase1 audit UnitClassesNumUnitCombatClass(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesNumUnitCombatClass(CvGlobals*) asm("_ZN9CvGlobals26getNumUnitCombatClassInfosEv");
// TODO: Phase1 audit UnitClassesNumUnitClass(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesNumUnitClass(CvGlobals*) asm("_ZN9CvGlobals20getNumUnitClassInfosEv");
// TODO: Phase1 audit UnitClassesNumUnit(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesNumUnit(CvGlobals*) asm("_ZN9CvGlobals15getNumUnitInfosEv");
// TODO: Phase1 audit UnitClassesPromotion(CvGlobals *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern CvPromotionEntry* UnitClassesPromotion(CvGlobals*, int) asm("_ZN9CvGlobals16getPromotionInfoE14PromotionTypes");
// TODO: Phase1 audit UnitClassesGetCityAttackPercent(const CvPromotionEntry *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetCityAttackPercent(const CvPromotionEntry*) asm("_ZNK16CvPromotionEntry20GetCityAttackPercentEv");
// TODO: Phase1 audit UnitClassesGetAttackMod(const CvPromotionEntry *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetAttackMod(const CvPromotionEntry*) asm("_ZNK16CvPromotionEntry12GetAttackModEv");
// TODO: Phase1 audit UnitClassesGetDefenseMod(const CvPromotionEntry *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetDefenseMod(const CvPromotionEntry*) asm("_ZNK16CvPromotionEntry13GetDefenseModEv");
// TODO: Phase1 audit UnitClassesGetDropRange(const CvPromotionEntry *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetDropRange(const CvPromotionEntry*) asm("_ZNK16CvPromotionEntry12GetDropRangeEv");
// TODO: Phase1 audit UnitClassesGetCargoChange(const CvPromotionEntry *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetCargoChange(const CvPromotionEntry*) asm("_ZNK16CvPromotionEntry14GetCargoChangeEv");
// TODO: Phase1 audit UnitClassesIsBlitz(const CvPromotionEntry *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern bool UnitClassesIsBlitz(const CvPromotionEntry*) asm("_ZNK16CvPromotionEntry7IsBlitzEv");
// TODO: Phase1 audit UnitClassesIsMustSetUpToRangedAttack(const CvPromotionEntry *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern bool UnitClassesIsMustSetUpToRangedAttack(const CvPromotionEntry*) asm("_ZNK16CvPromotionEntry25IsMustSetUpToRangedAttackEv");
// TODO: Phase1 audit UnitClassesIsOnlyDefensive(const CvPromotionEntry *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern bool UnitClassesIsOnlyDefensive(const CvPromotionEntry*) asm("_ZNK16CvPromotionEntry15IsOnlyDefensiveEv");
// TODO: Phase1 audit UnitClassesGetTerrainAttackPercent(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetTerrainAttackPercent(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry23GetTerrainAttackPercentEi");
// TODO: Phase1 audit UnitClassesGetTerrainDefensePercent(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetTerrainDefensePercent(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry24GetTerrainDefensePercentEi");
// TODO: Phase1 audit UnitClassesGetFeatureAttackPercent(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetFeatureAttackPercent(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry23GetFeatureAttackPercentEi");
// TODO: Phase1 audit UnitClassesGetFeatureDefensePercent(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetFeatureDefensePercent(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry24GetFeatureDefensePercentEi");
// TODO: Phase1 audit UnitClassesGetUnitCombatModifierPercent(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetUnitCombatModifierPercent(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry28GetUnitCombatModifierPercentEi");
// TODO: Phase1 audit UnitClassesGetUnitClassModifierPercent(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetUnitClassModifierPercent(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry27GetUnitClassModifierPercentEi");
// TODO: Phase1 audit UnitClassesGetUnitClassAttackModifier(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetUnitClassAttackModifier(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry26GetUnitClassAttackModifierEi");
// TODO: Phase1 audit UnitClassesGetUnitClassDefenseModifier(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetUnitClassDefenseModifier(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry27GetUnitClassDefenseModifierEi");
// TODO: Phase1 audit UnitClassesGetDomainModifierPercent(const CvPromotionEntry *,int): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int UnitClassesGetDomainModifierPercent(const CvPromotionEntry*, int) asm("_ZNK16CvPromotionEntry24GetDomainModifierPercentEi");

// TODO: Phase1 audit CvUnitEntry::CvUnitEntry(): MISMATCH; BE/object instructions 125/93; Civ5 changed/new UNVERIFIED.
CvUnitEntry::CvUnitEntry():
	m_iAdvancedStartCost(0),
	m_iAirInterceptRange(0),
	m_iAirUnitCap(0),
	m_iBaseBeakersTurnsToCount(0),
	m_iBaseCultureTurnsToCount(0),
	m_iBaseHurry(0),
	m_iBaseSightRange(0),
	m_iCivilianAttackPriority(-1),
	m_iCombat(0),
	m_iCombatLimit(0),
	m_iCommandType(-1),
	m_iConscriptionValue(0),
	m_iDefaultUnitAIType(-1),
	m_iDomainCargo(0),
	m_iDomainType(-1),
	m_iExtraMaintenanceCost(0),
	m_iFreePolicies(0),
	m_iGoodyHutUpgradeUnitClass(-1),
	m_iGroupDefinitions(0),
	m_iGroupSize(0),
	m_iHurryCostModifier(0),
	m_iHurryMultiplier(0),
	m_iMinAreaSize(0),
	m_iMoves(0),
	m_iNumExpeditionCharges(0),
	m_iNumFreeTechs(0),
	m_iNumGoldPerEra(0),
	m_iNumUnitNames(0),
	m_iObsoleteTech(-1),
	m_iOrbitalAttackRange(-1),
	m_iOrbitalUnitType(-1),
	m_iPolicyType(-1),
	m_iPrereqAndTech(-1),
	m_iPrereqPillageTech(-1),
	m_iProductionCost(0),
	m_iRange(0),
	m_iRangedCombat(0),
	m_iRangedCombatLimit(0),
	m_iSpecialCargo(0),
	m_iSpecialUnitType(-1),
	m_iUnhealth(0),
	m_iUnitCaptureClassType(-1),
	m_iUnitClassType(-1),
	m_iUnitCombatType(-1),
	m_iMeleeWaveSize(0),
	m_iRangedWaveSize(0),
	m_iWorkRate(0),
	m_iXPValueAttack(0),
	m_iXPValueDefense(0),
	m_iMeleeDefenseMod(0),
	m_iRangedDefenseMod(0),
	m_iAirDefenseMod(0),
	m_iCityStrikeDefenseMod(0),
	m_iOrbitalDefenseMod(0),
	m_iExtraAttacks(0),
	m_bAlienColossus(false),
	m_bAlienLifeform(false),
	m_bNonsentient(false),
	m_bAmphibiousAttack(false),
	m_bCaptureWhileEmbarked(false),
	m_bCoastalWalk(false),
	m_bDeepWaterOnly(false),
	m_bEarthlingSettler(false),
	m_bFoodProduction(false),
	m_bFound(false),
	m_bFoundAbroad(false),
	m_bIgnoreBuildingDefense(false),
	m_bMechUnit(false),
	m_bMilitaryProduction(false),
	m_bMilitarySupport(false),
	m_bCanMoveAfterPurchase(false),
	m_bCanMoveAfterAttacking(false),
	m_bImmobile(false),
	m_bNoBadGoodies(false),
	m_bNoMaintenance(false),
	m_bPillage(false),
	m_bPrereqResources(false),
	m_bPurchaseOnly(false),
	m_bRangeAttackOnlyInDomain(false),
	m_bRivalTerritory(false),
	m_bRushBuilding(false),
	m_bSuicide(false),
	m_bTrade(false),
	m_bRevealInFog(false),
	m_bBlockLineOfSight(false),
	m_bWorker(false),
	m_bHasInvisibility(false),
	m_iCachedPower(0),
	m_iUnitArtInfoCulturalVariation(0),
	m_iUnitArtInfoEraVariation(0),
	m_iUnitArtInfoUpgradeVariation(0),
	m_iUnitArtInfoVariationStart(2),
	m_iUnitArtInfoAmphibiousVariation(0),
	m_iEraOfProsperityTurns(0),
	m_piPrereqAndTechs(NULL),
	m_piAffinityPrereqs(NULL),
	m_piResourceQuantityRequirements(NULL),
	m_piProductionTraits(NULL),
	m_piFlavorValue(NULL),
	m_piUnitGroupRequired(NULL),
	m_piProductionModifierBuildings(NULL),
	m_piYieldFromKills(NULL),
	m_piUnused(NULL),
	m_pbUpgradeUnitClass(NULL),
	m_pbUnitAIType(NULL),
	m_pbNotUnitAIType(NULL),
	m_pbBuilds(NULL),
	m_pbBuildings(NULL),
	m_pbBuildingClassRequireds(NULL),
	m_pbFreePromotions(NULL),
	m_pbPassiveAbilities(NULL),
	m_paszEarlyArtDefineTags(NULL),
	m_paszLateArtDefineTags(NULL),
	m_paszMiddleArtDefineTags(NULL),
	m_paszUnitNames(NULL),
	m_paeGreatWorks(NULL)
{
}

// TODO: Phase1 audit CvUnitEntry::~CvUnitEntry(): MISMATCH; BE/object instructions 220/204; Civ5 changed/new UNVERIFIED.
CvUnitEntry::~CvUnitEntry()
{
	SAFE_DELETE_ARRAY(m_pbUpgradeUnitClass);
	SAFE_DELETE_ARRAY(m_pbUnitAIType);
	SAFE_DELETE_ARRAY(m_pbNotUnitAIType);
	SAFE_DELETE_ARRAY(m_pbBuilds);
	SAFE_DELETE_ARRAY(m_pbBuildings);
	SAFE_DELETE_ARRAY(m_pbBuildingClassRequireds);
	SAFE_DELETE_ARRAY(m_piPrereqAndTechs);
	SAFE_DELETE_ARRAY(m_piResourceQuantityRequirements);
	SAFE_DELETE_ARRAY(m_piAffinityPrereqs);
	SAFE_DELETE_ARRAY(m_piProductionTraits);
	SAFE_DELETE_ARRAY(m_piFlavorValue);
	SAFE_DELETE_ARRAY(m_piUnitGroupRequired);
	SAFE_DELETE_ARRAY(m_pbFreePromotions);
	SAFE_DELETE_ARRAY(m_pbPassiveAbilities);
	SAFE_DELETE_ARRAY(m_paszEarlyArtDefineTags);
	SAFE_DELETE_ARRAY(m_paszLateArtDefineTags);
	SAFE_DELETE_ARRAY(m_paszMiddleArtDefineTags);
	SAFE_DELETE_ARRAY(m_paszUnitNames);
	SAFE_DELETE_ARRAY(m_paeGreatWorks);
	SAFE_DELETE_ARRAY(m_piProductionModifierBuildings);
	SAFE_DELETE_ARRAY(m_piYieldFromKills);
}

int CvUnitEntry::GetAdvancedStartCost() const { return m_iAdvancedStartCost; }
int CvUnitEntry::GetAirInterceptRange() const { return m_iAirInterceptRange; }
int CvUnitEntry::GetAirUnitCap() const { return m_iAirUnitCap; }
int CvUnitEntry::GetBaseBeakersTurnsToCount() const { return m_iBaseBeakersTurnsToCount; }
int CvUnitEntry::GetBaseCultureTurnsToCount() const { return m_iBaseCultureTurnsToCount; }
int CvUnitEntry::GetBaseHurry() const { return m_iBaseHurry; }
int CvUnitEntry::GetBaseSightRange() const { return m_iBaseSightRange; }
int CvUnitEntry::GetCivilianAttackPriority() const { return m_iCivilianAttackPriority; }
int CvUnitEntry::GetCombat() const { return m_iCombat; }
int CvUnitEntry::GetCombatLimit() const { return m_iCombatLimit; }
int CvUnitEntry::GetCommandType() const { return m_iCommandType; }
int CvUnitEntry::GetConscriptionValue() const { return m_iConscriptionValue; }
int CvUnitEntry::GetDefaultUnitAIType() const { return m_iDefaultUnitAIType; }
int CvUnitEntry::GetDomainCargo() const { return m_iDomainCargo; }
int CvUnitEntry::GetDomainType() const { return m_iDomainType; }
int CvUnitEntry::GetExtraMaintenanceCost() const { return m_iExtraMaintenanceCost; }
int CvUnitEntry::GetFreePolicies() const { return m_iFreePolicies; }
int CvUnitEntry::GetGoodyHutUpgradeUnitClass() const { return m_iGoodyHutUpgradeUnitClass; }
int CvUnitEntry::GetGroupDefinitions() const { return m_iGroupDefinitions; }
int CvUnitEntry::GetGroupSize() const { return m_iGroupSize; }
int CvUnitEntry::GetHurryCostModifier() const { return m_iHurryCostModifier; }
int CvUnitEntry::GetHurryMultiplier() const { return m_iHurryMultiplier; }
int CvUnitEntry::GetLeaderExperience() const { return m_iLeaderExperience; }
int CvUnitEntry::GetLeaderPromotion() const { return m_iLeaderPromotion; }
int CvUnitEntry::GetMinAreaSize() const { return m_iMinAreaSize; }
int CvUnitEntry::GetMoves() const { return m_iMoves; }
int CvUnitEntry::GetNumExpeditionCharges() const { return m_iNumExpeditionCharges; }
int CvUnitEntry::GetNumFreeTechs() const { return m_iNumFreeTechs; }
int CvUnitEntry::GetNumGoldPerEra() const { return m_iNumGoldPerEra; }
int CvUnitEntry::GetNumUnitNames() const { return m_iNumUnitNames; }
int CvUnitEntry::GetObsoleteTech() const { return m_iObsoleteTech; }
int CvUnitEntry::GetOrbitalAttackRange() const { return m_iOrbitalAttackRange; }
int CvUnitEntry::GetOrbitalUnitType() const { return m_iOrbitalUnitType; }
int CvUnitEntry::GetPolicyType() const { return m_iPolicyType; }
int CvUnitEntry::GetPrereqAndTech() const { return m_iPrereqAndTech; }
int CvUnitEntry::GetPrereqPillageTech() const { return m_iPrereqPillageTech; }
int CvUnitEntry::GetProductionCost() const { return m_iProductionCost; }
int CvUnitEntry::GetProjectPrereq() const { return m_iProjectPrereq; }
int CvUnitEntry::GetRange() const { return m_iRange; }
int CvUnitEntry::GetRangedCombat() const { return m_iRangedCombat; }
int CvUnitEntry::GetRangedCombatLimit() const { return m_iRangedCombatLimit; }
int CvUnitEntry::GetSpaceshipProject() const { return m_iSpaceshipProject; }
int CvUnitEntry::GetSpecialCargo() const { return m_iSpecialCargo; }
int CvUnitEntry::GetSpecialUnitType() const { return m_iSpecialUnitType; }
int CvUnitEntry::GetUnhealth() const { return m_iUnhealth; }
int CvUnitEntry::GetUnitCaptureClassType() const { return m_iUnitCaptureClassType; }
int CvUnitEntry::GetUnitClassType() const { return m_iUnitClassType; }
int CvUnitEntry::GetUnitCombatType() const { return m_iUnitCombatType; }
int CvUnitEntry::GetMeleeWaveSize() const { return m_iMeleeWaveSize; }
int CvUnitEntry::GetRangedWaveSize() const { return m_iRangedWaveSize; }
int CvUnitEntry::GetWorkRate() const { return m_iWorkRate; }
int CvUnitEntry::GetXPValueAttack() const { return m_iXPValueAttack; }
int CvUnitEntry::GetXPValueDefense() const { return m_iXPValueDefense; }
int CvUnitEntry::GetMeleeDefenseMod() const { return m_iMeleeDefenseMod; }
int CvUnitEntry::GetRangedDefenseMod() const { return m_iRangedDefenseMod; }
int CvUnitEntry::GetAirDefenseMod() const { return m_iAirDefenseMod; }
int CvUnitEntry::GetCityStrikeDefenseMod() const { return m_iCityStrikeDefenseMod; }
int CvUnitEntry::GetOrbitalDefenseMod() const { return m_iOrbitalDefenseMod; }
int CvUnitEntry::GetExtraAttacks() const { return m_iExtraAttacks; }
bool CvUnitEntry::IsAlienColossus() const { return m_bAlienColossus; }
bool CvUnitEntry::IsAlienLifeform() const { return m_bAlienLifeform; }
bool CvUnitEntry::IsNonsentient() const { return m_bNonsentient; }
bool CvUnitEntry::IsAmphibiousAttack() const { return m_bAmphibiousAttack; }
bool CvUnitEntry::IsCaptureWhileEmbarked() const { return m_bCaptureWhileEmbarked; }
bool CvUnitEntry::IsCoastalWalk() const { return m_bCoastalWalk; }
bool CvUnitEntry::IsDeepWaterOnly() const { return m_bDeepWaterOnly; }
bool CvUnitEntry::IsEarthlingSettler() const { return m_bEarthlingSettler; }
bool CvUnitEntry::IsFoodProduction() const { return m_bFoodProduction; }
bool CvUnitEntry::IsFound() const { return m_bFound; }
bool CvUnitEntry::IsFoundAbroad() const { return m_bFoundAbroad; }
bool CvUnitEntry::IsIgnoreBuildingDefense() const { return m_bIgnoreBuildingDefense; }
bool CvUnitEntry::IsMechUnit() const { return m_bMechUnit; }
bool CvUnitEntry::IsMilitaryProduction() const { return m_bMilitaryProduction; }
bool CvUnitEntry::IsMilitarySupport() const { return m_bMilitarySupport; }
bool CvUnitEntry::CanMoveAfterPurchase() const { return m_bCanMoveAfterPurchase; }
bool CvUnitEntry::CanMoveAfterAttacking() const { return m_bCanMoveAfterAttacking; }
bool CvUnitEntry::IsImmobile() const { return m_bImmobile; }
bool CvUnitEntry::IsNoBadGoodies() const { return m_bNoBadGoodies; }
bool CvUnitEntry::IsNoMaintenance() const { return m_bNoMaintenance; }
bool CvUnitEntry::IsPillage() const { return m_bPillage; }
bool CvUnitEntry::IsPrereqResources() const { return m_bPrereqResources; }
bool CvUnitEntry::IsPurchaseOnly() const { return m_bPurchaseOnly; }
bool CvUnitEntry::IsRangeAttackOnlyInDomain() const { return m_bRangeAttackOnlyInDomain; }
bool CvUnitEntry::IsRivalTerritory() const { return m_bRivalTerritory; }
bool CvUnitEntry::IsRushBuilding() const { return m_bRushBuilding; }
bool CvUnitEntry::IsSuicide() const { return m_bSuicide; }
bool CvUnitEntry::IsTrade() const { return m_bTrade; }
bool CvUnitEntry::RevealInFog() const { return m_bRevealInFog; }
bool CvUnitEntry::BlockLineOfSight() const { return m_bBlockLineOfSight; }
bool CvUnitEntry::IsWorker() const { return m_bWorker; }
bool CvUnitEntry::HasInvisibility() const { return m_bHasInvisibility; }
int CvUnitEntry::GetPower() const { return m_iCachedPower; }
bool CvUnitEntry::GetUnitArtInfoCulturalVariation() const { return m_iUnitArtInfoCulturalVariation; }
bool CvUnitEntry::GetUnitArtInfoEraVariation() const { return m_iUnitArtInfoEraVariation; }
bool CvUnitEntry::GetUnitArtInfoUpgradeVariation() const { return m_iUnitArtInfoUpgradeVariation; }
int CvUnitEntry::GetUnitArtInfoVariationStart() const { return m_iUnitArtInfoVariationStart; }
bool CvUnitEntry::GetUnitArtInfoAmphibiousVariation() const { return m_iUnitArtInfoAmphibiousVariation; }

void CvUnitEntry::SetCombat(int value) { m_iCombat = value; }
void CvUnitEntry::SetCommandType(int value) { m_iCommandType = value; }
// TODO: Phase1 audit CvUnitEntry::IsOrbitalUnitType() const: UNVERIFIED; BE/object instructions 5/5; Civ5 changed/new UNVERIFIED.
bool CvUnitEntry::IsOrbitalUnitType() const { return m_iOrbitalUnitType != -1; }
const char* CvUnitEntry::GetUnitArtInfoTag() const { return m_strUnitArtInfoTag; }
// TODO: Phase1 audit CvUnitEntry::GetUnitNames(int) const: MISMATCH; BE/object instructions 64/66; Civ5 changed/new UNVERIFIED.
const char* CvUnitEntry::GetUnitNames(int i) const { return m_paszUnitNames ? m_paszUnitNames[i] : NULL; }
// TODO: Phase1 audit CvUnitEntry::GetGreatWorks(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
GreatWorkType CvUnitEntry::GetGreatWorks(int i) const { return m_paeGreatWorks ? m_paeGreatWorks[i] : NO_GREAT_WORK; }
UnitMoveRate CvUnitEntry::GetMoveRate(int i) const
{
	if(i < 0) i = 0;
	if(i > 11) i = 11;
	return m_unitMoveRate[i];
}
// TODO: Phase1 audit CvUnitEntry::GetPrereqAndTechs(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvUnitEntry::GetPrereqAndTechs(int i) const { return m_piPrereqAndTechs ? m_piPrereqAndTechs[i] : -1; }
// TODO: Phase1 audit CvUnitEntry::GetResourceQuantityRequirement(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvUnitEntry::GetResourceQuantityRequirement(int i) const { return m_piResourceQuantityRequirements ? m_piResourceQuantityRequirements[i] : -1; }
int CvUnitEntry::GetAffinityPrereq(AffinityType i) const { return m_piAffinityPrereqs ? m_piAffinityPrereqs[i] : 0; }
// TODO: Phase1 audit CvUnitEntry::GetProductionTraits(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
int CvUnitEntry::GetProductionTraits(int i) const { return m_piProductionTraits ? m_piProductionTraits[i] : -1; }
int CvUnitEntry::GetFlavorValue(int i) const { return m_piFlavorValue ? m_piFlavorValue[i] : 0; }
int CvUnitEntry::GetUnitGroupRequired(int i) const { return m_piUnitGroupRequired ? m_piUnitGroupRequired[i] : 0; }
int CvUnitEntry::GetBuildingProductionModifier(BuildingTypes i) const { return m_piProductionModifierBuildings[i]; }
int CvUnitEntry::GetYieldFromKills(YieldTypes i) const { return m_piYieldFromKills[i]; }
bool CvUnitEntry::GetUpgradeUnitClass(int i) const { return m_pbUpgradeUnitClass ? m_pbUpgradeUnitClass[i] : false; }
bool CvUnitEntry::GetUnitAIType(int i) const { return m_pbUnitAIType ? m_pbUnitAIType[i] : false; }
bool CvUnitEntry::GetNotUnitAIType(int i) const { return m_pbNotUnitAIType ? m_pbNotUnitAIType[i] : false; }
bool CvUnitEntry::GetBuilds(int i) const { return m_pbBuilds ? m_pbBuilds[i] : false; }
bool CvUnitEntry::GetBuildings(int i) const { return m_pbBuildings ? m_pbBuildings[i] : false; }
bool CvUnitEntry::GetBuildingClassRequireds(int i) const { return m_pbBuildingClassRequireds ? m_pbBuildingClassRequireds[i] : false; }
bool CvUnitEntry::GetFreePromotions(int i) const { return m_pbFreePromotions ? m_pbFreePromotions[i] : false; }
bool CvUnitEntry::GetPassiveAbilities(int i) const { return m_pbPassiveAbilities ? m_pbPassiveAbilities[i] : false; }
// TODO: Phase1 audit CvUnitEntry::GetSupportMissions(int) const: UNVERIFIED; BE/object instructions 24/24; Civ5 changed/new UNVERIFIED.
bool CvUnitEntry::GetSupportMissions(int i) const
{
	return m_supportMissions.lower_bound((MissionTypes)i) != m_supportMissions.end();
}
// TODO: Phase1 audit CvUnitEntry::GetSupportMissionData(MissionTypes) const: MISMATCH; BE/object instructions 29/29; Civ5 changed/new UNVERIFIED.
const UnitSupportMissionData* CvUnitEntry::GetSupportMissionData(MissionTypes mission) const
{
	return m_supportMissions.lower_bound(mission) != m_supportMissions.end() ? &m_supportMissions.at(mission) : NULL;
}

// TODO: Phase1 audit CvUnitEntry::CacheResults(Database::Results&, CvDatabaseUtility&): MISMATCH; BE/object instructions 1379/1314; Civ5 changed/new UNVERIFIED.
bool CvUnitEntry::CacheResults(Database::Results& results, CvDatabaseUtility& utility)
{
	if(!CvBaseInfo::CacheResults(results, utility)) return false;
	m_iAdvancedStartCost = results.GetInt("AdvancedStartCost");
	m_iAirInterceptRange = results.GetInt("AirInterceptRange");
	m_iAirUnitCap = results.GetInt("AirUnitCap");
	m_iBaseBeakersTurnsToCount = results.GetInt("BaseBeakersTurnsToCount");
	m_iBaseCultureTurnsToCount = results.GetInt("BaseCultureTurnsToCount");
	m_iBaseHurry = results.GetInt("BaseHurry");
	m_iBaseSightRange = results.GetInt("BaseSightRange");
	m_iCombat = results.GetInt("Combat");
	m_iCombatLimit = results.GetInt("CombatLimit");
	m_iConscriptionValue = results.GetInt("Conscription");
	m_iEraOfProsperityTurns = results.GetInt("EraOfProsperityTurns");
	m_iExtraMaintenanceCost = results.GetInt("ExtraMaintenanceCost");
	m_iFreePolicies = results.GetInt("FreePolicies");
	m_iHurryCostModifier = results.GetInt("HurryCostModifier");
	m_iHurryMultiplier = results.GetInt("HurryMultiplier");
	m_iLeaderExperience = results.GetInt("LeaderExperience");
	m_iMinAreaSize = results.GetInt("MinAreaSize");
	m_iMoves = results.GetInt("Moves");
	m_iNumExpeditionCharges = results.GetInt("NumExpeditionCharges");
	m_iNumFreeTechs = results.GetInt("NumFreeTechs");
	m_iNumGoldPerEra = results.GetInt("NumGoldPerEra");
	m_iOrbitalAttackRange = results.GetInt("OrbitalAttackRange");
	m_iProductionCost = results.GetInt("Cost");
	m_iRange = results.GetInt("Range");
	m_iRangedCombat = results.GetInt("RangedCombat");
	m_iRangedCombatLimit = results.GetInt("RangedCombatLimit");
	m_iUnhealth = results.GetInt("Unhealth");
	m_iWorkRate = results.GetInt("WorkRate");
	m_iXPValueAttack = results.GetInt("XPValueAttack");
	m_iXPValueDefense = results.GetInt("XPValueDefense");
	m_iMeleeDefenseMod = results.GetInt("MeleeDefenseMod");
	m_iRangedDefenseMod = results.GetInt("RangedDefenseMod");
	m_iAirDefenseMod = results.GetInt("AirDefenseMod");
	m_iCityStrikeDefenseMod = results.GetInt("CityStrikeDefenseMod");
	m_iOrbitalDefenseMod = results.GetInt("OrbitalDefenseMod");
	m_iExtraAttacks = results.GetInt("ExtraAttacks");
	m_bAlienColossus = results.GetBool("AlienColossus");
	m_bAlienLifeform = results.GetBool("AlienLifeform");
	m_bNonsentient = results.GetBool("Nonsentient");
	m_bAmphibiousAttack = results.GetBool("AmphibiousAttack");
	m_bCaptureWhileEmbarked = results.GetBool("CaptureWhileEmbarked");
	m_bCoastalWalk = results.GetBool("CoastalWalk");
	m_bDeepWaterOnly = results.GetBool("DeepWaterOnly");
	m_bEarthlingSettler = results.GetBool("EarthlingSettler");
	m_bFoodProduction = results.GetBool("Food");
	m_bFound = results.GetBool("Found");
	m_bFoundAbroad = results.GetBool("FoundAbroad");
	m_bIgnoreBuildingDefense = results.GetBool("IgnoreBuildingDefense");
	m_bMechUnit = results.GetBool("Mechanized");
	m_bMilitaryProduction = results.GetBool("MilitaryProduction");
	m_bMilitarySupport = results.GetBool("MilitarySupport");
	m_bCanMoveAfterPurchase = results.GetBool("MoveAfterPurchase");
	m_bCanMoveAfterAttacking = results.GetBool("MoveAfterAttacking");
	m_bImmobile = results.GetBool("Immobile");
	m_bNoBadGoodies = results.GetBool("NoBadGoodies");
	m_bNoMaintenance = results.GetBool("NoMaintenance");
	m_bPillage = results.GetBool("Pillage");
	m_bPrereqResources = results.GetBool("PrereqResources");
	m_bPurchaseOnly = results.GetBool("PurchaseOnly");
	m_bRangeAttackOnlyInDomain = results.GetBool("RangeAttackOnlyInDomain");
	m_bRivalTerritory = results.GetBool("RivalTerritory");
	m_bRushBuilding = results.GetBool("RushBuilding");
	m_bSuicide = results.GetBool("Suicide");
	m_bTrade = results.GetBool("Trade");
	m_bRevealInFog = results.GetBool("RevealInFog");
	m_bBlockLineOfSight = results.GetBool("BlockLineOfSight");
	m_bWorker = results.GetBool("Worker");
	m_bHasInvisibility = results.GetBool("Invisibility");
	m_iUnitArtInfoCulturalVariation = results.GetBool("UnitArtInfoCulturalVariation");
	m_iUnitArtInfoEraVariation = results.GetBool("UnitArtInfoEraVariation");
	m_iUnitArtInfoUpgradeVariation = results.GetBool("UnitArtInfoUpgradeVariation");
	m_iUnitArtInfoVariationStart = results.GetInt("UnitArtInfoAffinityVariationStart");
	m_iUnitArtInfoAmphibiousVariation = results.GetBool("UnitArtInfoAmphibiousVariation");
	m_strUnitArtInfoTag = results.GetText("UnitArtInfo");
	m_iUnitClassType = GC.getInfoTypeForString(results.GetText("Class"), true);
	m_iSpecialUnitType = GC.getInfoTypeForString(results.GetText("Special"), true);
	m_iOrbitalUnitType = GC.getInfoTypeForString(results.GetText("Orbital"), true);
	m_iUnitCaptureClassType = GC.getInfoTypeForString(results.GetText("Capture"), true);
	m_iUnitCombatType = GC.getInfoTypeForString(results.GetText("CombatClass"), true);
	m_iDomainType = GC.getInfoTypeForString(results.GetText("Domain"), true);
	m_iCivilianAttackPriority = GC.getInfoTypeForString(results.GetText("CivilianAttackPriority"), true);
	m_iDefaultUnitAIType = GC.getInfoTypeForString(results.GetText("DefaultUnitAI"), true);
	m_iPrereqPillageTech = GC.getInfoTypeForString(results.GetText("PillagePrereqTech"), true);
	m_iPrereqAndTech = GC.getInfoTypeForString(results.GetText("PrereqTech"), true);
	m_iObsoleteTech = GC.getInfoTypeForString(results.GetText("ObsoleteTech"), true);
	m_iPolicyType = GC.getInfoTypeForString(results.GetText("PolicyType"), true);
	m_iGoodyHutUpgradeUnitClass = GC.getInfoTypeForString(results.GetText("GoodyHutUpgradeUnitClass"), true);
	m_iSpecialCargo = GC.getInfoTypeForString(results.GetText("SpecialCargo"), true);
	m_iDomainCargo = GC.getInfoTypeForString(results.GetText("DomainCargo"), true);
	m_iProjectPrereq = GC.getInfoTypeForString(results.GetText("ProjectPrereq"), true);
	m_iSpaceshipProject = GC.getInfoTypeForString(results.GetText("SpaceshipProject"), true);
	m_iLeaderPromotion = GC.getInfoTypeForString(results.GetText("LeaderPromotion"), true);
	const char* unitType = GetType();
	utility.SetFlavors(m_piFlavorValue, "Unit_Flavors", "UnitType", unitType);
	utility.PopulateArrayByValue(m_piProductionTraits, "Traits", "Unit_ProductionTraits", "TraitType", "UnitType", unitType, "Trait");
	utility.PopulateArrayByValue(m_piResourceQuantityRequirements, "Resources", "Unit_ResourceQuantityRequirements", "ResourceType", "UnitType", unitType, "Cost");
	utility.PopulateArrayByValue(m_piAffinityPrereqs, "Affinity_Types", "Unit_AffinityPrereqs", "AffinityType", "UnitType", unitType, "Level");
	utility.PopulateArrayByValue(m_piProductionModifierBuildings, "Buildings", "Unit_ProductionModifierBuildings", "BuildingType", "UnitType", unitType, "ProductionModifier");
	utility.PopulateArrayByValue(m_piYieldFromKills, "Yields", "Unit_YieldFromKills", "YieldType", "UnitType", unitType, "Yield");
	utility.PopulateArrayByExistence(m_pbFreePromotions, "UnitPromotions", "Unit_FreePromotions", "PromotionType", "UnitType", unitType);
	utility.PopulateArrayByExistence(m_pbPassiveAbilities, "UnitPassiveAbilities", "Unit_PassiveAbilities", "UnitPassiveAbilityType", "UnitType", unitType);
	utility.PopulateArrayByExistence(m_pbUpgradeUnitClass, "UnitClasses", "Unit_ClassUpgrades", "UnitClassType", "UnitType", unitType);
	utility.PopulateArrayByExistence(m_pbUnitAIType, "UnitAIInfos", "Unit_AITypes", "UnitAIType", "UnitType", unitType);
	utility.PopulateArrayByExistence(m_pbNotUnitAIType, "UnitAIInfos", "Unit_NotAITypes", "UnitAIType", "UnitType", unitType);
	utility.PopulateArrayByExistence(m_pbBuilds, "Builds", "Unit_Builds", "BuildType", "UnitType", unitType);
	utility.PopulateArrayByExistence(m_pbBuildings, "Buildings", "Unit_Buildings", "BuildingType", "UnitType", unitType);
	utility.PopulateArrayByExistence(m_pbBuildingClassRequireds, "BuildingClasses", "Unit_BuildingClassRequireds", "BuildingClassType", "UnitType", unitType);
	utility.InitializeArray(m_piPrereqAndTechs, "Technologies", -1);
	{
		std::string key = "Units - TechTypes";
		Database::Results* rows = utility.GetResults(key);
		if(!rows) rows = utility.PrepareResults(key, "select Technologies.ID from Unit_TechTypes inner join Technologies on TechType = Technologies.Type where UnitType = ?");
		UnitClassesBind(rows, 1, unitType, -1, false);
		int i = 0;
		while(rows->Step()) m_piPrereqAndTechs[i++] = rows->GetInt(0);
		rows->Reset();
	}
	{
		std::string key = "Units - UniqueNameCount";
		Database::Results* rows = utility.GetResults(key);
		if(!rows) rows = utility.PrepareResults(key, "select count(*) from Unit_UniqueNames where UnitType = ?");
		UnitClassesBind(rows, 1, unitType, -1, false);
		rows->Step();
		m_iNumUnitNames = rows->GetInt(0);
		rows->Reset();
	}
	if(m_iNumUnitNames > 0)
	{
		m_paszUnitNames = FNEW(CvString[m_iNumUnitNames], c_eCiv5GameplayDLL, 0);
		m_paeGreatWorks = FNEW(GreatWorkType[m_iNumUnitNames], c_eCiv5GameplayDLL, 0);
		std::string key = "Units - UniqueNames";
		Database::Results* rows = utility.GetResults(key);
		if(!rows) rows = utility.PrepareResults(key, "select UniqueName, GreatWorkType from Unit_UniqueNames where UnitType = ? ORDER BY rowid");
		UnitClassesBind(rows, 1, unitType, -1, false);
		int i = 0;
		while(rows->Step())
		{
			m_paszUnitNames[i] = UnitClassesText(rows, 0);
			const char* work = UnitClassesText(rows, 1);
			m_paeGreatWorks[i++] = work ? (GreatWorkType)GC.getInfoTypeForString(work, true) : NO_GREAT_WORK;
		}
		rows->Reset();
	}
	{
		std::string key = "Units - MovementRates";
		Database::Results* rows = utility.GetResults(key);
		if(!rows) rows = utility.PrepareResults(key, "SELECT * FROM MovementRates where Type = ? ORDER BY NumHexes");
		UnitClassesBind(rows, 1, results.GetText("MoveRate"), -1, false);
		while(rows->Step())
		{
			int i = rows->GetInt("NumHexes") - 1;
			float total = UnitClassesFloat(rows, "TotalTime");
			float easeIn = UnitClassesFloat(rows, "EaseIn");
			float easeOut = UnitClassesFloat(rows, "EaseOut");
			float individual = UnitClassesFloat(rows, "IndividualOffset");
			float row = UnitClassesFloat(rows, "RowOffset");
			float roll = UnitClassesFloat(rows, "CurveRoll");
			int subdivisions = rows->GetInt("PathSubdivision");
			if(i >= 0 && i <= 11)
			{
				m_unitMoveRate[i].m_fTotalMoveRate = total;
				m_unitMoveRate[i].m_fEaseIn = easeIn;
				m_unitMoveRate[i].m_fEaseOut = easeOut;
				m_unitMoveRate[i].m_fIndividualOffset = individual;
				m_unitMoveRate[i].m_fRowOffset = row;
				m_unitMoveRate[i].m_fCurveRoll = roll;
				m_unitMoveRate[i].m_iPathSubdivision = subdivisions;
			}
		}
		rows->Reset();
	}
	{
		std::string key = "Unit_SupportMissions";
		Database::Results* rows = utility.GetResults(key);
		if(!rows) rows = utility.PrepareResults(key, "select Missions.ID as MissionID, * from Unit_SupportMissions inner join Missions on Missions.Type = MissionType where UnitType = ?");
		UnitClassesBind(rows, 1, unitType, -1, false);
		while(rows->Step())
		{
			MissionTypes mission = (MissionTypes)rows->GetInt(0);
			if(mission == NO_MISSION) continue;
			int strength = rows->GetInt("Strength");
			int range = rows->GetInt("RangeOverride");
			bool friendly = rows->GetBool("TargetFriendly");
			bool neutral = rows->GetBool("TargetNeutral");
			bool enemy = rows->GetBool("TargetEnemy");
			const char* popup = rows->GetText("PopupTextKey");
			if(m_supportMissions.lower_bound(mission) == m_supportMissions.end())
				m_supportMissions[mission] = UnitSupportMissionData();
			m_supportMissions[mission].m_iStrength = strength;
			m_supportMissions[mission].m_iRangeOverride = range;
			m_supportMissions[mission].m_bTargetFriendly = friendly;
			m_supportMissions[mission].m_bTargetNeutral = neutral;
			m_supportMissions[mission].m_bTargetEnemy = enemy;
			m_supportMissions[mission].m_strPopupTextKey = popup;
		}
		rows->Reset();
	}
	DoUpdatePower();
	return true;
}

// TODO: Phase1 audit CvUnitEntry::DoUpdatePower(): UNVERIFIED; BE/object instructions 401/401; Civ5 changed/new UNVERIFIED.
void CvUnitEntry::DoUpdatePower()
{
	int power = (int)pow((double)GetCombat(), 1.5);
	int ranged = (int)pow((double)GetRangedCombat(), 1.45);
	if(GetDomainType() == 0) ranged = ranged * 3 / 4;
	if(ranged > power) power = ranged;
	power = (int)((float)power * pow(std::min(1.0, (double)GetMoves()), 0.3));
	if(IsSuicide()) power /= 2;
	for(int i = 0; i < UnitClassesNumPromotion(&GC); ++i)
	{
		CvPromotionEntry* promotion = UnitClassesPromotion(&GC, (int)i);
		if(!promotion || !GetFreePromotions(i)) continue;
		if(UnitClassesGetCityAttackPercent(promotion) > 0) power += power * UnitClassesGetCityAttackPercent(promotion) / 200;
		if(UnitClassesGetAttackMod(promotion) > 0) power += power * UnitClassesGetAttackMod(promotion) / 200;
		if(UnitClassesGetDefenseMod(promotion) > 0) power += power * UnitClassesGetDefenseMod(promotion) / 200;
		if(UnitClassesGetDropRange(promotion) > 0) power += power / 4;
		if(UnitClassesIsBlitz(promotion)) power += power / 5;
		if(UnitClassesIsMustSetUpToRangedAttack(promotion)) power -= power / 5;
		if(UnitClassesIsOnlyDefensive(promotion) && GetRangedCombat() == 0) power -= power / 4;
		for(int j = 0; j < UnitClassesNumTerrain(&GC); ++j)
		{
			if(UnitClassesGetTerrainAttackPercent(promotion, j) > 0) power += power * UnitClassesGetTerrainAttackPercent(promotion, j) / 400;
			if(UnitClassesGetTerrainDefensePercent(promotion, j) > 0) power += power * UnitClassesGetTerrainDefensePercent(promotion, j) / 400;
		}
		for(int j = 0; j < UnitClassesNumFeature(&GC); ++j)
		{
			if(UnitClassesGetFeatureAttackPercent(promotion, j) > 0) power += power * UnitClassesGetFeatureAttackPercent(promotion, j) / 400;
			if(UnitClassesGetFeatureDefensePercent(promotion, j) > 0) power += power * UnitClassesGetFeatureDefensePercent(promotion, j) / 400;
		}
		for(int j = 0; j < UnitClassesNumUnitCombatClass(&GC); ++j)
			if(UnitClassesGetUnitCombatModifierPercent(promotion, j) > 0) power += power * UnitClassesGetUnitCombatModifierPercent(promotion, j) / 400;
		for(int j = 0; j < UnitClassesNumUnitClass(&GC); ++j)
		{
			if(UnitClassesGetUnitClassModifierPercent(promotion, j) > 0) power += power * UnitClassesGetUnitClassModifierPercent(promotion, j) / 800;
			if(UnitClassesGetUnitClassAttackModifier(promotion, j) > 0) power += power * UnitClassesGetUnitClassAttackModifier(promotion, j) / 1000;
			if(UnitClassesGetUnitClassDefenseModifier(promotion, j) > 0) power += power * UnitClassesGetUnitClassDefenseModifier(promotion, j) / 1000;
		}
		for(int j = 0; j < 6; ++j)
			if(UnitClassesGetDomainModifierPercent(promotion, j) > 0) power += power * UnitClassesGetDomainModifierPercent(promotion, j) / 400;
	}
	m_iCachedPower = power;
}

// TODO: Phase1 audit CvUnitEntry::GetCargoSpace() const: UNVERIFIED; BE/object instructions 42/42; Civ5 changed/new UNVERIFIED.
int CvUnitEntry::GetCargoSpace() const
{
	int cargo = 0;
	for(int i = 0; i < UnitClassesNumPromotion(&GC); ++i)
	{
		CvPromotionEntry* promotion = UnitClassesPromotion(&GC, (int)i);
		if(promotion && GetFreePromotions(i)) cargo += UnitClassesGetCargoChange(promotion);
	}
	return cargo;
}

CvUnitXMLEntries::CvUnitXMLEntries() {}
// TODO: Phase1 audit CvUnitXMLEntries::~CvUnitXMLEntries(): UNVERIFIED; BE/object instructions 12/12; Civ5 changed/new UNVERIFIED.
CvUnitXMLEntries::~CvUnitXMLEntries() { DeleteArray(); }
std::vector<CvUnitEntry*>& CvUnitXMLEntries::GetUnitEntries() { return m_paUnitEntries; }
int CvUnitXMLEntries::GetNumUnits() { return m_paUnitEntries.size(); }
CvUnitEntry* CvUnitXMLEntries::GetEntry(int i) { return m_paUnitEntries[i]; }
CvUnitEntry* CvUnitXMLEntries::GetEntry(int i) const { return m_paUnitEntries[i]; }
// TODO: Phase1 audit CvUnitXMLEntries::DeleteArray(): MISMATCH; BE/object instructions 39/38; Civ5 changed/new UNVERIFIED.
void CvUnitXMLEntries::DeleteArray()
{
	for(std::vector<CvUnitEntry*>::iterator it = m_paUnitEntries.begin(); it != m_paUnitEntries.end(); ++it)
	{
		if(*it)
		{
			(*it)->~CvUnitEntry();
			operator delete(*it, sizeof(CvUnitEntry));
		}
		*it = NULL;
	}
	m_paUnitEntries.clear();
}
// TODO: Phase1 audit UnitArrayHelpers::Read(FDataStream&, int*): UNVERIFIED; BE/object instructions 21/21; Civ5 changed/new UNVERIFIED.
void UnitArrayHelpers::Read(FDataStream& stream, int* array)
{
	CvInfosSerializationHelper::ReadHashedDataArray(stream, array, UnitClassesNumUnit(&GC));
}
// TODO: Phase1 audit UnitArrayHelpers::Write(FDataStream&, int*, int): UNVERIFIED; BE/object instructions 5/5; Civ5 changed/new UNVERIFIED.
void UnitArrayHelpers::Write(FDataStream& stream, int* array, int count)
{
	CvInfosSerializationHelper::WriteHashedDataArray<UnitTypes, int>(stream, array, count);
}

static_assert(sizeof(CvUnitEntry) == 0x36c, "Beyond Earth CvUnitEntry layout");
static_assert(sizeof(UnitSupportMissionData) == 24, "Beyond Earth support mission layout");
