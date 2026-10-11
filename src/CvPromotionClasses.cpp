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
#include "CvUnit.h"
#include "CvPlayerAI.h"
#include "CvTeam.h"
#include "CvGame.h"
#include "Fireworks/FString.h"

// Preserve target APIs absent from the currently reconstructed shared headers.
// TODO: Phase1 audit PromotionNumTerrain(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int PromotionNumTerrain(CvGlobals*) asm("_ZN9CvGlobals18getNumTerrainInfosEv");
// TODO: Phase1 audit PromotionNumFeature(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int PromotionNumFeature(CvGlobals*) asm("_ZN9CvGlobals18getNumFeatureInfosEv");
// TODO: Phase1 audit PromotionNumUnitClass(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int PromotionNumUnitClass(CvGlobals*) asm("_ZN9CvGlobals20getNumUnitClassInfosEv");
// TODO: Phase1 audit PromotionNumUnitCombat(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int PromotionNumUnitCombat(CvGlobals*) asm("_ZN9CvGlobals26getNumUnitCombatClassInfosEv");
// TODO: Phase1 audit PromotionNumUnit(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int PromotionNumUnit(CvGlobals*) asm("_ZN9CvGlobals15getNumUnitInfosEv");
// TODO: Phase1 audit PromotionNumPromotion(CvGlobals *): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int PromotionNumPromotion(CvGlobals*) asm("_ZN9CvGlobals20getNumPromotionInfosEv");
// TODO: Phase1 audit PromotionInfo(CvGlobals *,PromotionTypes): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern CvPromotionEntry* PromotionInfo(CvGlobals*, PromotionTypes) asm("_ZN9CvGlobals16getPromotionInfoE14PromotionTypes");
// TODO: Phase1 audit PromotionTypeForHash(const CvGlobals *,unsigned int,bool): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern int PromotionTypeForHash(const CvGlobals*, unsigned int, bool) asm("_ZNK9CvGlobals18getInfoTypeForHashEjb");
// TODO: Phase1 audit PromotionBind(Database::Results *,int,const char *,bool): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern bool PromotionBind(Database::Results*, int, const char*, bool) asm("_ZN8Database7Results4BindEiPKcb");
// TODO: Phase1 audit PromotionHasTech(const CvTeamTechs *,TechTypes): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern bool PromotionHasTech(const CvTeamTechs*, TechTypes) asm("_ZNK11CvTeamTechs7HasTechE9TechTypes");
// TODO: Phase1 audit PromotionUnitHasPromotion(const CvUnit *,PromotionTypes): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern bool PromotionUnitHasPromotion(const CvUnit*, PromotionTypes) asm("_ZNK6CvUnit14isHasPromotionE14PromotionTypes");
// TODO: Phase1 audit PromotionReadString(FDataStream *,FStringA &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
extern void PromotionReadString(FDataStream*, FStringA&) asm("_ZN11FDataStream4ReadER8FStringA");
extern CvTeam* PromotionTeams asm("_ZN6CvTeam8m_aTeamsE");
extern CvPlayerAI* PromotionPlayers asm("_ZN10CvPlayerAI10m_aPlayersE");

// TODO: Phase1 audit CvPromotionEntry::CvPromotionEntry(): UNVERIFIED; BE/object instructions 44/44; Civ5 changed/new UNVERIFIED.
CvPromotionEntry::CvPromotionEntry():
	m_iLayerAnimationPath(-1),
	m_iPrereqPromotion(-1),
	m_iPrereqOrPromotion1(-1),
	m_iPrereqOrPromotion2(-1),
	m_iPrereqOrPromotion3(-1),
	m_iPrereqOrPromotion4(-1),
	m_iPrereqOrPromotion5(-1),
	m_iPrereqOrPromotion6(-1),
	m_iPrereqOrPromotion7(-1),
	m_iPrereqOrPromotion8(-1),
	m_iPrereqOrPromotion9(-1),
	m_iTechPrereq(-1),
	m_iArtifactRewardPrereq(-1),
	m_iExactLevelPrereq(-1),
	m_iInvisibleType(-1),
	m_iSeeInvisibleType(-1),
	m_iVisibilityChange(0),
	m_iMovesChange(0),
	m_iMoveDiscountChange(0),
	m_iRangeChange(0),
	m_iRangedAttackModifier(0),
	m_iInterceptionCombatModifier(0),
	m_iInterceptionDefenseDamageModifier(0),
	m_iAirSweepCombatModifier(0),
	m_iInterceptChanceChange(0),
	m_iNumInterceptionChange(0),
	m_iEvasionChange(0),
	m_iCargoChange(0),
	m_iEnemyHealChange(0),
	m_iNeutralHealChange(0),
	m_iFriendlyHealChange(0),
	m_iSameTileHealChange(0),
	m_iAdjacentTileHealChange(0),
	m_iEnemyDamageChance(0),
	m_iNeutralDamageChance(0),
	m_iEnemyDamage(0),
	m_iNeutralDamage(0),
	m_iCombatPercent(0),
	m_iMeleeCombatPercent(0),
	m_iCityAttackPercent(0),
	m_iCityDefensePercent(0),
	m_iRangedDefenseMod(0),
	m_iHillsAttackPercent(0),
	m_iHillsDefensePercent(0),
	m_iOpenAttackPercent(0),
	m_iOpenRangedAttackMod(0),
	m_iRoughAttackPercent(0),
	m_iRoughRangedAttackMod(0),
	m_iAttackFortifiedMod(0),
	m_iAttackUnfortifiedMod(0),
	m_iAttackWoundedMod(0),
	m_iFlankAttackModifier(0),
	m_iNearbyEnemyCombatMod(0),
	m_iNearbyEnemyCombatRange(0),
	m_iOpenDefensePercent(0),
	m_iRoughDefensePercent(0),
	m_iExtraAttacks(0),
	m_bGreatGeneral(false),
	m_bGreatAdmiral(false),
	m_iGreatGeneralModifier(0),
	m_bGreatGeneralReceivesMovement(false),
	m_iGreatGeneralCombatModifier(0),
	m_iFriendlyLandsModifier(0),
	m_iFriendlyLandsAttackModifier(0),
	m_iOutsideFriendlyLandsModifier(0),
	m_iCommandType(-1),
	m_iUpgradeDiscount(0),
	m_iExperiencePercent(0),
	m_iAdjacentMod(0),
	m_iAttackMod(0),
	m_iDefenseMod(0),
	m_iDropRange(0),
	m_iExtraNavalMoves(0),
	m_iExtraWorkerMoves(0),
	m_iHPHealedIfDefeatEnemy(0),
	m_iEraOfProsperityValueFromKills(0),
	m_iExtraWithdrawal(0),
	m_iEmbarkExtraVisibility(0),
	m_iEmbarkDefenseModifier(0),
	m_iCapitalDefenseModifier(0),
	m_iCapitalDefenseFalloff(0),
	m_iCityAttackPlunderModifier(0),
	m_iReligiousStrengthLossRivalTerritory(0),
	m_iInstantHealAmount(0),
	m_iTradeMissionInfluenceModifier(0),
	m_iTradeMissionGoldModifier(0),
	m_iMiasmaFlatHealthModifier(0),
	m_iOrbitalCoverageRadiusChange(0),
	m_iAlienRepelRangeChange(0),
	m_iCivHealthBonusMinModifier(0),
	m_iCivHealthBonusMaxModifier(0),
	m_iCivHealthBonusMinHealth(0),
	m_iCivHealthBonusMaxHealth(0),
	m_bMiasmaImmune(false),
	m_bMiasmaImmuneWorkers(false),
	m_bCannotBeChosen(false),
	m_bLostWithUpgrade(false),
	m_bNotWithUpgrade(false),
	m_bLeader(false),
	m_bBlitz(false),
	m_bAmphibiousAttack(false),
	m_bRiver(false),
	m_bEnemyRoute(false),
	m_bRivalTerritory(false),
	m_bMustSetUpToRangedAttack(false),
	m_bRangedSupportFire(false),
	m_bAlwaysHeal(false),
	m_bHealOutsideFriendly(false),
	m_bHillsDoubleMove(false),
	m_bIgnoreTerrainCost(false),
	m_bRoughTerrainEndsTurn(false),
	m_bHoveringUnit(false),
	m_bCoastalWalk(false),
	m_bFlatMovementCost(false),
	m_bCanMoveImpassable(false),
	m_bNoCapture(false),
	m_bOnlyDefensive(false),
	m_bNoDefensiveBonus(false),
	m_bHiddenNationality(false),
	m_bAlwaysHostile(false),
	m_bNoRevealMap(false),
	m_bRecon(false),
	m_bCanMoveAllTerrain(false),
	m_bCanMoveAfterAttacking(false),
	m_bAirSweepCapable(false),
	m_bAllowsEmbarkation(false),
	m_bRangeAttackIgnoreLOS(false),
	m_bFreeMaintenance(false),
	m_bFreePillageMoves(false),
	m_bHealOnPillage(false),
	m_bHealIfDefeatExcludesBarbarians(false),
	m_bCityAttackOnly(false),
	m_bCaptureDefeatedEnemy(false),
	m_bIgnoreGreatGeneralBenefit(false),
	m_bIgnoreZOC(false),
	m_bHasPostCombatPromotions(false),
	m_bPostCombatPromotionsExclusive(false),
	m_bSapper(false),
	m_bCanHeavyCharge(false),
	m_piTerrainAttackPercent(NULL),
	m_piTerrainDefensePercent(NULL),
	m_piFeatureAttackPercent(NULL),
	m_piFeatureDefensePercent(NULL),
	m_piUnitCombatModifierPercent(NULL),
	m_piUnitClassModifierPercent(NULL),
	m_piDomainModifierPercent(NULL),
	m_piFeaturePassableTech(NULL),
	m_piUnitClassAttackModifier(NULL),
	m_piUnitClassDefenseModifier(NULL),
	m_pbTerrainDoubleMove(NULL),
	m_pbFeatureDoubleMove(NULL),
	m_pbTerrainImpassable(NULL),
	m_piTerrainPassableTech(NULL),
	m_pbFeatureImpassable(NULL),
	m_pbUnitCombat(NULL),
	m_pbCivilianUnitType(NULL),
	m_pbPostCombatRandomPromotion(NULL)
{
}

