#pragma once

#include <vector>
#include "CvStructs.h"
#include "CvGameCoreDLLUtil/include/CvString.h"

class CvSiteEvaluatorForStart;
class CvPlot;

class CvContinent
{
public:
	CvContinent() : m_uiFertility(0), m_uiFertilityNextRegion(0), m_iRegionsAssigned(0), m_iAreaID(-1) {}
	CvContinent(const CvContinent& other)
		: m_uiFertility(other.m_uiFertility), m_uiFertilityNextRegion(other.m_uiFertilityNextRegion),
		  m_iRegionsAssigned(other.m_iRegionsAssigned), m_iAreaID(other.m_iAreaID) {}
	bool operator<(const CvContinent& other) { return m_uiFertilityNextRegion > other.m_uiFertilityNextRegion; }
	void AddRegion() { ++m_iRegionsAssigned; m_uiFertilityNextRegion = m_uiFertility / (m_iRegionsAssigned + 1); }
	int GetNumRegions() const { return m_iRegionsAssigned; }
	void SetFertility(int value) { m_uiFertility = m_uiFertilityNextRegion = value; }
	int GetFertility() const { return m_uiFertility; }
	void SetArea(int area) { m_iAreaID = area; }
	int GetArea() const { return m_iAreaID; }
private:
	int m_uiFertility;
	int m_uiFertilityNextRegion;
	int m_iRegionsAssigned;
	int m_iAreaID;
};

class CvStartRegion
{
public:
	CvStartRegion() : m_uiFertility(0), m_iAreaID(-1), m_bLargeEnoughForMajorCiv(true), m_iNumCivsPlaced(0) {}
	CvStartRegion(const CvStartRegion& other)
		: m_Boundaries(other.m_Boundaries), m_uiFertility(other.m_uiFertility), m_iAreaID(other.m_iAreaID),
		  m_bLargeEnoughForMajorCiv(other.m_bLargeEnoughForMajorCiv), m_iNumCivsPlaced(other.m_iNumCivsPlaced) {}
	bool operator<(const CvStartRegion& other)
	{
		return m_uiFertility / (m_iNumCivsPlaced + 1) > other.m_uiFertility / (other.m_iNumCivsPlaced + 1);
	}
	bool Contains(int x, int y)
	{
		return x <= m_Boundaries.m_iEastEdge && x >= m_Boundaries.m_iWestEdge
			&& y <= m_Boundaries.m_iNorthEdge && y >= m_Boundaries.m_iSouthEdge;
	}
	CvAreaBoundaries m_Boundaries;
	int m_uiFertility;
	int m_iAreaID;
	bool m_bLargeEnoughForMajorCiv;
	int m_iNumCivsPlaced;
};

class CvPlayerStartRank
{
public:
	CvPlayerStartRank() : m_iPlayerID(-1), m_iRank(0) {}
	CvPlayerStartRank(const CvPlayerStartRank& other) : m_iPlayerID(other.m_iPlayerID), m_iRank(other.m_iRank) {}
	bool operator<(const CvPlayerStartRank& other) { return m_iRank < other.m_iRank; }
	int m_iPlayerID;
	int m_iRank;
};

class CvStartPositioner
{
public:
	CvStartPositioner();
	~CvStartPositioner();
	virtual void Init(CvSiteEvaluatorForStart* pSiteEvaluator);
	void DivideMapIntoRegions(int iNumRegions);
	void ComputeFoundValues();
	void RankPlayerStartOrder();
	void AssignStartingLocations();
	int GetRegion(int iX, int iY);
private:
	void DivideContinentIntoRegions(CvContinent continent);
	void ComputeTileFertilityValues();
	void SubdivideRegion(CvStartRegion region, int iNumDivisions);
	void ChopIntoTwoRegions(bool bTaller, CvStartRegion* region, CvStartRegion* secondRegion, int iChopPercent);
	void ChopIntoThreeRegions(bool bTaller, CvStartRegion* region, CvStartRegion* secondRegion, CvStartRegion* thirdRegion);
	int ComputeRowFertility(int iAreaID, int xMin, int xMax, int yMin, int yMax);
	bool AddCivToRegion(int iPlayerIndex, CvStartRegion region, bool bRelaxFoodReq);
	bool TooCloseToAnotherCiv(CvPlot* pPlot);
	bool MeetsFoodRequirement(CvPlot* pPlot, TeamTypes eTeam, int iFoodRequirement);
	int StartingPlotRange() const;
	void LogStartPositionMessage(CvString strMsg);
	CvSiteEvaluatorForStart* m_pSiteEvaluator;
	std::vector<CvContinent> m_ContinentVector;
	std::vector<CvStartRegion> m_StartRegionVector;
	std::vector<CvPlayerStartRank> m_PlayerOrder;
	std::vector<CvPlayerStartRank>::iterator m_PlayerOrderIter;
	int m_iRequiredSeparation;
	int m_iBestFoundValueOnMap;
};
