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
#include "CvGameCoreDLLPCH.h"
#include "CvStartPositioner.h"
#include "CvSiteEvaluationClasses.h"
#include "CvArea.h"
#include "CvMinorCivAI.h"
#include <algorithm>

namespace ASL { namespace StdLib { namespace Sort {
	template<class Iterator, class Difference> void _Sort(Iterator first, Iterator last, Difference count);
}}}

extern CvPlayerAI* startPlayers asm("_ZN10CvPlayerAI10m_aPlayersE");

namespace
{
	// TODO: Phase1 StartPlayer: hardcoded 0xf598 player stride is prohibited; recover CvPlayerAI storage/layout before claiming a match.
	CvPlayer& StartPlayer(int index)
	{
		return *reinterpret_cast<CvPlayer*>(reinterpret_cast<char*>(startPlayers) + index * 0xf598);
	}

	// TODO: Phase1 SortStartData: inlined template; referenced ASL sort target and all caller instructions require comparison.
	template<class T> void SortStartData(std::vector<T>& values)
	{
		ASL::StdLib::Sort::_Sort(values.begin(), values.end(), static_cast<int>(values.size()));
	}

	// Player storage is incomplete; these flags are verified target fields.
	// TODO: Phase1 PlayerFlag: raw 0x858/0x864 flag offsets are prohibited; recover named CvPlayer members/accessors.
	bool PlayerFlag(const CvPlayer& player, unsigned int offset)
	{
		return *reinterpret_cast<const bool*>(reinterpret_cast<const char*>(&player) + offset);
	}
	// TODO: Phase1 StartPlayerTeam: raw player ID offset 0x28 is prohibited; recover the named field/accessor.
	TeamTypes StartPlayerTeam(const CvPlayer& player)
	{
		const int id = *reinterpret_cast<const int*>(reinterpret_cast<const char*>(&player) + 0x28);
		return static_cast<unsigned int>(id) < 64 ? (*CvPreGame::sr_TeamTypes)[id] : NO_TEAM;
	}
	// TODO: Phase1 StartPlotX: raw coordinate reinterpretation is prohibited; use a verified named CvPlot field/accessor.
	int StartPlotX(const CvPlot* plot) { return *reinterpret_cast<const short*>(plot); }
	// TODO: Phase1 StartPlotY: hardcoded short-array coordinate slot is prohibited; use a verified named CvPlot field/accessor.
	int StartPlotY(const CvPlot* plot) { return reinterpret_cast<const short*>(plot)[1]; }
	// TODO: Phase1 StartAreaID: raw area ID offset 4 is prohibited; recover the named CvArea field/accessor.
	int StartAreaID(const CvArea* area)
	{
		return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(area) + 4);
	}
}

// TODO: Phase1 CvStartPositioner::CvStartPositioner(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvStartPositioner::CvStartPositioner(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
CvStartPositioner::CvStartPositioner()
{
	m_PlayerOrderIter = m_PlayerOrder.begin();
	m_iBestFoundValueOnMap = 0;
	m_iRequiredSeparation = 0;
}

// TODO: Phase1 CvStartPositioner::~CvStartPositioner(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvStartPositioner::~CvStartPositioner(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
CvStartPositioner::~CvStartPositioner()
{
}

// TODO: Phase1 CvStartPositioner::Init(CvSiteEvaluatorForStart*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvStartPositioner::Init(CvSiteEvaluatorForStart* pSiteEvaluator)
{
	if(!pSiteEvaluator) return;
	m_pSiteEvaluator = pSiteEvaluator;
	m_pSiteEvaluator->ComputeFlavorMultipliers(NULL);
}

// TODO: Phase1 CvStartPositioner::DivideMapIntoRegions(int): MISMATCH; Non-padding instruction count: BE 165, object 151; Civ5 changed/new instruction count unverified.
void CvStartPositioner::DivideMapIntoRegions(int iNumRegions)
{
	m_ContinentVector.clear();
	m_StartRegionVector.clear();
	ComputeTileFertilityValues();
	int iterator;
	for(CvArea* area = GC.getMap().firstArea(&iterator); area; area = GC.getMap().nextArea(&iterator))
	{
		if(area->getTotalFoundValue() > 0 && area->getNumTiles() >= GC.getMIN_START_AREA_TILES())
		{
			CvContinent continent;
			continent.SetFertility(area->getTotalFoundValue());
			continent.SetArea(StartAreaID(area));
			m_ContinentVector.push_back(continent);
		}
	}
	if(!m_ContinentVector.empty())
	{
		for(int i = 0; i < iNumRegions; ++i)
		{
			SortStartData(m_ContinentVector);
			m_ContinentVector[0].AddRegion();
		}
	}
	for(unsigned int i = 0; i < m_ContinentVector.size(); ++i)
		DivideContinentIntoRegions(m_ContinentVector[i]);
	SortStartData(m_StartRegionVector);
}

