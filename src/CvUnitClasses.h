#pragma once

#include "CvInfos.h"
#include "CvGameCoreDLLUtil/include/CvStructs.h"
#include "CvCityNativeContainers.h"

struct UnitSupportMissionData
{
	int m_iStrength;
	int m_iRangeOverride;
	bool m_bTargetFriendly;
	bool m_bTargetNeutral;
	bool m_bTargetEnemy;
	CvString m_strPopupTextKey;
	// TODO: Phase1 audit UnitSupportMissionData::UnitSupportMissionData(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	UnitSupportMissionData(): m_iStrength(0), m_iRangeOverride(-1), m_bTargetFriendly(false), m_bTargetNeutral(false), m_bTargetEnemy(false) {}
};

// Mission-map specialization uses the target's native ASL lookup entry points.
namespace ASL { namespace StdLib { namespace HashMap {
template<>
class _Hash<_Umap_traits<MissionTypes, UnitSupportMissionData, _Uhash_compare<MissionTypes, hash<MissionTypes>, std::equal_to<MissionTypes> >, std::allocator<std::pair<const MissionTypes, UnitSupportMissionData> >, false> >: public _Umap_traits<MissionTypes, UnitSupportMissionData, _Uhash_compare<MissionTypes, hash<MissionTypes>, std::equal_to<MissionTypes> >, std::allocator<std::pair<const MissionTypes, UnitSupportMissionData> >, false>
{
	typedef MissionTypes K;
	typedef UnitSupportMissionData V;
	typedef _Uhash_compare<K, hash<K>, std::equal_to<K> > C;
	typedef std::allocator<std::pair<const K, V> > A;
public:
	typedef std::pair<const K, V> value_type;
	typedef std::list<value_type, A> List;
	typedef typename List::iterator iterator;
	typedef typename List::const_iterator const_iterator;
	// TODO: Phase1 audit ASL::StdLib::HashMap::_Hash::_Hash(const C &,const A &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	_Hash(const C&, const A&);
	// TODO: Phase1 audit ASL::StdLib::HashMap::_Hash::lower_bound(const K &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	iterator lower_bound(const K&);
	// TODO: Phase1 audit ASL::StdLib::HashMap::_Hash::lower_bound(const K &) const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	const_iterator lower_bound(const K&) const;
	// TODO: Phase1 audit ASL::StdLib::HashMap::_Hash::end() const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	const_iterator end() const { return m_list.end(); }
protected:
	List m_list;
	std::vector<iterator, typename A::template rebind<iterator>::other> m_buckets;
	size_t m_mask;
	size_t m_maxIndex;
	float m_maxBucketSize;
};
template<>
class unordered_map<MissionTypes, UnitSupportMissionData>: public _Hash<_Umap_traits<MissionTypes, UnitSupportMissionData, _Uhash_compare<MissionTypes, hash<MissionTypes>, std::equal_to<MissionTypes> >, std::allocator<std::pair<const MissionTypes, UnitSupportMissionData> >, false> >
{
	typedef MissionTypes K;
	typedef UnitSupportMissionData V;
	typedef hash<K> H;
	typedef std::equal_to<K> E;
	typedef std::allocator<std::pair<const K, V> > A;
	typedef _Hash<_Umap_traits<K, V, _Uhash_compare<K, H, E>, A, false> > Base;
public:
	// TODO: Phase1 audit ASL::StdLib::HashMap::unordered_map::unordered_map(): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	unordered_map(): Base(_Uhash_compare<K, H, E>(), A()) {}
	// TODO: Phase1 audit ASL::StdLib::HashMap::unordered_map::operator [](const K &): UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	V& operator[](const K&);
	// TODO: Phase1 audit ASL::StdLib::HashMap::unordered_map::at(const K &) const: UNVERIFIED; BE/object instructions UNVERIFIED/UNVERIFIED; Civ5 changed/new UNVERIFIED.
	const V& at(const K&) const;
};
}}}

