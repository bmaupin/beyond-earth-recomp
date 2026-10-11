#pragma once

#include <list>
#include <map>
#include <array>
#include "CvCityNativeContainers.h"
#include "CvDllContextNativeContainers.h"
#include "CvGameCoreDLLUtil/include/LinkedList.h"
#include "Fireworks/FAutoVariable.h"
#include "CvUnitCycler.h"
#include "CvPlayerAchievements.h"
#include "CvPlotsVector.h"
#include "CvPreGame.h"

class CvCityAI;
class CvArmyAI;
class CvAIOperation;

template<class T> class CLLNode;
class CvFlavorManager;
class CvEconomicAI;
class CvMilitaryAI;
class CvWonderProductionAI;

class CvCity;
class CvPlayerTechs;
class CvMinorCivAI;

enum PlayerPerkTypes
{
	NO_PLAYER_PERK = -1
};

struct PlayerPerkHandle
{
	PlayerPerkTypes m_type;
	int m_cityID;
	int m_turnExpiration;
};

class CvQuest
{
public:
	int GetTechAIWeight(TechTypes eTech) const;
};

class CvPlayerAffinities
{
public:
	int GetAffinityLevel(AffinityType eAffinity) const;
	AffinityType GetDominantAffinityType() const;
	int GetAffinityPercentTowardsMaxLevel(AffinityType eAffinity) const;
};

class CvGrandStrategyAI
{
public:
	const CvQuest* GetActiveGrandStrategyQuest() const;
	AIGrandStrategyTypes GetActiveGrandStrategy() const;
	int GetPersonalityAndGrandStrategy(FlavorTypes eFlavor);
	AffinityType GetVictoryAffinityNeed(int* piNeed) const;
};

class CvPlayer;
class CvPlayerPerks
{
public:
	virtual ~CvPlayerPerks();

	int GetCityMoveCostMod(const CvCity& city) const;
	int GetAquaticCityMoveCostMod() const
	{
		return m_aquaticCityMoveCostMod;
	}
	int GetGlobalYieldPerTurnTimes100(YieldTypes eYield) const;

private:
	CvPlayer& m_player;
	std::list<PlayerPerkHandle> m_activePerks;
	int m_covertAgentRankRateChange;
	int m_expeditionSpeedMod;
	int m_unitVisibilityRangeChange;
	int m_navalMovementChange;
	int m_orbitalStrikeRangeChange;
	int m_outpostOrbitalCoverageChange;
	int m_stationOrbitalCoverageChange;
	int m_alienOpinionRecoveryMod;
	int m_orbitalCoverageCombatMod;
	int m_orbitalProductionModPerLaunchedUnit;
	int m_orbitalResourceCostChange;
	int m_orbitalUnitDurationMod;
	int m_aquaticCityMoveCostMod;
};

class CvOutpost;
class CvUnit;
class CvPlot;
class CvTreasury;
class CvDiplomacyAI;
class CvDealAI;
class CvNotifications;
class CvPlayerTraits
{
public:
	int GetSpecialistYieldChange(SpecialistTypes eSpecialist, YieldTypes eYield) const;
};
class CvPlayerLoadout;
class CvPlayerCovertOps;
class CvDiplomacyRequests;
class CvPlayerUnitUpgrades;

class CvBuilderTaskingAI;
class CvCityConnections;
class CvCitySpecializationAI;
class CvCovertOpsAI;
class CvDangerPlots;
class CvDealAI;
class CvDiplomacyAI;
class CvDiplomacyRequests;
class CvEconomicAI;
class CvEspionageAI;
class CvFlavorManager;
class CvGrandStrategyAI;
class CvHomelandAI;
class CvHostilityAI;
class CvLeagueAI;
class CvMilitaryAI;
class CvMinorCivAI;
class CvNotifications;
class CvOrbitalAI;
class CvPersonalityAI;
class CvPlayerAffinities;
class CvPlayerArtifacts;
class CvPlayerCovertOps;
class CvPlayerCulture;
class CvPlayerDiplomacy;
class CvPlayerEspionage;
class CvPlayerLoadout;
class CvPlayerMarvelRewards;
class CvPlayerMarvels;
class CvPlayerOrbitals;
class CvPlayerPerks;
class CvPlayerPersonality;
class CvPlayerPolicies;
class CvPlayerQuests;
class CvPlayerReligions;
class CvPlayerTechs;
class CvPlayerTrade;
class CvPlayerTraits;
class CvPlayerUnitUpgrades;
class CvReligionAI;
class CvTacticalAI;
class CvTradeAI;
class CvTreasury;
class CvWonderProductionAI;