// TODO: Phase1 CvStartPositioner::ComputeTileFertilityValues(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvStartPositioner::ComputeTileFertilityValues()
{
	int iterator;
	for(CvArea* area = GC.getMap().firstArea(&iterator); area; area = GC.getMap().nextArea(&iterator))
		area->setTotalFoundValue(0);
	for(int i = 0; i < GC.getMap().numPlots(); ++i)
	{
		CvPlot* plot = GC.getMap().plotByIndexUnchecked(i);
		if(!plot) continue;
		const int fertility = m_pSiteEvaluator->PlotFertilityValue(plot);
		plot->setFoundValue(static_cast<PlayerTypes>(0), fertility);
		if(fertility > 0)
		{
			CvArea* area = GC.getMap().getArea(plot->getArea());
			if(area) area->setTotalFoundValue(area->getTotalFoundValue() + fertility);
		}
	}
}

// TODO: Phase1 CvStartPositioner::DivideContinentIntoRegions(CvContinent): MISMATCH; Non-padding instruction count: BE 80, object 76; Civ5 changed/new instruction count unverified.
void CvStartPositioner::DivideContinentIntoRegions(CvContinent continent)
{
	CvStartRegion region;
	region.m_uiFertility = continent.GetFertility();
	region.m_iAreaID = continent.GetArea();
	region.m_Boundaries = GC.getMap().getArea(continent.GetArea())->getAreaBoundaries();
	if(continent.GetNumRegions() > 0)
		SubdivideRegion(region, continent.GetNumRegions());
	else
	{
		region.m_bLargeEnoughForMajorCiv = false;
		m_StartRegionVector.push_back(region);
	}
}

// TODO: Phase1 CvStartPositioner::ComputeFoundValues(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvStartPositioner::ComputeFoundValues()
{
	for(int i = 0; i < GC.getMap().numPlots(); ++i)
	{
		CvPlot* plot = GC.getMap().plotByIndexUnchecked(i);
		if(!plot) continue;
		const int value = m_pSiteEvaluator->PlotFoundValue(plot, NULL, NO_YIELD, false, false);
		plot->setFoundValue(static_cast<PlayerTypes>(1), value);
		if(value > m_iBestFoundValueOnMap) m_iBestFoundValueOnMap = value;
	}
}

// TODO: Phase1 CvStartPositioner::RankPlayerStartOrder(): MISMATCH; Non-padding instruction count: BE 103, object 102; Civ5 changed/new instruction count unverified.
void CvStartPositioner::RankPlayerStartOrder()
{
	m_PlayerOrder.clear();
	for(int i = 0; i < 62; ++i)
	{
		CvPlayer& player = StartPlayer(i);
		if(!PlayerFlag(player, 0x864) || player.getStartingPlot()) continue;
		CvPlayerStartRank rank;
		rank.m_iPlayerID = i;
		if(!player.isHuman())
		{
			// The target calls these predicates, but all nonhuman players receive 50.
			if(!player.isMinorCiv() && !player.isNeutralProxy()) player.isAlien();
			rank.m_iRank = 50;
		}
		rank.m_iRank += GC.getGame().getGameRandNum(49, "Player Start Plot Draft Order");
		m_PlayerOrder.push_back(rank);
	}
	SortStartData(m_PlayerOrder);
}

