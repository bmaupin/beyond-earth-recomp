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

const char* CvLuaMap::GetInstanceName()
{
	return "Map";
}

CvMap* CvLuaMap::GetInstance(lua_State*, int)
{
	return &GC.getMap();
}

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

int CvLuaMap::lAreas(lua_State* L)
{
	lua_pushcclosure(L, CvLuaMap::lAreasAux, 0);
	return 1;
}

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

int CvLuaMap::lFindBiggestArea(lua_State* L)
{
	CvArea* area = GC.getMap().findBiggestArea(lua_toboolean(L, 1));
	if(!area) return 0;
	CvLuaArea::Push(L, area);
	return 1;
}

int CvLuaMap::lFindWater(lua_State* L)
{
	CvPlot* plot = CvLuaPlot::GetInstance(L, 1);
	const int range = luaL_checkinteger(L, 2);
	const bool freshWater = lua_toboolean(L, 3);
	lua_pushboolean(L, GC.getMap().findWater(plot, range, freshWater));
	return 1;
}

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

MapInteger(GetClimate, GC.getMap().getClimate())
MapInteger(GetNumPlots, GC.getMap().numPlots())
MapInteger(GetIndexAfterLastArea, GC.getMap().getIndexAfterLastArea())
MapInteger(GetLandPlots, GC.getMap().getLandPlots())
MapInteger(GetWaterPlots, GC.getMap().getWaterPlots())
MapInteger(GetLakePlots, GC.getMap().getLakePlots())
MapInteger(GetNumAreas, GC.getMap().getNumAreas())
MapInteger(GetNumLandAreas, GC.getMap().getNumLandAreas())
MapInteger(GetSeaLevel, GC.getMap().getSeaLevel())
MapInteger(GetWorldSize, GC.getMap().getWorldSize())
MapInteger(MaxPlotDistance, GC.getMap().maxPlotDistance())
MapInteger(GetMapSeed, static_cast<int>(CvPreGame::mapRandomSeed()))
MapInteger(GetAIMapHint, GC.getMap().GetAIMapHint())

#undef MapInteger

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

int CvLuaMap::lGetGridSize(lua_State* L)
{
	lua_pushinteger(L, GC.getMap().getGridWidth());
	lua_pushinteger(L, GC.getMap().getGridHeight());
	return 2;
}

int CvLuaMap::lGetNumResources(lua_State* L)
{
	const ResourceTypes resource = static_cast<ResourceTypes>(luaL_checkinteger(L, 1));
	lua_pushinteger(L, GC.getMap().getNumResources(resource));
	return 1;
}

int CvLuaMap::lGetNumResourcesOnLand(lua_State* L)
{
	const ResourceTypes resource = static_cast<ResourceTypes>(luaL_checkinteger(L, 1));
	lua_pushinteger(L, GC.getMap().getNumResourcesOnLand(resource));
	return 1;
}

int CvLuaMap::lGetRandomResourceQuantity(lua_State* L)
{
	const ResourceTypes resource = static_cast<ResourceTypes>(luaL_checkinteger(L, 1));
	lua_pushinteger(L, GC.getMap().getRandomResourceQuantity(resource));
	return 1;
}

int CvLuaMap::lGetPlot(lua_State* L)
{
	const int x = lua_tointeger(L, 1);
	const int y = lua_tointeger(L, 2);
	CvPlot* plot = GC.getMap().plot(x, y);
	if(!plot) return 0;
	CvLuaPlot::Push(L, plot);
	return 1;
}

int CvLuaMap::lGetPlotByIndex(lua_State* L)
{
	CvPlot* plot = GC.getMap().plotByIndex(lua_tointeger(L, 1));
	if(!plot) return 0;
	CvLuaPlot::Push(L, plot);
	return 1;
}

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

int CvLuaMap::lGetArea(lua_State* L)
{
	CvArea* area = GC.getMap().getArea(lua_tointeger(L, 1));
	if(!area) return 0;
	CvLuaArea::Push(L, area);
	return 1;
}

int CvLuaMap::lIsPlot(lua_State* L)
{
	const int x = lua_tointeger(L, 1);
	const int y = lua_tointeger(L, 2);
	lua_pushboolean(L, GC.getMap().isPlot(x, y));
	return 1;
}

int CvLuaMap::lIsWrapX(lua_State* L)
{
	lua_pushboolean(L, GC.getMap().isWrapX());
	return 1;
}

int CvLuaMap::lIsWrapY(lua_State* L)
{
	lua_pushboolean(L, GC.getMap().isWrapY());
	return 1;
}

int CvLuaMap::lRand(lua_State* L)
{
	const int maximum = luaL_checkinteger(L, 1);
	const char* log = luaL_checkstring(L, 2);
	lua_pushinteger(L, GC.getGame().getMapRandNum(maximum, log));
	return 1;
}

int CvLuaMap::lCalculateAreas(lua_State*)
{
	GC.getMap().calculateAreas();
	return 0;
}

int CvLuaMap::lRecalculateAreas(lua_State*)
{
	GC.getMap().recalculateAreas();
	return 0;
}

int CvLuaMap::lPlotDistance(lua_State* L)
{
	const int x1 = lua_tointeger(L, 1);
	const int y1 = lua_tointeger(L, 2);
	const int x2 = lua_tointeger(L, 3);
	const int y2 = lua_tointeger(L, 4);
	lua_pushinteger(L, plotDistance(x1, y1, x2, y2));
	return 1;
}

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

int CvLuaMap::lPlotDirection(lua_State* L)
{
	const int x = lua_tointeger(L, 1);
	const int y = lua_tointeger(L, 2);
	const DirectionTypes direction = static_cast<DirectionTypes>(lua_tointeger(L, 3));
	CvLuaPlot::Push(L, plotDirection(x, y, direction));
	return 1;
}

int CvLuaMap::lDefaultContinentStamper(lua_State*)
{
	GC.getMap().DefaultContinentStamper();
	return 0;
}

int CvLuaMap::lGetCustomOption(lua_State* L)
{
	const char* name = luaL_checkstring(L, 1);
	int value = 0;
	if(!CvPreGame::GetMapOption(name, value)) return 0;
	lua_pushinteger(L, value);
	return 1;
}

int CvLuaMap::lUpdateDeferredFog(lua_State*)
{
	GC.getMap().updateDeferredFog();
	return 0;
}

int CvLuaMap::lChangeAIMapHint(lua_State* L)
{
	GC.getMap().ChangeAIMapHint(lua_tointeger(L, 1));
	return 0;
}
