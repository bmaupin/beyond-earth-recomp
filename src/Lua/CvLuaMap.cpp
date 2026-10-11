// TODO: Phase1 (anonymous namespace)::OffsetPlot(int, int, int, int): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 CvLuaStaticInstance<CvLuaMap, CvMap>::RegisterMethod(lua_State*, int (*)(lua_State*), char const*): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 CvLuaStaticInstance<CvLuaMap, CvMap>::pRegister(lua_State*): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
#include "CvGameCoreDLLPCH.h"
#include "CvLuaMap.h"
#include "CvLuaArea.h"
#include "CvLuaPlot.h"
#include "CvFractal.h"
#include "CvMap.h"
#include "CvPreGame.h"
#include "CvGameCoreUtils.h"

template int CvLuaStaticInstance<CvLuaMap, CvMap>::pRegister(lua_State* L);

#define Method(Name) RegisterMethod(L, l##Name, #Name)

namespace
{
	CvPlot* OffsetPlot(int x, int y, int dx, int dy)
	{
		const int hexX = xToHexspaceX(x, y) + dx;
		const int plotY = y + dy;
		const int plotX = hexX + (plotY >= 0 ? plotY >> 1 : (plotY - 1) / 2);
		return GC.getMap().plot(plotX, plotY);
	}
}

// TODO: Phase1 CvLuaMap::GetInstanceName(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
const char* CvLuaMap::GetInstanceName()
{
	return "Map";
}

// TODO: Phase1 CvLuaMap::GetInstance(lua_State*, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
CvMap* CvLuaMap::GetInstance(lua_State*, int)
{
	return &GC.getMap();
}

// TODO: Phase1 CvLuaMap::RegisterMembers(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvLuaMap::RegisterMembers(lua_State* L)
{
	Method(Areas);
	Method(FindBiggestArea);
	Method(FindWater);
	Method(FindNearestStartPlot);
	Method(GetClimate);
	Method(GetFractalFlags);
	Method(GetGridSize);
	Method(GetNumPlots);
	Method(GetNumResources);
	Method(GetNumResourcesOnLand);
	Method(GetPlot);
	Method(GetPlotByIndex);
	Method(GetPlotXY);
	Method(GetArea);
	Method(GetIndexAfterLastArea);
	Method(GetLandPlots);
	Method(GetWaterPlots);
	Method(GetLakePlots);
	Method(GetNumAreas);
	Method(GetNumLandAreas);
	Method(GetRandomResourceQuantity);
	Method(GetSeaLevel);
	Method(GetWorldSize);
	Method(IsPlot);
	Method(IsWrapX);
	Method(IsWrapY);
	Method(MaxPlotDistance);
	Method(Rand);
	Method(GetMapSeed);
	Method(CalculateAreas);
	Method(RecalculateAreas);
	Method(PlotDistance);
	Method(PlotXYWithRangeCheck);
	Method(PlotDirection);
	Method(DefaultContinentStamper);
	Method(GetCustomOption);
	Method(UpdateDeferredFog);
	Method(ChangeAIMapHint);
	Method(GetAIMapHint);
}

#undef Method

// TODO: Phase1 CvLuaMap::lAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lAreas(lua_State* L)
{
	lua_pushcclosure(L, CvLuaMap::lAreasAux, 0);
	return 1;
}

// TODO: Phase1 CvLuaMap::lAreasAux(lua_State*): MISMATCH; Non-padding instruction count: BE 58, object 53; Civ5 changed/new instruction count unverified.
int CvLuaMap::lAreasAux(lua_State* L)
{
	int iterator = 0;
	CvArea* area;
	if(lua_isnoneornil(L, 2))
		area = GC.getMap().firstArea(&iterator);
	else
	{
		iterator = lua_tointeger(L, 2);
		area = GC.getMap().nextArea(&iterator);
	}
	if(!area) return 0;
	lua_pushinteger(L, iterator);
	CvLuaArea::Push(L, area);
	return 2;
}

// TODO: Phase1 CvLuaMap::lFindBiggestArea(lua_State*): MISMATCH; Non-padding instruction count: BE 41, object 43; Civ5 changed/new instruction count unverified.
int CvLuaMap::lFindBiggestArea(lua_State* L)
{
	CvArea* area = GC.getMap().findBiggestArea(lua_toboolean(L, 1));
	if(!area) return 0;
	CvLuaArea::Push(L, area);
	return 1;
}

// TODO: Phase1 CvLuaMap::lFindWater(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lFindWater(lua_State* L)
{
	CvPlot* plot = CvLuaPlot::GetInstance(L, 1);
	const int range = luaL_checkinteger(L, 2);
	const bool freshWater = lua_toboolean(L, 3);
	lua_pushboolean(L, GC.getMap().findWater(plot, range, freshWater));
	return 1;
}

// TODO: Phase1 CvLuaMap::lFindNearestStartPlot(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lFindNearestStartPlot(lua_State* L)
{
	const int x = lua_tointeger(L, 1);
	const int y = lua_tointeger(L, 2);
	PlayerTypes player = NO_PLAYER;
	CvLuaPlot::Push(L, GC.getMap().findNearestStartPlot(x, y, player));
	return 1;
}

