#include "CvGameCoreDLLPCH.h"
#include "CvArea.h"
#include "CvLuaSupport.h"
#include "CvLuaArea.h"
#include "CvLuaCity.h"

// Beyond Earth's Havok API registers named closures rather than Lua 5.1 closures.
#define Method(Name) \
	lua_pushcclosure(L, l##Name, 0); \
	lua_setfield(L, t, #Name)

void CvLuaArea::PushMethods(lua_State* L, int t)
{
	Method(IsNone);
	Method(CalculateTotalBestNatureYield);
	Method(CountCoastalLand);
	Method(CountNumUniqueResourceTypes);
	Method(GetID);
	Method(GetNumTiles);
	Method(GetNumOwnedTiles);
	Method(GetNumUnownedTiles);
	Method(GetNumRiverEdges);
	Method(GetNumCities);
	Method(GetNumUnits);
	Method(GetTotalPopulation);
	Method(GetNumStartingPlots);
	Method(IsWater);
	Method(GetUnitsPerPlayer);
	Method(GetCitiesPerPlayer);
	Method(GetPopulationPerPlayer);
	Method(GetFreeSpecialist);
	Method(GetNumRevealedTiles);
	Method(GetNumUnrevealedTiles);
	Method(GetTargetCity);
	Method(GetYieldRateModifier);
	Method(GetNumResources);
	Method(GetNumTotalResources);
	Method(GetNumImprovements);
}

#undef Method

const char* CvLuaArea::GetTypeName() { return "Area"; }
void CvLuaArea::HandleMissingInstance(lua_State* L) { DefaultHandleMissingInstance(L); }

int CvLuaArea::lIsNone(lua_State* L)
{
	lua_pushboolean(L, GetInstance(L, false) != NULL);
	return 1;
}


int CvLuaArea::lCalculateTotalBestNatureYield(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->calculateTotalBestNatureYield());
	return 1;
}

int CvLuaArea::lCountCoastalLand(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->countCoastalLand());
	return 1;
}

int CvLuaArea::lCountNumUniqueResourceTypes(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->countNumUniqueResourceTypes());
	return 1;
}

int CvLuaArea::lGetID(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->GetID());
	return 1;
}

int CvLuaArea::lGetNumTiles(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getNumTiles());
	return 1;
}

int CvLuaArea::lGetNumOwnedTiles(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getNumOwnedTiles());
	return 1;
}

int CvLuaArea::lGetNumUnownedTiles(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getNumUnownedTiles());
	return 1;
}

int CvLuaArea::lGetNumRiverEdges(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getNumRiverEdges());
	return 1;
}

int CvLuaArea::lGetNumCities(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getNumCities());
	return 1;
}

int CvLuaArea::lGetNumUnits(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getNumUnits());
	return 1;
}

int CvLuaArea::lGetTotalPopulation(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getTotalPopulation());
	return 1;
}

int CvLuaArea::lGetNumStartingPlots(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getNumStartingPlots());
	return 1;
}


int CvLuaArea::lIsWater(lua_State* L)
{
	lua_pushboolean(L, GetInstance(L)->isWater());
	return 1;
}


int CvLuaArea::lGetUnitsPerPlayer(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, pArea->getUnitsPerPlayer(ePlayer));
	return 1;
}

int CvLuaArea::lGetCitiesPerPlayer(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, pArea->getCitiesPerPlayer(ePlayer));
	return 1;
}

int CvLuaArea::lGetPopulationPerPlayer(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, pArea->getPopulationPerPlayer(ePlayer));
	return 1;
}

int CvLuaArea::lGetFreeSpecialist(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, pArea->getFreeSpecialist(ePlayer));
	return 1;
}



int CvLuaArea::lGetNumRevealedTiles(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const TeamTypes eTeam = static_cast<TeamTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, pArea->getNumRevealedTiles(eTeam));
	return 1;
}

int CvLuaArea::lGetNumUnrevealedTiles(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const TeamTypes eTeam = static_cast<TeamTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, pArea->getNumUnrevealedTiles(eTeam));
	return 1;
}


int CvLuaArea::lGetTargetCity(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(lua_tointeger(L, 2));
	CvLuaCity::Push(L, pArea->getTargetCity(ePlayer));
	return 1;
}

int CvLuaArea::lGetYieldRateModifier(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(lua_tointeger(L, 2));
	const YieldTypes eYield = static_cast<YieldTypes>(lua_tointeger(L, 3));
	lua_pushinteger(L, pArea->getYieldRateModifier(ePlayer, eYield));
	return 1;
}

int CvLuaArea::lGetNumResources(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const ResourceTypes eResource = static_cast<ResourceTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, pArea->getNumResources(eResource));
	return 1;
}

int CvLuaArea::lGetNumTotalResources(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	lua_pushinteger(L, pArea->getNumTotalResources());
	return 1;
}


int CvLuaArea::lGetNumImprovements(lua_State* L)
{
	CvArea* pArea = GetInstance(L);
	const ImprovementTypes eImprovement = static_cast<ImprovementTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, pArea->getNumImprovements(eImprovement));
	return 1;
}