/// Destructor
// TODO: Phase1 audit CvPromotionEntry::~CvPromotionEntry(): UNVERIFIED; BE/object instructions 128/128; Civ5 changed/new UNVERIFIED.
CvPromotionEntry::~CvPromotionEntry(void)
{
	SAFE_DELETE_ARRAY(m_piTerrainAttackPercent);
	SAFE_DELETE_ARRAY(m_piTerrainDefensePercent);
	SAFE_DELETE_ARRAY(m_piFeatureAttackPercent);
	SAFE_DELETE_ARRAY(m_piFeatureDefensePercent);
	SAFE_DELETE_ARRAY(m_piUnitCombatModifierPercent);
	SAFE_DELETE_ARRAY(m_piUnitClassModifierPercent);
	SAFE_DELETE_ARRAY(m_piDomainModifierPercent);
	SAFE_DELETE_ARRAY(m_piFeaturePassableTech);
	SAFE_DELETE_ARRAY(m_piUnitClassAttackModifier);
	SAFE_DELETE_ARRAY(m_piUnitClassDefenseModifier);
	SAFE_DELETE_ARRAY(m_pbTerrainDoubleMove);
	SAFE_DELETE_ARRAY(m_pbFeatureDoubleMove);
	SAFE_DELETE_ARRAY(m_pbTerrainImpassable);
	SAFE_DELETE_ARRAY(m_piTerrainPassableTech);
	SAFE_DELETE_ARRAY(m_pbFeatureImpassable);
	SAFE_DELETE_ARRAY(m_pbUnitCombat);
	SAFE_DELETE_ARRAY(m_pbCivilianUnitType);
	SAFE_DELETE_ARRAY(m_pbPostCombatRandomPromotion);
}
//------------------------------------------------------------------------------
// TODO: Phase1 audit CvPromotionEntry::CacheResults(Database::Results&, CvDatabaseUtility&): MISMATCH; BE/object instructions 1607/1564; Civ5 changed/new UNVERIFIED.
bool CvPromotionEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvHotKeyInfo::CacheResults(kResults, kUtility))
		return false;

	SetSound(kResults.GetText("Sound"));

	m_bCannotBeChosen = kResults.GetBool("CannotBeChosen");
	m_bLostWithUpgrade = kResults.GetBool("LostWithUpgrade");
	m_bNotWithUpgrade = kResults.GetBool("NotWithUpgrade");
	m_bLeader = kResults.GetBool("Leader");
	m_bBlitz = kResults.GetBool("Blitz");
	m_bAmphibiousAttack = kResults.GetBool("AmphibiousAttack");
	m_bRiver = kResults.GetBool("River");
	m_bEnemyRoute = kResults.GetBool("EnemyRoute");
	m_bRivalTerritory = kResults.GetBool("RivalTerritory");
	m_bMustSetUpToRangedAttack = kResults.GetBool("MustSetUpToRangedAttack");
	m_bRangedSupportFire = kResults.GetBool("RangedSupportFire");
	m_bAlwaysHeal = kResults.GetBool("AlwaysHeal");
	m_bHealOutsideFriendly = kResults.GetBool("HealOutsideFriendly");
	m_bHillsDoubleMove = kResults.GetBool("HillsDoubleMove");
	m_bIgnoreTerrainCost = kResults.GetBool("IgnoreTerrainCost");
	m_bRoughTerrainEndsTurn = kResults.GetBool("RoughTerrainEndsTurn");
	m_bHoveringUnit = kResults.GetBool("HoveringUnit");
	m_bCoastalWalk = kResults.GetBool("CoastalWalk");
	m_bFlatMovementCost = kResults.GetBool("FlatMovementCost");
	m_bCanMoveImpassable = kResults.GetBool("CanMoveImpassable");
	m_bNoCapture = kResults.GetBool("NoCapture");
	m_bOnlyDefensive = kResults.GetBool("OnlyDefensive");
	m_bNoDefensiveBonus = kResults.GetBool("NoDefensiveBonus");
	m_bHiddenNationality = kResults.GetBool("HiddenNationality");
	m_bAlwaysHostile = kResults.GetBool("AlwaysHostile");
	m_bNoRevealMap = kResults.GetBool("NoRevealMap");
	m_bRecon = kResults.GetBool("Recon");
	m_bCanMoveAllTerrain = kResults.GetBool("CanMoveAllTerrain");
	m_bCanMoveAfterAttacking = kResults.GetBool("CanMoveAfterAttacking");
	m_bAirSweepCapable = kResults.GetBool("AirSweepCapable");
	m_bAllowsEmbarkation = kResults.GetBool("AllowsEmbarkation");
	m_bRangeAttackIgnoreLOS = kResults.GetBool("RangeAttackIgnoreLOS");
	m_bFreeMaintenance = kResults.GetBool("FreeMaintenance");
	m_bFreePillageMoves = kResults.GetBool("FreePillageMoves");
	m_bHealOnPillage = kResults.GetBool("HealOnPillage");
	m_bHealIfDefeatExcludesBarbarians = kResults.GetBool("HealIfDestroyExcludesBarbarians");
	m_bCityAttackOnly = kResults.GetBool("CityAttackOnly");
	m_bCaptureDefeatedEnemy = kResults.GetBool("CaptureDefeatedEnemy");
	m_bIgnoreGreatGeneralBenefit = kResults.GetBool("IgnoreGreatGeneralBenefit");
	m_bIgnoreZOC = kResults.GetBool("IgnoreZOC");
	m_bHasPostCombatPromotions = kResults.GetBool("HasPostCombatPromotions");
	m_bPostCombatPromotionsExclusive = kResults.GetBool("PostCombatPromotionsExclusive");
	m_bSapper = kResults.GetBool("Sapper");
	m_bCanHeavyCharge = kResults.GetBool("HeavyCharge");
	m_iVisibilityChange = kResults.GetInt("VisibilityChange");
	m_iMovesChange = kResults.GetInt("MovesChange");
	m_iMoveDiscountChange = kResults.GetInt("MoveDiscountChange");
	m_iRangeChange = kResults.GetInt("RangeChange");
	m_iRangedAttackModifier = kResults.GetInt("RangedAttackModifier");
	m_iInterceptionCombatModifier = kResults.GetInt("InterceptionCombatModifier");
	m_iInterceptionDefenseDamageModifier = kResults.GetInt("InterceptionDefenseDamageModifier");
	m_iAirSweepCombatModifier = kResults.GetInt("AirSweepCombatModifier");
	m_iInterceptChanceChange = kResults.GetInt("InterceptChanceChange");
	m_iNumInterceptionChange = kResults.GetInt("NumInterceptionChange");
	m_iEvasionChange = kResults.GetInt("EvasionChange");
	m_iCargoChange = kResults.GetInt("CargoChange");
	m_iEnemyHealChange = kResults.GetInt("EnemyHealChange");
	m_iNeutralHealChange = kResults.GetInt("NeutralHealChange");
	m_iFriendlyHealChange = kResults.GetInt("FriendlyHealChange");
	m_iSameTileHealChange = kResults.GetInt("SameTileHealChange");
	m_iAdjacentTileHealChange = kResults.GetInt("AdjacentTileHealChange");
	m_iEnemyDamageChance = kResults.GetInt("EnemyDamageChance");
	m_iNeutralDamageChance = kResults.GetInt("NeutralDamageChance");
	m_iEnemyDamage = kResults.GetInt("EnemyDamage");
	m_iNeutralDamage = kResults.GetInt("NeutralDamage");
	m_iCombatPercent = kResults.GetInt("CombatPercent");
	m_iMeleeCombatPercent = kResults.GetInt("MeleeCombatPercent");
	m_iCityAttackPercent = kResults.GetInt("CityAttack");
	m_iCityDefensePercent = kResults.GetInt("CityDefense");
	m_iRangedDefenseMod = kResults.GetInt("RangedDefenseMod");
	m_iHillsAttackPercent = kResults.GetInt("HillsAttack");
	m_iHillsDefensePercent = kResults.GetInt("HillsDefense");
	m_iOpenAttackPercent = kResults.GetInt("OpenAttack");
	m_iOpenRangedAttackMod = kResults.GetInt("OpenRangedAttackMod");
	m_iRoughAttackPercent = kResults.GetInt("RoughAttack");
	m_iRoughRangedAttackMod = kResults.GetInt("RoughRangedAttackMod");
	m_iAttackFortifiedMod = kResults.GetInt("AttackFortifiedMod");
	m_iAttackUnfortifiedMod = kResults.GetInt("AttackUnfortifiedMod");
	m_iAttackWoundedMod = kResults.GetInt("AttackWoundedMod");
	m_iFlankAttackModifier = kResults.GetInt("FlankAttackModifier");
	m_iNearbyEnemyCombatMod = kResults.GetInt("NearbyEnemyCombatMod");
	m_iNearbyEnemyCombatRange = kResults.GetInt("NearbyEnemyCombatRange");
	m_iOpenDefensePercent = kResults.GetInt("OpenDefense");
	m_iRoughDefensePercent = kResults.GetInt("RoughDefense");
	m_iExtraAttacks = kResults.GetInt("ExtraAttacks");
	m_bGreatGeneral = kResults.GetBool("GreatGeneral");
	m_bGreatAdmiral = kResults.GetBool("GreatAdmiral");
	m_iGreatGeneralModifier = kResults.GetInt("GreatGeneralModifier");
	m_bGreatGeneralReceivesMovement = kResults.GetBool("GreatGeneralReceivesMovement");
	m_iGreatGeneralCombatModifier = kResults.GetInt("GreatGeneralCombatModifier");
	m_iFriendlyLandsModifier = kResults.GetInt("FriendlyLandsModifier");
	m_iFriendlyLandsAttackModifier = kResults.GetInt("FriendlyLandsAttackModifier");
	m_iOutsideFriendlyLandsModifier = kResults.GetInt("OutsideFriendlyLandsModifier");
	m_iUpgradeDiscount = kResults.GetInt("UpgradeDiscount");
	m_iExperiencePercent = kResults.GetInt("ExperiencePercent");
	m_iAdjacentMod = kResults.GetInt("AdjacentMod");
	m_iAttackMod = kResults.GetInt("AttackMod");
	m_iDefenseMod = kResults.GetInt("DefenseMod");
	m_iDropRange = kResults.GetInt("DropRange");
	m_iExtraNavalMoves = kResults.GetInt("ExtraNavalMovement");
	m_iExtraWorkerMoves = kResults.GetInt("ExtraWorkerMovement");
	m_iHPHealedIfDefeatEnemy = kResults.GetInt("HPHealedIfDestroyEnemy");
	m_iEraOfProsperityValueFromKills = kResults.GetInt("EraOfProsperityValueFromKills");
	m_iExtraWithdrawal = kResults.GetInt("ExtraWithdrawal");
	m_iEmbarkExtraVisibility = kResults.GetInt("EmbarkExtraVisibility");
	m_iEmbarkDefenseModifier = kResults.GetInt("EmbarkDefenseModifier");
	m_iCapitalDefenseModifier = kResults.GetInt("CapitalDefenseModifier");
	m_iCapitalDefenseFalloff = kResults.GetInt("CapitalDefenseFalloff");
	m_iCityAttackPlunderModifier = kResults.GetInt("CityAttackPlunderModifier");
	m_iReligiousStrengthLossRivalTerritory = kResults.GetInt("ReligiousStrengthLossRivalTerritory");
	m_iInstantHealAmount = kResults.GetInt("InstantHealAmount");
	m_iTradeMissionInfluenceModifier = kResults.GetInt("TradeMissionInfluenceModifier");
	m_iTradeMissionGoldModifier = kResults.GetInt("TradeMissionGoldModifier");
	m_iMiasmaFlatHealthModifier = kResults.GetInt("MiasmaFlatHealthMod");
	m_iOrbitalCoverageRadiusChange = kResults.GetInt("OrbitalCoverageRadiusChange");
	m_bMiasmaImmune = kResults.GetBool("MiasmaImmune");
	m_iAlienRepelRangeChange = kResults.GetInt("AlienRepelRangeChange");
	m_bMiasmaImmuneWorkers = kResults.GetBool("MiasmaImmuneWorkers");
	m_iCivHealthBonusMinModifier = kResults.GetInt("CivHealthBonusMinModifier");
	m_iCivHealthBonusMaxModifier = kResults.GetInt("CivHealthBonusMaxModifier");
	m_iCivHealthBonusMinHealth = kResults.GetInt("CivHealthBonusMinHealth");
	m_iCivHealthBonusMaxHealth = kResults.GetInt("CivHealthBonusMaxHealth");
	m_iLayerAnimationPath = GC.getInfoTypeForString(kResults.GetText("LayerAnimationPath"), true);
	m_iTechPrereq = GC.getInfoTypeForString(kResults.GetText("TechPrereq"), true);
	m_iArtifactRewardPrereq = GC.getInfoTypeForString(kResults.GetText("ArtifactRewardPrereq"), true);
	m_iExactLevelPrereq = kResults.GetInt("ExactLevelPrereq");
	m_iInvisibleType = GC.getInfoTypeForString(kResults.GetText("Invisible"), true);
	m_iSeeInvisibleType = GC.getInfoTypeForString(kResults.GetText("SeeInvisible"), true);
	m_iPrereqPromotion = GC.getInfoTypeForString(kResults.GetText("PromotionPrereq"), true);
	m_iPrereqOrPromotion1 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr1"), true);
	m_iPrereqOrPromotion2 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr2"), true);
	m_iPrereqOrPromotion3 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr3"), true);
	m_iPrereqOrPromotion4 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr4"), true);
	m_iPrereqOrPromotion5 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr5"), true);
	m_iPrereqOrPromotion6 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr6"), true);
	m_iPrereqOrPromotion7 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr7"), true);
	m_iPrereqOrPromotion8 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr8"), true);
	m_iPrereqOrPromotion9 = GC.getInfoTypeForString(kResults.GetText("PromotionPrereqOr9"), true);
	//Arrays
	const int iNumUnitClasses = kUtility.MaxRows("UnitClasses");
	const int iNumTerrains = PromotionNumTerrain(&GC);
	const int iNumFeatures = PromotionNumFeature(&GC);
	const int iNumDomains = kUtility.MaxRows("Domains");
	const int iNumUnitCombatClasses = kUtility.MaxRows("UnitCombatInfos");
	const int iNumUnitTypes = kUtility.MaxRows("Units");

	const char* szPromotionType = GetType();

	//UnitPromotions_Terrains
	{
		kUtility.InitializeArray(m_piTerrainAttackPercent, iNumTerrains, 0);
		kUtility.InitializeArray(m_piTerrainDefensePercent, iNumTerrains, 0);
		kUtility.InitializeArray(m_piTerrainPassableTech, iNumTerrains, NO_TECH);
		kUtility.InitializeArray(m_pbTerrainDoubleMove, iNumTerrains, false);
		kUtility.InitializeArray(m_pbTerrainImpassable, iNumTerrains, false);

		std::string sqlKey = "UnitPromotions_Terrains";
		Database::Results* pResults = kUtility.GetResults(sqlKey);
		if(pResults == NULL)
		{
			const char* szSQL = "select Terrains.ID as TerrainID, coalesce(Technologies.ID, -1) as PassableTechID, UnitPromotions_Terrains.* from UnitPromotions_Terrains inner join Terrains on TerrainType = Terrains.Type left join Technologies on PassableTech = Technologies.Type where PromotionType = ?";
			pResults = kUtility.PrepareResults(sqlKey, szSQL);
		}

		CvAssert(pResults);
		if(!pResults) return false;

		PromotionBind(pResults, 1, szPromotionType, true);

		while(pResults->Step())
		{
			const int iTerrainID = pResults->GetInt("TerrainID");
			CvAssert(iTerrainID > -1 && iTerrainID < iNumTerrains);

			const int iTerrainAttack = pResults->GetInt("Attack");
			m_piTerrainAttackPercent[iTerrainID] = iTerrainAttack;

			const int iTerrainDefense = pResults->GetInt("Defense");
			m_piTerrainDefensePercent[iTerrainID] = iTerrainDefense;

			const bool bDoubleMove = pResults->GetBool("DoubleMove");
			m_pbTerrainDoubleMove[iTerrainID] = bDoubleMove;

			const bool bImpassable = pResults->GetBool("Impassable");
			m_pbTerrainImpassable[iTerrainID] = bImpassable;

			const int iPassableTechID = pResults->GetInt("PassableTechID");
			m_piTerrainPassableTech[iTerrainID] = iPassableTechID;
		}
	}

	//UnitPromotions_Features
	{
		kUtility.InitializeArray(m_piFeatureAttackPercent, iNumFeatures, 0);
		kUtility.InitializeArray(m_piFeatureDefensePercent, iNumFeatures, 0);
		kUtility.InitializeArray(m_piFeaturePassableTech, iNumFeatures, NO_TECH);
		kUtility.InitializeArray(m_pbFeatureDoubleMove, iNumFeatures, false);
		kUtility.InitializeArray(m_pbFeatureImpassable, iNumFeatures, false);

		std::string sqlKey = "UnitPromotions_Features";
		Database::Results* pResults = kUtility.GetResults(sqlKey);
		if(pResults == NULL)
		{
			const char* szSQL = "select Features.ID as FeatureID, coalesce(Technologies.ID, -1) as PassableTechID, UnitPromotions_Features.* from UnitPromotions_Features inner join Features on FeatureType = Features.Type left join Technologies on PassableTech = Technologies.Type where PromotionType = ?";
			pResults = kUtility.PrepareResults(sqlKey, szSQL);
		}

		CvAssert(pResults);
		if(!pResults) return false;

		PromotionBind(pResults, 1, szPromotionType, true);

		while(pResults->Step())
		{
			const int iFeatureID = pResults->GetInt("FeatureID");
			CvAssert(iFeatureID > -1 && iFeatureID < iNumFeatures);

			const int iFeatureAttack = pResults->GetInt("Attack");
			m_piFeatureAttackPercent[iFeatureID] = iFeatureAttack;

			const int iFeatureDefense = pResults->GetInt("Defense");
			m_piFeatureDefensePercent[iFeatureID] = iFeatureDefense;

			const bool bDoubleMove = pResults->GetBool("DoubleMove");
			m_pbFeatureDoubleMove[iFeatureID] = bDoubleMove;

			const bool bImpassable = pResults->GetBool("Impassable");
			m_pbFeatureImpassable[iFeatureID] = bImpassable;

			const int iPassableTech = pResults->GetInt("PassableTechID");
			m_piFeaturePassableTech[iFeatureID] = iPassableTech;
		}
	}

	//UnitPromotions_UnitClasses
	{
		kUtility.InitializeArray(m_piUnitClassModifierPercent, iNumUnitClasses, 0);
		kUtility.InitializeArray(m_piUnitClassAttackModifier, iNumUnitClasses, 0);
		kUtility.InitializeArray(m_piUnitClassDefenseModifier, iNumUnitClasses, 0);

		std::string sqlKey = "UnitPromotions_UnitClasses";
		Database::Results* pResults = kUtility.GetResults(sqlKey);
		if(pResults == NULL)
		{
			const char* szSQL = "select UnitClasses.ID, Modifier, Attack, Defense from UnitPromotions_UnitClasses inner join UnitClasses on UnitClassType = UnitClasses.Type where PromotionType = ?";
			pResults = kUtility.PrepareResults(sqlKey, szSQL);
		}

		CvAssert(pResults);
		if(!pResults) return false;

		PromotionBind(pResults, 1, szPromotionType, true);

		while(pResults->Step())
		{
			const int iUnitClassID = pResults->GetInt(0);
			CvAssert(iUnitClassID > -1 && iUnitClassID  < iNumUnitClasses);

			const int iModifier = pResults->GetInt("Modifier");
			m_piUnitClassModifierPercent[iUnitClassID] = iModifier;

			const int iAttack = pResults->GetInt("Attack");
			m_piUnitClassAttackModifier[iUnitClassID] = iAttack;

			const int iDefense = pResults->GetInt("Defense");
			m_piUnitClassDefenseModifier[iUnitClassID] = iDefense;
		}

		pResults->Reset();
	}

	//UnitPromotions_Domains
	{
		kUtility.InitializeArray(m_piDomainModifierPercent, 6, 0);

		std::string sqlKey = "m_piDomainModifierPercent";
		Database::Results* pResults = kUtility.GetResults(sqlKey);
		if(pResults == NULL)
		{
			const char* szSQL = "select Domains.ID, Modifier from UnitPromotions_Domains inner join Domains on DomainType = Domains.Type where PromotionType = ?;";
			pResults = kUtility.PrepareResults(sqlKey, szSQL);
		}

		CvAssert(pResults);
		if(!pResults) return false;

		PromotionBind(pResults, 1, szPromotionType, true);

		while(pResults->Step())
		{
			const int iDomainID = pResults->GetInt(0);
			CvAssert(iDomainID > -1 && iDomainID < iNumDomains);

			const int iDomainMod = pResults->GetInt(1);
			if (iDomainID > -1 && iDomainID < 6)
				m_piDomainModifierPercent[iDomainID] = iDomainMod;
		}

		pResults->Reset();
	}

	//UnitPromotions_UnitCombatMods
	{
		kUtility.InitializeArray(m_piUnitCombatModifierPercent, iNumUnitCombatClasses, 0);

		std::string sqlKey = "m_piUnitCombatModifierPercent";
		Database::Results* pResults = kUtility.GetResults(sqlKey);
		if(pResults == NULL)
		{
			const char* szSQL = "select UnitCombatInfos.ID, Modifier from UnitPromotions_UnitCombatMods inner join UnitCombatInfos on UnitCombatInfos.Type = UnitCombatType where PromotionType = ?;";
			pResults = kUtility.PrepareResults(sqlKey, szSQL);
		}

		CvAssert(pResults);
		if(!pResults) return false;

		PromotionBind(pResults, 1, szPromotionType, true);

		while(pResults->Step())
		{
			const int iUnitCombatID = pResults->GetInt(0);
			CvAssert(iUnitCombatID > -1 && iUnitCombatID < iNumUnitCombatClasses);

			const int iUnitCombatMod = pResults->GetInt(1);
			m_piUnitCombatModifierPercent[iUnitCombatID] = iUnitCombatMod;
		}

		pResults->Reset();
	}

	//UnitPromotions_UnitCombats
	{
		kUtility.InitializeArray(m_pbUnitCombat, iNumUnitCombatClasses, false);

		std::string sqlKey = "m_pbUnitCombat";
		Database::Results* pResults = kUtility.GetResults(sqlKey);
		if(pResults == NULL)
		{
			const char* szSQL = "select UnitCombatInfos.ID from UnitPromotions_UnitCombats inner join UnitCombatInfos On UnitCombatInfos.Type = UnitCombatType where PromotionType = ?";
			pResults = kUtility.PrepareResults(sqlKey, szSQL);
		}

		CvAssert(pResults);
		if(!pResults) return false;

		PromotionBind(pResults, 1, szPromotionType, true);

		while(pResults->Step())
		{
			const int iUnitCombatInfoID = pResults->GetInt(0);
			CvAssert(iUnitCombatInfoID < iNumUnitCombatClasses);

			m_pbUnitCombat[iUnitCombatInfoID] = true;
		}

		pResults->Reset();
	}

	//UnitPromotions_CivilianUnitType
	{
		kUtility.InitializeArray(m_pbCivilianUnitType, iNumUnitTypes, false);

		std::string sqlKey = "m_pbCivilianUnitType";
		Database::Results* pResults = kUtility.GetResults(sqlKey);
		if(pResults == NULL)
		{
			const char* szSQL = "select Units.ID from UnitPromotions_CivilianUnitType inner join Units On Units.Type = UnitType where PromotionType = ?";
			pResults = kUtility.PrepareResults(sqlKey, szSQL);
		}

		CvAssert(pResults);
		if(!pResults) return false;

		PromotionBind(pResults, 1, szPromotionType, true);

		while(pResults->Step())
		{
			const int iUnit = (UnitTypes)pResults->GetInt(0);
			CvAssert(iUnit < iNumUnitTypes);

			m_pbCivilianUnitType[iUnit] = true;
		}

		pResults->Reset();
	}

	kUtility.PopulateArrayByExistence(m_pbPostCombatRandomPromotion,
		"UnitPromotions",
		"UnitPromotions_PostCombatRandomPromotion",
		"NewPromotion",
		"PromotionType",
		szPromotionType);

	return true;
}