#define MapInteger(Name, Expression) \
int CvLuaMap::l##Name(lua_State* L) \
{ \
	lua_pushinteger(L, Expression); \
	return 1; \
}

// TODO: Phase1 CvLuaMap::lGetClimate(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetClimate, GC.getMap().getClimate())
// TODO: Phase1 CvLuaMap::lGetNumPlots(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetNumPlots, GC.getMap().numPlots())
// TODO: Phase1 CvLuaMap::lGetIndexAfterLastArea(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetIndexAfterLastArea, GC.getMap().getIndexAfterLastArea())
// TODO: Phase1 CvLuaMap::lGetLandPlots(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetLandPlots, GC.getMap().getLandPlots())
// TODO: Phase1 CvLuaMap::lGetWaterPlots(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetWaterPlots, GC.getMap().getWaterPlots())
// TODO: Phase1 CvLuaMap::lGetLakePlots(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetLakePlots, GC.getMap().getLakePlots())
// TODO: Phase1 CvLuaMap::lGetNumAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetNumAreas, GC.getMap().getNumAreas())
// TODO: Phase1 CvLuaMap::lGetNumLandAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetNumLandAreas, GC.getMap().getNumLandAreas())
// TODO: Phase1 CvLuaMap::lGetSeaLevel(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetSeaLevel, GC.getMap().getSeaLevel())
// TODO: Phase1 CvLuaMap::lGetWorldSize(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetWorldSize, GC.getMap().getWorldSize())
// TODO: Phase1 CvLuaMap::lMaxPlotDistance(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(MaxPlotDistance, GC.getMap().maxPlotDistance())
// TODO: Phase1 CvLuaMap::lGetMapSeed(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetMapSeed, static_cast<int>(CvPreGame::mapRandomSeed()))
// TODO: Phase1 CvLuaMap::lGetAIMapHint(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
MapInteger(GetAIMapHint, GC.getMap().GetAIMapHint())

#undef MapInteger

// TODO: Phase1 CvLuaMap::lGetFractalFlags(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetFractalFlags(lua_State* L)
{
	const int flags = GC.getMap().getMapFractalFlags();
	lua_createtable(L, 0, 2);
	if(flags & CvFractal::FRAC_WRAP_X)
	{
		lua_pushboolean(L, true);
		lua_setfield(L, -2, "FRAC_WRAP_X");
	}
	if(flags & CvFractal::FRAC_WRAP_Y)
	{
		lua_pushboolean(L, true);
		lua_setfield(L, -2, "FRAC_WRAP_Y");
	}
	return 1;
}

// TODO: Phase1 CvLuaMap::lGetGridSize(lua_State*): MISMATCH; Mnemonic divergence at BE #9 cvtsi2sd, object #9 movsd; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetGridSize(lua_State* L)
{
	lua_pushinteger(L, GC.getMap().getGridWidth());
	lua_pushinteger(L, GC.getMap().getGridHeight());
	return 2;
}

// TODO: Phase1 CvLuaMap::lGetNumResources(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetNumResources(lua_State* L)
{
	const ResourceTypes resource = static_cast<ResourceTypes>(luaL_checkinteger(L, 1));
	lua_pushinteger(L, GC.getMap().getNumResources(resource));
	return 1;
}

// TODO: Phase1 CvLuaMap::lGetNumResourcesOnLand(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetNumResourcesOnLand(lua_State* L)
{
	const ResourceTypes resource = static_cast<ResourceTypes>(luaL_checkinteger(L, 1));
	lua_pushinteger(L, GC.getMap().getNumResourcesOnLand(resource));
	return 1;
}

// TODO: Phase1 CvLuaMap::lGetRandomResourceQuantity(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetRandomResourceQuantity(lua_State* L)
{
	const ResourceTypes resource = static_cast<ResourceTypes>(luaL_checkinteger(L, 1));
	lua_pushinteger(L, GC.getMap().getRandomResourceQuantity(resource));
	return 1;
}

// TODO: Phase1 CvLuaMap::lGetPlot(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetPlot(lua_State* L)
{
	const int x = lua_tointeger(L, 1);
	const int y = lua_tointeger(L, 2);
	CvPlot* plot = GC.getMap().plot(x, y);
	if(!plot) return 0;
	CvLuaPlot::Push(L, plot);
	return 1;
}

// TODO: Phase1 CvLuaMap::lGetPlotByIndex(lua_State*): MISMATCH; Non-padding instruction count: BE 37, object 39; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetPlotByIndex(lua_State* L)
{
	CvPlot* plot = GC.getMap().plotByIndex(lua_tointeger(L, 1));
	if(!plot) return 0;
	CvLuaPlot::Push(L, plot);
	return 1;
}