enum EndTurnBlockingTypes
{
	NO_ENDTURN_BLOCKING_TYPE = -1,
	ENDTURN_BLOCKING_POLICY,
	ENDTURN_BLOCKING_RESEARCH,
	ENDTURN_BLOCKING_PRODUCTION,
	ENDTURN_BLOCKING_UNITS,
	ENDTURN_BLOCKING_DIPLO_VOTE,
	ENDTURN_BLOCKING_MINOR_QUEST,
	ENDTURN_BLOCKING_FREE_TECH,
	ENDTURN_BLOCKING_STACKED_UNITS,
	ENDTURN_BLOCKING_UNIT_NEEDS_ORDERS,
	ENDTURN_BLOCKING_UNIT_PROMOTION,
	ENDTURN_BLOCKING_CITY_RANGE_ATTACK,
	ENDTURN_BLOCKING_FREE_POLICY,
	ENDTURN_BLOCKING_FREE_ITEMS,
	ENDTURN_BLOCKING_FOUND_PANTHEON,
	ENDTURN_BLOCKING_FOUND_RELIGION,
	ENDTURN_BLOCKING_ENHANCE_RELIGION,
	ENDTURN_BLOCKING_STEAL_TECH,
	ENDTURN_BLOCKING_MAYA_LONG_COUNT,
	ENDTURN_BLOCKING_FAITH_GREAT_PERSON,
	ENDTURN_BLOCKING_ADD_REFORMATION_BELIEF,
	ENDTURN_BLOCKING_LEAGUE_CALL_FOR_PROPOSALS,
	ENDTURN_BLOCKING_CHOOSE_ARCHAEOLOGY,
	ENDTURN_BLOCKING_LEAGUE_CALL_FOR_VOTES,
	ENDTURN_BLOCKING_CHOOSE_IDEOLOGY,
	ENDTURN_BLOCKING_QUEST_PROMPT,
	ENDTURN_BLOCKING_UNIT_UPGRADE_PROMPT,
	ENDTURN_BLOCKING_FREE_AFFINITY_LEVEL,
	ENDTURN_BLOCKING_PLANETFALL,
	ENDTURN_BLOCKING_SELECT_NATIONAL_SECURITY_PROJECT,
	ENDTURN_BLOCKING_DIPLOMACY_PENDING_TRANSACTIONS,
	NUM_ENDTURN_BLOCKING_TYPES
};

class CvPlayer
{
protected:
	class ConqueredByBoolField
	{
	public:
		enum { eCount = 4, eSize = 32 };
		DWORD m_dwBits[eCount];
	};