class CvUnitEntry: public CvBaseInfo
{
public:
	// TODO: Phase1 audit CvUnitEntry::CvUnitEntry(): MISMATCH; BE/object instructions 125/93; Civ5 changed/new UNVERIFIED.
	CvUnitEntry();
	// TODO: Phase1 audit CvUnitEntry::~CvUnitEntry(): MISMATCH; BE/object instructions 220/204; Civ5 changed/new UNVERIFIED.
	~CvUnitEntry();
	// TODO: Phase1 audit CvUnitEntry::CacheResults(Database::Results&, CvDatabaseUtility&): MISMATCH; BE/object instructions 1379/1314; Civ5 changed/new UNVERIFIED.
	virtual bool CacheResults(Database::Results&, CvDatabaseUtility&);
	int GetAdvancedStartCost() const;
	int GetAirInterceptRange() const;
	int GetAirUnitCap() const;
	int GetBaseBeakersTurnsToCount() const;
	int GetBaseCultureTurnsToCount() const;
	int GetBaseHurry() const;
	int GetBaseSightRange() const;
	int GetCivilianAttackPriority() const;
	int GetCombat() const;
	int GetCombatLimit() const;
	int GetCommandType() const;
	int GetConscriptionValue() const;
	int GetDefaultUnitAIType() const;
	int GetDomainCargo() const;
	int GetDomainType() const;
	int GetExtraMaintenanceCost() const;
	int GetFreePolicies() const;
	int GetGoodyHutUpgradeUnitClass() const;
	int GetGroupDefinitions() const;
	int GetGroupSize() const;
	int GetHurryCostModifier() const;
	int GetHurryMultiplier() const;
	int GetLeaderExperience() const;
	int GetLeaderPromotion() const;
	int GetMinAreaSize() const;
	int GetMoves() const;
	int GetNumExpeditionCharges() const;
	int GetNumFreeTechs() const;
	int GetNumGoldPerEra() const;
	int GetNumUnitNames() const;
	int GetObsoleteTech() const;
	int GetOrbitalAttackRange() const;
	int GetOrbitalUnitType() const;
	int GetPolicyType() const;
	int GetPrereqAndTech() const;
	int GetPrereqPillageTech() const;
	int GetProductionCost() const;
	int GetProjectPrereq() const;
	int GetRange() const;
	int GetRangedCombat() const;
	int GetRangedCombatLimit() const;
	int GetSpaceshipProject() const;
	int GetSpecialCargo() const;
	int GetSpecialUnitType() const;
	int GetUnhealth() const;
	int GetUnitCaptureClassType() const;
	int GetUnitClassType() const;
	int GetUnitCombatType() const;
	int GetMeleeWaveSize() const;
	int GetRangedWaveSize() const;
	int GetWorkRate() const;
	int GetXPValueAttack() const;
	int GetXPValueDefense() const;
	int GetMeleeDefenseMod() const;
	int GetRangedDefenseMod() const;
	int GetAirDefenseMod() const;
	int GetCityStrikeDefenseMod() const;
	int GetOrbitalDefenseMod() const;
	int GetExtraAttacks() const;
	bool IsAlienColossus() const;
	bool IsAlienLifeform() const;
	bool IsNonsentient() const;
	bool IsAmphibiousAttack() const;
	bool IsCaptureWhileEmbarked() const;
	bool IsCoastalWalk() const;
	bool IsDeepWaterOnly() const;
	bool IsEarthlingSettler() const;
	bool IsFoodProduction() const;
	bool IsFound() const;
	bool IsFoundAbroad() const;
	bool IsIgnoreBuildingDefense() const;
	bool IsMechUnit() const;
	bool IsMilitaryProduction() const;
	bool IsMilitarySupport() const;
	bool CanMoveAfterPurchase() const;
	bool CanMoveAfterAttacking() const;
	bool IsImmobile() const;
	bool IsNoBadGoodies() const;
	bool IsNoMaintenance() const;
	bool IsPillage() const;
	bool IsPrereqResources() const;
	bool IsPurchaseOnly() const;
	bool IsRangeAttackOnlyInDomain() const;
	bool IsRivalTerritory() const;
	bool IsRushBuilding() const;
	bool IsSuicide() const;
	bool IsTrade() const;
	bool RevealInFog() const;
	bool BlockLineOfSight() const;
	bool IsWorker() const;
	bool HasInvisibility() const;
	int GetPower() const;
	bool GetUnitArtInfoCulturalVariation() const;
	bool GetUnitArtInfoEraVariation() const;
	bool GetUnitArtInfoUpgradeVariation() const;
	int GetUnitArtInfoVariationStart() const;
	bool GetUnitArtInfoAmphibiousVariation() const;
	void SetCombat(int);
	void SetCommandType(int);
	// TODO: Phase1 audit CvUnitEntry::DoUpdatePower(): UNVERIFIED; BE/object instructions 401/401; Civ5 changed/new UNVERIFIED.
	void DoUpdatePower();
	// TODO: Phase1 audit CvUnitEntry::IsOrbitalUnitType() const: UNVERIFIED; BE/object instructions 5/5; Civ5 changed/new UNVERIFIED.
	bool IsOrbitalUnitType() const;
	// TODO: Phase1 audit CvUnitEntry::GetPrereqAndTechs(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetPrereqAndTechs(int) const;
	// TODO: Phase1 audit CvUnitEntry::GetResourceQuantityRequirement(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetResourceQuantityRequirement(int) const;
	int GetAffinityPrereq(AffinityType) const;
	int GetBuildingProductionModifier(BuildingTypes) const;
	int GetYieldFromKills(YieldTypes) const;
	// TODO: Phase1 audit CvUnitEntry::GetProductionTraits(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	int GetProductionTraits(int) const;
	int GetFlavorValue(int) const;
	int GetUnitGroupRequired(int) const;
	bool GetUpgradeUnitClass(int) const;
	bool GetUnitAIType(int) const;
	bool GetNotUnitAIType(int) const;
	bool GetBuilds(int) const;
	bool GetBuildings(int) const;
	bool GetBuildingClassRequireds(int) const;
	bool GetFreePromotions(int) const;
	bool GetPassiveAbilities(int) const;
	// TODO: Phase1 audit CvUnitEntry::GetSupportMissions(int) const: UNVERIFIED; BE/object instructions 24/24; Civ5 changed/new UNVERIFIED.
	bool GetSupportMissions(int) const;
	// TODO: Phase1 audit CvUnitEntry::GetSupportMissionData(MissionTypes) const: MISMATCH; BE/object instructions 29/29; Civ5 changed/new UNVERIFIED.
	const UnitSupportMissionData* GetSupportMissionData(MissionTypes) const;
	const char* GetUnitArtInfoTag() const;
	// TODO: Phase1 audit CvUnitEntry::GetUnitNames(int) const: MISMATCH; BE/object instructions 64/66; Civ5 changed/new UNVERIFIED.
	const char* GetUnitNames(int) const;
	// TODO: Phase1 audit CvUnitEntry::GetGreatWorks(int) const: UNVERIFIED; BE/object instructions 8/8; Civ5 changed/new UNVERIFIED.
	GreatWorkType GetGreatWorks(int) const;
	// TODO: Phase1 audit CvUnitEntry::GetCargoSpace() const: UNVERIFIED; BE/object instructions 42/42; Civ5 changed/new UNVERIFIED.
	int GetCargoSpace() const;
	UnitMoveRate GetMoveRate(int) const;
protected:
	int m_iAdvancedStartCost;
	int m_iAirInterceptRange;
	int m_iAirUnitCap;
	int m_iBaseBeakersTurnsToCount;
	int m_iBaseCultureTurnsToCount;
	int m_iBaseHurry;
	int m_iBaseSightRange;
	int m_iCivilianAttackPriority;
	int m_iCombat;
	int m_iCombatLimit;
	int m_iCommandType;
	int m_iConscriptionValue;
	int m_iDefaultUnitAIType;
	int m_iDomainCargo;
	int m_iDomainType;
	int m_iEraOfProsperityTurns;
	int m_iExtraMaintenanceCost;
	int m_iFreePolicies;
	int m_iGoodyHutUpgradeUnitClass;
	int m_iGroupDefinitions;
	int m_iGroupSize;
	int m_iHurryCostModifier;
	int m_iHurryMultiplier;
	int m_iLeaderExperience;
	int m_iLeaderPromotion;
	int m_iMinAreaSize;
	int m_iMoves;
	int m_iNumExpeditionCharges;
	int m_iNumFreeTechs;
	int m_iNumGoldPerEra;
	int m_iNumUnitNames;
	int m_iObsoleteTech;
	int m_iOrbitalAttackRange;
	int m_iOrbitalUnitType;
	int m_iPolicyType;
	int m_iPrereqAndTech;
	int m_iPrereqPillageTech;
	int m_iProductionCost;
	int m_iProjectPrereq;
	int m_iRange;
	int m_iRangedCombat;
	int m_iRangedCombatLimit;
	int m_iSpaceshipProject;
	int m_iSpecialCargo;
	int m_iSpecialUnitType;
	int m_iUnhealth;
	int m_iUnitCaptureClassType;
	int m_iUnitClassType;
	int m_iUnitCombatType;
	int m_iMeleeWaveSize;
	int m_iRangedWaveSize;
	int m_iWorkRate;
	int m_iXPValueAttack;
	int m_iXPValueDefense;
	int m_iMeleeDefenseMod;
	int m_iRangedDefenseMod;
	int m_iAirDefenseMod;
	int m_iCityStrikeDefenseMod;
	int m_iOrbitalDefenseMod;
	int m_iExtraAttacks;
	bool m_bAlienColossus;
	bool m_bAlienLifeform;
	bool m_bNonsentient;
	bool m_bAmphibiousAttack;
	bool m_bCaptureWhileEmbarked;
	bool m_bCoastalWalk;
	bool m_bDeepWaterOnly;
	bool m_bEarthlingSettler;
	bool m_bFoodProduction;
	bool m_bFound;
	bool m_bFoundAbroad;
	bool m_bIgnoreBuildingDefense;
	bool m_bMechUnit;
	bool m_bMilitaryProduction;
	bool m_bMilitarySupport;
	bool m_bCanMoveAfterPurchase;
	bool m_bCanMoveAfterAttacking;
	bool m_bImmobile;
	bool m_bNoBadGoodies;
	bool m_bNoMaintenance;
	bool m_bPillage;
	bool m_bPrereqResources;
	bool m_bPurchaseOnly;
	bool m_bRangeAttackOnlyInDomain;
	bool m_bRivalTerritory;
	bool m_bRushBuilding;
	bool m_bSuicide;
	bool m_bTrade;
	bool m_bRevealInFog;
	bool m_bBlockLineOfSight;
	bool m_bWorker;
	bool m_bHasInvisibility;
	int m_iCachedPower;
	CvString m_strUnitArtInfoTag;
	bool m_iUnitArtInfoCulturalVariation;
	bool m_iUnitArtInfoEraVariation;
	bool m_iUnitArtInfoUpgradeVariation;
	int m_iUnitArtInfoVariationStart;
	bool m_iUnitArtInfoAmphibiousVariation;
	UnitMoveRate m_unitMoveRate[12];
	int* m_piPrereqAndTechs;
	int* m_piAffinityPrereqs;
	int* m_piResourceQuantityRequirements;
	int* m_piProductionTraits;
	int* m_piFlavorValue;
	int* m_piUnitGroupRequired;
	int* m_piProductionModifierBuildings;
	int* m_piYieldFromKills;
	int* m_piUnused;
	bool* m_pbUpgradeUnitClass;
	bool* m_pbUnitAIType;
	bool* m_pbNotUnitAIType;
	bool* m_pbBuilds;
	bool* m_pbBuildings;
	bool* m_pbBuildingClassRequireds;
	bool* m_pbFreePromotions;
	bool* m_pbPassiveAbilities;
	CvString* m_paszEarlyArtDefineTags;
	CvString* m_paszLateArtDefineTags;
	CvString* m_paszMiddleArtDefineTags;
	CvString* m_paszUnitNames;
	GreatWorkType* m_paeGreatWorks;
	ASL::StdLib::HashMap::unordered_map<MissionTypes, UnitSupportMissionData> m_supportMissions;
};

