/*	-------------------------------------------------------------------------------------------------------
	� 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.
	All other marks and trademarks are the property of their respective owners.
	All rights reserved.
	------------------------------------------------------------------------------------------------------- */
#pragma once

#ifndef CIV5_PROMOTION_CLASSES_H
#define CIV5_PROMOTION_CLASSES_H

#include <vector>
#include <cstring>

// Beyond Earth's bitfield stores up to 31 bytes inline.
#ifndef CVBITFIELD_H
#define CVBITFIELD_H
template<unsigned int InlineBytes = 32> class CvBitfield
{
public:
	// TODO: Phase1 audit CvBitfield::CvBitfield(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	CvBitfield() : m_uiByteSize(0), m_pBits(NULL) {}
	// TODO: Phase1 audit CvBitfield::~CvBitfield(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	~CvBitfield() { SetSize(0); }
	// TODO: Phase1 audit CvBitfield::GetBit(unsigned int index) const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	bool GetBit(unsigned int index) const
	{
		return (index >> 3) < m_uiByteSize && (m_pBits[index >> 3] & (1 << (index & 7))) != 0;
	}
	// TODO: Phase1 audit CvBitfield<32u>::SetBit(unsigned int, bool): MISMATCH; BE/object instructions 52/46; Civ5 changed/new UNVERIFIED.
	__attribute__((noinline)) void SetBit(unsigned int index, bool value)
	{
		unsigned int byte = index >> 3;
		if(byte >= m_uiByteSize)
		{
			if(!value) return;
			SetSize(index + 1);
		}
		if(value) m_pBits[byte] |= 1 << (index & 7);
		else m_pBits[byte] &= ~(1 << (index & 7));
	}
	// TODO: Phase1 audit CvBitfield<32u>::SetSize(unsigned int): MISMATCH; BE/object instructions 103/102; Civ5 changed/new UNVERIFIED.
	void SetSize(unsigned int bits)
	{
		unsigned int size = (bits >> 3) + ((bits & 7) ? 1 : 0);
		if(!size)
		{
			if(m_pBits != m_inlineBits && m_pBits) delete[] m_pBits;
			m_uiByteSize = 0;
			m_pBits = NULL;
		}
		else if(size < InlineBytes)
		{
			if(m_pBits == m_inlineBits)
			{
				if(size > m_uiByteSize) memset(m_inlineBits + m_uiByteSize, 0, size - m_uiByteSize);
				m_uiByteSize = size;
				return;
			}
			memset(m_inlineBits, 0, size);
			if(m_uiByteSize) memcpy(m_inlineBits, m_pBits, size < m_uiByteSize ? size : m_uiByteSize);
			if(m_pBits && m_pBits != m_inlineBits) delete[] m_pBits;
			m_pBits = m_inlineBits;
			m_uiByteSize = size;
		}
		else if(size != m_uiByteSize)
		{
			unsigned char* storage = new unsigned char[size];
			memset(storage, 0, size);
			if(m_uiByteSize) memcpy(storage, m_pBits, size < m_uiByteSize ? size : m_uiByteSize);
			if(m_pBits && m_pBits != m_inlineBits) delete[] m_pBits;
			m_pBits = storage;
			m_uiByteSize = size;
		}
	}
private:
	unsigned int m_uiByteSize;
	unsigned char m_inlineBits[InlineBytes];
	unsigned char* m_pBits;
};
#endif