/// Accessor: The granny animation index used to indicate that a unit has leveled up
int CvPromotionEntry::GetLayerAnimationPath() const
{
	return m_iLayerAnimationPath;
}

int CvPromotionEntry::GetPrereqPromotion() const
{
	return m_iPrereqPromotion;
}

void CvPromotionEntry::SetPrereqPromotion(int value)
{
	m_iPrereqPromotion = value;
}

int CvPromotionEntry::GetPrereqOrPromotion1() const
{
	return m_iPrereqOrPromotion1;
}

void CvPromotionEntry::SetPrereqOrPromotion1(int value)
{
	m_iPrereqOrPromotion1 = value;
}

int CvPromotionEntry::GetPrereqOrPromotion2() const
{
	return m_iPrereqOrPromotion2;
}

void CvPromotionEntry::SetPrereqOrPromotion2(int value)
{
	m_iPrereqOrPromotion2 = value;
}

int CvPromotionEntry::GetPrereqOrPromotion3() const
{
	return m_iPrereqOrPromotion3;
}

void CvPromotionEntry::SetPrereqOrPromotion3(int value)
{
	m_iPrereqOrPromotion3 = value;
}

int CvPromotionEntry::GetPrereqOrPromotion4() const
{
	return m_iPrereqOrPromotion4;
}