	FAutoArchiveClassContainer<CvPlayer> m_syncArchive;
	FAutoVariable<PlayerTypes, CvPlayer> m_eID;
	FAutoVariable<LeaderHeadTypes, CvPlayer> m_ePersonalityType;
	FAutoVariable<int, CvPlayer> m_iStartingX;
	FAutoVariable<int, CvPlayer> m_iStartingY;
	FAutoVariable<int, CvPlayer> m_iTotalPopulation;
	FAutoVariable<int, CvPlayer> m_iTotalLand;
	FAutoVariable<int, CvPlayer> m_iTotalLandScored;
	FAutoVariable<int, CvPlayer> m_iCulturePerTurnForFree;
	FAutoVariable<int, CvPlayer> m_iCulturePerTurnFromMinorCivs;
	FAutoVariable<int, CvPlayer> m_iCultureCityModifier;
	FAutoVariable<int, CvPlayer> m_iCulture;
	FAutoVariable<int, CvPlayer> m_iCultureEverGenerated;
	FAutoVariable<int, CvPlayer> m_iCulturePerWonder;
	FAutoVariable<int, CvPlayer> m_iCultureWonderMultiplier;
	FAutoVariable<int, CvPlayer> m_iCulturePerTechResearched;
	int m_iFaith;
	int m_iFaithEverGenerated;
	int m_iDiplomaticCapital;
	int m_iDiplomaticCapitalEverGenerated;
	int m_iTradeRoutesMiasmaImmuneCount;
	FAutoVariable<int, CvPlayer> m_iHealth;
	FAutoVariable<int, CvPlayer> m_iUnhealth;
	FAutoVariable<int, CvPlayer> m_iUprisingCounter;
	FAutoVariable<int, CvPlayer> m_iExtraHealthPerLuxury;
	FAutoVariable<int, CvPlayer> m_iUnhealthFromUnits;
	FAutoVariable<int, CvPlayer> m_iUnhealthFromUnitsMod;
	FAutoVariable<int, CvPlayer> m_iUnhealthMod;
	FAutoVariable<int, CvPlayer> m_iCityCountUnhealthMod;
	FAutoVariable<int, CvPlayer> m_iOccupiedPopulationUnhealthMod;
	FAutoVariable<int, CvPlayer> m_iCapitalUnhealthMod;
	FAutoVariable<int, CvPlayer> m_iCityRevoltCounter;
	FAutoVariable<int, CvPlayer> m_iHealthPerGarrisonedUnitCount;
	FAutoVariable<int, CvPlayer> m_iHealthPerTradeRouteCount;
	int m_iHealthPerXPopulation;
	int m_iHealthFromLeagues;
	FAutoVariable<int, CvPlayer> m_iResearchFromDiplomacy;
	FAutoVariable<int, CvPlayer> m_iWoundedUnitDamageMod;
	FAutoVariable<int, CvPlayer> m_iUnitUpgradeCostMod;
	FAutoVariable<int, CvPlayer> m_iAlienCombatBonus;
	FAutoVariable<int, CvPlayer> m_iAlwaysSeeAlienNestsCount;
	FAutoVariable<int, CvPlayer> m_iHealthFromBuildings;
	FAutoVariable<int, CvPlayer> m_iHealthPerCity;
	int m_iHealthPerXPolicies;
	int m_iEspionageModifier;
	int m_iSpyStartingRank;
	int m_iExtraLeagueVotes;
	FAutoVariable<int, CvPlayer> m_iAdvancedStartPoints;
	FAutoVariable<int, CvPlayer> m_iAttackBonusTurns;
	int m_iCultureBonusTurns;
	int m_iTourismBonusTurns;
	FAutoVariable<int, CvPlayer> m_iEraOfProsperityProgressMeter;
	FAutoVariable<int, CvPlayer> m_iEraOfProsperityMeterMod;
	FAutoVariable<int, CvPlayer> m_iNumErasOfProsperity;
	FAutoVariable<int, CvPlayer> m_iEraOfProsperityTurns;
	FAutoVariable<int, CvPlayer> m_iNumUnitErasOfProsperity;
	FAutoVariable<int, CvPlayer> m_iStrikeTurns;
	FAutoVariable<int, CvPlayer> m_iEraOfProsperityModifier;
	FAutoVariable<int, CvPlayer> m_iAnarchyNumTurns;
	FAutoVariable<int, CvPlayer> m_iPolicyCostModifier;
	FAutoVariable<int, CvPlayer> m_iMaxGlobalBuildingProductionModifier;
	FAutoVariable<int, CvPlayer> m_iMaxTeamBuildingProductionModifier;
	FAutoVariable<int, CvPlayer> m_iMaxPlayerBuildingProductionModifier;
	FAutoVariable<int, CvPlayer> m_iExtraExperienceLevelsAllowed;
	FAutoVariable<int, CvPlayer> m_iFreeExperience;
	FAutoVariable<int, CvPlayer> m_iFreeExperienceFromBldgs;
	FAutoVariable<int, CvPlayer> m_iFreeExperienceFromMinors;
	FAutoVariable<int, CvPlayer> m_iFeatureProductionModifier;
	FAutoVariable<int, CvPlayer> m_iWorkerSpeedModifier;
	FAutoVariable<int, CvPlayer> m_iImprovementCostModifier;
	FAutoVariable<int, CvPlayer> m_iImprovementUpgradeRateModifier;
	FAutoVariable<int, CvPlayer> m_iSpecialistProductionModifier;
	FAutoVariable<int, CvPlayer> m_iMilitaryProductionModifier;
	FAutoVariable<int, CvPlayer> m_iOrbitalProductionModifier;
	FAutoVariable<int, CvPlayer> m_iOrbitalDurationModifier;
	FAutoVariable<int, CvPlayer> m_iSpaceProductionModifier;
	FAutoVariable<int, CvPlayer> m_iCityDefenseModifier;
	FAutoVariable<int, CvPlayer> m_iUnitFortificationModifier;
	FAutoVariable<int, CvPlayer> m_iUnitBaseHealModifier;
	FAutoVariable<int, CvPlayer> m_iUnitBaseMiasmaHeal;
	FAutoVariable<int, CvPlayer> m_iUnitBaseMiasmaDamage;
	FAutoVariable<int, CvPlayer> m_iWonderProductionModifier;
	FAutoVariable<int, CvPlayer> m_iSettlerProductionModifier;
	FAutoVariable<int, CvPlayer> m_iCapitalSettlerProductionModifier;
	FAutoVariable<int, CvPlayer> m_iUnitProductionMaintenanceMod;
	FAutoVariable<int, CvPlayer> m_iPolicyCostBuildingModifier;
	FAutoVariable<int, CvPlayer> m_iPolicyCostMinorCivModifier;
	int m_iInfluenceSpreadModifier;
	int m_iExtraVotesPerDiplomat;
	FAutoVariable<int, CvPlayer> m_iNumNukeUnits;
	FAutoVariable<int, CvPlayer> m_iNumOutsideUnits;
	FAutoVariable<int, CvPlayer> m_iBaseFreeUnits;
	FAutoVariable<int, CvPlayer> m_iBaseFreeMilitaryUnits;
	FAutoVariable<int, CvPlayer> m_iFreeUnitsPopulationPercent;
	FAutoVariable<int, CvPlayer> m_iFreeMilitaryUnitsPopulationPercent;
	FAutoVariable<int, CvPlayer> m_iGoldPerUnit;
	FAutoVariable<int, CvPlayer> m_iGoldPerMilitaryUnit;
	FAutoVariable<int, CvPlayer> m_iRouteEnergyMaintenanceMod;
	FAutoVariable<int, CvPlayer> m_iBuildingGoldMaintenanceMod;
	FAutoVariable<int, CvPlayer> m_iUnitGoldMaintenanceMod;
	FAutoVariable<int, CvPlayer> m_iUnitSupplyMod;
	FAutoVariable<int, CvPlayer> m_iExtraUnitCost;
	FAutoVariable<int, CvPlayer> m_iNumMilitaryUnits;
	FAutoVariable<int, CvPlayer> m_iHealthPerMilitaryUnit;
	FAutoVariable<int, CvPlayer> m_iHealthToCulture;
	FAutoVariable<int, CvPlayer> m_iHealthToScience;
	FAutoVariable<int, CvPlayer> m_iHalfSpecialistUnhealthCount;
	FAutoVariable<int, CvPlayer> m_iHalfSpecialistFoodCount;
	FAutoVariable<int, CvPlayer> m_iMilitaryFoodProductionCount;
	int m_iEraOfProsperityCultureBonusDisabledCount;
	int m_iSecondReligionPantheonCount;
	int m_iEnablesSSPartHurryCount;
	int m_iEnablesSSPartPurchaseCount;
	FAutoVariable<int, CvPlayer> m_iConscriptCount;
	FAutoVariable<int, CvPlayer> m_iMaxConscript;
	FAutoVariable<int, CvPlayer> m_iHighestUnitLevel;
	FAutoVariable<int, CvPlayer> m_iOverflowResearch;
	FAutoVariable<int, CvPlayer> m_iExpModifier;
	FAutoVariable<int, CvPlayer> m_iExpInBorderModifier;
	FAutoVariable<int, CvPlayer> m_iLevelExperienceModifier;
	FAutoVariable<int, CvPlayer> m_iMinorQuestFriendshipMod;
	FAutoVariable<int, CvPlayer> m_iMinorGoldFriendshipMod;
	FAutoVariable<int, CvPlayer> m_iMinorFriendshipMinimum;
	FAutoVariable<int, CvPlayer> m_iMinorFriendshipDecayMod;
	FAutoVariable<int, CvPlayer> m_iMinorScienceAlliesCount;
	FAutoVariable<int, CvPlayer> m_iMinorResourceBonusCount;
	int m_iAbleToAnnexCityStatesCount;
	FAutoVariable<int, CvPlayer> m_iCaptureOutpostsForSelfCount;
	FAutoVariable<int, CvPlayer> m_iExtraExplorerExpeditionCharges;
	FAutoVariable<int, CvPlayer> m_iExpeditionsEverCompleted;
	FAutoVariable<int, CvPlayer> m_iCovertOpsIntrigueModifier;
	int m_iCovertOpsCounterIntelModifier;
	FAutoVariable<int, CvPlayer> m_iCovertOpsLengthModifier;
	FAutoVariable<int, CvPlayer> m_iExtraOrbitalCoverageRadius;
	FAutoVariable<int, CvPlayer> m_iGlobalGrowthCarryover;
	FAutoVariable<int, CvPlayer> m_iOrbitalCoverageRadiusFromStationTrade;
	FAutoVariable<int, CvPlayer> m_iFreeSpecialist;
	FAutoVariable<int, CvPlayer> m_iCultureBombTimer;
	FAutoVariable<int, CvPlayer> m_iConversionTimer;
	FAutoVariable<int, CvPlayer> m_iCapitalCityID;
	FAutoVariable<int, CvPlayer> m_iCitiesLost;
	FAutoVariable<int, CvPlayer> m_iMilitaryMight;
	FAutoVariable<int, CvPlayer> m_iEconomicMight;
	FAutoVariable<int, CvPlayer> m_iTurnMightRecomputed;
	FAutoVariable<int, CvPlayer> m_iNewCityExtraPopulation;
	FAutoVariable<int, CvPlayer> m_iFreeFoodBox;
	FAutoVariable<int, CvPlayer> m_iScenarioScore1;
	FAutoVariable<int, CvPlayer> m_iScenarioScore2;
	FAutoVariable<int, CvPlayer> m_iScenarioScore3;
	FAutoVariable<int, CvPlayer> m_iScenarioScore4;
	FAutoVariable<int, CvPlayer> m_iScoreFromFutureTech;
	FAutoVariable<int, CvPlayer> m_iScoreFromFuturePolicies;
	FAutoVariable<int, CvPlayer> m_iCombatExperience;
	int m_iLifetimeCombatExperience;
	int m_iNavalCombatExperience;
	int m_iBorderObstacleCount;
	FAutoVariable<int, CvPlayer> m_iPopRushHurryCount;
	FAutoVariable<int, CvPlayer> m_iTotalImprovementsBuilt;
	FAutoVariable<int, CvPlayer> m_iNumPermanentsBuilt;
	FAutoVariable<int, CvPlayer> m_iNextOperationID;
	FAutoVariable<int, CvPlayer> m_iCostNextPolicy;
	FAutoVariable<int, CvPlayer> m_iNumBuilders;
	FAutoVariable<int, CvPlayer> m_iMaxNumBuilders;
	FAutoVariable<int, CvPlayer> m_iCityStrengthMod;
	FAutoVariable<int, CvPlayer> m_iCityGrowthMod;
	FAutoVariable<int, CvPlayer> m_iCapitalGrowthMod;
	FAutoVariable<int, CvPlayer> m_iNumPlotsBought;
	FAutoVariable<int, CvPlayer> m_iPlotGoldCostMod;
	FAutoVariable<int, CvPlayer> m_iPlotCultureCostModifier;
	int m_iPlotCultureExponentModifier;
	int m_iNumCitiesPolicyCostDiscount;
	int m_iNumCitiesResearchCostDiscount;
	int m_iGarrisonedCityRangeStrikeModifier;
	int m_iGarrisonFreeMaintenanceCount;
	int m_iNumCitiesFreeCultureBuilding;
	int m_iNumCitiesFreeFoodBuilding;
	FAutoVariable<int, CvPlayer> m_iUnitPurchaseCostModifier;
	FAutoVariable<int, CvPlayer> m_iAllFeatureProduction;
	FAutoVariable<int, CvPlayer> m_iCityDistanceHighwaterMark;
	FAutoVariable<int, CvPlayer> m_iOriginalCapitalX;
	FAutoVariable<int, CvPlayer> m_iOriginalCapitalY;
	FAutoVariable<int, CvPlayer> m_iNumWonders;
	FAutoVariable<int, CvPlayer> m_iNumPolicies;
	FAutoVariable<int, CvPlayer> m_iCityConnectionHealth;
	FAutoVariable<int, CvPlayer> m_iHolyCityID;
	FAutoVariable<int, CvPlayer> m_iTurnsSinceSettledLastCity;
	FAutoVariable<int, CvPlayer> m_iStrategicResourceMod;
	FAutoVariable<int, CvPlayer> m_iSpecialistCultureChange;
	FAutoVariable<int, CvPlayer> m_iFreeTechCount;
	FAutoVariable<int, CvPlayer> m_iNumFreePolicies;
	FAutoVariable<int, CvPlayer> m_iNumFreePoliciesEver;
	FAutoVariable<int, CvPlayer> m_iOutpostTradeGrowthMod;
	FAutoVariable<int, CvPlayer> m_iNumFreeAffinityLevels;
	int m_iMedianTechPercentage;
	int m_iNumFreeTenets;
	int m_iMaxEffectiveCities;
	int m_iLastSliceMoved;
	FAutoVariable<unsigned int, CvPlayer> m_uiStartTime;
	FAutoVariable<bool, CvPlayer> m_bHasBetrayedMinorCiv;
	FAutoVariable<bool, CvPlayer> m_bAlive;
	FAutoVariable<bool, CvPlayer> m_bEverAlive;
	bool m_bBeingResurrected;
	FAutoVariable<bool, CvPlayer> m_bTurnActive;
	FAutoVariable<bool, CvPlayer> m_bAutoMoves;
	bool m_bProcessedAutoMoves;
	FAutoVariable<bool, CvPlayer> m_bEndTurn;
	bool m_bDynamicTurnsSimultMode;
	FAutoVariable<bool, CvPlayer> m_bPbemNewTurn;
	FAutoVariable<bool, CvPlayer> m_bExtendedGame;
	FAutoVariable<bool, CvPlayer> m_bFoundedFirstCity;
	int m_iNumCitiesFounded;
	FAutoVariable<bool, CvPlayer> m_bStrike;
	FAutoVariable<bool, CvPlayer> m_bCramped;
	FAutoVariable<bool, CvPlayer> m_bLostCapital;
	PlayerTypes m_eConqueror;
	FAutoVariable<bool, CvPlayer> m_bHasAdoptedStateReligion;
	FAutoVariable<bool, CvPlayer> m_bHasMadePlanetfall;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiCityYieldChange;
	std::vector<int, std::allocator<int> > m_aiCityYieldPerPopChange;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiCoastalCityYieldChange;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiCapitalYieldChange;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiCapitalYieldPerPopChange;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiSeaPlotYield;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiYieldRateModifier;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiCapitalYieldRateModifier;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiExtraYieldThreshold;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiSpecialistExtraYield;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiTradeRouteWithStationPerTierYieldChanges;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiProximityToPlayer;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiIncomingUnitTypes;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiIncomingUnitCountdowns;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_aiMinorFriendshipAnchors;
	std::vector<int, std::allocator<int> > m_aiSiphonLuxuryCount;
	std::vector<int, std::allocator<int> > m_aiGreatWorkYieldChange;
	FAutoVariable<std::vector<std::pair<unsigned int, int>, std::allocator<std::pair<unsigned int, int> > >, CvPlayer> m_aOptions;
	FAutoVariable<CvString, CvPlayer> m_strReligionKey;
	FAutoVariable<CvString, CvPlayer> m_strScriptData;
	CvString m_strEmbarkedGraphicOverride;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiNumResourceUsed;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiNumResourceTotal;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiResourceGiftedToMinors;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiResourceExport;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiResourceImport;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiResourceFromMinors;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiResourcesSiphoned;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiImprovementCount;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiFreeBuildingCount;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiFreePromotionCount;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiUnitCombatProductionModifiers;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiUnitCombatFreeExperiences;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiUnitClassCount;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiUnitClassMaking;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiBuildingClassCount;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiBuildingClassMaking;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiProjectMaking;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiHurryCount;
	FAutoVariable<std::vector<int, std::allocator<int> >, CvPlayer> m_paiHurryModifier;
	FAutoVariable<std::vector<bool, std::allocator<bool> >, CvPlayer> m_pabLoyalMember;
	FAutoVariable<std::vector<bool, std::allocator<bool> >, CvPlayer> m_pabGetsScienceFromPlayer;
	FAutoVariable<std::vector<Firaxis::Array<int, 7>, std::allocator<Firaxis::Array<int, 7> > >, CvPlayer> m_ppaaiSpecialistExtraYield;
	FAutoVariable<std::vector<Firaxis::Array<int, 7>, std::allocator<Firaxis::Array<int, 7> > >, CvPlayer> m_ppaaiImprovementYieldChange;
	FAutoVariable<std::vector<Firaxis::Array<int, 7>, std::allocator<Firaxis::Array<int, 7> > >, CvPlayer> m_ppaaiImprovementYieldModifier;
	FAutoVariable<std::vector<Firaxis::Array<int, 7>, std::allocator<Firaxis::Array<int, 7> > >, CvPlayer> m_ppaaiBuildingClassYieldMod;
	CvUnitCycler m_UnitCycle;
	FAutoVariable<bool, CvPlayer> m_bEverPoppedGoody;
	FAutoVariable<bool, CvPlayer> m_bEverTrainedBuilder;
	EndTurnBlockingTypes m_eEndTurnBlockingType;
	int m_iEndTurnBlockingNotificationIndex;
	CLinkList<TechTypes> m_researchQueue;
	CLinkList<CvString> m_cityNames;
	FFreeListTrashArray<CvCityAI> m_cities;
	FFreeListTrashArray<CvOutpost> m_outposts;
	FFreeListTrashArray<CvUnit> m_units;
	FFreeListTrashArray<CvArmyAI> m_armyAIs;
	std::map<int, CvAIOperation*, std::less<int>, std::allocator<std::pair<int const, CvAIOperation*> > > m_AIOperations;
	std::map<int, CvAIOperation*, std::less<int>, std::allocator<std::pair<int const, CvAIOperation*> > >::iterator m_CurrentOperation;
	std::vector<std::pair<int, PlayerVoteTypes>, std::allocator<std::pair<int, PlayerVoteTypes> > > m_aVote;
	std::vector<std::pair<UnitClassTypes, int>, std::allocator<std::pair<UnitClassTypes, int> > > m_aUnitExtraCosts;
	std::vector<CvString, std::allocator<CvString> > m_ReplayDataSets;
	std::vector<std::map<unsigned int, int, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, int> > >, std::allocator<std::map<unsigned int, int, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, int> > > > > m_ReplayDataSetValues;
	CvDangerPlots *m_pDangerPlots;
	CvPlayerPolicies *m_pPlayerPolicies;
	CvEconomicAI *m_pEconomicAI;
	CvMilitaryAI *m_pMilitaryAI;
	CvCitySpecializationAI *m_pCitySpecializationAI;
	CvWonderProductionAI *m_pWonderProductionAI;
	CvGrandStrategyAI *m_pGrandStrategyAI;
	CvPlayerDiplomacy *m_pPlayerDiplomacy;
	CvDiplomacyAI *m_pDiplomacyAI;
	CvPlayerReligions *m_pReligions;
	CvReligionAI *m_pReligionAI;
	CvOrbitalAI *m_pOrbitalAI;
	CvTacticalAI *m_pTacticalAI;
	CvHomelandAI *m_pHomelandAI;
	CvPlayerTechs *m_pPlayerTechs;
	CvFlavorManager *m_pFlavorManager;
	CvMinorCivAI *m_pMinorCivAI;
	CvDealAI *m_pDealAI;
	CvBuilderTaskingAI *m_pBuilderTaskingAI;
	CvCityConnections *m_pCityConnections;
	CvPlayerEspionage *m_pEspionage;
	CvEspionageAI *m_pEspionageAI;
	CvPlayerCovertOps *m_pPlayerCovertOps;
	CvCovertOpsAI *m_pCovertOpsAI;
	CvPlayerPersonality *m_pPlayerPersonality;
	CvPlayerArtifacts *m_pPlayerArtifacts;
	CvPlayerMarvels *m_pPlayerMarvels;
	CvPlayerMarvelRewards *m_pPlayerMarvelRewards;
	CvPlayerTrade *m_pTrade;
	CvTradeAI *m_pTradeAI;
	CvLeagueAI *m_pLeagueAI;
	CvHostilityAI *m_pHostilityAI;
	CvPersonalityAI *m_pPersonalityAI;
	CvPlayerCulture *m_pCulture;
	CvNotifications *m_pNotifications;
	CvDiplomacyRequests *m_pDiplomacyRequests;
	CvPlotsVector m_aiPlots;
	CvTreasury *m_pTreasury;
	CvPlayerTraits *m_pTraits;
	CvPlayerLoadout *m_pLoadout;
	CvPlayerOrbitals *m_pOrbitals;
	CvPlayerQuests *m_pQuests;
	CvPlayerAffinities *m_pAffinities;
	CvPlayerUnitUpgrades *m_pUnitUpgrades;
	CvPlayerPerks *m_pPlayerPerks;
	bool m_bPolicyNotificationNeedsTest;
	bool m_bPolicyNofificationSeen;
	bool m_activeWaitingForEndTurnMessage;
	int m_endTurnBusyUnitUpdatesLeft;
	int m_lastTurnInitialUnitAIProcessed;
	ConqueredByBoolField m_bfEverConqueredBy;
	int m_iNumArchaeologyChoices;
	FaithPurchaseTypes m_eFaithPurchaseType;
	int m_iFaithPurchaseIndex;
	CvPlayerAchievements m_kPlayerAchievements;
	int m_iWaitingForEffect;
	std::array<int, 22> m_lastTurnUnitGifted;
public:
	std::string debugDump(const FAutoVariableBase& var) const;
	std::string stackTraceRemark(const FAutoVariableBase& var) const;
	static TeamTypes getTeam(PlayerTypes ePlayerID) { return CvPreGame::teamType(ePlayerID); }
	TeamTypes getTeam() const;
	bool isAlive() const;
	bool isFoundedFirstCity() const;
	bool isLocalPlayer() const;
	int getAdvancedStartPoints() const;
	CLLNode<TechTypes>* headResearchQueueNode();
	const CLLNode<TechTypes>* headResearchQueueNode() const;
	int GetTotalSciencePerTurnTimes100() const;
	int getOverflowResearch() const;
	int calculateResearchModifier(TechTypes);
	int GetMaxEffectiveCities(bool);
	int GetNumCitiesResearchCostDiscount() const;
	bool canBuild(const CvPlot*, BuildTypes, bool, bool, bool, bool) const;
	int getQueuePosition(TechTypes) const;
	void changeOverflowResearchTimes100(int);
	int GetCulturePerTechResearched() const;
	void ChangeTotalAccumulatedCulture(int);
	virtual ~CvPlayer();
	virtual void Read(FDataStream& kStream);
	virtual void Write(FDataStream& kStream) const;
	virtual void AI_init() = 0;
	virtual void AI_reset() = 0;
	virtual void AI_doTurnPre() = 0;
	virtual void AI_doTurnPost() = 0;
	virtual void AI_doTurnUnitsPre() = 0;
	virtual void AI_doTurnUnitsPost() = 0;
	virtual void AI_updateFoundValues(bool bStartingLoc = false) = 0;
	virtual void AI_unitUpdate() = 0;
	virtual void AI_conquerCity(CvCity* pCity, PlayerTypes eOldOwner, bool bGift) = 0;
	virtual int AI_foundValue(int iX, int iY, int iMinUnitRange, bool bStartingLoc, bool bCheckResources, bool bCheckStrategic) = 0;
	virtual void AI_chooseFreeTech() = 0;
	virtual void AI_chooseResearch() = 0;
	virtual int AI_plotTargetMissionAIs(CvPlot* pPlot, MissionAITypes eMissionAI, int iRange = 0) = 0;
	virtual void AI_launch(VictoryTypes eVictory) = 0;
	virtual OperationSlot PeekAtNextUnitToBuildForOperationSlot(int iAreaID) = 0;
	virtual OperationSlot CityCommitToBuildUnitForOperationSlot(int iAreaID, int iTurns, CvCity* pCity) = 0;
	virtual void CityUncommitToBuildUnitForOperationSlot(OperationSlot slot) = 0;
	virtual void CityFinishedBuildingUnitForOperationSlot(OperationSlot slot, CvUnit* pUnit) = 0;
	virtual int GetNumUnitsNeededToBeBuilt() = 0;
	CvFlavorManager* GetFlavorManager() const;
	CvEconomicAI* GetEconomicAI() const;
	class CvCitySpecializationAI* GetCitySpecializationAI() const;
	int GetTotalNetHealthPerTurn() const;
	bool IsEmpireUnhealthy() const;
	bool isHalfSpecialistFood() const;
	bool isHalfSpecialistUnhealth() const;
	void DoUpdateHealth();
	int specialistYield(SpecialistTypes eSpecialist, YieldTypes eYield) const;
	int getSpecialistExtraYield(YieldTypes eYield) const;
	CvMilitaryAI* GetMilitaryAI() const;
	CvWonderProductionAI* GetWonderProductionAI() const;
	int GetNumPuppetCities() const;
	int GetNumUnitsWithUnitAI(UnitAITypes eUnitAI, bool bIncludeTraining, bool bIncludeOutposts);
	int GetID() const;
	bool isHuman() const;
	bool isEverAlive() const;
	bool isBarbarian() const;
	bool isMinorCiv() const;
	int getPersonalityType() const;
	CvMinorCivAI* GetMinorCivAI() const;
	bool IsAITeammateOfHuman() const;
	bool isAlien() const;
	bool isNeutralProxy() const;
	// TODO: Inline after restoring authentic members through m_pPlayerPerks (target offset 0xf4bc).
	CvPlayerPerks* GetPlayerPerks() const;
	int GetRouteEnergyMaintenanceMod() const;
	const char* getCivilizationShortDescription() const;
	const CvCity* firstCity(int* pIterIdx, bool bRev = false) const;
	const CvCity* nextCity(int* pIterIdx, bool bRev = false) const;
	const CvCity* getCapitalCity() const;
	CvPlayerTechs* GetPlayerTechs() const;
	class CvPlayerPolicies* GetPlayerPolicies() const;
	int GetNumFreeTenets() const;
	CvCivilizationInfo& getCivilizationInfo() const;
	CvCity* firstCity(int* pIterIdx, bool bRev = false);
	CvCity* nextCity(int* pIterIdx, bool bRev = false);
	CvGrandStrategyAI* GetGrandStrategyAI() const;
	CvPlayerAffinities* GetAffinities() const;
	int GetGameProgress() const;
	int GetNumFreeTechs() const;
	void init(PlayerTypes eID);
	void setupGraphical();
	void InitAffinityValues();
	void gameStartInit();
	void uninit();
	bool isObserver() const;
	const char* getName() const;
	const char* getNickName() const;
	ArtStyleTypes getArtStyleType() const;
	CvUnit* GetFirstReadyUnit() const;
	bool hasBusyUnit() const;
	bool hasBusyUnitOrCity() const;
	int GetScore(bool bFinal, bool bVictory) const;
	CvPlot* getStartingPlot() const;
	void setStartingPlot(CvPlot* pPlot);
	CvCity* getCapitalCity();
	bool IsHasLostCapital() const;
	void setStartTime(unsigned int uiStartTime);
	bool isTurnActive() const;
	void setTurnActive(bool bNewValue, bool bDoTurn);
	HandicapTypes getHandicapType() const;
	CivilizationTypes getCivilizationType() const;
	LeaderHeadTypes getLeaderType() const;
	const char* getLeaderTypeKey() const;
	EraTypes GetCurrentEra() const;
	PlayerColorTypes getPlayerColor() const;
	bool isOption(PlayerOptionTypes eOption) const;
	int getNumCities() const;
	CvOutpost* FirstOutpost(int* pIterIdx, bool bRev);
	CvOutpost* NextOutpost(int* pIterIdx, bool bRev);
	int GetNumOutposts() const;
	CvOutpost* GetOutpost(int iID);
	CvCity* getCity(int iID);
	CvUnit* firstUnit(int* pIterIdx, bool bRev);
	CvUnit* nextUnit(int* pIterIdx, bool bRev);
	CvUnit* getUnit(int iID);
	int GetPlotDanger(CvPlot& plot) const;
	int GetCityDistanceHighwaterMark() const;
	void disconnected();
	void reconnected();
	void setBusyUnitUpdatesRemaining(int iUpdateCount);
	bool hasUnitsThatNeedAIUpdate() const;
	CvTreasury* GetTreasury() const;
	FAutoArchive& getSyncArchive();
	CvDiplomacyAI* GetDiplomacyAI() const;
	CvDealAI* GetDealAI() const;
	CvPlayerTraits* GetPlayerTraits() const;
	CvPlayerLoadout* GetPlayerLoadout() const;
	CvDiplomacyRequests* GetDiplomacyRequests() const;
	CvNotifications* GetNotifications() const;
	bool isSimultaneousTurns() const;
	bool hasTurnTimerExpired();
	void WaitForEffect(bool bWait);
	CvPlayerCovertOps* GetPlayerCovertOps() const;
	bool hasMadePlanetfall() const;
	// TODO(Phase1): CvPlayer (remaining method declarations and implementations;
	// virtual method order still requires independent target validation).
};