// TODO: Phase1 CvStartPositioner::AssignStartingLocations(): MISMATCH; Non-padding instruction count: BE 579, object 546; Civ5 changed/new instruction count unverified.
void CvStartPositioner::AssignStartingLocations()
{
	CvString message;
	unsigned int nextRegion = 0;
	int placed = 0;
	int majors = 0;
	for(unsigned int i = 0; i < m_PlayerOrder.size(); ++i)
		if(!StartPlayer(m_PlayerOrder[i].m_iPlayerID).isMinorCiv()) ++majors;
	m_iRequiredSeparation = StartingPlotRange();
	if(GC.getMap().getWorldSize() == WORLDSIZE_DEBUG) m_iRequiredSeparation = 1;
	while(placed < majors && nextRegion < m_StartRegionVector.size())
	{
		CvStartRegion& region = m_StartRegionVector[nextRegion];
		if(region.m_bLargeEnoughForMajorCiv)
		{
			message.Format("Trying to place major civ with full separation of %d", m_iRequiredSeparation);
			LogStartPositionMessage(message);
			if(AddCivToRegion(m_PlayerOrder[placed].m_iPlayerID, region, false))
			{
				++placed;
				++region.m_iNumCivsPlaced;
			}
		}
		++nextRegion;
	}
	const int halfMinimum = GC.getMIN_CIV_STARTING_DISTANCE() / 2;
	while(placed < majors && m_iRequiredSeparation >= 0)
	{
		SortStartData(m_StartRegionVector);
		--m_iRequiredSeparation;
		nextRegion = 0;
		while(placed < majors && nextRegion < m_StartRegionVector.size())
		{
			CvStartRegion& region = m_StartRegionVector[nextRegion];
			if(region.m_bLargeEnoughForMajorCiv)
			{
				message.Format("Trying to place major civ with reduced separation of %d", m_iRequiredSeparation);
				LogStartPositionMessage(message);
				if(AddCivToRegion(m_PlayerOrder[placed].m_iPlayerID, region, m_iRequiredSeparation < halfMinimum))
				{
					++placed;
					++region.m_iNumCivsPlaced;
				}
			}
			++nextRegion;
		}
	}
	m_iRequiredSeparation = StartingPlotRange();
	SortStartData(m_StartRegionVector);
	while(placed < static_cast<int>(m_PlayerOrder.size()) && nextRegion < m_StartRegionVector.size())
	{
		message.Format("Trying to place minor civ with full separation of %d", m_iRequiredSeparation);
		LogStartPositionMessage(message);
		if(AddCivToRegion(m_PlayerOrder[placed].m_iPlayerID, m_StartRegionVector[nextRegion], false))
		{
			++placed;
			++m_StartRegionVector[nextRegion].m_iNumCivsPlaced;
			SortStartData(m_StartRegionVector);
			nextRegion = 0;
		}
		else ++nextRegion;
	}
	while(placed < static_cast<int>(m_PlayerOrder.size()) && m_iRequiredSeparation >= 0)
	{
		SortStartData(m_StartRegionVector);
		--m_iRequiredSeparation;
		nextRegion = 0;
		while(placed < static_cast<int>(m_PlayerOrder.size()) && nextRegion < m_StartRegionVector.size())
		{
			message.Format("Trying to place minor civ with reduced separation of %d", m_iRequiredSeparation);
			LogStartPositionMessage(message);
			if(AddCivToRegion(m_PlayerOrder[placed].m_iPlayerID, m_StartRegionVector[nextRegion], false))
			{
				++placed;
				++m_StartRegionVector[nextRegion].m_iNumCivsPlaced;
				SortStartData(m_StartRegionVector);
				nextRegion = 0;
			}
			else ++nextRegion;
		}
	}
}

// TODO: Phase1 CvStartPositioner::StartingPlotRange() const: UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvStartPositioner::StartingPlotRange() const
{
	int range = (GC.getMap().maxPlotDistance() + 10) * GC.getSTARTING_DISTANCE_PERCENT() / 100;
	const int majors = GC.getGame().countMajorCivsAlive();
	const int minors = GC.getGame().countCivPlayersAlive() - majors;
	const int cities = std::max(1, GC.getMap().getWorldInfo().getTargetNumCities() * majors + minors);
	range = range * GC.getMap().getLandPlots() / 18 / cities;
	return std::max(range, GC.getMIN_CIV_STARTING_DISTANCE());
}

// TODO: Phase1 CvStartPositioner::LogStartPositionMessage(CvString): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvStartPositioner::LogStartPositionMessage(CvString strMsg)
{
	if(GC.getLogging() && GC.getAILogging())
		LOGFILEMGR.GetLog("StartPositionLog.csv", FILogFile::kDontTimeStamp)->Msg(strMsg.c_str());
}

