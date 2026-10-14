#pragma once

#include "Fireworks/FAutoVariable.h"
#include "Fireworks/FAutoVector.h"
#include <array>
#include "CvCityNativeContainers.h"
#include "CvCityStrategicSite.h"

class CvCityBuildings
{
public:
	int GetNumBuildings() const;
	int GetNumBuildingClass(BuildingClassTypes eBuildingClass) const;
};

class CvPlayer;

class CvCityStrategyAI;
class CvPlot;
class CvCity;
class CvCovertAgent;

class CvCityCitizens
{
public:
	bool IsWorkingPlot(const CvPlot*) const;
	bool IsCanWork(CvPlot*) const;
	CvPlot* GetCityPlotFromIndex(int) const;
};

class CvCityCovertOps
{
	CvCity* m_city;
	int m_intrigue;
	int m_intrigueCap;
	int m_intrigueLevelLastTurn;
	std::array<int, 22> m_agentIndices;
public:
	int GetIntrigue() const { return m_intrigue; }
	int GetIntrigueLevel() const;
	int GetClampedIntrigueCap() const;
	CvCovertAgent* GetAgent(PlayerTypes) const;
};

// Partial SDK declarations.
class CvCity
{
public:
	// Beyond Earth adds the optional failure-message argument.
	bool canCreate(ProjectTypes eProject, bool bContinue = false, bool bTestVisible = false, CvString* pFailureMessage = NULL) const;
	const CvPlayer* GetPlayer() const;
	CvCityBuildings* GetCityBuildings() const;
	int GetMoveCityCostModifier() const;
	int getProductionTurnsLeft(ProjectTypes eProject, int iNum) const;
	virtual ~CvCity();
	int GetID() const { return m_iID; }
	PlayerTypes getOwner() const { return m_eOwner; }
	int getX() const { return m_iX; }
	int getY() const { return m_iY; }
	int getPopulation() const;
	const char* getNameKey() const;
	bool CanBuyPlot(int, int, bool);
	CitySizeTypes getCitySizeType() const;
	TeamTypes getTeam() const;
	int foodDifference(bool) const;
	int getFoodTurnsLeft() const;
	int getYieldRate(YieldTypes, bool bIgnoreTrade = false) const;
	int getCulturePerTurn() const;
	IDInfo GetIDInfo() const;
	FAutoArchive& getSyncArchive();
	CvCityCitizens* GetCityCitizens() const;
	CvCityCovertOps* GetCityCovertOps() const;
	CvCityStrategicSite* GetStrategicSite() const { return m_pStrategicSite; }
	bool IsPuppet() const;
	void GetProjectPlotList(ProjectTypes eProject, std::vector<int>& kPlots) const;
	const CvString getName() const;
	CvCityStrategyAI* GetCityStrategyAI() const;
	CvPlot* plot() const;
	CvPlot* GetBestCityMovePlot(int* piScore) const;
	// TODO: CvCity (remaining members).
	int iScratch;
protected:
	FAutoArchiveClassContainer<CvCity> m_syncArchive;
	FAutoVariable<CvString, CvCity> m_strNameIAmNotSupposedToBeUsedAnyMoreBecauseThisShouldNotBeCheckedAndWeNeedToPreserveSaveGameCompatibility;
	FAutoVariable<PlayerTypes, CvCity> m_eOwner;
	FAutoVariable<int, CvCity> m_iX;
	FAutoVariable<int, CvCity> m_iY;
	FAutoVariable<int, CvCity> m_iID;
	FAutoVariable<int, CvCity> m_iRallyX;
	FAutoVariable<int, CvCity> m_iRallyY;
	FAutoVariable<int, CvCity> m_iGameTurnFounded;
	FAutoVariable<int, CvCity> m_iGameTurnAcquired;
	FAutoVariable<int, CvCity> m_iGameTurnLastExpanded;
	FAutoVariable<int, CvCity> m_iPopulation;
	FAutoVariable<int, CvCity> m_iHighestPopulation;
	int m_iExtraHitPoints;
	FAutoVariable<int, CvCity> m_iCultureStored;
	FAutoVariable<int, CvCity> m_iCultureLevel;
	FAutoVariable<int, CvCity> m_iCulturePerTurnFromBuildings;
	FAutoVariable<int, CvCity> m_iCulturePerTurnFromPolicies;
	FAutoVariable<int, CvCity> m_iCulturePerTurnFromSpecialists;
	FAutoVariable<int, CvCity> m_iCulturePerTurnFromReligion;
	int m_iFaithPerTurnFromBuildings;
	int m_iFaithPerTurnFromPolicies;
	int m_iFaithPerTurnFromReligion;
	FAutoVariable<int, CvCity> m_iCultureRateModifier;
	FAutoVariable<int, CvCity> m_iNumWorldWonders;
	FAutoVariable<int, CvCity> m_iNumTeamWonders;
	FAutoVariable<int, CvCity> m_iNumNationalWonders;
	FAutoVariable<int, CvCity> m_iWonderProductionModifier;
	FAutoVariable<int, CvCity> m_iFreeAssignableCitizens;
	FAutoVariable<int, CvCity> m_iCapturePlunderModifier;
	FAutoVariable<int, CvCity> m_iPlotCultureCostModifier;
	int m_iPlotBuyCostModifier;
	FAutoVariable<int, CvCity> m_iMaintenance;
	FAutoVariable<int, CvCity> m_iHealRate;
	FAutoVariable<int, CvCity> m_iMartialLawTurns;
	FAutoVariable<int, CvCity> m_iFood;
	FAutoVariable<int, CvCity> m_iFoodKeptTimes100;
	FAutoVariable<int, CvCity> m_iFoodKeptPercentFromBuildings;
	FAutoVariable<int, CvCity> m_iOverflowProduction;
	FAutoVariable<int, CvCity> m_iFeatureProduction;
	FAutoVariable<int, CvCity> m_iMilitaryProductionModifier;
	FAutoVariable<int, CvCity> m_iOrbitalProductionModifier;
	FAutoVariable<int, CvCity> m_iFreeExperience;
	FAutoVariable<int, CvCity> m_iMaxAirUnits;
	FAutoVariable<int, CvCity> m_iNukeModifier;
	int m_iTradeRouteTargetBonus;
	int m_iTradeRouteRecipientBonus;
	int m_iDomesticTradeRouteBonus;
	FAutoVariable<int, CvCity> m_iCultureUpdateTimer;
	FAutoVariable<int, CvCity> m_iCitySizeBoost;
	FAutoVariable<int, CvCity> m_iResourceDemanded;
	FAutoVariable<int, CvCity> m_iWeLoveTheKingDayCounter;
	FAutoVariable<int, CvCity> m_iLastTurnGarrisonAssigned;
	FAutoVariable<int, CvCity> m_iThingsProduced;
	FAutoVariable<int, CvCity> m_iDemandResourceCounter;
	FAutoVariable<int, CvCity> m_iResistanceTurns;
	FAutoVariable<int, CvCity> m_iRazingTurns;
	FAutoVariable<int, CvCity> m_iCountExtraLuxuries;
	FAutoVariable<int, CvCity> m_iCheapestPlotInfluence;
	int m_iEspionageModifier;
	int m_iOrbitalCoverageRadius;
	int m_iOrbitalStrikeRange;
	int m_iMoveCityCostModifier;
	int m_iInvisibleSightRange;
	OperationSlot m_unitBeingBuiltForOperation;
	FAutoVariable<bool, CvCity> m_bNeverLost;
	FAutoVariable<bool, CvCity> m_bDrafted;
	FAutoVariable<bool, CvCity> m_bProductionAutomated;
	FAutoVariable<bool, CvCity> m_bLayoutDirty;
	FAutoVariable<bool, CvCity> m_bMadeAttack;
	FAutoVariable<bool, CvCity> m_bPuppet;
	bool m_bIgnoreCityForHealth;
	FAutoVariable<bool, CvCity> m_bEverCapital;
	FAutoVariable<bool, CvCity> m_bAdvancedRouteToCapital;
	FAutoVariable<bool, CvCity> m_bFeatureSurrounded;
	FAutoVariable<PlayerTypes, CvCity> m_ePreviousOwner;
	FAutoVariable<PlayerTypes, CvCity> m_eOriginalOwner;
	FAutoVariable<PlayerTypes, CvCity> m_ePlayersReligion;
	FAutoVariable<std::vector<int>, CvCity> m_aiSeaPlotYield;
	FAutoVariable<std::vector<int>, CvCity> m_aiRiverPlotYield;
	FAutoVariable<std::vector<int>, CvCity> m_aiLakePlotYield;
	FAutoVariable<std::vector<int>, CvCity> m_aiSeaResourceYield;
	FAutoVariable<std::vector<int>, CvCity> m_aiBaseYieldRateFromTerrain;
	FAutoVariable<std::vector<int>, CvCity> m_aiBaseYieldRateFromBuildings;
	FAutoVariable<std::vector<int>, CvCity> m_aiBaseYieldRateFromSpecialists;
	FAutoVariable<std::vector<int>, CvCity> m_aiBaseYieldRateFromMisc;
	FAutoVariable<std::vector<int>, CvCity> m_aiTradeRouteYieldChanges;
	FAutoVariable<std::vector<int>, CvCity> m_aiTradeRouteYieldModifiers;
	std::vector<int> m_aiBaseYieldRateFromReligion;
	std::vector<int> m_aiBaseYieldRateFromMiasma;
	FAutoVariable<std::vector<int>, CvCity> m_aiYieldRateModifier;
	FAutoVariable<std::vector<int>, CvCity> m_aiYieldRateWarModifier;
	FAutoVariable<std::vector<int>, CvCity> m_aiYieldPerPop;
	std::vector<int> m_aiYieldPerReligion;
	FAutoVariable<std::vector<int>, CvCity> m_aiPowerYieldRateModifier;
	FAutoVariable<std::vector<int>, CvCity> m_aiResourceYieldRateModifier;
	FAutoVariable<std::vector<int>, CvCity> m_aiExtraSpecialistYield;
	FAutoVariable<std::vector<int>, CvCity> m_aiProductionToYieldModifier;
	FAutoVariable<std::vector<int>, CvCity> m_aiDomainFreeExperience;
	FAutoVariable<std::vector<int>, CvCity> m_aiDomainProductionModifier;
	FAutoVariable<std::vector<bool>, CvCity> m_abEverOwned;
	FAutoVariable<std::vector<bool>, CvCity> m_abRevealed;
	FAutoVariable<CvString, CvCity> m_strScriptData;
	FAutoVariable<std::vector<int>, CvCity> m_paiNoResource;
	FAutoVariable<std::vector<int>, CvCity> m_paiFreeResource;
	FAutoVariable<std::vector<int>, CvCity> m_paiNumResourcesLocal;
	FAutoVariable<std::vector<int>, CvCity> m_paiProjectProduction;
	FAutoVariable<std::vector<int>, CvCity> m_paiSpecialistProduction;
	FAutoVariable<std::vector<int>, CvCity> m_paiUnitProduction;
	FAutoVariable<std::vector<int>, CvCity> m_paiUnitProductionTime;
	FAutoVariable<std::vector<int>, CvCity> m_paiSpecialistCount;
	FAutoVariable<std::vector<int>, CvCity> m_paiMaxSpecialistCount;
	FAutoVariable<std::vector<int>, CvCity> m_paiForceSpecialistCount;
	FAutoVariable<std::vector<int>, CvCity> m_paiFreeSpecialistCount;
	FAutoVariable<std::vector<int>, CvCity> m_paiImprovementFreeSpecialists;
	FAutoVariable<std::vector<int>, CvCity> m_paiUnitCombatFreeExperience;
	FAutoVariable<std::vector<int>, CvCity> m_paiUnitCombatProductionModifier;
	FAutoVariable<std::vector<int>, CvCity> m_paiFreePromotionCount;
	int m_iBaseHealthFromBuildings;
	int m_iUnmoddedHealthFromBuildings;
	int m_iBaseHealthFromTerrain;
	int m_iBaseUnhealthFromTerrain;
	int m_iHealthModifier;
	int m_iProductionToHealthModifier;
	ASL::StdLib::HashMap::unordered_map<ResourceTypes, GenericYieldHealthChange> m_localResourceChanges;
	ASL::StdLib::HashMap::unordered_map<FeatureTypes, GenericYieldHealthChange> m_localFeatureChanges;
	ASL::StdLib::HashMap::unordered_map<TerrainTypes, GenericYieldHealthChange> m_localTerrainChanges;
	int m_iCityStrikeModifier;
	int m_iAlienBaseRepelRange;
	bool m_bRouteToCapitalConnectedLastTurn;
	bool m_bRouteToCapitalConnectedThisTurn;
	int m_iBaseNumTradeRoutesAllowed;
	int m_iNumTradeRoutesOccupied;
	CvString m_strName;
	bool m_bOwedCultureBuilding;
	FFastSmallFixedList<OrderData, 25, true, 1256, 0> m_orderQueue;
	int **m_aaiBuildingSpecialistUpgradeProgresses;
	int **m_ppaiResourceYieldChange;
	int **m_ppaiFeatureYieldChange;
	int **m_ppaiTerrainYieldChange;
	CvCityBuildings *m_pCityBuildings;
	CvCityStrategicSite *m_pStrategicSite;
};