// TODO: Phase1 CvLuaMap::lGetPlotXY(lua_State*): MISMATCH; Non-padding instruction count: BE 174, object 85; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetPlotXY(lua_State* L)
{
	const bool offsetOnly = lua_gettop(L) == 2;
	const int x = offsetOnly ? 0 : lua_tointeger(L, 1);
	const int y = offsetOnly ? 0 : lua_tointeger(L, 2);
	const int dx = lua_tointeger(L, offsetOnly ? 1 : 3);
	const int dy = lua_tointeger(L, offsetOnly ? 2 : 4);
	CvLuaPlot::Push(L, OffsetPlot(x, y, dx, dy));
	return 1;
}

// TODO: Phase1 CvLuaMap::lGetArea(lua_State*): MISMATCH; Non-padding instruction count: BE 35, object 37; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetArea(lua_State* L)
{
	CvArea* area = GC.getMap().getArea(lua_tointeger(L, 1));
	if(!area) return 0;
	CvLuaArea::Push(L, area);
	return 1;
}

// TODO: Phase1 CvLuaMap::lIsPlot(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lIsPlot(lua_State* L)
{
	const int x = lua_tointeger(L, 1);
	const int y = lua_tointeger(L, 2);
	lua_pushboolean(L, GC.getMap().isPlot(x, y));
	return 1;
}

// TODO: Phase1 CvLuaMap::lIsWrapX(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lIsWrapX(lua_State* L)
{
	lua_pushboolean(L, GC.getMap().isWrapX());
	return 1;
}

// TODO: Phase1 CvLuaMap::lIsWrapY(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lIsWrapY(lua_State* L)
{
	lua_pushboolean(L, GC.getMap().isWrapY());
	return 1;
}

// TODO: Phase1 CvLuaMap::lRand(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lRand(lua_State* L)
{
	const int maximum = luaL_checkinteger(L, 1);
	const char* log = luaL_checkstring(L, 2);
	lua_pushinteger(L, GC.getGame().getMapRandNum(maximum, log));
	return 1;
}

// TODO: Phase1 CvLuaMap::lCalculateAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lCalculateAreas(lua_State*)
{
	GC.getMap().calculateAreas();
	return 0;
}

// TODO: Phase1 CvLuaMap::lRecalculateAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lRecalculateAreas(lua_State*)
{
	GC.getMap().recalculateAreas();
	return 0;
}

// TODO: Phase1 CvLuaMap::lPlotDistance(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lPlotDistance(lua_State* L)
{
	const int x1 = lua_tointeger(L, 1);
	const int y1 = lua_tointeger(L, 2);
	const int x2 = lua_tointeger(L, 3);
	const int y2 = lua_tointeger(L, 4);
	lua_pushinteger(L, plotDistance(x1, y1, x2, y2));
	return 1;
}

// TODO: Phase1 CvLuaMap::lPlotXYWithRangeCheck(lua_State*): MISMATCH; Non-padding instruction count: BE 176, object 101; Civ5 changed/new instruction count unverified.
int CvLuaMap::lPlotXYWithRangeCheck(lua_State* L)
{
	const int x = lua_tointeger(L, 1);
	const int y = lua_tointeger(L, 2);
	const int dx = lua_tointeger(L, 3);
	const int dy = lua_tointeger(L, 4);
	const int range = lua_tointeger(L, 5);
	const int distance = (dx >= 0) == (dy >= 0) ? abs(dx) + abs(dy) : std::max(abs(dx), abs(dy));
	CvLuaPlot::Push(L, distance <= range ? OffsetPlot(x, y, dx, dy) : NULL);
	return 1;
}

// TODO: Phase1 CvLuaMap::lPlotDirection(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lPlotDirection(lua_State* L)
{
	const int x = lua_tointeger(L, 1);
	const int y = lua_tointeger(L, 2);
	const DirectionTypes direction = static_cast<DirectionTypes>(lua_tointeger(L, 3));
	CvLuaPlot::Push(L, plotDirection(x, y, direction));
	return 1;
}

// TODO: Phase1 CvLuaMap::lDefaultContinentStamper(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lDefaultContinentStamper(lua_State*)
{
	GC.getMap().DefaultContinentStamper();
	return 0;
}

// TODO: Phase1 CvLuaMap::lGetCustomOption(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lGetCustomOption(lua_State* L)
{
	const char* name = luaL_checkstring(L, 1);
	int value = 0;
	if(!CvPreGame::GetMapOption(name, value)) return 0;
	lua_pushinteger(L, value);
	return 1;
}

// TODO: Phase1 CvLuaMap::lUpdateDeferredFog(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaMap::lUpdateDeferredFog(lua_State*)
{
	GC.getMap().updateDeferredFog();
	return 0;
}

// TODO: Phase1 CvLuaMap::lChangeAIMapHint(lua_State*): MISMATCH; Non-padding instruction count: BE 24, object 26; Civ5 changed/new instruction count unverified.
int CvLuaMap::lChangeAIMapHint(lua_State* L)
{
	GC.getMap().ChangeAIMapHint(lua_tointeger(L, 1));
	return 0;
}