// TODO: Phase1 CvStartPositioner::AddCivToRegion(int, CvStartRegion, bool): MISMATCH; Non-padding instruction count: BE 325, object 320; Civ5 changed/new instruction count unverified.
bool CvStartPositioner::AddCivToRegion(int iPlayerIndex, CvStartRegion region, bool bRelaxFoodReq)
{
	CvString message;
	int bestValue = 0;
	CvPlot* bestPlot = NULL;
	int minorFood = GC.getMINOR_CIV_FOOD_REQUIREMENT();
	int majorFood = GC.getMAJOR_CIV_FOOD_REQUIREMENT();
	CvPlayer& player = StartPlayer(iPlayerIndex);
	const bool minor = player.isMinorCiv();
	const TeamTypes team = StartPlayerTeam(player);
	const int percent = GC.getMIN_START_FOUND_VALUE_AS_PERCENT_OF_BEST();
	MinorCivTypes minorType = NO_MINORCIV;
	if(minor) minorType = static_cast<MinorCivTypes>(player.GetMinorCivAI()->GetMinorCivType());
	const bool debug = GC.getMap().getWorldSize() == WORLDSIZE_DEBUG;
	if(debug) minorFood = majorFood = 0;
	for(int y = region.m_Boundaries.m_iSouthEdge; y <= region.m_Boundaries.m_iNorthEdge; ++y)
	{
		for(int x = region.m_Boundaries.m_iWestEdge; x <= region.m_Boundaries.m_iEastEdge; ++x)
		{
			CvPlot* plot = GC.getMap().plot(x, y);
			if(!plot || plot->getArea() != region.m_iAreaID) continue;
			if(!((bRelaxFoodReq && MeetsFoodRequirement(plot, team, minorFood))
				|| (minor && MeetsFoodRequirement(plot, team, minorFood))
				|| MeetsFoodRequirement(plot, team, majorFood))) continue;
			int value = plot->getFoundValue(static_cast<PlayerTypes>(1));
			if(minor && GC.getMinorCivInfo(minorType)->GetMinorCivTrait() == 2
				&& !plot->isCoastalLand(GC.getLAKE_MAX_AREA_SIZE())) value /= 2;
			if((debug || value > m_iBestFoundValueOnMap * percent / 100)
				&& !TooCloseToAnotherCiv(plot) && (debug || value > bestValue))
			{
				bestValue = value;
				bestPlot = plot;
			}
		}
	}
	if(!bestPlot) return false;
	player.setStartingPlot(bestPlot);
	message.Format("Adding player, id = %d, plot x = %d, y = %d, fertility = %u",
		iPlayerIndex, StartPlotX(bestPlot), StartPlotY(bestPlot), bestValue);
	LogStartPositionMessage(message);
	return true;
}

int CvStartPositioner::GetRegion(int iX, int iY)
{
	for(int i = 0; i < static_cast<int>(m_StartRegionVector.size()); ++i)
		if(m_StartRegionVector[i].Contains(iX, iY)) return i;
	return -1;
}

// TODO: Phase1 CvStartPositioner::SubdivideRegion(CvStartRegion, int): MISMATCH; Non-padding instruction count: BE 183, object 169; Civ5 changed/new instruction count unverified.
void CvStartPositioner::SubdivideRegion(CvStartRegion region, int iNumDivisions)
{
	if(iNumDivisions == 1)
	{
		m_StartRegionVector.push_back(region);
		return;
	}
	if(iNumDivisions < 2 || iNumDivisions > 22) return;
	const bool taller = region.m_Boundaries.m_iNorthEdge - region.m_Boundaries.m_iSouthEdge
		>= region.m_Boundaries.m_iEastEdge - region.m_Boundaries.m_iWestEdge;
	static const int divisions[] = {2, 3, 2, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 3, 3};
	static const int later[] = {1, 1, 2, 2, 2, 4, 4, 3, 4, 4, 4, 8, 8, 8, 8, 6, 6, 10, 10, 8, 8};
	const int count = later[iNumDivisions - 2];
	CvStartRegion second;
	if(divisions[iNumDivisions - 2] == 2)
	{
		ChopIntoTwoRegions(taller, &region, &second, 50);
		SubdivideRegion(region, count);
		SubdivideRegion(second, count);
	}
	else
	{
		CvStartRegion third;
		ChopIntoThreeRegions(taller, &region, &second, &third);
		SubdivideRegion(region, count);
		SubdivideRegion(second, count);
		SubdivideRegion(third, count);
	}
}

