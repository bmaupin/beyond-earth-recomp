#pragma once

#include <vector>
#include "FFastVector.h"
#include "FObjectHandle.h"
#include "FAutoVariable.h"

class CvUnit;
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

class CvPlot
{
public:
	int getArea() const { return m_iArea; }
	int getFoundValue(PlayerTypes ePlayer);
	void setFoundValue(PlayerTypes ePlayer, int iValue);
	int calculateNatureYield(YieldTypes eYield, TeamTypes eTeam, bool bIgnoreFeature = false) const;
	bool isCoastalLand(int iMinWaterSize = -1) const;
	int GetPlotIndex() const;
	TeamTypes getTeam() const;
	FogOfWarModeTypes GetActiveFogOfWarMode() const;
	void updateCenterUnit();
	bool isAdjacent(const CvPlot* pPlot) const;
	bool isRiver() const;
	CvPlot* getNeighboringPlot(DirectionTypes eDirection) const;
	DirectionTypes getAdjacentPlotDirection(CvPlot* pPlot) const;
	int getBuildTime(BuildTypes eBuild, PlayerTypes ePlayer) const;
	bool IsAllowsWalkWater() const;
	bool isVisible(TeamTypes eTeam, bool bDebug) const;
	bool HasMiasma() const;
	bool HasBubbles() const;
	int getX() const;
	int getY() const;
	bool isEnemyStrategicSite(const CvUnit& kUnit) const;
	bool isEnemyCity(const CvUnit& kUnit) const;
	bool isEnemyOutpost(const CvUnit& kUnit) const;
	bool isFighting() const;
	bool IsTradeRoute(PlayerTypes ePlayer) const;
	bool isImpassable() const;
	bool isNEOfRiver() const;
	bool isWOfRiver() const;
	bool isNWOfRiver() const;
	FlowDirectionTypes getRiverEFlowDirection() const;
	FlowDirectionTypes getRiverSEFlowDirection() const;
	FlowDirectionTypes getRiverSWFlowDirection() const;
	PlayerTypes getOwner() const;
	PlotTypes getPlotType() const;
	bool isWater() const;
	bool isHills() const;
	bool isOpenGround() const;
	bool isMountain() const;
	bool isCanyon() const;
	TerrainTypes getTerrainType() const;
	FeatureTypes getFeatureType() const;
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
	CvCity* getPlotCity() const;
	CvCity* getWorkingCity() const;
	CvOutpost* getPlotOutpost() const;
	CvStrategicSite* getPlotStrategicSite() const;
	bool isRevealed(TeamTypes eTeam, bool bDebug) const;
	void setRevealed(TeamTypes eTeam, bool bNewValue, bool bTerrainOnly, TeamTypes eFromTeam);
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
