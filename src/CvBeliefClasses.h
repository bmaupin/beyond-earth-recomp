/*	-------------------------------------------------------------------------------------------------------
	� 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.
	All other marks and trademarks are the property of their respective owners.
	All rights reserved.
	------------------------------------------------------------------------------------------------------- */
#pragma once

#ifndef CIV5_BELIEF_CLASSES_H
#define CIV5_BELIEF_CLASSES_H

class CvReligion;

#define SAFE_ESTIMATE_NUM_BELIEFS 100

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvBeliefEntry
//!  \brief		A single entry in the Belief XML file
//
//!  Key Attributes:
//!  - Used to be called CvBeliefInfo
//!  - Populated from XML\Civilizations\CIV5Beliefs.xml
//!  - Array of these contained in CvBeliefXMLEntries class
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvBeliefEntry: public CvBaseInfo
{
public:
	// TODO: Phase1 audit CvBeliefEntry::CvBeliefEntry(): UNVERIFIED; BE/object instructions 31/31; Civ5 changed/new UNVERIFIED.
	CvBeliefEntry(void);
	// TODO: Phase1 audit CvBeliefEntry::~CvBeliefEntry(): MISMATCH; BE/object instructions 101/89; Civ5 changed/new UNVERIFIED.
	~CvBeliefEntry(void);

	int GetMinPopulation() const;
	int GetMinFollowers() const;
	int GetMaxDistance() const;
	int GetCityGrowthModifier() const;
	int GetFaithFromKills() const;
	int GetFaithFromDyingUnits() const;
	int GetHealthNextToRiver() const;
	int GetHealthPerCanyon() const;
	int GetHealthPerCity() const;
	int GetHealthPerXPeacefulForeignFollowers() const;
	int GetPlotCultureCostModifier() const;
	int GetCityRangeStrikeModifier() const;
	int GetCombatModifierEnemyCities() const;
	int GetCombatModifierFriendlyCities() const;
	int GetFriendlyHealChange() const;
	int GetCityStateFriendshipModifier() const;
	int GetLandBarbarianConversionPercent() const;
	int GetWonderProductionModifier() const;
	int GetPlayerHealth() const;
	int GetPlayerCultureModifier() const;
	float GetHealthPerFollowingCity() const;
	int GetGoldPerFollowingCity() const;
	int GetGoldPerXFollowers() const;
	int GetGoldWhenCityAdopts() const;
	int GetSciencePerOtherReligionFollower() const;
	int GetSpreadDistanceModifier() const;
	int GetSpreadStrengthModifier() const;
	int GetProphetStrengthModifier() const;
	int GetProphetCostModifier() const;
	int GetMissionaryStrengthModifier() const;
	int GetMissionaryCostModifier() const;
	int GetFriendlyCityStateSpreadModifier() const;
	int GetCityStateMinimumInfluence() const;
	int GetCityStateInfluenceModifier() const;
	int GetOtherReligionPressureErosion() const;
	int GetSpyPressure() const;
	int GetInquisitorPressureRetention() const;
	int GetFaithBuildingTourism() const;

	int GetFaithCost() const;
	bool IsCreateCreed() const;
	// TODO: Phase1 audit CvBeliefEntry::IsCreateDogma() const: UNVERIFIED; BE/object instructions 5/5; Civ5 changed/new UNVERIFIED.
	bool IsCreateDogma() const;
	int GetCreateDogma() const;
	bool RequiresPeace() const;
	bool ConvertsBarbarians() const;

	EraTypes GetObsoleteEra() const;
	ResourceTypes GetResourceRevealed() const;
	TechTypes GetSpreadModifierDoublingTech() const;

	const char* getShortDescription() const;
	// TODO: Phase1 audit CvBeliefEntry::setShortDescription(char const*): UNVERIFIED; BE/object instructions 14/14; Civ5 changed/new UNVERIFIED.
	void setShortDescription(const char* szVal);

	// Arrays
	// TODO: Phase1 audit CvBeliefEntry::GetCityYieldChange(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetCityYieldChange(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetHolyCityYieldChange(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetHolyCityYieldChange(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetYieldChangePerForeignCity(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetYieldChangePerForeignCity(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetYieldChangePerXForeignFollowers(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetYieldChangePerXForeignFollowers(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetResourceQuantityModifier(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetResourceQuantityModifier(int i) const;
	int GetImprovementYieldChange(ImprovementTypes eIndex1, YieldTypes eIndex2) const;
	int GetBuildingClassYieldChange(int i, int j) const;
	// TODO: Phase1 audit CvBeliefEntry::GetBuildingClassHealth(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetBuildingClassHealth(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetBuildingClassTourism(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetBuildingClassTourism(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetFeatureYieldChange(int, int) const: UNVERIFIED; BE/object instructions 10/10; Civ5 changed/new UNVERIFIED.
	int GetFeatureYieldChange(int i, int j) const;
	// TODO: Phase1 audit CvBeliefEntry::GetResourceYieldChange(int, int) const: UNVERIFIED; BE/object instructions 10/10; Civ5 changed/new UNVERIFIED.
	int GetResourceYieldChange(int i, int j) const;
	// TODO: Phase1 audit CvBeliefEntry::GetTerrainYieldChange(int, int) const: UNVERIFIED; BE/object instructions 10/10; Civ5 changed/new UNVERIFIED.
	int GetTerrainYieldChange(int i, int j) const;
	// TODO: Phase1 audit CvBeliefEntry::GetResourceHealth(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetResourceHealth(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetYieldChangeAnySpecialist(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetYieldChangeAnySpecialist(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetYieldChangeTradeRoute(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetYieldChangeTradeRoute(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetYieldChangeWorldWonder(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetYieldChangeWorldWonder(int i) const;
	// TODO: Phase1 audit CvBeliefEntry::GetMaxYieldModifierPerFollower(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetMaxYieldModifierPerFollower(int i) const;
	bool IsFaithUnitPurchaseEra(int i) const;
	bool IsBuildingClassEnabled(int i) const;

	// TODO: Phase1 audit CvBeliefEntry::CacheResults(Database::Results&, CvDatabaseUtility&): MISMATCH; BE/object instructions 850/807; Civ5 changed/new UNVERIFIED.
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

protected:
	int m_iMinPopulation;
	int m_iMinFollowers;
	int m_iMaxDistance;
	int m_iCityGrowthModifier;
	int m_iFaithFromKills;
	int m_iFaithFromDyingUnits;
	int m_iHealthNextToRiver;
	int m_iHealthPerCanyon;
	int m_iHealthPerCity;
	int m_iHealthPerXPeacefulForeignFollowers;
	int m_iPlotCultureCostModifier;
	int m_iCityRangeStrikeModifier;
	int m_iCombatModifierEnemyCities;
	int m_iCombatModifierFriendlyCities;
	int m_iFriendlyHealChange;
	int m_iCityStateFriendshipModifier;
	int m_iLandBarbarianConversionPercent;
	int m_iWonderProductionModifier;
	int m_iPlayerHealth;
	int m_iPlayerCultureModifier;

	float m_fHealthPerFollowingCity;

	int m_iGoldPerFollowingCity;
	int m_iGoldPerXFollowers;
	int m_iGoldWhenCityAdopts;
	int m_iSciencePerOtherReligionFollower;
	int m_iSpreadDistanceModifier;
	int m_iSpreadStrengthModifier;
	int m_iProphetStrengthModifier;
	int m_iProphetCostModifier;
	int m_iMissionaryStrengthModifier;
	int m_iMissionaryCostModifier;
	int m_iFriendlyCityStateSpreadModifier;
	int m_iCityStateMinimumInfluence;
	int m_iCityStateInfluenceModifier;
	int m_iOtherReligionPressureErosion;
	int m_iSpyPressure;
	int m_iInquisitorPressureRetention;
	int m_iFaithBuildingTourism;

	int m_iFaithCost;
	bool m_bCreatesCreed;
	int m_iCreatesDogma;
	bool m_bRequiresPeace;
	bool m_bConvertsBarbarians;

	EraTypes m_eObsoleteEra;
	ResourceTypes m_eResourceRevealed;
	TechTypes m_eSpreadModifierDoublingTech;

	CvString m_strShortDescription;

	// Arrays
	int* m_paiCityYieldChange;
	int* m_paiHolyCityYieldChange;
	int* m_paiYieldChangePerForeignCity;
	int* m_paiYieldChangePerXForeignFollowers;
	int* m_piResourceQuantityModifiers;
	int** m_ppiImprovementYieldChanges;
	int** m_ppiBuildingClassYieldChanges;
	int* m_paiBuildingClassHealth;
	int* m_paiBuildingClassTourism;
	int** m_ppaiFeatureYieldChange;
	int** m_ppaiResourceYieldChange;
	int** m_ppaiTerrainYieldChange;
	int* m_piResourceHealth;
	int* m_piYieldChangeAnySpecialist;
	int* m_piYieldChangeTradeRoute;
	int* m_piYieldChangeWorldWonder;
	int* m_piMaxYieldModifierPerFollower;
	bool* m_pbFaithPurchaseUnitEraEnabled;
    bool* m_pbBuildingClassEnabled;

private:
	// TODO: Phase1 audit CvBeliefEntry::CvBeliefEntry(): UNVERIFIED; BE/object instructions 31/31; Civ5 changed/new UNVERIFIED.
	CvBeliefEntry(const CvBeliefEntry&);
	// TODO: Phase1 audit CvBeliefEntry::operator =(const CvBeliefEntry &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	CvBeliefEntry& operator=(const CvBeliefEntry&);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvBeliefXMLEntries
//!  \brief		Game-wide information about religious beliefs
//
//! Key Attributes:
//! - Plan is it will be contained in CvGameRules object within CvGame class
//! - Populated from XML\GameInfo\CIV5Beliefs.xml
//! - Contains an array of CvBeliefEntry from the above XML file
//! - One instance for the entire game
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvBeliefXMLEntries
{
public:
	CvBeliefXMLEntries(void);
	// TODO: Phase1 audit CvBeliefXMLEntries::~CvBeliefXMLEntries(): UNVERIFIED; BE/object instructions 12/12; Civ5 changed/new UNVERIFIED.
	~CvBeliefXMLEntries(void);

	// Accessor functions
	std::vector<CvBeliefEntry*>& GetBeliefEntries();
	int GetNumBeliefs();
	CvBeliefEntry* GetEntry(int index);

	// TODO: Phase1 audit CvBeliefXMLEntries::DeleteArray(): MISMATCH; BE/object instructions 39/40; Civ5 changed/new UNVERIFIED.
	void DeleteArray();

private:
	std::vector<CvBeliefEntry*> m_paBeliefEntries;
};

typedef FStaticVector<int, 5, false, c_eCiv5GameplayDLL >BeliefList;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvReligionBeliefs
//!  \brief		Information about the beliefs of a religion
//
//!  Key Attributes:
//!  - One instance for each religion (or pantheon)
//!  - Accessed by any class that needs to check belief info
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvReligionBeliefs
{
public:
	// TODO: Phase1 audit CvReligionBeliefs::CvReligionBeliefs(CvReligionBeliefs const&): MISMATCH; BE/object instructions 123/78; Civ5 changed/new UNVERIFIED.
	// TODO: Phase1 audit CvReligionBeliefs::CvReligionBeliefs(): MISMATCH; BE/object instructions 26/11; Civ5 changed/new UNVERIFIED.
	CvReligionBeliefs(void);
	// TODO: Phase1 audit CvReligionBeliefs::~CvReligionBeliefs(): UNVERIFIED; BE/object instructions 20/20; Civ5 changed/new UNVERIFIED.
	~CvReligionBeliefs(void);
	// TODO: Phase1 audit CvReligionBeliefs::CvReligionBeliefs(CvReligionBeliefs const&): MISMATCH; BE/object instructions 123/78; Civ5 changed/new UNVERIFIED.
	// TODO: Phase1 audit CvReligionBeliefs::CvReligionBeliefs(): MISMATCH; BE/object instructions 26/11; Civ5 changed/new UNVERIFIED.
	CvReligionBeliefs(const CvReligionBeliefs& source);
	// TODO: Phase1 audit CvReligionBeliefs::Uninit(): UNVERIFIED; BE/object instructions 17/17; Civ5 changed/new UNVERIFIED.
	void Uninit();
	// TODO: Phase1 audit CvReligionBeliefs::Reset(): MISMATCH; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	void Reset();
	// TODO: Phase1 audit CvReligionBeliefs::AddBelief(BeliefTypes): MISMATCH; BE/object instructions 106/98; Civ5 changed/new UNVERIFIED.
	void AddBelief(BeliefTypes eBelief);

	// Accessor functions
	// TODO: Phase1 audit CvReligionBeliefs::HasBelief(BeliefTypes) const: UNVERIFIED; BE/object instructions 20/20; Civ5 changed/new UNVERIFIED.
	bool HasBelief(BeliefTypes eBelief) const;
	BeliefTypes GetBelief(int iIndex) const;
	int GetNumBeliefs() const;

	// TODO: Phase1 audit CvReligionBeliefs::GetFaithFromDyingUnits() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetFaithFromDyingUnits() const
	{
		return m_iFaithFromDyingUnits;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetHealthNextToRiver() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetHealthNextToRiver() const
	{
		return m_iHealthNextToRiver;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetHealthPerCanyon() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetHealthPerCanyon() const
	{
		return m_iHealthPerCanyon;
	}
	// TODO: Phase1 audit CvReligionBeliefs::GetPlotCultureCostModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetPlotCultureCostModifier() const
	{
		return m_iPlotCultureCostModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetCityRangeStrikeModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetCityRangeStrikeModifier() const
	{
		return m_iCityRangeStrikeModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetCombatModifierEnemyCities() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetCombatModifierEnemyCities() const
	{
		return m_iCombatModifierEnemyCities;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetCombatModifierFriendlyCities() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetCombatModifierFriendlyCities() const
	{
		return m_iCombatModifierFriendlyCities;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetFriendlyHealChange() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetFriendlyHealChange() const
	{
		return m_iFriendlyHealChange;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetCityStateFriendshipModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetCityStateFriendshipModifier() const
	{
		return m_iCityStateFriendshipModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetLandBarbarianConversionPercent() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetLandBarbarianConversionPercent() const
	{
		return m_iLandBarbarianConversionPercent;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetSpreadDistanceModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetSpreadDistanceModifier() const
	{
		return m_iSpreadDistanceModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetSpreadStrengthModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetSpreadStrengthModifier() const
	{
		return m_iSpreadStrengthModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetProphetStrengthModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetProphetStrengthModifier() const
	{
		return m_iProphetStrengthModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetProphetCostModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetProphetCostModifier() const
	{
		return m_iProphetCostModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetMissionaryStrengthModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetMissionaryStrengthModifier() const
	{
		return m_iMissionaryStrengthModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetMissionaryCostModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetMissionaryCostModifier() const
	{
		return m_iMissionaryCostModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetFriendlyCityStateSpreadModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetFriendlyCityStateSpreadModifier() const
	{
		return m_iFriendlyCityStateSpreadModifier;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetCityStateMinimumInfluence() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetCityStateMinimumInfluence() const
	{
		return m_iCityStateMinimumInfluence;
	}
	// TODO: Phase1 audit CvReligionBeliefs::GetCityStateInfluenceModifier() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetCityStateInfluenceModifier() const
	{
		return m_iCityStateInfluenceModifier;
	}
	// TODO: Phase1 audit CvReligionBeliefs::GetOtherReligionPressureErosion() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetOtherReligionPressureErosion() const
	{
		return m_iOtherReligionPressureErosion;
	}
	// TODO: Phase1 audit CvReligionBeliefs::GetSpyPressure() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetSpyPressure() const
	{
		return m_iSpyPressure;
	}
	// TODO: Phase1 audit CvReligionBeliefs::GetInquisitorPressureRetention() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetInquisitorPressureRetention() const
	{
		return m_iInquisitorPressureRetention;
	}
	// TODO: Phase1 audit CvReligionBeliefs::GetFaithBuildingTourism() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	int GetFaithBuildingTourism() const
	{
		return m_iFaithBuildingTourism;
	}

	// TODO: Phase1 audit CvReligionBeliefs::GetObsoleteEra() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	EraTypes GetObsoleteEra() const
	{
		return m_eObsoleteEra;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetResourceRevealed() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	ResourceTypes GetResourceRevealed() const
	{
		return m_eResourceRevealed;
	};
	// TODO: Phase1 audit CvReligionBeliefs::GetSpreadModifierDoublingTech() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	TechTypes GetSpreadModifierDoublingTech() const
	{
		return m_eSpreadModifierDoublingTech;
	};

	// TODO: Phase1 audit CvReligionBeliefs::GetFaithFromKills(int) const: UNVERIFIED; BE/object instructions 59/59; Civ5 changed/new UNVERIFIED.
	int GetFaithFromKills(int iDistance) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetHealthPerCity(int) const: UNVERIFIED; BE/object instructions 57/57; Civ5 changed/new UNVERIFIED.
	int GetHealthPerCity(int iPopulation) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetHealthPerXPeacefulForeignFollowers() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
	int GetHealthPerXPeacefulForeignFollowers() const;
	// TODO: Phase1 audit CvReligionBeliefs::GetWonderProductionModifier(EraTypes) const: UNVERIFIED; BE/object instructions 57/57; Civ5 changed/new UNVERIFIED.
	int GetWonderProductionModifier(EraTypes eWonderEra) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetPlayerHealth(bool) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetPlayerHealth(bool bAtPeace) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetPlayerCultureModifier(bool) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetPlayerCultureModifier(bool bAtPeace) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetHealthPerFollowingCity() const: UNVERIFIED; BE/object instructions 53/53; Civ5 changed/new UNVERIFIED.
	float GetHealthPerFollowingCity() const;
	// TODO: Phase1 audit CvReligionBeliefs::GetGoldPerFollowingCity() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
	int GetGoldPerFollowingCity() const;
	// TODO: Phase1 audit CvReligionBeliefs::GetGoldPerXFollowers() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
	int GetGoldPerXFollowers() const;
	// TODO: Phase1 audit CvReligionBeliefs::GetGoldWhenCityAdopts() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
	int GetGoldWhenCityAdopts() const;
	// TODO: Phase1 audit CvReligionBeliefs::GetSciencePerOtherReligionFollower() const: UNVERIFIED; BE/object instructions 54/54; Civ5 changed/new UNVERIFIED.
	int GetSciencePerOtherReligionFollower() const;
	// TODO: Phase1 audit CvReligionBeliefs::GetCityGrowthModifier(bool) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetCityGrowthModifier(bool bAtPeace) const;

	// TODO: Phase1 audit CvReligionBeliefs::GetCityYieldChange(int, YieldTypes) const: UNVERIFIED; BE/object instructions 61/61; Civ5 changed/new UNVERIFIED.
	int GetCityYieldChange(int iPopulation, YieldTypes eYield) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetHolyCityYieldChange(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetHolyCityYieldChange(YieldTypes eYield) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangePerForeignCity(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetYieldChangePerForeignCity(YieldTypes eYield) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangePerXForeignFollowers(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetYieldChangePerXForeignFollowers(YieldTypes eYield) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetResourceQuantityModifier(ResourceTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetResourceQuantityModifier(ResourceTypes eResource) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetImprovementYieldChange(ImprovementTypes, YieldTypes) const: UNVERIFIED; BE/object instructions 60/60; Civ5 changed/new UNVERIFIED.
	int GetImprovementYieldChange(ImprovementTypes eImprovement, YieldTypes eYield) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetBuildingClassYieldChange(BuildingClassTypes, YieldTypes, int) const: UNVERIFIED; BE/object instructions 64/64; Civ5 changed/new UNVERIFIED.
	int GetBuildingClassYieldChange(BuildingClassTypes eBuildingClass, YieldTypes eYieldType, int iFollowers) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetBuildingClassHealth(BuildingClassTypes, int) const: UNVERIFIED; BE/object instructions 61/61; Civ5 changed/new UNVERIFIED.
	int GetBuildingClassHealth(BuildingClassTypes eBuildingClass, int iFollowers) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetBuildingClassTourism(BuildingClassTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetBuildingClassTourism(BuildingClassTypes eBuildingClass) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetFeatureYieldChange(FeatureTypes, YieldTypes) const: UNVERIFIED; BE/object instructions 60/60; Civ5 changed/new UNVERIFIED.
	int GetFeatureYieldChange(FeatureTypes eFeature, YieldTypes eYieldType) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetResourceYieldChange(ResourceTypes, YieldTypes) const: UNVERIFIED; BE/object instructions 60/60; Civ5 changed/new UNVERIFIED.
	int GetResourceYieldChange(ResourceTypes eResource, YieldTypes eYieldType) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetTerrainYieldChange(TerrainTypes, YieldTypes) const: UNVERIFIED; BE/object instructions 60/60; Civ5 changed/new UNVERIFIED.
	int GetTerrainYieldChange(TerrainTypes eTerrain, YieldTypes eYieldType) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetResourceHealth(ResourceTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetResourceHealth(ResourceTypes eResource) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangeAnySpecialist(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetYieldChangeAnySpecialist(YieldTypes eYieldType) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangeTradeRoute(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetYieldChangeTradeRoute(YieldTypes eYieldType) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetYieldChangeWorldWonder(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetYieldChangeWorldWonder(YieldTypes eYieldType) const;
	// TODO: Phase1 audit CvReligionBeliefs::GetMaxYieldModifierPerFollower(YieldTypes) const: UNVERIFIED; BE/object instructions 58/58; Civ5 changed/new UNVERIFIED.
	int GetMaxYieldModifierPerFollower(YieldTypes eYieldType) const;

	bool IsBuildingClassEnabled(BuildingClassTypes eType) const;
	// TODO: Phase1 audit CvReligionBeliefs::IsFaithBuyingEnabled(EraTypes) const: UNVERIFIED; BE/object instructions 62/62; Civ5 changed/new UNVERIFIED.
	bool IsFaithBuyingEnabled(EraTypes eEra) const;
	// TODO: Phase1 audit CvReligionBeliefs::IsConvertsBarbarians() const: UNVERIFIED; BE/object instructions 56/56; Civ5 changed/new UNVERIFIED.
	bool IsConvertsBarbarians() const;

	// Serialization
	// TODO: Phase1 audit CvReligionBeliefs::Read(FDataStream&): UNVERIFIED; BE/object instructions 153/153; Civ5 changed/new UNVERIFIED.
	void Read(FDataStream& kStream);
	// TODO: Phase1 audit CvReligionBeliefs::Write(FDataStream&) const: UNVERIFIED; BE/object instructions 149/149; Civ5 changed/new UNVERIFIED.
	void Write(FDataStream& kStream) const;

private:
	// Cached data about this religion's beliefs
	int m_iFaithFromDyingUnits;
	int m_iHealthNextToRiver;
	int m_iHealthPerCanyon;
	int m_iPlotCultureCostModifier;
	int m_iCityRangeStrikeModifier;
	int m_iCombatModifierEnemyCities;
	int m_iCombatModifierFriendlyCities;
	int m_iFriendlyHealChange;
	int m_iCityStateFriendshipModifier;
	int m_iLandBarbarianConversionPercent;
	int m_iSpreadDistanceModifier;
	int m_iSpreadStrengthModifier;
	int m_iProphetStrengthModifier;
	int m_iProphetCostModifier;
	int m_iMissionaryStrengthModifier;
	int m_iMissionaryCostModifier;
	int m_iFriendlyCityStateSpreadModifier;
	int m_iCityStateMinimumInfluence;
	int m_iCityStateInfluenceModifier;
	int m_iOtherReligionPressureErosion;
	int m_iSpyPressure;
	int m_iInquisitorPressureRetention;
	int m_iFaithBuildingTourism;

	EraTypes m_eObsoleteEra;
	ResourceTypes m_eResourceRevealed;
	TechTypes m_eSpreadModifierDoublingTech;

	BeliefList m_ReligionBeliefs;

	// Arrays
	int* m_paiBuildingClassEnabled;
};


#endif