void CvPromotionEntry::SetPrereqOrPromotion4(int value)
{
	m_iPrereqOrPromotion4 = value;
}

int CvPromotionEntry::GetPrereqOrPromotion5() const
{
	return m_iPrereqOrPromotion5;
}

void CvPromotionEntry::SetPrereqOrPromotion5(int value)
{
	m_iPrereqOrPromotion5 = value;
}

int CvPromotionEntry::GetPrereqOrPromotion6() const
{
	return m_iPrereqOrPromotion6;
}

void CvPromotionEntry::SetPrereqOrPromotion6(int value)
{
	m_iPrereqOrPromotion6 = value;
}

int CvPromotionEntry::GetPrereqOrPromotion7() const
{
	return m_iPrereqOrPromotion7;
}

void CvPromotionEntry::SetPrereqOrPromotion7(int value)
{
	m_iPrereqOrPromotion7 = value;
}

int CvPromotionEntry::GetPrereqOrPromotion8() const
{
	return m_iPrereqOrPromotion8;
}

void CvPromotionEntry::SetPrereqOrPromotion8(int value)
{
	m_iPrereqOrPromotion8 = value;
}

int CvPromotionEntry::GetPrereqOrPromotion9() const
{
	return m_iPrereqOrPromotion9;
}

void CvPromotionEntry::SetPrereqOrPromotion9(int value)
{
	m_iPrereqOrPromotion9 = value;
}

int CvPromotionEntry::GetTechPrereq() const
{
	return m_iTechPrereq;
}

int CvPromotionEntry::GetArtifactRewardPrereq() const
{
	return m_iArtifactRewardPrereq;
}

int CvPromotionEntry::GetExactLevelPrereq() const
{
	return m_iExactLevelPrereq;
}

int CvPromotionEntry::GetInvisibleType() const
{
	return m_iInvisibleType;
}

int CvPromotionEntry::GetSeeInvisibleType() const
{
	return m_iSeeInvisibleType;
}

int CvPromotionEntry::GetVisibilityChange() const
{
	return m_iVisibilityChange;
}

int CvPromotionEntry::GetMovesChange() const
{
	return m_iMovesChange;
}

int CvPromotionEntry::GetMoveDiscountChange() const
{
	return m_iMoveDiscountChange;
}

int CvPromotionEntry::GetRangeChange() const
{
	return m_iRangeChange;
}

