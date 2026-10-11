#pragma once

class CvImprovementResourceInfo
{
	friend class CvImprovementEntry;
public:
	CvImprovementResourceInfo();
	// TODO: Phase1 audit CvImprovementResourceInfo::~CvImprovementResourceInfo(): UNVERIFIED; BE/object instructions 17/17; Civ5 changed/new UNVERIFIED.
	~CvImprovementResourceInfo();
	int getDiscoverRand() const;
	bool isResourceMakesValid() const;
	bool isResourceTrade() const;
	// TODO: Phase1 audit CvImprovementResourceInfo::getYieldChange(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int getYieldChange(int i) const;
private:
	int m_iDiscoverRand;
	bool m_bResourceMakesValid;
	bool m_bResourceTrade;
	int* m_piYieldChange;
};

class CvImprovementEntry : public CvBaseInfo
{
public:
	// TODO: Phase1 audit CvImprovementEntry::CvImprovementEntry(): UNVERIFIED; BE/object instructions 56/56; Civ5 changed/new UNVERIFIED.
	CvImprovementEntry();
	// TODO: Phase1 audit CvImprovementEntry::~CvImprovementEntry(): MISMATCH; BE/object instructions 161/151; Civ5 changed/new UNVERIFIED.
	~CvImprovementEntry();
	// TODO: Phase1 audit CvImprovementEntry::CacheResults(Database::Results&, CvDatabaseUtility&): MISMATCH; BE/object instructions 1127/1050; Civ5 changed/new UNVERIFIED.
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: Phase1 audit CvImprovementEntry::SetArtDefineTag(char const*): UNVERIFIED; BE/object instructions 14/14; Civ5 changed/new UNVERIFIED.
	void SetArtDefineTag(const char* szTag);
	const char* GetArtDefineTag() const;
	int GetEnergyMaintenance() const;
	int GetRequiresXAdjacentLand() const;
	int GetMinRangeToCity() const;
	int GetCultureAdjacentSameType() const;
	int GetTilesPerGoody() const;
	int GetGoodyUniqueRange() const;
	int GetUpgradeTime() const;
	int GetRiverSideUpgradeMod() const;
	int GetCoastalLandUpgradeMod() const;
	int GetHillsUpgradeMod() const;
	int GetFreshWaterUpgradeMod() const;
	int GetDefenseModifier() const;
	int GetNearbyEnemyDamage() const;
	int GetNearbyFriendlyHeal() const;
	int GetHealth() const;
	int GetUnhealth() const;
	int GetCityHP() const;
	int GetPillageEnergy() const;
	int GetResourceExtractionMod() const;
	int GetOrbitalCoverageForCity() const;
	int GetImprovementPillage() const;
	void SetImprovementPillage(int i);
	int GetImprovementUpgrade() const;
	void SetImprovementUpgrade(int i);
	bool IsHillsMakesValid() const;
	bool IsFreshWaterMakesValid() const;
	bool IsRiverSideMakesValid() const;
	bool IsNoFreshWater() const;
	bool IsNoMiasma() const;
	bool IsRequiresFlatlands() const;
	bool IsRequiresFlatlandsOrFreshWater() const;
	bool IsRequiresFeature() const;
	bool IsRequiresImprovement() const;
	bool IsRemovesAnyResource() const;
	bool IsRemovesArtifactResource() const;
	bool IsPromptWhenComplete() const;
	bool IsWater() const;
	bool IsCoastal() const;
	bool IsSelectable() const;
	bool IsCannotPillage() const;
	bool IsDestroyedWhenPillaged() const;
	bool IsDisplacePillager() const;
	bool IsBuildableOnAnyResource() const;
	bool IsGoody() const;
	bool IsPermanent() const;
	bool IsImpassable() const;
	bool IsOutsideBorders() const;
	bool IsOverrideYield() const;
	bool IsIgnoreOwnership() const;
	bool IsNoTwoAdjacent() const;
	bool IsAllowsWalkWater() const;
	bool IsInAdjacentFriendly() const;
	CivilizationTypes GetRequiredCivilization() const;
	bool ResourceStaysVisible() const;
	ImprovementUsageTypes GetImprovementUsage() const;
	void SetImprovementUsage(ImprovementUsageTypes eType);
	int GetWorldSoundscapeScriptId() const;
	// TODO: Phase1 audit CvImprovementEntry::RefreshWorldSoundscapeID(): UNVERIFIED; BE/object instructions 22/22; Civ5 changed/new UNVERIFIED.
	void RefreshWorldSoundscapeID();
	// TODO: Phase1 audit CvImprovementEntry::GetResourceQuantityRequirement(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetResourceQuantityRequirement(int i) const;
	// TODO: Phase1 audit CvImprovementEntry::GetPrereqNatureYield(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetPrereqNatureYield(int i) const;
	int* GetPrereqNatureYieldArray();
	int GetYieldChange(int i) const;
	int* GetYieldChangeArray();
	int GetYieldChangePerEra(int i) const;
	int GetRiverSideYieldChange(int i) const;
	int* GetRiverSideYieldChangeArray();
	int GetCoastalLandYieldChange(int i) const;
	int* GetCoastalLandYieldChangeArray();
	int GetHillsYieldChange(int i) const;
	int* GetHillsYieldChangeArray();
	int GetFreshWaterYieldChange(int i) const;
	int* GetFreshWaterYieldChangeArray();
	int GetAdjacentCityYieldChange(int i) const;
	int* GetAdjacentCityYieldChangeArray();
	int GetAdjacentMountainYieldChange(int i) const;
	int* GetAdjacentMountainYieldChangeArray();
	bool GetTerrainMakesValid(int i) const;
	bool GetFeatureMakesValid(int i) const;
	bool GetImprovementMakesValid(int i) const;
	int GetTechYieldChanges(int i, int j) const;
	int* GetTechYieldChangesArray(int i);
	int GetTechNoFreshWaterYieldChanges(int i, int j) const;
	int* GetTechNoFreshWaterYieldChangesArray(int i);
	int GetTechFreshWaterYieldChanges(int i, int j) const;
	int* GetTechFreshWaterYieldChangesArray(int i);
	int GetRouteYieldChanges(int i, int j) const;
	int* GetRouteYieldChangesArray(int i);
	int GetImprovementResourceYield(int i, int j) const;
	bool IsImprovementResourceMakesValid(int i) const;
	bool IsImprovementResourceTrade(int i) const;
	int GetImprovementResourceDiscoverRand(int i) const;
	int GetFlavorValue(int i) const;
private:
	// Member order follows Beyond Earth's i386 layout (entry size 0x154).
	int m_iCityHP;
	int m_iCoastalLandUpgradeMod;
	int m_iCultureAdjacentSameType;
	int m_iDefenseModifier;
	int m_iEnergyMaintenance;
	int m_iUnhealth;
	int m_iFreshWaterUpgradeMod;
	int m_iGoodyRange;
	int m_iHealth;
	int m_iHillsUpgradeMod;
	int m_iImprovementPillage;
	int m_iImprovementUpgrade;
	int m_iMinRangeToCity;
	int m_iNearbyEnemyDamage;
	int m_iNearbyFriendlyHeal;
	int m_iPillageEnergy;
	int m_iRequiresXAdjacentLand;
	int m_iResourceExtractionMod;
	int m_iRiverSideUpgradeMod;
	int m_iTilesPerGoody;
	int m_iUpgradeTime;
	int m_iOrbitalCoverageForCity;
	bool m_bAllowsWalkWater;
	bool m_bBuildableOnAnyResource;
	bool m_bCoastal;
	bool m_bDestroyedWhenPillaged;
	bool m_bDisplacePillager;
	bool m_bFreshWaterMakesValid;
	bool m_bGoody;
	bool m_bHillsMakesValid;
	bool m_bIgnoreOwnership;
	bool m_bImpassable;
	bool m_bInAdjacentFriendly;
	bool m_bNoFreshWater;
	bool m_bNoMiasma;
	bool m_bNoTwoAdjacent;
	bool m_bOutsideBorders;
	bool m_bOverrideYield;
	bool m_bPermanent;
	bool m_bPromptWhenComplete;
	bool m_bRemovesAnyResource;
	bool m_bRemovesArtifactResource;
	bool m_bRequiresFeature;
	bool m_bRequiresFlatlands;
	bool m_bRequiresFlatlandsOrFreshWater;
	bool m_bRequiresImprovement;
	bool m_bResourceStaysVisible;
	bool m_bRiverSideMakesValid;
	// TODO: Phase1 audit CvImprovementEntry layout: fabricated padding is prohibited; recover the authentic member at this location without an ABI shortcut.
	unsigned char m_paddingE6;
	bool m_bWater;
	bool m_bSelectable;
	bool m_bCannotPillage;
	CvString m_strArtDefineTag;
	ImprovementUsageTypes m_eImprovementUsageType;
	CivilizationTypes m_eRequiredCivilization;
	int m_iWorldSoundscapeScriptId;
	unsigned int m_uiWorldSoundscapeScriptHash;
	int* m_piResourceQuantityRequirements;
	int* m_piPrereqNatureYield;
	int* m_piYieldChange;
	int* m_piYieldPerEra;
	int* m_piRiverSideYieldChange;
	int* m_piCoastalLandYieldChange;
	int* m_piHillsYieldChange;
	int* m_piFreshWaterChange;
	int* m_piAdjacentCityYieldChange;
	int* m_piAdjacentMountainYieldChange;
	int* m_piFlavorValue;
	bool* m_pbTerrainMakesValid;
	bool* m_pbFeatureMakesValid;
	bool* m_pbImprovementMakesValid;
	int** m_ppiTechYieldChanges;
	int** m_ppiTechNoFreshWaterYieldChanges;
	int** m_ppiTechFreshWaterYieldChanges;
	int** m_ppiRouteYieldChanges;
	CvImprovementResourceInfo* m_paImprovementResource;
};

