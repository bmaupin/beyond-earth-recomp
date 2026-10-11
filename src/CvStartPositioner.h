// TODO: Phase1 std::__1::__vector_base_common<true>::__throw_length_error() const: MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__basic_string_common<true>::__throw_length_error() const: MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__init(char const*, unsigned int): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<CvContinent, std::__1::allocator<CvContinent> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<CvStartRegion, std::__1::allocator<CvStartRegion> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<CvPlayerStartRank, std::__1::allocator<CvPlayerStartRank> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__split_buffer<CvContinent, std::__1::allocator<CvContinent>&>::~__split_buffer(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__split_buffer<CvStartRegion, std::__1::allocator<CvStartRegion>&>::~__split_buffer(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__split_buffer<CvPlayerStartRank, std::__1::allocator<CvPlayerStartRank>&>::~__split_buffer(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 void std::__1::vector<CvContinent, std::__1::allocator<CvContinent> >::__push_back_slow_path<CvContinent const&>(CvContinent const&): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::vector<CvContinent, std::__1::allocator<CvContinent> >::__swap_out_circular_buffer(std::__1::__split_buffer<CvContinent, std::__1::allocator<CvContinent>&>&): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 void std::__1::vector<CvStartRegion, std::__1::allocator<CvStartRegion> >::__push_back_slow_path<CvStartRegion const&>(CvStartRegion const&): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::vector<CvStartRegion, std::__1::allocator<CvStartRegion> >::__swap_out_circular_buffer(std::__1::__split_buffer<CvStartRegion, std::__1::allocator<CvStartRegion>&>&): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 void std::__1::vector<CvPlayerStartRank, std::__1::allocator<CvPlayerStartRank> >::__push_back_slow_path<CvPlayerStartRank const&>(CvPlayerStartRank const&): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::vector<CvPlayerStartRank, std::__1::allocator<CvPlayerStartRank> >::__swap_out_circular_buffer(std::__1::__split_buffer<CvPlayerStartRank, std::__1::allocator<CvPlayerStartRank>&>&): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
#pragma once

#include <vector>
#include "CvStructs.h"
#include "CvGameCoreDLLUtil/include/CvString.h"

class CvSiteEvaluatorForStart;
class CvPlot;

class CvContinent
{
public:
	// TODO: Phase1 inline CvContinent() : m_uiFertility(0), m_uiFertilityNextRegion(0), m_iRegionsAssigned(0), m_iAreaID(-1): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	CvContinent() : m_uiFertility(0), m_uiFertilityNextRegion(0), m_iRegionsAssigned(0), m_iAreaID(-1) {}
	// TODO: Phase1 inline CvContinent(const CvContinent& other): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	CvContinent(const CvContinent& other)
		: m_uiFertility(other.m_uiFertility), m_uiFertilityNextRegion(other.m_uiFertilityNextRegion),
		  m_iRegionsAssigned(other.m_iRegionsAssigned), m_iAreaID(other.m_iAreaID) {}
	// TODO: Phase1 inline bool operator<(const CvContinent& other): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	bool operator<(const CvContinent& other) { return m_uiFertilityNextRegion > other.m_uiFertilityNextRegion; }
	// TODO: Phase1 inline void AddRegion(): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	void AddRegion() { ++m_iRegionsAssigned; m_uiFertilityNextRegion = m_uiFertility / (m_iRegionsAssigned + 1); }
	// TODO: Phase1 inline int GetNumRegions() const: UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	int GetNumRegions() const { return m_iRegionsAssigned; }
	// TODO: Phase1 inline void SetFertility(int value): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	void SetFertility(int value) { m_uiFertility = m_uiFertilityNextRegion = value; }
	// TODO: Phase1 inline int GetFertility() const: UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	int GetFertility() const { return m_uiFertility; }
	// TODO: Phase1 inline void SetArea(int area): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	void SetArea(int area) { m_iAreaID = area; }
	// TODO: Phase1 inline int GetArea() const: UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
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
	// TODO: Phase1 inline CvStartRegion() : m_uiFertility(0), m_iAreaID(-1), m_bLargeEnoughForMajorCiv(true), m_iNumCivsPlaced(0): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	CvStartRegion() : m_uiFertility(0), m_iAreaID(-1), m_bLargeEnoughForMajorCiv(true), m_iNumCivsPlaced(0) {}
	// TODO: Phase1 inline CvStartRegion(const CvStartRegion& other): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	CvStartRegion(const CvStartRegion& other)
		: m_Boundaries(other.m_Boundaries), m_uiFertility(other.m_uiFertility), m_iAreaID(other.m_iAreaID),
		  m_bLargeEnoughForMajorCiv(other.m_bLargeEnoughForMajorCiv), m_iNumCivsPlaced(other.m_iNumCivsPlaced) {}
	// TODO: Phase1 inline bool operator<(const CvStartRegion& other): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	bool operator<(const CvStartRegion& other)
	{
		return m_uiFertility / (m_iNumCivsPlaced + 1) > other.m_uiFertility / (other.m_iNumCivsPlaced + 1);
	}
	// TODO: Phase1 inline bool Contains(int x, int y): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
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
	// TODO: Phase1 inline CvPlayerStartRank() : m_iPlayerID(-1), m_iRank(0): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	CvPlayerStartRank() : m_iPlayerID(-1), m_iRank(0) {}
	// TODO: Phase1 inline CvPlayerStartRank(const CvPlayerStartRank& other) : m_iPlayerID(other.m_iPlayerID), m_iRank(other.m_iRank): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	CvPlayerStartRank(const CvPlayerStartRank& other) : m_iPlayerID(other.m_iPlayerID), m_iRank(other.m_iRank) {}
	// TODO: Phase1 inline bool operator<(const CvPlayerStartRank& other): UNVERIFIED; no standalone current export; compare inlined callers and Civ5 changed/new regions.
	bool operator<(const CvPlayerStartRank& other) { return m_iRank < other.m_iRank; }
	int m_iPlayerID;
	int m_iRank;
};