int CvPromotionEntry::GetRangedAttackModifier() const
{
	return m_iRangedAttackModifier;
}

int CvPromotionEntry::GetInterceptionCombatModifier() const
{
	return m_iInterceptionCombatModifier;
}

int CvPromotionEntry::GetInterceptionDefenseDamageModifier() const
{
	return m_iInterceptionDefenseDamageModifier;
}

int CvPromotionEntry::GetAirSweepCombatModifier() const
{
	return m_iAirSweepCombatModifier;
}

int CvPromotionEntry::GetInterceptChanceChange() const
{
	return m_iInterceptChanceChange;
}

int CvPromotionEntry::GetNumInterceptionChange() const
{
	return m_iNumInterceptionChange;
}

int CvPromotionEntry::GetEvasionChange() const
{
	return m_iEvasionChange;
}

int CvPromotionEntry::GetCargoChange() const
{
	return m_iCargoChange;
}

int CvPromotionEntry::GetEnemyHealChange() const
{
	return m_iEnemyHealChange;
}

int CvPromotionEntry::GetNeutralHealChange() const
{
	return m_iNeutralHealChange;
}

int CvPromotionEntry::GetFriendlyHealChange() const
{
	return m_iFriendlyHealChange;
}

int CvPromotionEntry::GetSameTileHealChange() const
{
	return m_iSameTileHealChange;
}

int CvPromotionEntry::GetAdjacentTileHealChange() const
{
	return m_iAdjacentTileHealChange;
}

int CvPromotionEntry::GetEnemyDamageChance() const
{
	return m_iEnemyDamageChance;
}

int CvPromotionEntry::GetNeutralDamageChance() const
{
	return m_iNeutralDamageChance;
}

int CvPromotionEntry::GetEnemyDamage() const
{
	return m_iEnemyDamage;
}

int CvPromotionEntry::GetNeutralDamage() const
{
	return m_iNeutralDamage;
}

int CvPromotionEntry::GetCombatPercent() const
{
	return m_iCombatPercent;
}

int CvPromotionEntry::GetMeleeCombatPercent() const
{
	return m_iMeleeCombatPercent;
}

int CvPromotionEntry::GetCityAttackPercent() const
{
	return m_iCityAttackPercent;
}

int CvPromotionEntry::GetCityDefensePercent() const
{
	return m_iCityDefensePercent;
}

int CvPromotionEntry::GetRangedDefenseMod() const
{
	return m_iRangedDefenseMod;
}

int CvPromotionEntry::GetHillsAttackPercent() const
{
	return m_iHillsAttackPercent;
}

int CvPromotionEntry::GetHillsDefensePercent() const
{
	return m_iHillsDefensePercent;
}

int CvPromotionEntry::GetOpenAttackPercent() const
{
	return m_iOpenAttackPercent;
}

int CvPromotionEntry::GetOpenRangedAttackMod() const
{
	return m_iOpenRangedAttackMod;
}

int CvPromotionEntry::GetRoughAttackPercent() const
{
	return m_iRoughAttackPercent;
}

int CvPromotionEntry::GetRoughRangedAttackMod() const
{
	return m_iRoughRangedAttackMod;
}

int CvPromotionEntry::GetAttackFortifiedMod() const
{
	return m_iAttackFortifiedMod;
}

int CvPromotionEntry::GetAttackUnfortifiedMod() const
{
	return m_iAttackUnfortifiedMod;
}

int CvPromotionEntry::GetAttackWoundedMod() const
{
	return m_iAttackWoundedMod;
}

int CvPromotionEntry::GetFlankAttackModifier() const
{
	return m_iFlankAttackModifier;
}

int CvPromotionEntry::GetNearbyEnemyCombatMod() const
{
	return m_iNearbyEnemyCombatMod;
}

int CvPromotionEntry::GetNearbyEnemyCombatRange() const
{
	return m_iNearbyEnemyCombatRange;
}

int CvPromotionEntry::GetOpenDefensePercent() const
{
	return m_iOpenDefensePercent;
}

int CvPromotionEntry::GetRoughDefensePercent() const
{
	return m_iRoughDefensePercent;
}

int CvPromotionEntry::GetExtraAttacks() const
{
	return m_iExtraAttacks;
}

bool CvPromotionEntry::IsGreatGeneral() const
{
	return m_bGreatGeneral;
}

bool CvPromotionEntry::IsGreatAdmiral() const
{
	return m_bGreatAdmiral;
}

int CvPromotionEntry::GetGreatGeneralModifier() const
{
	return m_iGreatGeneralModifier;
}

bool CvPromotionEntry::IsGreatGeneralReceivesMovement() const
{
	return m_bGreatGeneralReceivesMovement;
}

int CvPromotionEntry::GetGreatGeneralCombatModifier() const
{
	return m_iGreatGeneralCombatModifier;
}

int CvPromotionEntry::GetFriendlyLandsModifier() const
{
	return m_iFriendlyLandsModifier;
}

int CvPromotionEntry::GetFriendlyLandsAttackModifier() const
{
	return m_iFriendlyLandsAttackModifier;
}

int CvPromotionEntry::GetOutsideFriendlyLandsModifier() const
{
	return m_iOutsideFriendlyLandsModifier;
}

int CvPromotionEntry::GetCommandType() const
{
	return m_iCommandType;
}

void CvPromotionEntry::SetCommandType(int value)
{
	m_iCommandType = value;
}

int CvPromotionEntry::GetUpgradeDiscount() const
{
	return m_iUpgradeDiscount;
}

int CvPromotionEntry::GetExperiencePercent() const
{
	return m_iExperiencePercent;
}

int CvPromotionEntry::GetAdjacentMod() const
{
	return m_iAdjacentMod;
}

int CvPromotionEntry::GetAttackMod() const
{
	return m_iAttackMod;
}

int CvPromotionEntry::GetDefenseMod() const
{
	return m_iDefenseMod;
}

int CvPromotionEntry::GetDropRange() const
{
	return m_iDropRange;
}

int CvPromotionEntry::GetExtraNavalMoves() const
{
	return m_iExtraNavalMoves;
}

int CvPromotionEntry::GetExtraWorkerMoves() const
{
	return m_iExtraWorkerMoves;
}

int CvPromotionEntry::GetHPHealedIfDefeatEnemy() const
{
	return m_iHPHealedIfDefeatEnemy;
}

int CvPromotionEntry::GetEraOfProsperityValueFromKills() const
{
	return m_iEraOfProsperityValueFromKills;
}

int CvPromotionEntry::GetExtraWithdrawal() const
{
	return m_iExtraWithdrawal;
}

int CvPromotionEntry::GetEmbarkExtraVisibility() const
{
	return m_iEmbarkExtraVisibility;
}

int CvPromotionEntry::GetEmbarkDefenseModifier() const
{
	return m_iEmbarkDefenseModifier;
}

int CvPromotionEntry::GetCapitalDefenseModifier() const
{
	return m_iCapitalDefenseModifier;
}

int CvPromotionEntry::GetCapitalDefenseFalloff() const
{
	return m_iCapitalDefenseFalloff;
}

int CvPromotionEntry::GetCityAttackPlunderModifier() const
{
	return m_iCityAttackPlunderModifier;
}

int CvPromotionEntry::GetReligiousStrengthLossRivalTerritory() const
{
	return m_iReligiousStrengthLossRivalTerritory;
}

bool CvPromotionEntry::IsInstantHeal() const
{
	return m_iInstantHealAmount > 0;
}

int CvPromotionEntry::GetInstantHealAmount() const
{
	return m_iInstantHealAmount;
}

int CvPromotionEntry::GetTradeMissionInfluenceModifier() const
{
	return m_iTradeMissionInfluenceModifier;
}

int CvPromotionEntry::GetTradeMissionGoldModifier() const
{
	return m_iTradeMissionGoldModifier;
}

int CvPromotionEntry::GetMiasmaFlatHealthModifier() const
{
	return m_iMiasmaFlatHealthModifier;
}

int CvPromotionEntry::GetOrbitalCoverageRadiusChange() const
{
	return m_iOrbitalCoverageRadiusChange;
}

int CvPromotionEntry::GetAlienRepelRangeChange() const
{
	return m_iAlienRepelRangeChange;
}

int CvPromotionEntry::GetCivHealthBonusMinModifier() const
{
	return m_iCivHealthBonusMinModifier;
}

int CvPromotionEntry::GetCivHealthBonusMaxModifier() const
{
	return m_iCivHealthBonusMaxModifier;
}

int CvPromotionEntry::GetCivHealthBonusMinHealth() const
{
	return m_iCivHealthBonusMinHealth;
}

int CvPromotionEntry::GetCivHealthBonusMaxHealth() const
{
	return m_iCivHealthBonusMaxHealth;
}

bool CvPromotionEntry::GetMiasmaImmune() const
{
	return m_bMiasmaImmune;
}

bool CvPromotionEntry::GetMiasmaImmuneWorkers() const
{
	return m_bMiasmaImmuneWorkers;
}

bool CvPromotionEntry::IsCannotBeChosen() const
{
	return m_bCannotBeChosen;
}

bool CvPromotionEntry::IsLostWithUpgrade() const
{
	return m_bLostWithUpgrade;
}

bool CvPromotionEntry::IsNotWithUpgrade() const
{
	return m_bNotWithUpgrade;
}

bool CvPromotionEntry::IsLeader() const
{
	return m_bLeader;
}

bool CvPromotionEntry::IsBlitz() const
{
	return m_bBlitz;
}

bool CvPromotionEntry::IsAmphibiousAttack() const
{
	return m_bAmphibiousAttack;
}

bool CvPromotionEntry::IsRiver() const
{
	return m_bRiver;
}

