#include "CvGameCoreDLLPCH.h"
#include "Lua/CvLuaSupport.h"
#include "CvMapGenerator.h"
#include "CvGame.h"
#include "Lua/CvLuaPlot.h"
#include <cmath>

static void PushPlot(lua_State* L, CvPlot* pPlot)
{
	CvLuaScopedInstance<CvLuaPlot, CvPlot>::Push(L, pPlot);
}

static CvPlot* GetPlot(lua_State* L)
{
	return CvLuaScopedInstance<CvLuaPlot, CvPlot>::GetInstance(L, 1, false);
}

static bool IsCallable(lua_State* L, int iIndex)
{
	return lua_isfunction(L, iIndex);
}

struct GetMapInitDataArgs
{
	ICvEngineScriptSystem1* pkScriptSystem;
	CvMapInitData* pkMapInitData;
	int iWorldSize;
	bool bSuccess;
};

struct GetGameInitialItemsOverridesArgs
{
	ICvEngineScriptSystem1* pkScriptSystem;
	CvGameInitialItemsOverrides* pkOverrides;
	bool bSuccess;
};

CvMapGenerator::CvMapGenerator(const char* szMapScriptName)
	: m_pkLuaState(NULL)
{
	ICvEngineScriptSystem1* pkScriptSystem = gDLL->GetScriptSystem();
	m_pkLuaState = pkScriptSystem->CreateLuaThread("Map Script");
	RegisterLua();
	CvAssertMsg(pkScriptSystem->LoadFile(m_pkLuaState, szMapScriptName), "Cannot load mapscript.");
}

CvMapGenerator::~CvMapGenerator()
{
	gDLL->GetScriptSystem()->FreeLuaThread(m_pkLuaState);
}

void CvMapGenerator::RegisterLua()
{
	lua_createtable(m_pkLuaState, 0, 7);
	lua_pushcclosure(m_pkLuaState, lCalculateRegions, 0); lua_setfield(m_pkLuaState, -2, "lCalculateRegions");
	lua_pushcclosure(m_pkLuaState, lGetNumRegions, 0); lua_setfield(m_pkLuaState, -2, "lGetNumRegions");
	lua_pushcclosure(m_pkLuaState, lGetNumMatchingNeighborPlots, 0); lua_setfield(m_pkLuaState, -2, "lGetNumMatchingNeighborPlots");
	lua_pushcclosure(m_pkLuaState, lDoForEachNeighborPlot, 0); lua_setfield(m_pkLuaState, -2, "lDoForEachNeighborPlot");
	lua_pushcclosure(m_pkLuaState, lDoForEachRingPlot, 0); lua_setfield(m_pkLuaState, -2, "lDoForEachRingPlot");
	lua_pushcclosure(m_pkLuaState, lGetPlotLinearDistanceFromRegionCentroid, 0); lua_setfield(m_pkLuaState, -2, "lGetPlotLinearDistanceFromRegionCentroid");
	lua_pushcclosure(m_pkLuaState, lGetPlotHexDistanceFromRegionCentroid, 0); lua_setfield(m_pkLuaState, -2, "lGetPlotHexDistanceFromRegionCentroid");
	lua_setglobal(m_pkLuaState, "MapGenerator");
}

bool CvMapGenerator::GetMapInitData(CvMapInitData& kData, WorldSizeTypes eWorldSize)
{
	GetMapInitDataArgs kArgs = { gDLL->GetScriptSystem(), &kData, eWorldSize, false };
	kArgs.pkScriptSystem->CallCFunction(m_pkLuaState, pGetMapInitData, &kArgs);
	return kArgs.bSuccess;
}

void CvMapGenerator::GenerateRandomMap()
{
	ICvEngineScriptSystem1* pkScriptSystem = gDLL->GetScriptSystem();
	pkScriptSystem->CallCFunction(m_pkLuaState, pGenerateRandomMap, pkScriptSystem);
	lua_gc(m_pkLuaState, LUA_GCCOLLECT, 0);
}

bool CvMapGenerator::GetGameInitialItemsOverrides(CvGameInitialItemsOverrides& kOverrides)
{
	GetGameInitialItemsOverridesArgs kArgs = { gDLL->GetScriptSystem(), &kOverrides, false };
	kArgs.pkScriptSystem->CallCFunction(m_pkLuaState, pGetGameInitialItemsOverrides, &kArgs);
	return kArgs.bSuccess;
}