class CvUnitXMLEntries
{
public:
	CvUnitXMLEntries();
	// TODO: Phase1 audit CvUnitXMLEntries::~CvUnitXMLEntries(): UNVERIFIED; BE/object instructions 12/12; Civ5 changed/new UNVERIFIED.
	~CvUnitXMLEntries();
	std::vector<CvUnitEntry*>& GetUnitEntries();
	int GetNumUnits();
	int GetNumUnits() const { return m_paUnitEntries.size(); }
	// TODO: Phase1 audit CvUnitXMLEntries::DeleteArray(): MISMATCH; BE/object instructions 39/38; Civ5 changed/new UNVERIFIED.
	void DeleteArray();
	CvUnitEntry* GetEntry(int);
	CvUnitEntry* GetEntry(int) const;
private:
	std::vector<CvUnitEntry*> m_paUnitEntries;
};

namespace UnitArrayHelpers
{
// TODO: Phase1 audit UnitArrayHelpers::Read(FDataStream&, int*): UNVERIFIED; BE/object instructions 21/21; Civ5 changed/new UNVERIFIED.
void Read(FDataStream&, int*);
// TODO: Phase1 audit UnitArrayHelpers::Write(FDataStream&, int*, int): UNVERIFIED; BE/object instructions 5/5; Civ5 changed/new UNVERIFIED.
void Write(FDataStream&, int*, int);
}