class CvImprovementXMLEntries
{
public:
	CvImprovementXMLEntries();
	// TODO: Phase1 audit CvImprovementXMLEntries::~CvImprovementXMLEntries(): UNVERIFIED; BE/object instructions 12/12; Civ5 changed/new UNVERIFIED.
	~CvImprovementXMLEntries();
	std::vector<CvImprovementEntry*>& GetImprovementEntries();
	int GetNumImprovements();
	CvImprovementEntry* GetEntry(int index);
	// TODO: Phase1 audit CvImprovementXMLEntries::GetImprovementForResource(int): MISMATCH; BE/object instructions 28/27; Civ5 changed/new UNVERIFIED.
	CvImprovementEntry* GetImprovementForResource(int eResource);
	// TODO: Phase1 audit CvImprovementXMLEntries::DeleteArray(): UNVERIFIED; BE/object instructions 39/39; Civ5 changed/new UNVERIFIED.
	void DeleteArray();
private:
	std::vector<CvImprovementEntry*> m_paImprovementEntries;
};

namespace ImprovementArrayHelpers
{
	// TODO: Phase1 audit ImprovementArrayHelpers::Read(FDataStream&, int*): MISMATCH; BE/object instructions 83/75; Civ5 changed/new UNVERIFIED.
	void Read(FDataStream& kStream, int* paiImprovementArray);
	// TODO: Phase1 audit ImprovementArrayHelpers::Write(FDataStream&, int*, int): UNVERIFIED; BE/object instructions 47/47; Civ5 changed/new UNVERIFIED.
	void Write(FDataStream& kStream, int* paiImprovementArray, int iArraySize);
	// TODO: Phase1 audit ImprovementArrayHelpers::ReadYieldArray(FDataStream&, int**, int): MISMATCH; BE/object instructions 116/106; Civ5 changed/new UNVERIFIED.
	void ReadYieldArray(FDataStream& kStream, int** ppaaiImprovementYieldArray, int iNumYields);
	// TODO: Phase1 audit ImprovementArrayHelpers::WriteYieldArray(FDataStream&, int**, int): UNVERIFIED; BE/object instructions 59/59; Civ5 changed/new UNVERIFIED.
	void WriteYieldArray(FDataStream& kStream, int** ppaaiImprovementYieldArray, int iArraySize);
}