class CvStartPositioner
{
public:
// TODO: Phase1 CvStartPositioner::CvStartPositioner(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvStartPositioner::CvStartPositioner(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	CvStartPositioner();
// TODO: Phase1 CvStartPositioner::~CvStartPositioner(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvStartPositioner::~CvStartPositioner(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	~CvStartPositioner();
// TODO: Phase1 CvStartPositioner::Init(CvSiteEvaluatorForStart*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	virtual void Init(CvSiteEvaluatorForStart* pSiteEvaluator);
// TODO: Phase1 CvStartPositioner::DivideMapIntoRegions(int): MISMATCH; Non-padding instruction count: BE 165, object 151; Civ5 changed/new instruction count unverified.
	void DivideMapIntoRegions(int iNumRegions);
// TODO: Phase1 CvStartPositioner::ComputeFoundValues(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	void ComputeFoundValues();
// TODO: Phase1 CvStartPositioner::RankPlayerStartOrder(): MISMATCH; Non-padding instruction count: BE 103, object 102; Civ5 changed/new instruction count unverified.
	void RankPlayerStartOrder();
// TODO: Phase1 CvStartPositioner::AssignStartingLocations(): MISMATCH; Non-padding instruction count: BE 579, object 546; Civ5 changed/new instruction count unverified.
	void AssignStartingLocations();
	int GetRegion(int iX, int iY);
private:
// TODO: Phase1 CvStartPositioner::DivideContinentIntoRegions(CvContinent): MISMATCH; Non-padding instruction count: BE 80, object 76; Civ5 changed/new instruction count unverified.
	void DivideContinentIntoRegions(CvContinent continent);
// TODO: Phase1 CvStartPositioner::ComputeTileFertilityValues(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	void ComputeTileFertilityValues();
// TODO: Phase1 CvStartPositioner::SubdivideRegion(CvStartRegion, int): MISMATCH; Non-padding instruction count: BE 183, object 169; Civ5 changed/new instruction count unverified.
	void SubdivideRegion(CvStartRegion region, int iNumDivisions);
// TODO: Phase1 CvStartPositioner::ChopIntoTwoRegions(bool, CvStartRegion*, CvStartRegion*, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	void ChopIntoTwoRegions(bool bTaller, CvStartRegion* region, CvStartRegion* secondRegion, int iChopPercent);
// TODO: Phase1 CvStartPositioner::ChopIntoThreeRegions(bool, CvStartRegion*, CvStartRegion*, CvStartRegion*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	void ChopIntoThreeRegions(bool bTaller, CvStartRegion* region, CvStartRegion* secondRegion, CvStartRegion* thirdRegion);
// TODO: Phase1 CvStartPositioner::ComputeRowFertility(int, int, int, int, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	int ComputeRowFertility(int iAreaID, int xMin, int xMax, int yMin, int yMax);
// TODO: Phase1 CvStartPositioner::AddCivToRegion(int, CvStartRegion, bool): MISMATCH; Non-padding instruction count: BE 325, object 320; Civ5 changed/new instruction count unverified.
	bool AddCivToRegion(int iPlayerIndex, CvStartRegion region, bool bRelaxFoodReq);
// TODO: Phase1 CvStartPositioner::TooCloseToAnotherCiv(CvPlot*): MISMATCH; Non-padding instruction count: BE 254, object 146; Civ5 changed/new instruction count unverified.
	bool TooCloseToAnotherCiv(CvPlot* pPlot);
// TODO: Phase1 CvStartPositioner::MeetsFoodRequirement(CvPlot*, TeamTypes, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool MeetsFoodRequirement(CvPlot* pPlot, TeamTypes eTeam, int iFoodRequirement);
// TODO: Phase1 CvStartPositioner::StartingPlotRange() const: UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	int StartingPlotRange() const;
// TODO: Phase1 CvStartPositioner::LogStartPositionMessage(CvString): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	void LogStartPositionMessage(CvString strMsg);
	CvSiteEvaluatorForStart* m_pSiteEvaluator;
	std::vector<CvContinent> m_ContinentVector;
	std::vector<CvStartRegion> m_StartRegionVector;
	std::vector<CvPlayerStartRank> m_PlayerOrder;
	std::vector<CvPlayerStartRank>::iterator m_PlayerOrderIter;
	int m_iRequiredSeparation;
	int m_iBestFoundValueOnMap;
};
