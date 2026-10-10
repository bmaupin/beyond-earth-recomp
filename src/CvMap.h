#pragma once

#include "FFastVector.h"
#include "CvPlot.h"
#include <climits>

class CvArea;
class CvWorldInfo;
struct CvMapInitData;
enum MapRegionTypes { NO_MAP_REGION = -1 };

struct CvMapRegionData
{
	int m_iIndex;
	MapRegionTypes m_eType;
	float m_fCentroidX;
	float m_fCentroidY;
	int m_iUnknown10;
	int m_iUnknown14;

	CvMapRegionData(MapRegionTypes eType, int iIndex);
};

class CvMapRegionLayout
{
public:
	CvMapRegionData* GetRegionByIndex(int iIndex) const;
	int GetNumRegions() const { return static_cast<int>(m_vRegions.size()); }

private:
	float m_fMapWidth;
	float m_fMapHeight;
	std::vector<CvMapRegionData> m_vRegions;
};

class CvCity;
class FDataStream;

inline int coordRange(int iCoord, int iRange, bool bWrap)
{
	if(bWrap)
	{
		if(iCoord < 0)
			return (iRange + (iCoord % iRange));
		else if(iCoord >= iRange)
			return (iCoord % iRange);
	}
	return iCoord;
}

class CvPlot;

// Partial SDK declaration.
class CvMap
{
public:
	virtual ~CvMap();

	inline int getGridWidth() const { return m_iGridWidth; }
	inline int getGridHeight() const { return m_iGridHeight; }
	inline bool isWrapX() const { return m_bWrapX; }
	inline bool isWrapY() const { return m_bWrapY; }

	typedef FStaticVector<CvPlot*, 1000, true, c_eCiv5GameplayDLL, 1> DeferredPlotArray;
	DeferredPlotArray m_vDeferredFogPlots;

	void init(CvMapInitData* pInitData = NULL);
	void uninit();
	void updateLayout(bool bDebug);
	void updateDeferredFog();
	CvCity* findCity(int iX, int iY, PlayerTypes eOwner = NO_PLAYER,
		TeamTypes eTeam = NO_TEAM, bool bSameArea = true, bool bCoastalOnly = false,
		TeamTypes eTeamAtWarWith = NO_TEAM, DirectionTypes eDirection = NO_DIRECTION,
		const CvCity* pSkipCity = NULL);
	const CvWorldInfo& getWorldInfo() const;
	int getLandPlots() const;
	int getWaterPlots() const;
	int getLakePlots() const;
	CvArea* firstArea(int* pIterator, bool bRev = false);
	CvArea* nextArea(int* pIterator, bool bRev = false);
	CvArea* findBiggestArea(bool bWater);
	CvArea* getArea(int iID);
	bool findWater(CvPlot* pPlot, int iRange, bool bFreshWater);
	CvPlot* findNearestStartPlot(int iX, int iY, PlayerTypes& ePlayer);
	ClimateTypes getClimate();
	SeaLevelTypes getSeaLevel();
	WorldSizeTypes getWorldSize();
	int getMapFractalFlags();
	int getNumResources(ResourceTypes eResource);
	int getNumResourcesOnLand(ResourceTypes eResource);
	int getRandomResourceQuantity(ResourceTypes eResource);
	int getIndexAfterLastArea();
	int getNumAreas();
	int getNumLandAreas();
	int maxPlotDistance();
	void calculateAreas();
	void recalculateAreas();
	void DefaultContinentStamper();
	void ChangeAIMapHint(int iHint);
	int GetAIMapHint();
	inline int numPlots() const { return m_iGridSize; }
	inline int plotNum(int iX, int iY) const { return ((iY * getGridWidth()) + iX); }
	inline bool isPlot(int iX, int iY) const
	{
		return ((iX >= 0) && (iX < getGridWidth()) && (iY >= 0) && (iY < getGridHeight()));
	}
	__forceinline CvPlot* plotByIndex(int iIndex) const
	{
		return (((iIndex >= 0) && (iIndex < numPlots())) ? &(m_pMapPlots[iIndex]) : NULL);
	}
	__forceinline CvPlot* plotByIndexUnchecked(int iIndex) const
	{
		return &m_pMapPlots[iIndex];
	}
	__forceinline CvPlot* plot(int iX, int iY) const
	{
		if((iX == INVALID_PLOT_COORD) || (iY == INVALID_PLOT_COORD))
			return NULL;
		int iMapX = coordRange(iX, getGridWidth(), isWrapX());
		int iMapY = coordRange(iY, getGridHeight(), isWrapY());
		return ((isPlot(iMapX, iMapY)) ? &(m_pMapPlots[plotNum(iMapX, iMapY)]) : NULL);
	}
	void recalculateLandmasses();
	void CalculateRegionLayout(float fMapWidth, float fMapHeight, std::vector<CvMapRegionData>&& vMapRegions);
	const CvMapRegionLayout& GetMapRegionLayout() const { return m_kMapRegionLayout; }
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream) const;
	int Validate();
protected:
	int m_iGridWidth;
	int m_iGridHeight;
	int m_iGridSize;
	int m_iLandPlots;
	// Beyond Earth counts lake plots instead of natural wonders in this prefix.
	int m_iLakePlots;
	int m_iOwnedPlots;
	int m_iTopLatitude;
	int m_iBottomLatitude;
	int m_iAIMapHints;
	bool m_bWrapX;
	bool m_bWrapY;
	int* m_paiNumResource;
	int* m_paiNumResourceOnLand;
	CvPlot* m_pMapPlots;
	char m_regionLayoutPadding[0x94];
	CvMapRegionLayout m_kMapRegionLayout;
	// TODO: CvMap (remaining members).
};