int CvMapGenerator::pGetMapInitData(lua_State* L)
{
	GetMapInitDataArgs* pArgs = static_cast<GetMapInitDataArgs*>(lua_touserdata(L, 1));
	pArgs->bSuccess = false;
	lua_getglobal(L, "GetMapInitData");
	if(!lua_isfunction(L, -1))
		return 0;

	lua_pushinteger(L, pArgs->iWorldSize);
	pArgs->pkScriptSystem->CallFunction(L, 1, 1);
	if(!lua_istable(L, -1))
		return 0;

	const int iTable = lua_gettop(L);
	lua_getfield(L, iTable, "Width");
	if(!lua_isnoneornil(L, -1)) pArgs->pkMapInitData->m_iGridW = lua_tointeger(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, iTable, "Height");
	if(!lua_isnoneornil(L, -1)) pArgs->pkMapInitData->m_iGridH = lua_tointeger(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, iTable, "WrapX");
	if(!lua_isnoneornil(L, -1)) pArgs->pkMapInitData->m_bWrapX = lua_toboolean(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, iTable, "WrapY");
	if(!lua_isnoneornil(L, -1)) pArgs->pkMapInitData->m_bWrapY = lua_toboolean(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, iTable, "TopLatitude");
	if(!lua_isnoneornil(L, -1)) pArgs->pkMapInitData->m_iTopLatitude = lua_tointeger(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, iTable, "BottomLatitude");
	if(!lua_isnoneornil(L, -1)) pArgs->pkMapInitData->m_iBottomLatitude = lua_tointeger(L, -1);
	lua_pop(L, 1);
	pArgs->bSuccess = true;
	return 0;
}

int CvMapGenerator::pGenerateRandomMap(lua_State* L)
{
	ICvEngineScriptSystem1* pkScriptSystem = static_cast<ICvEngineScriptSystem1*>(lua_touserdata(L, 1));
	lua_getglobal(L, "GenerateMap");
	if(lua_isnil(L, -1))
		luaL_error(L, "Cannot find map script entry point GenerateMap()");
	pkScriptSystem->CallFunction(L, 0, 0);
	return 0;
}