bool CvPromotionEntry::IsEnemyRoute() const
{
	return m_bEnemyRoute;
}

bool CvPromotionEntry::IsRivalTerritory() const
{
	return m_bRivalTerritory;
}

bool CvPromotionEntry::IsMustSetUpToRangedAttack() const
{
	return m_bMustSetUpToRangedAttack;
}

bool CvPromotionEntry::IsRangedSupportFire() const
{
	return m_bRangedSupportFire;
}

bool CvPromotionEntry::IsAlwaysHeal() const
{
	return m_bAlwaysHeal;
}

bool CvPromotionEntry::IsHealOutsideFriendly() const
{
	return m_bHealOutsideFriendly;
}

bool CvPromotionEntry::IsHillsDoubleMove() const
{
	return m_bHillsDoubleMove;
}

bool CvPromotionEntry::IsIgnoreTerrainCost() const
{
	return m_bIgnoreTerrainCost;
}

bool CvPromotionEntry::IsRoughTerrainEndsTurn() const
{
	return m_bRoughTerrainEndsTurn;
}

bool CvPromotionEntry::IsHoveringUnit() const
{
	return m_bHoveringUnit;
}

bool CvPromotionEntry::IsCoastalWalk() const
{
	return m_bCoastalWalk;
}

bool CvPromotionEntry::IsFlatMovementCost() const
{
	return m_bFlatMovementCost;
}

bool CvPromotionEntry::IsCanMoveImpassable() const
{
	return m_bCanMoveImpassable;
}

bool CvPromotionEntry::IsNoCapture() const
{
	return m_bNoCapture;
}

bool CvPromotionEntry::IsOnlyDefensive() const
{
	return m_bOnlyDefensive;
}

bool CvPromotionEntry::IsNoDefensiveBonus() const
{
	return m_bNoDefensiveBonus;
}

bool CvPromotionEntry::IsHiddenNationality() const
{
	return m_bHiddenNationality;
}

bool CvPromotionEntry::IsAlwaysHostile() const
{
	return m_bAlwaysHostile;
}

bool CvPromotionEntry::IsNoRevealMap() const
{
	return m_bNoRevealMap;
}

bool CvPromotionEntry::IsRecon() const
{
	return m_bRecon;
}

bool CvPromotionEntry::CanMoveAllTerrain() const
{
	return m_bCanMoveAllTerrain;
}

bool CvPromotionEntry::IsCanMoveAfterAttacking() const
{
	return m_bCanMoveAfterAttacking;
}

bool CvPromotionEntry::IsAirSweepCapable() const
{
	return m_bAirSweepCapable;
}

bool CvPromotionEntry::IsAllowsEmbarkation() const
{
	return m_bAllowsEmbarkation;
}

bool CvPromotionEntry::IsRangeAttackIgnoreLOS() const
{
	return m_bRangeAttackIgnoreLOS;
}

bool CvPromotionEntry::IsFreeMaintenance() const
{
	return m_bFreeMaintenance;
}

bool CvPromotionEntry::IsFreePillageMoves() const
{
	return m_bFreePillageMoves;
}

bool CvPromotionEntry::IsHealOnPillage() const
{
	return m_bHealOnPillage;
}

bool CvPromotionEntry::IsHealIfDefeatExcludeBarbarians() const
{
	return m_bHealIfDefeatExcludesBarbarians;
}

bool CvPromotionEntry::IsCityAttackOnly() const
{
	return m_bCityAttackOnly;
}

bool CvPromotionEntry::IsCaptureDefeatedEnemy() const
{
	return m_bCaptureDefeatedEnemy;
}

bool CvPromotionEntry::IsIgnoreGreatGeneralBenefit() const
{
	return m_bIgnoreGreatGeneralBenefit;
}

bool CvPromotionEntry::IsIgnoreZOC() const
{
	return m_bIgnoreZOC;
}

bool CvPromotionEntry::IsSapper() const
{
	return m_bSapper;
}

bool CvPromotionEntry::IsCanHeavyCharge() const
{
	return m_bCanHeavyCharge;
}

bool CvPromotionEntry::HasPostCombatPromotions() const
{
	return m_bHasPostCombatPromotions;
}

bool CvPromotionEntry::ArePostCombatPromotionsExclusive() const
{
	return m_bPostCombatPromotionsExclusive;
}

const char* CvPromotionEntry::GetSound() const
{
	return m_strSound;
}

/// Set the sound to be played when the promotion is gained
// TODO: Phase1 audit CvPromotionEntry::SetSound(char const*): UNVERIFIED; BE/object instructions 14/14; Civ5 changed/new UNVERIFIED.
void CvPromotionEntry::SetSound(const char* szVal)
{
	m_strSound = szVal;
}

// ARRAYS