class CvUnit;
class FDataStream;
enum UnitClassTypes : int;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvPromotionEntry
//!  \brief		A single promotion available in the game
//
//!  Key Attributes:
//!  - Used to be called CvPromotionInfo
//!  - Populated from XML\Units\CIV5UnitPromotions.xml
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvPromotionEntry: public CvHotKeyInfo
{
public:
	// TODO: Phase1 audit CvPromotionEntry::CvPromotionEntry(): UNVERIFIED; BE/object instructions 44/44; Civ5 changed/new UNVERIFIED.
	CvPromotionEntry(void);
	// TODO: Phase1 audit CvPromotionEntry::~CvPromotionEntry(): UNVERIFIED; BE/object instructions 128/128; Civ5 changed/new UNVERIFIED.
	~CvPromotionEntry(void);

	// TODO: Phase1 audit CvPromotionEntry::CacheResults(Database::Results&, CvDatabaseUtility&): MISMATCH; BE/object instructions 1607/1564; Civ5 changed/new UNVERIFIED.
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	bool IsOnlyDefensive() const;
	int GetCivHealthBonusMaxHealth() const;
	int GetNearbyEnemyCombatMod() const;
	int GetNeutralHealChange() const;
	bool IsIgnoreTerrainCost() const;
	int GetNearbyEnemyCombatRange() const;
	int GetMeleeCombatPercent() const;
	int GetMovesChange() const;
	bool IsRecon() const;
	int GetExperiencePercent() const;
	int GetAlienRepelRangeChange() const;
	int GetAirSweepCombatModifier() const;
	bool HasPostCombatPromotions() const;
	int GetPrereqOrPromotion7() const;
	bool IsEnemyRoute() const;
	int GetEmbarkDefenseModifier() const;
	int GetTechPrereq() const;
	bool IsLostWithUpgrade() const;
	int GetCivHealthBonusMinModifier() const;
	int GetExtraWorkerMoves() const;
	int GetPrereqOrPromotion9() const;
	bool IsAirSweepCapable() const;
	int GetCityAttackPlunderModifier() const;
	int GetFriendlyLandsModifier() const;
	int GetExactLevelPrereq() const;
	int GetHPHealedIfDefeatEnemy() const;
	int GetGreatGeneralModifier() const;
	int GetUpgradeDiscount() const;
	int GetOpenDefensePercent() const;
	int GetFriendlyLandsAttackModifier() const;
	int GetEnemyHealChange() const;
	bool IsHealOnPillage() const;
	int GetOpenAttackPercent() const;
	bool IsCoastalWalk() const;
	int GetEraOfProsperityValueFromKills() const;
	bool IsFreeMaintenance() const;
	bool IsAlwaysHostile() const;
	bool IsFreePillageMoves() const;
	int GetDefenseMod() const;
	int GetAdjacentTileHealChange() const;
	bool IsLeader() const;
	int GetAttackUnfortifiedMod() const;
	int GetCombatPercent() const;
	int GetArtifactRewardPrereq() const;
	bool IsCanMoveAfterAttacking() const;
	bool IsNotWithUpgrade() const;
	bool IsGreatGeneral() const;
	int GetSameTileHealChange() const;
	bool IsAmphibiousAttack() const;
	int GetRangedDefenseMod() const;
	bool IsCaptureDefeatedEnemy() const;
	int GetCapitalDefenseModifier() const;
	int GetPrereqOrPromotion4() const;
	bool IsGreatAdmiral() const;
	int GetEnemyDamageChance() const;
	bool IsIgnoreZOC() const;
	int GetLayerAnimationPath() const;
	int GetMiasmaFlatHealthModifier() const;
	int GetOutsideFriendlyLandsModifier() const;
	bool IsRiver() const;
	int GetPrereqOrPromotion1() const;
	int GetHillsAttackPercent() const;
	int GetInterceptionCombatModifier() const;
	bool ArePostCombatPromotionsExclusive() const;
	bool IsHillsDoubleMove() const;
	int GetNeutralDamage() const;
	int GetInterceptChanceChange() const;
	bool IsHiddenNationality() const;
	bool IsGreatGeneralReceivesMovement() const;
	int GetRoughAttackPercent() const;
	int GetInterceptionDefenseDamageModifier() const;
	bool IsRangeAttackIgnoreLOS() const;
	int GetCivHealthBonusMinHealth() const;
	int GetCivHealthBonusMaxModifier() const;
	int GetEmbarkExtraVisibility() const;
	bool IsCityAttackOnly() const;
	bool CanMoveAllTerrain() const;
	bool IsNoCapture() const;
	int GetPrereqOrPromotion2() const;
	int GetAttackWoundedMod() const;
	int GetRoughRangedAttackMod() const;
	bool IsSapper() const;
	bool IsInstantHeal() const;
	int GetInstantHealAmount() const;
	bool IsCanMoveImpassable() const;
	int GetOrbitalCoverageRadiusChange() const;
	int GetCommandType() const;
	int GetOpenRangedAttackMod() const;
	bool IsCannotBeChosen() const;
	int GetAttackMod() const;
	int GetCargoChange() const;
	int GetPrereqOrPromotion5() const;
	bool IsNoDefensiveBonus() const;
	bool GetMiasmaImmune() const;
	bool IsNoRevealMap() const;
	bool IsAllowsEmbarkation() const;
	int GetExtraAttacks() const;
	int GetHillsDefensePercent() const;
	int GetEnemyDamage() const;
	int GetExtraNavalMoves() const;
	int GetPrereqPromotion() const;
	bool IsFlatMovementCost() const;
	bool IsRoughTerrainEndsTurn() const;
	int GetReligiousStrengthLossRivalTerritory() const;
	int GetEvasionChange() const;
	int GetNeutralDamageChance() const;
	bool IsBlitz() const;
	int GetExtraWithdrawal() const;
	int GetPrereqOrPromotion6() const;
	bool IsRangedSupportFire() const;
	int GetGreatGeneralCombatModifier() const;
	int GetRoughDefensePercent() const;
	int GetNumInterceptionChange() const;
	int GetRangedAttackModifier() const;
	int GetPrereqOrPromotion8() const;
	bool IsIgnoreGreatGeneralBenefit() const;
	int GetTradeMissionInfluenceModifier() const;
	int GetVisibilityChange() const;
	bool IsHealIfDefeatExcludeBarbarians() const;
	bool IsHoveringUnit() const;
	bool IsHealOutsideFriendly() const;
	bool GetMiasmaImmuneWorkers() const;
	int GetMoveDiscountChange() const;
	int GetSeeInvisibleType() const;
	int GetFriendlyHealChange() const;
	bool IsRivalTerritory() const;
	int GetDropRange() const;
	int GetAdjacentMod() const;
	int GetAttackFortifiedMod() const;
	int GetPrereqOrPromotion3() const;
	bool IsCanHeavyCharge() const;
	int GetTradeMissionGoldModifier() const;
	int GetRangeChange() const;
	int GetCityDefensePercent() const;
	int GetCityAttackPercent() const;
	bool IsAlwaysHeal() const;
	int GetFlankAttackModifier() const;
	int GetInvisibleType() const;
	bool IsMustSetUpToRangedAttack() const;
	int GetCapitalDefenseFalloff() const;

	void	SetPrereqPromotion(int i);
	void	SetPrereqOrPromotion1(int i);
	void	SetPrereqOrPromotion2(int i);
	void	SetPrereqOrPromotion3(int i);
	void	SetPrereqOrPromotion4(int i);
	void	SetPrereqOrPromotion5(int i);
	void	SetPrereqOrPromotion6(int i);
	void	SetPrereqOrPromotion7(int i);
	void	SetPrereqOrPromotion8(int i);
	void	SetPrereqOrPromotion9(int i);

	void SetCommandType(int iNewType);






	const char* GetSound() const;
	// TODO: Phase1 audit CvPromotionEntry::SetSound(char const*): UNVERIFIED; BE/object instructions 14/14; Civ5 changed/new UNVERIFIED.
	void SetSound(const char* szVal);

	// Arrays
	// TODO: Phase1 audit CvPromotionEntry::GetTerrainAttackPercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetTerrainAttackPercent(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetTerrainDefensePercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetTerrainDefensePercent(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetFeatureAttackPercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetFeatureAttackPercent(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetFeatureDefensePercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetFeatureDefensePercent(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetUnitCombatModifierPercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetUnitCombatModifierPercent(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetUnitClassModifierPercent(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetUnitClassModifierPercent(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetDomainModifierPercent(int) const: UNVERIFIED; BE/object instructions 10/10; Civ5 changed/new UNVERIFIED.
	int GetDomainModifierPercent(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetFeaturePassableTech(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetFeaturePassableTech(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetUnitClassAttackModifier(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetUnitClassAttackModifier(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetUnitClassDefenseModifier(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int GetUnitClassDefenseModifier(int i) const;

	// TODO: Phase1 audit CvPromotionEntry::GetTerrainDoubleMove(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	bool GetTerrainDoubleMove(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetFeatureDoubleMove(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	bool GetFeatureDoubleMove(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetTerrainImpassable(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	bool GetTerrainImpassable(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetTerrainPassableTech(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	int  GetTerrainPassableTech(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetFeatureImpassable(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	bool GetFeatureImpassable(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetUnitCombatClass(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	bool GetUnitCombatClass(int i) const;
	// TODO: Phase1 audit CvPromotionEntry::GetCivilianUnitType(int) const: UNVERIFIED; BE/object instructions 27/27; Civ5 changed/new UNVERIFIED.
	bool GetCivilianUnitType(int i) const;
	bool IsPostCombatRandomPromotion(int i) const;

protected:
	int m_iLayerAnimationPath;
	int m_iPrereqPromotion;
	int m_iPrereqOrPromotion1;
	int m_iPrereqOrPromotion2;
	int m_iPrereqOrPromotion3;
	int m_iPrereqOrPromotion4;
	int m_iPrereqOrPromotion5;
	int m_iPrereqOrPromotion6;
	int m_iPrereqOrPromotion7;
	int m_iPrereqOrPromotion8;
	int m_iPrereqOrPromotion9;
	int m_iTechPrereq;
	int m_iArtifactRewardPrereq;
	int m_iExactLevelPrereq;
	int m_iInvisibleType;
	int m_iSeeInvisibleType;
	int m_iVisibilityChange;
	int m_iMovesChange;
	int m_iMoveDiscountChange;
	int m_iRangeChange;
	int m_iRangedAttackModifier;
	int m_iInterceptionCombatModifier;
	int m_iInterceptionDefenseDamageModifier;
	int m_iAirSweepCombatModifier;
	int m_iInterceptChanceChange;
	int m_iNumInterceptionChange;
	int m_iEvasionChange;
	int m_iCargoChange;
	int m_iEnemyHealChange;
	int m_iNeutralHealChange;
	int m_iFriendlyHealChange;
	int m_iSameTileHealChange;
	int m_iAdjacentTileHealChange;
	int m_iEnemyDamageChance;
	int m_iNeutralDamageChance;
	int m_iEnemyDamage;
	int m_iNeutralDamage;
	int m_iCombatPercent;
	int m_iMeleeCombatPercent;
	int m_iCityAttackPercent;
	int m_iCityDefensePercent;
	int m_iRangedDefenseMod;
	int m_iHillsAttackPercent;
	int m_iHillsDefensePercent;
	int m_iOpenAttackPercent;
	int m_iOpenRangedAttackMod;
	int m_iRoughAttackPercent;
	int m_iRoughRangedAttackMod;
	int m_iAttackFortifiedMod;
	int m_iAttackUnfortifiedMod;
	int m_iAttackWoundedMod;
	int m_iFlankAttackModifier;
	int m_iNearbyEnemyCombatMod;
	int m_iNearbyEnemyCombatRange;
	int m_iOpenDefensePercent;
	int m_iRoughDefensePercent;
	int m_iExtraAttacks;
	bool m_bGreatGeneral;
	bool m_bGreatAdmiral;
	int m_iGreatGeneralModifier;
	bool m_bGreatGeneralReceivesMovement;
	int m_iGreatGeneralCombatModifier;
	int m_iFriendlyLandsModifier;
	int m_iFriendlyLandsAttackModifier;
	int m_iOutsideFriendlyLandsModifier;
	int m_iCommandType;
	int m_iUpgradeDiscount;
	int m_iExperiencePercent;
	int m_iAdjacentMod;
	int m_iAttackMod;
	int m_iDefenseMod;
	int m_iDropRange;
	int m_iExtraNavalMoves;
	int m_iExtraWorkerMoves;
	int m_iHPHealedIfDefeatEnemy;
	int m_iEraOfProsperityValueFromKills;
	int m_iExtraWithdrawal;
	int m_iEmbarkExtraVisibility;
	int m_iEmbarkDefenseModifier;
	int m_iCapitalDefenseModifier;
	int m_iCapitalDefenseFalloff;
	int m_iCityAttackPlunderModifier;
	int m_iReligiousStrengthLossRivalTerritory;
	int m_iInstantHealAmount;
	int m_iTradeMissionInfluenceModifier;
	int m_iTradeMissionGoldModifier;
	int m_iMiasmaFlatHealthModifier;
	int m_iOrbitalCoverageRadiusChange;
	int m_iAlienRepelRangeChange;
	int m_iCivHealthBonusMinModifier;
	int m_iCivHealthBonusMaxModifier;
	int m_iCivHealthBonusMinHealth;
	int m_iCivHealthBonusMaxHealth;
	bool m_bMiasmaImmune;
	bool m_bMiasmaImmuneWorkers;
	bool m_bCannotBeChosen;
	bool m_bLostWithUpgrade;
	bool m_bNotWithUpgrade;
	bool m_bLeader;
	bool m_bBlitz;
	bool m_bAmphibiousAttack;
	bool m_bRiver;
	bool m_bEnemyRoute;
	bool m_bRivalTerritory;
	bool m_bMustSetUpToRangedAttack;
	bool m_bRangedSupportFire;
	bool m_bAlwaysHeal;
	bool m_bHealOutsideFriendly;
	bool m_bHillsDoubleMove;
	bool m_bIgnoreTerrainCost;
	bool m_bRoughTerrainEndsTurn;
	bool m_bHoveringUnit;
	bool m_bCoastalWalk;
	bool m_bFlatMovementCost;
	bool m_bCanMoveImpassable;
	bool m_bNoCapture;
	bool m_bOnlyDefensive;
	bool m_bNoDefensiveBonus;
	bool m_bHiddenNationality;
	bool m_bAlwaysHostile;
	bool m_bNoRevealMap;
	bool m_bRecon;
	bool m_bCanMoveAllTerrain;
	bool m_bCanMoveAfterAttacking;
	bool m_bAirSweepCapable;
	bool m_bAllowsEmbarkation;
	bool m_bRangeAttackIgnoreLOS;
	bool m_bFreeMaintenance;
	bool m_bFreePillageMoves;
	bool m_bHealOnPillage;
	bool m_bHealIfDefeatExcludesBarbarians;
	bool m_bCityAttackOnly;
	bool m_bCaptureDefeatedEnemy;
	bool m_bIgnoreGreatGeneralBenefit;
	bool m_bIgnoreZOC;
	bool m_bHasPostCombatPromotions;
	bool m_bPostCombatPromotionsExclusive;
	bool m_bSapper;
	bool m_bCanHeavyCharge;
	CvString m_strSound;

	// Arrays
	int* m_piTerrainAttackPercent;
	int* m_piTerrainDefensePercent;
	int* m_piFeatureAttackPercent;
	int* m_piFeatureDefensePercent;
	int* m_piUnitCombatModifierPercent;
	int* m_piUnitClassModifierPercent;
	int* m_piDomainModifierPercent;

	int* m_piUnitClassAttackModifier;
	int* m_piUnitClassDefenseModifier;

	int* m_piTerrainPassableTech;
	int* m_piFeaturePassableTech;

	bool* m_pbTerrainDoubleMove;
	bool* m_pbFeatureDoubleMove;
	bool* m_pbTerrainImpassable;
	bool* m_pbFeatureImpassable;
	bool* m_pbUnitCombat;
	bool* m_pbCivilianUnitType;
	bool* m_pbPostCombatRandomPromotion;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvPromotionXMLEntries
//!  \brief		Game-wide information about promotions
//
//! Key Attributes:
//! - Plan is it will be contained in CvGameRules object within CvGame class
//! - Populated from XML\GameInfo\CIV5PromotionInfo.xml
//! - Contains an array of CvPromotionEntry from the above XML file
//! - One instance for the entire game
//! - Accessed heavily by the [what stores info on projects built?] class
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvPromotionXMLEntries
{
public:
	CvPromotionXMLEntries(void);
	// TODO: Phase1 audit CvPromotionXMLEntries::~CvPromotionXMLEntries(): UNVERIFIED; BE/object instructions 12/12; Civ5 changed/new UNVERIFIED.
	~CvPromotionXMLEntries(void);

	// Accessor functions
	std::vector<CvPromotionEntry*>& GetPromotionEntries();
	int GetNumPromotions();
	_Ret_maybenull_ CvPromotionEntry* GetEntry(int index);

	// Binary cache functions
	// TODO: Phase1 audit CvPromotionXMLEntries::DeleteArray(): MISMATCH; BE/object instructions 39/38; Civ5 changed/new UNVERIFIED.
	void DeleteArray();

private:
	std::vector<CvPromotionEntry*> m_paPromotionEntries;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvUnitPromotions
//!  \brief		Information about the promotions of a single unit
//
//!  Key Attributes:
//!  - Plan is it will be contained in CvPlayerState object within CvUnit class
//!  - One instance for each unit
//!  - Accessed by any class that needs to check promotions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvUnitPromotions
{
public:
	CvUnitPromotions(void);
	// TODO: Phase1 audit CvUnitPromotions::~CvUnitPromotions(): MISMATCH; BE/object instructions 21/21; Civ5 changed/new UNVERIFIED.
	~CvUnitPromotions(void);
	// TODO: Phase1 audit CvUnitPromotions::Init(CvPromotionXMLEntries*, CvUnit*): MISMATCH; BE/object instructions 29/29; Civ5 changed/new UNVERIFIED.
	void Init(CvPromotionXMLEntries* pPromotions, CvUnit* pUnit);
	// TODO: Phase1 audit CvUnitPromotions::Uninit(): MISMATCH; BE/object instructions 21/21; Civ5 changed/new UNVERIFIED.
	void Uninit();
	// TODO: Phase1 audit CvUnitPromotions::Reset(): MISMATCH; BE/object instructions 21/21; Civ5 changed/new UNVERIFIED.
	void Reset();
	// TODO: Phase1 audit CvUnitPromotions::Read(FDataStream&): MISMATCH; BE/object instructions 35/35; Civ5 changed/new UNVERIFIED.
	void Read(FDataStream& kStream);
	// TODO: Phase1 audit CvUnitPromotions::Write(FDataStream&) const: UNVERIFIED; BE/object instructions 33/33; Civ5 changed/new UNVERIFIED.
	void Write(FDataStream& kStream) const;

	CvUnit* GetUnit();

	// TODO: Phase1 audit CvUnitPromotions::HasPromotion(PromotionTypes) const: UNVERIFIED; BE/object instructions 34/34; Civ5 changed/new UNVERIFIED.
	bool HasPromotion(PromotionTypes eIndex) const;
	// TODO: Phase1 audit CvUnitPromotions::SetPromotion(PromotionTypes, bool): UNVERIFIED; BE/object instructions 25/25; Civ5 changed/new UNVERIFIED.
	void SetPromotion(PromotionTypes eIndex, bool bValue);

	// TODO: Phase1 audit CvUnitPromotions::GetAllowFeaturePassable(FeatureTypes) const: MISMATCH; BE/object instructions 85/86; Civ5 changed/new UNVERIFIED.
	bool GetAllowFeaturePassable(FeatureTypes eFeatureType) const;
	// TODO: Phase1 audit CvUnitPromotions::GetAllowTerrainPassable(TerrainTypes) const: MISMATCH; BE/object instructions 85/86; Civ5 changed/new UNVERIFIED.
	bool GetAllowTerrainPassable(TerrainTypes eTerrainType) const ;

	// TODO: Phase1 audit CvUnitPromotions::GetUnitClassAttackMod(UnitClassTypes) const: MISMATCH; BE/object instructions 57/57; Civ5 changed/new UNVERIFIED.
	int GetUnitClassAttackMod(UnitClassTypes eUnitClass) const;
	// TODO: Phase1 audit CvUnitPromotions::GetUnitClassDefenseMod(UnitClassTypes) const: MISMATCH; BE/object instructions 57/57; Civ5 changed/new UNVERIFIED.
	int GetUnitClassDefenseMod(UnitClassTypes eUnitClass) const;

	// TODO: Phase1 audit CvUnitPromotions::ChangePromotionAfterCombat(PromotionTypes): MISMATCH; BE/object instructions 98/89; Civ5 changed/new UNVERIFIED. Raw player/team stride or member access requires authentic layout (no ABI shortcut).
	PromotionTypes ChangePromotionAfterCombat(PromotionTypes eIndex);

private:

	// TODO: Phase1 audit CvUnitPromotions::IsInUseByPlayer(PromotionTypes, PlayerTypes): MISMATCH; BE/object instructions 42/42; Civ5 changed/new UNVERIFIED. Raw player/team stride or member access requires authentic layout (no ABI shortcut).
	bool IsInUseByPlayer(PromotionTypes eIndex, PlayerTypes ePlayer);

	CvBitfield<32> m_kHasPromotion;
	CvPromotionXMLEntries* m_pPromotions;
	CvUnit* m_pUnit;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Helper Functions to serialize arrays of variable length (based on number of promotions defined in game)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace PromotionArrayHelpers
{
// TODO: Phase1 audit PromotionArrayHelpers::ReadV3(FDataStream&, CvBitfield<32u>&): MISMATCH; BE/object instructions 152/123; Civ5 changed/new UNVERIFIED.
void ReadV3(FDataStream& kStream, CvBitfield<32>& kPromotions);
// TODO: Phase1 audit PromotionArrayHelpers::Read(FDataStream&, CvBitfield<32u>&): MISMATCH; BE/object instructions 110/101; Civ5 changed/new UNVERIFIED.
void Read(FDataStream& kStream, CvBitfield<32>& kPromotions);
// TODO: Phase1 audit PromotionArrayHelpers::Write(FDataStream&, CvBitfield<32u> const&, int): UNVERIFIED; BE/object instructions 119/119; Civ5 changed/new UNVERIFIED.
void Write(FDataStream& kStream, const CvBitfield<32>& kPromotions, int iArraySize);
}

#endif //CIV5_PROMOTION_CLASSES_H