static void ReadOverrideTable(lua_State* L, int iTable, const char* szName, bool* pOverrides, int iCount)
{
	lua_getfield(L, iTable, szName);
	if(lua_istable(L, -1))
	{
		lua_pushnil(L);
		while(lua_next(L, -2) != 0)
		{
			if(lua_isnumber(L, -2) && lua_isboolean(L, -1))
			{
				const int iIndex = lua_tointeger(L, -2);
				if(iIndex >= 0 && iIndex < iCount)
					pOverrides[iIndex] = lua_toboolean(L, -1);
			}
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
}

int CvMapGenerator::pGetGameInitialItemsOverrides(lua_State* L)
{
	GetGameInitialItemsOverridesArgs* pArgs = static_cast<GetGameInitialItemsOverridesArgs*>(lua_touserdata(L, 1));
	pArgs->bSuccess = false;
	lua_getglobal(L, "GetGameInitialItemsOverrides");
	if(!lua_isfunction(L, -1))
		return 0;
	pArgs->pkScriptSystem->CallFunction(L, 0, 1);
	if(!lua_istable(L, -1))
		return 0;

	const int iTable = lua_gettop(L);
	ReadOverrideTable(L, iTable, "GrantInitialFreeTechsPerTeam", pArgs->pkOverrides->GrantInitialFreeTechsPerTeam, REALLY_MAX_TEAMS);
	ReadOverrideTable(L, iTable, "GrantInitialGoldPerPlayer", pArgs->pkOverrides->GrantInitialGoldPerPlayer, MAX_MAJOR_CIVS);
	ReadOverrideTable(L, iTable, "GrantInitialCulturePerPlayer", pArgs->pkOverrides->GrantInitialCulturePerPlayer, MAX_MAJOR_CIVS);
	ReadOverrideTable(L, iTable, "ClearResearchQueuePerPlayer", pArgs->pkOverrides->ClearResearchQueuePerPlayer, MAX_MAJOR_CIVS);
	ReadOverrideTable(L, iTable, "GrantInitialUnitsPerPlayer", pArgs->pkOverrides->GrantInitialUnitsPerPlayer, MAX_MAJOR_CIVS);
	pArgs->bSuccess = true;
	return 0;
}

int CvMapGenerator::lCalculateRegions(lua_State* L)
{
	if(!lua_istable(L, 1))
		return 0;

	std::vector<CvMapRegionData> vRegions;
	lua_pushnil(L);
	while(lua_next(L, 1) != 0)
	{
		if(lua_isnumber(L, -1))
			vRegions.push_back(CvMapRegionData(static_cast<MapRegionTypes>(lua_tointeger(L, -1)), vRegions.size()));
		lua_pop(L, 1);
	}
	GC.getMap().CalculateRegionLayout(static_cast<float>(lua_tonumber(L, 2)), static_cast<float>(lua_tonumber(L, 3)), std::move(vRegions));
	return 0;
}

int CvMapGenerator::lGetNumRegions(lua_State* L)
{
	lua_pushinteger(L, GC.getMap().GetMapRegionLayout().GetNumRegions());
	return 1;
}

static int DoForEachNeighborPlot(lua_State* L, bool bRingOnly, bool bCountMatches)
{
	CvPlot* pOrigin = GetPlot(L);
	const int iRadius = static_cast<int>(lua_tointeger(L, 2));
	if(!pOrigin || iRadius < 0 || !IsCallable(L, 3))
	{
		if(bCountMatches) lua_pushinteger(L, 0);
		return bCountMatches ? 1 : 0;
	}

	int iMatches = 0;
	for(int iY = pOrigin->getY() - iRadius; iY <= pOrigin->getY() + iRadius; ++iY)
	{
		for(int iX = pOrigin->getX() - iRadius; iX <= pOrigin->getX() + iRadius; ++iX)
		{
			CvPlot* pPlot = GC.getMap().plot(iX, iY);
			if(!pPlot || pPlot == pOrigin)
				continue;
			const int iDistance = plotDistance(pOrigin, pPlot);
			if(iDistance > iRadius || (bRingOnly && iDistance != iRadius))
				continue;
			lua_pushvalue(L, 3);
			PushPlot(L, pPlot);
			lua_call(L, 1, bCountMatches ? 1 : 0);
			if(bCountMatches)
			{
				if(lua_toboolean(L, -1)) ++iMatches;
				lua_pop(L, 1);
			}
		}
	}
	if(bCountMatches) lua_pushinteger(L, iMatches);
	return bCountMatches ? 1 : 0;
}

int CvMapGenerator::lGetNumMatchingNeighborPlots(lua_State* L) { return DoForEachNeighborPlot(L, false, true); }
int CvMapGenerator::lDoForEachNeighborPlot(lua_State* L) { return DoForEachNeighborPlot(L, false, false); }
int CvMapGenerator::lDoForEachRingPlot(lua_State* L) { return DoForEachNeighborPlot(L, true, false); }

int CvMapGenerator::lGetPlotLinearDistanceFromRegionCentroid(lua_State* L)
{
	CvPlot* pPlot = GetPlot(L);
	const CvMapRegionData* pRegion = pPlot ? GC.getMap().GetMapRegionLayout().GetRegionByIndex(pPlot->GetMapRegionIndex()) : NULL;
	if(!pRegion)
	{
		lua_pushnumber(L, -1.0);
		return 1;
	}
	const float fDX = static_cast<float>(pPlot->getX()) - pRegion->m_fCentroidX;
	const float fDY = static_cast<float>(pPlot->getY()) - pRegion->m_fCentroidY;
	lua_pushnumber(L, sqrtf(fDX * fDX + fDY * fDY));
	return 1;
}

int CvMapGenerator::lGetPlotHexDistanceFromRegionCentroid(lua_State* L)
{
	CvPlot* pPlot = GetPlot(L);
	const CvMapRegionData* pRegion = pPlot ? GC.getMap().GetMapRegionLayout().GetRegionByIndex(pPlot->GetMapRegionIndex()) : NULL;
	if(!pRegion)
	{
		lua_pushinteger(L, -1);
		return 1;
	}
	lua_pushinteger(L, plotDistance(pPlot->getX(), pPlot->getY(), static_cast<int>(pRegion->m_fCentroidX), static_cast<int>(pRegion->m_fCentroidY)));
	return 1;
}