// TODO: Phase1 CvStartPositioner::ChopIntoTwoRegions(bool, CvStartRegion*, CvStartRegion*, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvStartPositioner::ChopIntoTwoRegions(bool bTaller, CvStartRegion* region, CvStartRegion* secondRegion, int iChopPercent)
{
	if(!region || !secondRegion) return;
	secondRegion->m_iAreaID = region->m_iAreaID;
	const int target = region->m_uiFertility * iChopPercent / 100;
	int fertility = 0;
	if(bTaller)
	{
		secondRegion->m_Boundaries.m_iEastEdge = region->m_Boundaries.m_iEastEdge;
		secondRegion->m_Boundaries.m_iWestEdge = region->m_Boundaries.m_iWestEdge;
		secondRegion->m_Boundaries.m_iNorthEdge = region->m_Boundaries.m_iNorthEdge;
		int edge = region->m_Boundaries.m_iSouthEdge;
		while(fertility < target)
		{
			fertility += ComputeRowFertility(region->m_iAreaID, region->m_Boundaries.m_iWestEdge,
				region->m_Boundaries.m_iEastEdge, edge, edge);
			++edge;
		}
		region->m_Boundaries.m_iNorthEdge = edge - 1;
		secondRegion->m_Boundaries.m_iSouthEdge = edge;
	}
	else
	{
		secondRegion->m_Boundaries.m_iNorthEdge = region->m_Boundaries.m_iNorthEdge;
		secondRegion->m_Boundaries.m_iSouthEdge = region->m_Boundaries.m_iSouthEdge;
		secondRegion->m_Boundaries.m_iEastEdge = region->m_Boundaries.m_iEastEdge;
		int edge = region->m_Boundaries.m_iWestEdge;
		while(fertility < target)
		{
			fertility += ComputeRowFertility(region->m_iAreaID, edge, edge,
				region->m_Boundaries.m_iSouthEdge, region->m_Boundaries.m_iNorthEdge);
			++edge;
		}
		region->m_Boundaries.m_iEastEdge = edge - 1;
		secondRegion->m_Boundaries.m_iWestEdge = edge;
	}
	secondRegion->m_uiFertility = region->m_uiFertility - fertility;
	region->m_uiFertility = fertility;
}

// TODO: Phase1 CvStartPositioner::ChopIntoThreeRegions(bool, CvStartRegion*, CvStartRegion*, CvStartRegion*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvStartPositioner::ChopIntoThreeRegions(bool bTaller, CvStartRegion* region, CvStartRegion* secondRegion, CvStartRegion* thirdRegion)
{
	if(!region || !secondRegion || !thirdRegion) return;
	ChopIntoTwoRegions(bTaller, region, secondRegion, 33);
	ChopIntoTwoRegions(bTaller, secondRegion, thirdRegion, 50);
}

// TODO: Phase1 CvStartPositioner::ComputeRowFertility(int, int, int, int, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvStartPositioner::ComputeRowFertility(int iAreaID, int xMin, int xMax, int yMin, int yMax)
{
	int fertility = 0;
	for(int y = yMin; y <= yMax; ++y)
		for(int x = xMin; x <= xMax; ++x)
		{
			CvPlot* plot = GC.getMap().plot(x, y);
			if(plot && plot->getArea() == iAreaID) fertility += plot->getFoundValue(static_cast<PlayerTypes>(0));
		}
	return fertility;
}

// TODO: Phase1 CvStartPositioner::MeetsFoodRequirement(CvPlot*, TeamTypes, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool CvStartPositioner::MeetsFoodRequirement(CvPlot* pPlot, TeamTypes eTeam, int iFoodRequirement)
{
	if(!pPlot) return false;
	for(int i = 0; i < 6; ++i)
	{
		CvPlot* neighbor = plotDirection(StartPlotX(pPlot), StartPlotY(pPlot), static_cast<DirectionTypes>(i));
		if(!neighbor) return false;
		if(neighbor->calculateNatureYield(YIELD_FOOD, eTeam, false) >= iFoodRequirement) return true;
	}
	return false;
}

// TODO: Phase1 CvStartPositioner::TooCloseToAnotherCiv(CvPlot*): MISMATCH; Non-padding instruction count: BE 254, object 146; Civ5 changed/new instruction count unverified.
bool CvStartPositioner::TooCloseToAnotherCiv(CvPlot* pPlot)
{
	if(!pPlot) return false;
	for(int i = 0; i < 64; ++i)
	{
		CvPlayer& player = StartPlayer(i);
		if(!PlayerFlag(player, 0x858)) continue;
		CvPlot* start = player.getStartingPlot();
		if(!start) continue;
		const int separation = start->getArea() == pPlot->getArea() ? m_iRequiredSeparation
			: m_iRequiredSeparation * GC.getMIN_DISTANCE_OTHER_AREA_PERCENT() / 100;
		if(plotDistance(StartPlotX(pPlot), StartPlotY(pPlot), StartPlotX(start), StartPlotY(start)) < separation)
			return true;
	}
	return false;
}
