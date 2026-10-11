#pragma once

#include <vector>
#include "FFastVector.h"
#include "FObjectHandle.h"
#include "FAutoVariable.h"
#include "CvPlayerAI.h"
#include "CvGlobals.h"
#include "CvGame.h"

class CvUnit;
class CvArea;
class CvStation;
class CvCity;
class CvStrategicSite;
class CvOutpost;
class FAutoArchive;
typedef FObjectHandle<CvUnit> UnitHandle;

struct CvArchaeologyData
{
	GreatWorkArtifactClass m_eArtifactType;
	EraTypes m_eEra;
	PlayerTypes m_ePlayer1;
	PlayerTypes m_ePlayer2;
	GreatWorkType m_eWork;
};

// TODO(Phase1): remaining native CvPlot method implementations.
class CvPlot
{
public:
	int getArea() const { return m_iArea; }
	int getFoundValue(PlayerTypes ePlayer);
	int getYield(YieldTypes eYield) const;
	bool isOwned() const;
	void setFoundValue(PlayerTypes ePlayer, int iValue);
	int calculateNatureYield(YieldTypes eYield, TeamTypes eTeam, bool bIgnoreFeature = false) const;
	bool isCoastalLand(int iMinWaterSize = -1) const;
	int GetPlotIndex() const;
	TeamTypes getTeam() const
	{
		PlayerTypes playerID = getOwner();
		if(playerID != NO_PLAYER)
			return CvPlayer::getTeam(playerID);
		return NO_TEAM;
	}
	FogOfWarModeTypes GetActiveFogOfWarMode() const;
	void updateCenterUnit();
	bool isAdjacent(const CvPlot* pPlot) const;
	bool isRiver() const { return m_iRiverCrossingCount > 0; }
	CvPlot* getNeighboringPlot(DirectionTypes eDirection) const;
	DirectionTypes getAdjacentPlotDirection(CvPlot* pPlot) const;
	int getBuildTime(BuildTypes eBuild, PlayerTypes ePlayer) const;
	bool IsAllowsWalkWater() const;
	bool isVisible(TeamTypes eTeam, bool bDebug) const
	{
		if(bDebug && GC.getGame().isDebugMode())
			return true;
		if(eTeam == NO_TEAM)
			return false;
		return getVisibilityCount(eTeam) > 0;
	}
	// Beyond Earth exposes miasma and bubbles in the native plot flags.
	bool HasMiasma() const { return m_HasMiasma; }
	bool HasBubbles() const { return m_HasBubbles; }
	int getX() const { return m_iX; }
	int getY() const { return m_iY; }
	bool isEnemyStrategicSite(const CvUnit& kUnit) const;
	bool isEnemyCity(const CvUnit& kUnit) const;
	bool isEnemyOutpost(const CvUnit& kUnit) const;
	bool isFighting() const;
	bool IsTradeRoute(PlayerTypes ePlayer) const;
	bool isImpassable() const { return m_bIsImpassable; }
	bool isNEOfRiver() const;
	bool isWOfRiver() const;
	bool isNWOfRiver() const;
	FlowDirectionTypes getRiverEFlowDirection() const;
	FlowDirectionTypes getRiverSEFlowDirection() const;
	FlowDirectionTypes getRiverSWFlowDirection() const;
	PlayerTypes getOwner() const { return (PlayerTypes)m_eOwner; }
	PlotTypes getPlotType() const { return (PlotTypes)m_ePlotType; }
	bool isWater() const { return m_ePlotType == PLOT_OCEAN; }
	bool isHills() const { return (PlotTypes)m_ePlotType == PLOT_HILLS; }
	bool isOpenGround() const
	{
		// Beyond Earth's canyons also block open ground.
		if((PlotTypes)m_ePlotType == PLOT_CANYON || (PlotTypes)m_ePlotType == PLOT_HILLS || (PlotTypes)m_ePlotType == PLOT_MOUNTAIN || m_bRoughFeature)
			return false;
		return true;
	}
	bool isMountain() const { return (PlotTypes)m_ePlotType == PLOT_MOUNTAIN; }
	bool isCanyon() const { return (PlotTypes)m_ePlotType == PLOT_CANYON; }
	TerrainTypes getTerrainType() const { return (TerrainTypes)m_eTerrainType; }
	FeatureTypes getFeatureType() const { return static_cast<FeatureTypes>(static_cast<char>(m_eFeatureType)); }
	HeroLandmarkTypes getHeroLandmark() const;
	int getHeroLandmarkPiece() const;
	int getHeroLandmarkOrientation() const;
	ResourceTypes getResourceType(TeamTypes eTeam) const;
	int getNumResource() const;
	ImprovementTypes getImprovementType() const;
	bool IsImprovementPillaged() const;
	bool IsImprovementActivated() const;
	GenericWorldAnchorTypes GetWorldAnchor() const;
	int GetWorldAnchorData() const;
	RouteTypes getRouteType() const;
	bool IsRoutePillaged() const;
	CvCity* getPlotCity() const
	{
		if(m_plotCity.eOwner >= 0 && m_plotCity.eOwner < MAX_PLAYERS)
			return GET_PLAYER(m_plotCity.eOwner).getCity(m_plotCity.iID);
		return NULL;
	}
	CvCity* getWorkingCity() const;
	CvCity* getWorkingCityOverride() const;
	void setWorkingCityOverride(const CvCity* pCity);
	bool hasYield() const;
	bool isUnitBlockingCityWork(PlayerTypes ePlayer) const;
	int getHealth(PlayerTypes ePlayer) const;
	int getUnhealth(PlayerTypes ePlayer) const;
	int getExtraWorkingCityHP(PlayerTypes ePlayer) const;
	// Beyond Earth resolves outposts through the owning player, like cities.
	CvOutpost* getPlotOutpost() const
	{
		if(m_plotOutpost.eOwner >= 0 && m_plotOutpost.eOwner < MAX_PLAYERS)
			return GET_PLAYER(m_plotOutpost.eOwner).GetOutpost(m_plotOutpost.iID);
		return NULL;
	}
	CvStrategicSite* getPlotStrategicSite() const;
	bool isRevealed(TeamTypes eTeam, bool bDebug) const;
	bool setRevealed(TeamTypes eTeam, bool bNewValue, bool bTerrainOnly, TeamTypes eFromTeam);
	bool isRevealed(TeamTypes eTeam) const;
	ImprovementTypes getRevealedImprovementType(TeamTypes eTeam) const;
	ImprovementTypes getRevealedImprovementType(TeamTypes eTeam, bool bDebug) const;
	int getBuildProgress(BuildTypes eBuild) const;
	bool getAnyBuildProgress() const;
	void updateLayout(bool bDebug);
	UnitHandle getCenterUnit();
	int getNumUnits() const;
	CvUnit* getUnitByIndex(int iIndex) const;
	void addUnit(CvUnit* pUnit, bool bUpdate);
	void removeUnit(CvUnit* pUnit, bool bUpdate);
	const IDInfo* nextUnitNode(const IDInfo* pNode) const;
	IDInfo* nextUnitNode(IDInfo* pNode);
	IDInfo* headUnitNode();
	char GetContinentType() const;
	int GetMapRegionIndex() const { return m_mapRegionIndex; }
	void updateImpassable();
	FAutoArchive& getSyncArchive();
	void erase(bool);
	void updateFog(bool);
	void updateVisibility();
	void nukeExplosion(int, CvUnit *);
	bool isAdjacentToArea(int) const;
	bool isAdjacentToArea(const CvArea *) const;
	bool shareAdjacentArea(const CvPlot *) const;
	bool isAdjacentToLand() const;
	bool isAdjacentToShallowWater() const;
	bool isWithinTeamCityRadius(TeamTypes, PlayerTypes) const;
	bool isLake() const;
	bool isFreshWater() const;
	bool isRiverCrossingFlowClockwise(DirectionTypes) const;
	bool isRiverSide() const;
	bool isRiverConnection(DirectionTypes) const;
	int getNearestLandArea() const;
	CvPlot * getNearestLandPlot() const;
	int seeFromLevel(TeamTypes) const;
	int seeThroughLevel(bool) const;
	bool canSeePlot(const CvPlot *, TeamTypes, int, DirectionTypes) const;
	bool canHaveResource(ResourceTypes) const;
	bool canHaveImprovement(ImprovementTypes, TeamTypes, bool) const;
	bool canBuild(BuildTypes, PlayerTypes, bool, bool) const;
	int getBuildTurnsTotal(BuildTypes, PlayerTypes) const;
	int getBuildTurnsLeft(BuildTypes, PlayerTypes, int, int) const;
	int getFeatureProduction(BuildTypes, PlayerTypes, CvCity **) const;
	UnitHandle getBestDefender(PlayerTypes, PlayerTypes, const CvUnit *, bool, bool, bool, bool);
	const UnitHandle getBestDefender(PlayerTypes, PlayerTypes, const CvUnit *, bool, bool, bool, bool) const;
	const CvUnit * getSelectedUnit() const;
	CvUnit * getSelectedUnit();
	int getUnitPower(PlayerTypes) const;
	int defenseModifier(TeamTypes, bool, bool) const;
	int movementCost(const CvUnit *, const CvPlot *, int) const;
	int getExtraMovePathCost() const;
	void changeExtraMovePathCost(int);
	bool isAdjacentOwned() const;
	bool isAdjacentPlayer(PlayerTypes, bool) const;
	bool isAdjacentTeam(TeamTypes, bool) const;
	bool isAlien() const;
	bool HasAlienNest() const;
	bool isActiveVisible(bool) const;
	bool isActiveVisible() const;
	bool isVisibleToWatchingHuman() const;
	bool isAdjacentVisible(TeamTypes, bool) const;
	bool isAdjacentVisible(TeamTypes) const;
	bool isAdjacentNonvisible(TeamTypes) const;
	bool isGoody(TeamTypes) const;
	bool isRevealedGoody(TeamTypes) const;
	void removeGoody();
	bool isCity() const { return getPlotCity() != NULL; }
	bool isOutpost() const { return getPlotOutpost() != NULL; }
	bool isFriendlyCity(const CvUnit &, bool) const;
	bool isFriendlyOutpost(const CvUnit &, bool) const;
	bool IsFriendlyTerritory(PlayerTypes) const;
	bool IsNeutralTerritory(PlayerTypes) const;
	bool IsEnemyTerritory(PlayerTypes) const;
	bool isStation() const;
	bool isOrbitalUnit() const;
	bool isEnemyOrbitalUnit(TeamTypes) const;
	bool isBeingWorked() const;
	bool isUnit() const;
	bool isImmobileUnit() const;
	bool isUnlaunchedOrbitalUnit() const;
	bool isVisibleEnemyDefender(const CvUnit *) const;
	int getNumDefenders(PlayerTypes) const;
	int getNumVisibleEnemyDefenders(const CvUnit *) const;
	int getNumVisiblePotentialEnemyDefenders(const CvUnit *) const;
	bool isVisibleEnemyUnit(PlayerTypes) const;
	bool isVisibleEnemyUnit(const CvUnit *) const;
	bool isVisibleOtherUnit(PlayerTypes) const;
	bool IsActualEnemyUnit(PlayerTypes, bool) const;
	int getNumFriendlyUnitsOfType(const CvUnit *, bool, bool) const;
	bool canHaveFeature(FeatureTypes) const;
	bool CanHaveAnchorage() const;
	bool CanHaveMiasma() const;
	bool isRoute() const;
	bool isValidDomainForLocation(const CvUnit &) const;
	bool isValidDomainForAction(const CvUnit &) const;
	bool at(int, int) const;
	int getLatitude() const;
	CvArea * area() const;
	CvArea * waterArea() const;
	void setArea(int);
	int getWildness() const;
	void setWildness(int);
	void changeWildness(int);
	int getFeatureVariety() const;
	int getOwnershipDuration() const;
	bool isOwnershipScore() const;
	void setOwnershipDuration(int);
	void changeOwnershipDuration(int);
	int getImprovementDuration() const;
	void setImprovementDuration(int);
	void changeImprovementDuration(int);
	int getUpgradeProgress() const;
	int getUpgradeTimeLeft(ImprovementTypes, PlayerTypes) const;
	void setUpgradeProgress(int);
	void changeUpgradeProgress(int);
	int getCityRadiusCount() const;
	int isCityRadius() const;
	bool isStartingPlot() const;
	void setStartingPlot(bool);
	void setNEOfRiver(bool, FlowDirectionTypes);
	void setWOfRiver(bool, FlowDirectionTypes);
	void setNWOfRiver(bool, FlowDirectionTypes);
	CvPlot * getInlandCorner() const;
	void setOwner(PlayerTypes, int, bool, bool);
	int GetCityPurchaseID();
	void SetCityPurchaseID(int);
	bool isTrench() const;
	bool HasAnchorage() const;
	void SetAnchorage(bool);
	void SetMiasma(bool);
	void SetBubbles(bool);
	bool isRoughGround() const;
	bool isFlatlands() const;
	void setPlotType(PlotTypes, bool, bool, bool);
	void setTerrainType(TerrainTypes, bool, bool);
	void setFeatureType(FeatureTypes, int);
	bool hasResource(TeamTypes) const;
	ResourceTypes getNonObsoleteResourceType(TeamTypes) const;
	void setResourceType(ResourceTypes, int);
	void setNumResource(int);
	void changeNumResource(int);
	void SetResourceType(ResourceLayers, ResourceTypes, int);
	ResourceTypes GetPrimaryResourceType(TeamTypes) const;
	ResourceTypes GetSecondaryResourceType(TeamTypes) const;
	void SetPrimaryResourceType(ResourceTypes, int);
	void SetSecondaryResourceType(ResourceTypes, int);
	bool hasImprovement() const;
	void setImprovementType(ImprovementTypes, PlayerTypes);
	void clearImprovementType();
	void SetImprovementPillaged(bool);
	MapRegionTypes GetMapRegionType() const;
	ImprovementTypes GetPrimaryImprovementType() const;
	ImprovementTypes GetSecondaryImprovementType() const;
	void SetPrimaryImprovementType(ImprovementTypes, PlayerTypes);
	void SetSecondaryImprovementType(ImprovementTypes, PlayerTypes);
	void setRouteType(RouteTypes);
	CvStation * getPlotStation() const;
	CvUnit * getPlotOrbitalUnit() const;
	int getReconCount() const;
	int getRiverCrossingCount() const;
	short * getYield();
	int calculateBestNatureYield(YieldTypes, TeamTypes) const;
	int calculateTotalBestNatureYield(TeamTypes) const;
	int calculateImprovementYieldChange(ImprovementTypes, YieldTypes, PlayerTypes, bool, RouteTypes) const;
	int calculateYield(YieldTypes, bool);
	int getYieldWithBuild(BuildTypes, YieldTypes, bool, PlayerTypes) const;
	bool isStrategicSite() const;
	int countNumAirUnits(TeamTypes) const;
	bool isBestAdjacentFound(PlayerTypes);
	int getPlayerCityRadiusCount(PlayerTypes) const;
	bool isPlayerCityRadius(PlayerTypes) const;
	int getVisibilityCount(TeamTypes eTeam) const { return m_aiVisibilityCount[eTeam]; }
	PlotVisibilityChangeResult changeVisibilityCount(TeamTypes, int, bool, bool);
	PlayerTypes getRevealedOwner(TeamTypes, bool) const;
	PlayerTypes getRevealedOwner(TeamTypes) const;
	TeamTypes getRevealedTeam(TeamTypes, bool) const;
	TeamTypes getRevealedTeam(TeamTypes) const;
	bool isRiverCrossing(DirectionTypes) const;
	bool isAdjacentRevealed(TeamTypes) const;
	bool isAdjacentNonrevealed(TeamTypes) const;
	bool setRevealedImprovementType(TeamTypes, ImprovementTypes);
	RouteTypes getRevealedRouteType(TeamTypes, bool) const;
	RouteTypes getRevealedRouteType(TeamTypes) const;
	int getPlotEnergyMaintenance(PlayerTypes) const;
	bool changeBuildProgress(BuildTypes, int, PlayerTypes);
	void setLayoutDirty(bool);
	int getInvisibleVisibilityCount(TeamTypes) const;
	void changeInvisibleVisibilityCount(TeamTypes, int);
	bool isInvisibleVisibleToTeam(TeamTypes, TeamTypes) const;
	bool isInvisibleVisibleToAnyEnemyTeam(TeamTypes) const;
	int getNumLayerUnits(int) const;
	CvUnit * getLayerUnit(int, int) const;
	CvString getScriptData() const;
	void setScriptData(const char *);
	const CvString getLogString() const;
	const CvString getSiteName() const;
	void SetContinentType(const char);
	CvArchaeologyData GetArchaeologicalRecord() const;
	bool HasWrittenArtifact() const;
	void SetLandmarkActionPerformed(bool);
	bool GetLandmarkActionPerformed() const;
	bool HasInfluencingOrbitalUnit() const;
	bool HasInfluencingOrbitalUnit(PlayerTypes) const;
	CvString GetInfluencingOrbitalUnitsText() const;
	int GetCityIntrigueModFromOrbitalUnits() const;
	bool IsCityCovertOpsPreventedByOrbitalUnits() const;
	CvUnit * GetOrbitalUnitAbovePlot();
	CvUnit * GetOrbitalUnitInfluencingPlot() const;
protected:
	short m_iX;
	short m_iY;
	char m_eOwner;
	char m_ePlotType;
	char m_eTerrainType;
	class PlotBoolField
	{
	public:
		DWORD m_dwBits[4];
	} m_bfRevealed;
	FFastSmallFixedList<IDInfo, 8, true, c_eCiv5GameplayDLL> m_units;
	// Beyond Earth adds orbital units, outposts, wonders and stations.
	std::vector<IDInfo> m_vInfluencingOrbitalUnits;
	IDInfo m_pOrbitalUnit;
	IDInfo m_plotOutpost;
	IDInfo m_plotCity;
	IDInfo m_plotWonder;
	IDInfo m_plotStation;
	IDInfo m_workingCity;
	IDInfo m_workingCityOverride;
	IDInfo m_ResourceLinkedCity;
	IDInfo m_purchaseCity;
	short* m_aiYield;
	int* m_aiFoundValue;
	char* m_aiPlayerCityRadiusCount;
	short* m_aiVisibilityCount;
	char* m_aiRevealedOwner;
	short* m_aeRevealedImprovementType;
	short* m_aeRevealedRouteType;
	bool* m_abNoSettling;
	bool* m_abResourceForceReveal;
	char* m_szScriptData;
	short* m_paiBuildProgress;
	UnitHandle m_pCenterUnit;
	short m_apaiInvisibleVisibilityCount[REALLY_MAX_TEAMS][1];
	int m_iArea;
	int m_iLandmass;
	int m_iWildness;
	int m_iScratchPad;
	char m_cBuilderAIScratchPadPlayer;
	short m_sBuilderAIScratchPadTurn;
	short m_sBuilderAIScratchPadValue;
	RouteTypes m_eBuilderAIScratchPadRoute;
	short m_iOwnershipDuration;
	short m_iImprovementDuration;
	short m_iUpgradeProgress;
	short m_iCulture;
	short m_iTradeCount;
	uint m_uiTradeRouteBitFlags;
	FAutoArchiveClassContainer<CvPlot> m_syncArchive;
	FAutoVariable<char, CvPlot> m_eFeatureType;
	// Beyond Earth splits primary/secondary resources and improvements.
	char m_ePrimaryResourceType;
	char m_eSecondaryResourceType;
	char m_eImprovementType;
	char m_eSecondaryImprovementType;
	char m_eImprovementTypeUnderConstruction;
	char m_mapRegionType;
	char m_mapRegionIndex;
	char m_ePlayerBuiltImprovement;
	char m_ePlayerResponsibleForImprovement;
	char m_ePlayerResponsibleForRoute;
	char m_ePlayerThatClearedBarbCampHere;
	char m_eRouteType;
	char m_eWorldAnchor;
	char m_cWorldAnchorData;
	char m_eRiverEFlowDirection;
	char m_eRiverSEFlowDirection;
	char m_eRiverSWFlowDirection;
	char m_iFeatureVariety;
	char m_iNumMajorCivsRevealed;
	char m_iCityRadiusCount;
	char m_iReconCount;
	char m_iRiverCrossingCount;
	char m_iPrimaryResourceQuantity;
	char m_iSecondaryResourceQuantity;
	char m_cContinentType;
	char m_cRiverCrossing;
	char m_eHeroLandmarkType;
	char m_eHeroLandmarkPiece;
	bool m_bImprovementPillaged : 1;
	bool m_bImprovementActivated : 1;
	bool m_bRoutePillaged : 1;
	bool m_bStartingPlot : 1;
	bool m_bHills : 1;
	bool m_bNEOfRiver : 1;
	bool m_bWOfRiver : 1;
	bool m_bNWOfRiver : 1;
	bool m_bPlotLayoutDirty : 1;
	bool m_bLayoutStateWorked : 1;
	bool m_bBarbCampNotConverting : 1;
	bool m_bRoughFeature : 1;
	bool m_bResourceLinkedCityActive : 1;
	bool m_bImprovedByGiftFromMajor : 1;
	bool m_bIsAdjacentToLand : 1;
	bool m_bIsImpassable : 1;
	bool m_bLandmarkActionPerformed : 1;
	bool m_HasAnchorage : 1;
	bool m_HasMiasma : 1;
	bool m_HasBubbles : 1;
	CvArchaeologyData m_kArchaeologyData;
};