/// Returns an array of bonuses when attacking a tile of a given terrain
// TODO: Phase1 audit CvPromotionEntry::GetTerrainAttackPercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetTerrainAttackPercent(int i) const
{
	CvAssertMsg(i < PromotionNumTerrain(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumTerrain(&GC) && m_piTerrainAttackPercent)
	{
		return m_piTerrainAttackPercent[i];
	}

	return -1;
}

/// Returns an array of bonuses when defending a tile of a given terrain
// TODO: Phase1 audit CvPromotionEntry::GetTerrainDefensePercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetTerrainDefensePercent(int i) const
{
	CvAssertMsg(i < PromotionNumTerrain(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumTerrain(&GC) && m_piTerrainDefensePercent)
	{
		return m_piTerrainDefensePercent[i];
	}

	return-1;
}

/// Returns an array of bonuses when attacking a tile with a terrain feature
// TODO: Phase1 audit CvPromotionEntry::GetFeatureAttackPercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetFeatureAttackPercent(int i) const
{
	CvAssertMsg(i < PromotionNumFeature(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumFeature(&GC) && m_piFeatureAttackPercent)
	{
		return m_piFeatureAttackPercent[i];
	}

	return -1;
}

/// Returns an array of bonuses when defending a tile with a terrain feature
// TODO: Phase1 audit CvPromotionEntry::GetFeatureDefensePercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetFeatureDefensePercent(int i) const
{
	CvAssertMsg(i < PromotionNumFeature(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumFeature(&GC) && m_piFeatureDefensePercent)
	{
		return m_piFeatureDefensePercent[i];
	}

	return -1;
}

/// Returns an array of bonuses when fighting against a certain unit
// TODO: Phase1 audit CvPromotionEntry::GetUnitCombatModifierPercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetUnitCombatModifierPercent(int i) const
{
	CvAssertMsg(i < PromotionNumUnitCombat(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumUnitCombat(&GC) && m_piUnitCombatModifierPercent)
	{
		return m_piUnitCombatModifierPercent[i];
	}

	return -1;
}

/// Returns an array of bonuses when fighting against a type of unit
// TODO: Phase1 audit CvPromotionEntry::GetUnitClassModifierPercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetUnitClassModifierPercent(int i) const
{
	CvAssertMsg(i < PromotionNumUnitClass(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumUnitClass(&GC) && m_piUnitClassModifierPercent)
	{
		return m_piUnitClassModifierPercent[i];
	}

	return -1;
}

/// Returns an array of bonuses when I have no idea
// TODO: Phase1 audit CvPromotionEntry::GetDomainModifierPercent(int) const: UNVERIFIED; BE/object instructions 10/10; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetDomainModifierPercent(int i) const
{
	CvAssertMsg(i < 6, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < 6 && m_piDomainModifierPercent)
	{
		return m_piDomainModifierPercent[i];
	}

	return -1;
}

/// Percentage bonus when attacking a specific unit class
// TODO: Phase1 audit CvPromotionEntry::GetUnitClassAttackModifier(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetUnitClassAttackModifier(int i) const
{
	CvAssertMsg(i < PromotionNumUnitClass(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumUnitClass(&GC) && m_piUnitClassAttackModifier)
	{
		return m_piUnitClassAttackModifier[i];
	}

	return -1;
}

/// Percentage bonus when defending against a specific unit class
// TODO: Phase1 audit CvPromotionEntry::GetUnitClassDefenseModifier(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetUnitClassDefenseModifier(int i) const
{
	CvAssertMsg(i < PromotionNumUnitClass(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumUnitClass(&GC) && m_piUnitClassDefenseModifier)
	{
		return m_piUnitClassDefenseModifier[i];
	}

	return -1;
}

/// Returns an array that indicates if a feature type is traversable by the unit
// TODO: Phase1 audit CvPromotionEntry::GetFeaturePassableTech(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetFeaturePassableTech(int i) const
{
	CvAssertMsg(i < PromotionNumFeature(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumFeature(&GC) && m_piFeaturePassableTech)
	{
		return m_piFeaturePassableTech[i];
	}

	return -1;
}

/// Returns an array that indicates if a unit can move twice in a type of terrain
// TODO: Phase1 audit CvPromotionEntry::GetTerrainDoubleMove(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
bool CvPromotionEntry::GetTerrainDoubleMove(int i) const
{
	CvAssertMsg(i < PromotionNumTerrain(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumTerrain(&GC) && m_pbTerrainDoubleMove)
	{
		return m_pbTerrainDoubleMove[i];
	}

	return false;
}

/// Returns an array that indicates if a unit can move twice in a type of terrain feature
// TODO: Phase1 audit CvPromotionEntry::GetFeatureDoubleMove(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
bool CvPromotionEntry::GetFeatureDoubleMove(int i) const
{
	CvAssertMsg(i < PromotionNumFeature(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumFeature(&GC) && m_pbFeatureDoubleMove)
	{
		return m_pbFeatureDoubleMove[i];
	}

	return false;
}

/// Returns an array that indicates if a terrain type is impassable
// TODO: Phase1 audit CvPromotionEntry::GetTerrainImpassable(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
bool CvPromotionEntry::GetTerrainImpassable(int i) const
{
	CvAssertMsg(i < PromotionNumTerrain(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumTerrain(&GC) && m_pbTerrainImpassable)
	{
		return m_pbTerrainImpassable[i];
	}

	return false;
}

/// Returns an array that indicates what tech is needed to pass through a terrain type
// TODO: Phase1 audit CvPromotionEntry::GetTerrainPassableTech(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
int CvPromotionEntry::GetTerrainPassableTech(int i) const
{
	CvAssertMsg(i < PromotionNumTerrain(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumTerrain(&GC) && m_piTerrainPassableTech)
	{
		return m_piTerrainPassableTech[i];
	}

	return -1;
}

/// Returns an array that indicates what tech is needed to pass through a terrain feature type
// TODO: Phase1 audit CvPromotionEntry::GetFeatureImpassable(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
bool CvPromotionEntry::GetFeatureImpassable(int i) const
{
	CvAssertMsg(i < PromotionNumFeature(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumFeature(&GC) && m_pbFeatureImpassable)
	{
		return m_pbFeatureImpassable[i];
	}

	return false;
}

/// Returns the combat classes that this promotion is available for
// TODO: Phase1 audit CvPromotionEntry::GetUnitCombatClass(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
bool CvPromotionEntry::GetUnitCombatClass(int i) const
{
	CvAssertMsg(i < PromotionNumUnitCombat(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumUnitCombat(&GC) && m_pbUnitCombat)
	{
		return m_pbUnitCombat[i];
	}

	return false;
}

/// Returns the civilian unit type that this promotion is available for
// TODO: Phase1 audit CvPromotionEntry::GetCivilianUnitType(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
bool CvPromotionEntry::GetCivilianUnitType(int i) const
{
	CvAssertMsg(i < PromotionNumUnit(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if(i > -1 && i < PromotionNumUnit(&GC) && m_pbCivilianUnitType)
	{
		return m_pbCivilianUnitType[i];
	}

	return false;
}

/// If this a promotion that can randomly turn into other c
bool CvPromotionEntry::IsPostCombatRandomPromotion(int i) const
{
	CvAssertMsg(i < PromotionNumPromotion(&GC), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_pbPostCombatRandomPromotion ? m_pbPostCombatRandomPromotion[i] : false;
}

//=====================================
// CvPromotionEntryXMLEntries
//=====================================
/// Constructor
CvPromotionXMLEntries::CvPromotionXMLEntries(void)
{

}

/// Destructor
// TODO: Phase1 audit CvPromotionXMLEntries::~CvPromotionXMLEntries(): UNVERIFIED; BE/object instructions 12/12; Civ5 changed/new UNVERIFIED.
CvPromotionXMLEntries::~CvPromotionXMLEntries(void)
{
	DeleteArray();
}

/// Returns vector of promotion entries
std::vector<CvPromotionEntry*>& CvPromotionXMLEntries::GetPromotionEntries()
{
	return m_paPromotionEntries;
}

/// Number of defined projects
int CvPromotionXMLEntries::GetNumPromotions()
{
	return m_paPromotionEntries.size();
}

/// Get a specific entry
CvPromotionEntry* CvPromotionXMLEntries::GetEntry(int index)
{
	return m_paPromotionEntries[index];
}

/// Clear promotion entries
// TODO: Phase1 audit CvPromotionXMLEntries::DeleteArray(): MISMATCH; BE/object instructions 39/38; Civ5 changed/new UNVERIFIED.
void CvPromotionXMLEntries::DeleteArray()
{
	for(std::vector<CvPromotionEntry*>::iterator it = m_paPromotionEntries.begin(); it != m_paPromotionEntries.end(); ++it)
	{
		delete *it; *it = NULL;
	}

	m_paPromotionEntries.clear();
}

//=====================================
// CvUnitPromotions
//=====================================
/// Constructor
CvUnitPromotions::CvUnitPromotions():
	m_pPromotions(NULL),
	m_pUnit(NULL)
{
}

/// Destructor
// TODO: Phase1 audit CvUnitPromotions::~CvUnitPromotions(): MISMATCH; BE/object instructions 21/21; Civ5 changed/new UNVERIFIED.
CvUnitPromotions::~CvUnitPromotions(void)
{
}

/// Initialize
// TODO: Phase1 audit CvUnitPromotions::Init(CvPromotionXMLEntries*, CvUnit*): MISMATCH; BE/object instructions 29/29; Civ5 changed/new UNVERIFIED.
void CvUnitPromotions::Init(CvPromotionXMLEntries* pPromotions, CvUnit* pUnit)
{
	CvAssert(pPromotions);
	if(!pPromotions)
		return;

	CvAssert(pUnit);
	if(!pUnit)
		return;

	m_pPromotions = pPromotions;
	m_pUnit = pUnit;

	Reset();
}

/// Deallocate memory created in initialize
// TODO: Phase1 audit CvUnitPromotions::Uninit(): MISMATCH; BE/object instructions 21/21; Civ5 changed/new UNVERIFIED.
void CvUnitPromotions::Uninit()
{
	m_kHasPromotion.SetSize(0);
}

/// Reset unit promotion array to all false
// TODO: Phase1 audit CvUnitPromotions::Reset(): MISMATCH; BE/object instructions 21/21; Civ5 changed/new UNVERIFIED.
void CvUnitPromotions::Reset()
{
	m_kHasPromotion.SetSize(0);
}

/// Serialization read
// TODO: Phase1 audit CvUnitPromotions::Read(FDataStream&): MISMATCH; BE/object instructions 35/35; Civ5 changed/new UNVERIFIED.
void CvUnitPromotions::Read(FDataStream& kStream)
{
	Reset();

	// Version number to maintain backwards compatibility
	uint uiVersion;
	kStream >> uiVersion;

	// Read number of promotions
	int iNumPromotions;
	kStream >> iNumPromotions;
	CvAssertMsg(m_pPromotions != NULL && m_pPromotions->GetNumPromotions() > 0, "Number of promotions to serialize is expected to greater than 0");

	PromotionArrayHelpers::Read(kStream, m_kHasPromotion);
}

/// Serialization write
// TODO: Phase1 audit CvUnitPromotions::Write(FDataStream&) const: UNVERIFIED; BE/object instructions 33/33; Civ5 changed/new UNVERIFIED.
void CvUnitPromotions::Write(FDataStream& kStream) const
{
	// Current version number
	uint uiVersion = 1;
	kStream << uiVersion;

	// Write out number of promotions to save
	int iNumPromotions = m_pPromotions->GetNumPromotions();
	kStream << iNumPromotions;
	CvAssertMsg(iNumPromotions > 0, "Number of promotions to serialize is expected to greater than 0");

	PromotionArrayHelpers::Write(kStream, m_kHasPromotion, iNumPromotions);
}

/// Accessor: Unit object
CvUnit* CvUnitPromotions::GetUnit()
{
	return m_pUnit;
}

/// Accessor: Does the unit have a certain promotion
// TODO: Phase1 audit CvUnitPromotions::HasPromotion(PromotionTypes) const: UNVERIFIED; BE/object instructions 34/34; Civ5 changed/new UNVERIFIED.
bool CvUnitPromotions::HasPromotion(PromotionTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < PromotionNumPromotion(&GC), "eIndex is expected to be within maximum bounds (invalid Index)");

	if(eIndex >= 0 && eIndex < PromotionNumPromotion(&GC))
	{
		return m_kHasPromotion.GetBit(eIndex);
	}

	return false;
}

/// Sets the promotion to a certain value
// TODO: Phase1 audit CvUnitPromotions::SetPromotion(PromotionTypes, bool): UNVERIFIED; BE/object instructions 25/25; Civ5 changed/new UNVERIFIED.
void CvUnitPromotions::SetPromotion(PromotionTypes eIndex, bool bValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < PromotionNumPromotion(&GC), "eIndex is expected to be within maximum bounds (invalid Index)");

	if(eIndex >= 0 && eIndex < PromotionNumPromotion(&GC))
	{
		m_kHasPromotion.SetBit(eIndex, bValue);
	}
}

/// determines if the terrain feature is passable given the unit's current promotions
// TODO: Phase1 audit CvUnitPromotions::GetAllowFeaturePassable(FeatureTypes) const: MISMATCH; BE/object instructions 85/86; Civ5 changed/new UNVERIFIED. Replace prohibited raw team stride with authentic layout.
bool CvUnitPromotions::GetAllowFeaturePassable(FeatureTypes eFeatureType) const
{
	CvTeamTechs* teamTechs = (*reinterpret_cast<CvTeam*>(reinterpret_cast<char*>(PromotionTeams) + 0xb44 * static_cast<int>(m_pUnit->getTeam()))).GetTeamTechs();
	CvAssert(teamTechs);
	if(!teamTechs) return false;

	int iNumPromos = PromotionNumPromotion(&GC);
	for(int iLoop = 0; iLoop < iNumPromos; iLoop++)
	{
		PromotionTypes ePromotion = (PromotionTypes) iLoop;
		if(m_kHasPromotion.GetBit(ePromotion))
		{
			CvPromotionEntry* promotion = PromotionInfo(&GC, ePromotion);
			if(promotion)
			{
				TechTypes eTech = (TechTypes) promotion->GetFeaturePassableTech(eFeatureType);
				if(eTech != NO_TECH && PromotionHasTech(teamTechs, eTech))
				{
					return true;
				}
			}
		}
	}

	return false;
}

/// determines if the terrain type is passable given the unit's current promotions
// TODO: Phase1 audit CvUnitPromotions::GetAllowTerrainPassable(TerrainTypes) const: MISMATCH; BE/object instructions 85/86; Civ5 changed/new UNVERIFIED. Replace prohibited raw team stride with authentic layout.
bool CvUnitPromotions::GetAllowTerrainPassable(TerrainTypes eTerrainType) const
{
	CvTeamTechs* teamTechs = (*reinterpret_cast<CvTeam*>(reinterpret_cast<char*>(PromotionTeams) + 0xb44 * static_cast<int>(m_pUnit->getTeam()))).GetTeamTechs();
	CvAssert(teamTechs);
	if(!teamTechs) return false;

	int iNumPromos = PromotionNumPromotion(&GC);
	for(int iLoop = 0; iLoop < iNumPromos; iLoop++)
	{
		PromotionTypes ePromotion = (PromotionTypes) iLoop;
		if(m_kHasPromotion.GetBit(ePromotion))
		{
			CvPromotionEntry* promotion = PromotionInfo(&GC, ePromotion);

			if(promotion)
			{
				TechTypes eTech = (TechTypes) promotion->GetTerrainPassableTech(eTerrainType);
				if(eTech != NO_TECH && PromotionHasTech(teamTechs, eTech))
				{
					return true;
				}
			}
		}
	}
	return false;
}

/// returns the advantage percent when attacking the specified unit class
// TODO: Phase1 audit CvUnitPromotions::GetUnitClassAttackMod(UnitClassTypes) const: MISMATCH; BE/object instructions 57/57; Civ5 changed/new UNVERIFIED.
int CvUnitPromotions::GetUnitClassAttackMod(UnitClassTypes eUnitClass) const
{
	int iSum = 0;
	for(int iLoop = 0; iLoop < PromotionNumPromotion(&GC); iLoop++)
	{
		PromotionTypes ePromotion = (PromotionTypes)iLoop;
		CvPromotionEntry* promotion = PromotionInfo(&GC, ePromotion);
		if(promotion && HasPromotion(ePromotion))
		{
			iSum += promotion->GetUnitClassAttackModifier(eUnitClass);
		}
	}
	return iSum;
}

/// returns the advantage percent when defending against the specified unit class
// TODO: Phase1 audit CvUnitPromotions::GetUnitClassDefenseMod(UnitClassTypes) const: MISMATCH; BE/object instructions 57/57; Civ5 changed/new UNVERIFIED.
int CvUnitPromotions::GetUnitClassDefenseMod(UnitClassTypes eUnitClass) const
{
	int iSum = 0;
	for(int iLoop = 0; iLoop < PromotionNumPromotion(&GC); iLoop++)
	{
		PromotionTypes ePromotion = (PromotionTypes)iLoop;
		CvPromotionEntry* promotion = PromotionInfo(&GC, ePromotion);
		if(promotion && HasPromotion(ePromotion))
		{
			iSum += promotion->GetUnitClassDefenseModifier(eUnitClass);
		}
	}
	return iSum;
}

// Swap to a new promotion after a combat - returns new promotion we switched to
// TODO: Phase1 audit CvUnitPromotions::ChangePromotionAfterCombat(PromotionTypes): MISMATCH; BE/object instructions 98/89; Civ5 changed/new UNVERIFIED. Raw player/team stride or member access requires authentic layout (no ABI shortcut).
PromotionTypes CvUnitPromotions::ChangePromotionAfterCombat(PromotionTypes eIndex)
{
	std::vector<int> aPossiblePromotions;

	for (int iI = 0; iI < m_pPromotions->GetNumPromotions(); iI++)
	{
		CvPromotionEntry *pkEntry = m_pPromotions->GetEntry(eIndex);
		if (pkEntry && pkEntry->IsPostCombatRandomPromotion(iI))
		{
			if (!pkEntry->ArePostCombatPromotionsExclusive() || !IsInUseByPlayer((PromotionTypes)iI, *reinterpret_cast<const PlayerTypes*>(reinterpret_cast<const char*>(m_pUnit) + 0x24)))
			{
				aPossiblePromotions.push_back(iI);
			}
		}
	}

	int iNumChoices = aPossiblePromotions.size();
	if (iNumChoices > 0)
	{
		int iChoice = GC.getGame().getGameRandNum(iNumChoices, "Random Promotion Pick");
		return (PromotionTypes)aPossiblePromotions[iChoice];
	}

	return NO_PROMOTION;
}

// PRIVATE METHODS

// Is this (post-combat) promotion already present for some unit of this player?
// TODO: Phase1 audit CvUnitPromotions::IsInUseByPlayer(PromotionTypes, PlayerTypes): MISMATCH; BE/object instructions 42/42; Civ5 changed/new UNVERIFIED. Raw player/team stride or member access requires authentic layout (no ABI shortcut).
bool CvUnitPromotions::IsInUseByPlayer(PromotionTypes eIndex, PlayerTypes ePlayer)
{
	bool bRtnValue = false;
	CvPlayer &kPlayer = (*reinterpret_cast<CvPlayer*>(reinterpret_cast<char*>(PromotionPlayers) + 0xf598 * static_cast<int>(ePlayer)));

	CvUnit *pLoopUnit;
	int iValueLoop;
	for(pLoopUnit = kPlayer.firstUnit(&iValueLoop, false); pLoopUnit != NULL; pLoopUnit = kPlayer.nextUnit(&iValueLoop, false))
	{
		if (PromotionUnitHasPromotion(pLoopUnit, eIndex))
		{
			return true;
		}
	}

	return bRtnValue;
}

// Read the saved promotions.  Entries are saved as string values, all entries are saved.
// TODO: Phase1 audit PromotionArrayHelpers::ReadV3(FDataStream&, CvBitfield<32u>&): MISMATCH; BE/object instructions 152/123; Civ5 changed/new UNVERIFIED.
void PromotionArrayHelpers::ReadV3(FDataStream& kStream, CvBitfield<32>& kPromotions)
{
	int iNumEntries;
	FStringA sTemp;
	FStringA::FStringAFixedBuffer<64> stringBuffer(sTemp);
	int iType;

	kStream >> iNumEntries;

	kPromotions.SetSize( iNumEntries );

	for(int iI = 0; iI < iNumEntries; iI++)
	{
		PromotionReadString(&kStream, sTemp);
		if(strcmp(sTemp.c_str(), "PROMOTION_OLIGARCHY") == 0)
		{
			bool bTemp;
			kStream >> bTemp;
		}
		else
		{
			iType = GC.getInfoTypeForString(sTemp.c_str());
			if(iType != -1)
			{
				bool bValue;
				kStream >> bValue;
				kPromotions.SetBit(iType, bValue);
			}
			else
			{
				CvString szError;
				szError.Format("LOAD ERROR: Promotion Type not found: %s", sTemp.c_str());
				GC.LogMessage(szError.GetCString());
				CvAssertMsg(false, szError);
				bool bDummy;
				kStream >> bDummy;
			}
		}
	}
}

// Read the saved promotions.  Entries are saved as hash values
// TODO: Phase1 audit PromotionArrayHelpers::Read(FDataStream&, CvBitfield<32u>&): MISMATCH; BE/object instructions 110/101; Civ5 changed/new UNVERIFIED.
void PromotionArrayHelpers::Read(FDataStream& kStream, CvBitfield<32>& kPromotions)
{
	int iNumEntries;
	int iType;

	kStream >> iNumEntries;

	kPromotions.SetSize( iNumEntries );

	uint uiHashTemp;
	uint uiOligarchyHash = FStringA::Hash("PROMOTION_OLIGARCHY");
	for(int iI = 0; iI < iNumEntries; iI++)
	{
		kStream >> uiHashTemp;
		if(uiHashTemp == uiOligarchyHash)
		{
			bool bTemp;
			kStream >> bTemp;
		}
		else
		{
			iType = PromotionTypeForHash(&GC, uiHashTemp, false);
			if(iType != -1)
			{
				bool bValue;
				kStream >> bValue;
				kPromotions.SetBit(iType, bValue);
			}
			else
			{
				CvString szError;
				szError.Format("LOAD ERROR: Promotion Type not found for hash: %u", uiHashTemp);
				GC.LogMessage(szError.GetCString());
				CvAssertMsg(false, szError);
				bool bDummy;
				kStream >> bDummy;
			}
		}
	}
}

// Save the promotions.  Entries are saved as hash values and only the entries that are 'on' are saved
// TODO: Phase1 audit PromotionArrayHelpers::Write(FDataStream&, CvBitfield<32u> const&, int): UNVERIFIED; BE/object instructions 119/119; Civ5 changed/new UNVERIFIED.
void PromotionArrayHelpers::Write(FDataStream& kStream, const CvBitfield<32>& kPromotions, int iArraySize)
{
	// We are only going to save the 'on' bit, so we have to count them
	int iCount = 0;

	for(int iI = 0; iI < iArraySize; iI++)
	{
		const PromotionTypes ePromotion = static_cast<PromotionTypes>(iI);
		if (kPromotions.GetBit(ePromotion) && PromotionInfo(&GC, ePromotion) != NULL)
			++iCount;
	}

	kStream << iCount;

	for(int iI = 0; iI < iArraySize; iI++)
	{
		const PromotionTypes ePromotion = static_cast<PromotionTypes>(iI);
		bool bValue = kPromotions.GetBit(ePromotion);
		if (bValue)
		{
			CvPromotionEntry* pkPromotionInfo = PromotionInfo(&GC, ePromotion);
			if(pkPromotionInfo)
			{
				uint uiHash = FStringA::Hash( pkPromotionInfo->GetType() );		// Save just the hash
				kStream << uiHash;
				kStream << bValue;
			}
		}
	}
}
