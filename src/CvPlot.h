#pragma once

#include <vector>
#include "FFastVector.h"
#include "FObjectHandle.h"
#include "FAutoVariable.h"

class CvUnit;
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
	int GetPlotIndex() const;
	// TODO: CvPlot (remaining SDK methods).
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
