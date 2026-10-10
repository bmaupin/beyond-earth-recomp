#include "CvGameCoreDLLPCH.h"
#include "CvArea.h"
#include "CvLuaSupport.h"
#include "CvLuaArea.h"
#include "CvLuaCity.h"

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

void CvLuaArea::HandleMissingInstance(lua_State* L) { DefaultHandleMissingInstance(L); }
const char* CvLuaArea::GetTypeName() { return "Area"; }

int CvLuaArea::lIsNone(lua_State* L)
{
	lua_pushboolean(L, GetInstance(L, false) != NULL);
	return 1;
}

#define AreaIntegerMethod(Name, Expression) \
	int CvLuaArea::l##Name(lua_State* L) { \
		CvArea* pArea = GetInstance(L); \
		lua_pushinteger(L, (Expression)); \
		return 1; \
	}

AreaIntegerMethod(CalculateTotalBestNatureYield, pArea->calculateTotalBestNatureYield())
AreaIntegerMethod(CountCoastalLand, pArea->countCoastalLand())
AreaIntegerMethod(CountNumUniqueResourceTypes, pArea->countNumUniqueResourceTypes())
AreaIntegerMethod(GetID, pArea->GetID())
AreaIntegerMethod(GetNumTiles, pArea->getNumTiles())
AreaIntegerMethod(GetNumOwnedTiles, pArea->getNumOwnedTiles())
AreaIntegerMethod(GetNumUnownedTiles, pArea->getNumUnownedTiles())
AreaIntegerMethod(GetNumRiverEdges, pArea->getNumRiverEdges())
AreaIntegerMethod(GetNumCities, pArea->getNumCities())
AreaIntegerMethod(GetNumUnits, pArea->getNumUnits())
AreaIntegerMethod(GetTotalPopulation, pArea->getTotalPopulation())
AreaIntegerMethod(GetNumStartingPlots, pArea->getNumStartingPlots())

int CvLuaArea::lIsWater(lua_State* L)
{
	lua_pushboolean(L, GetInstance(L)->isWater());
	return 1;
}

#define AreaPlayerMethod(Name, Expression) \
	int CvLuaArea::l##Name(lua_State* L) { \
		CvArea* pArea = GetInstance(L); \
		const PlayerTypes ePlayer = static_cast<PlayerTypes>(lua_tointeger(L, 2)); \
		lua_pushinteger(L, (Expression)); \
		return 1; \
	}

AreaPlayerMethod(GetUnitsPerPlayer, pArea->getUnitsPerPlayer(ePlayer))
AreaPlayerMethod(GetCitiesPerPlayer, pArea->getCitiesPerPlayer(ePlayer))
AreaPlayerMethod(GetPopulationPerPlayer, pArea->getPopulationPerPlayer(ePlayer))
AreaPlayerMethod(GetFreeSpecialist, pArea->getFreeSpecialist(ePlayer))

#define AreaTeamMethod(Name, Expression) \
	int CvLuaArea::l##Name(lua_State* L) { \
		CvArea* pArea = GetInstance(L); \
		const TeamTypes eTeam = static_cast<TeamTypes>(lua_tointeger(L, 2)); \
		lua_pushinteger(L, (Expression)); \
		return 1; \
	}

AreaTeamMethod(GetNumRevealedTiles, pArea->getNumRevealedTiles(eTeam))
AreaTeamMethod(GetNumUnrevealedTiles, pArea->getNumUnrevealedTiles(eTeam))

int CvLuaArea::lGetTargetCity(lua_State* L)
{
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(lua_tointeger(L, 2));
	CvLuaCity::Push(L, GetInstance(L)->getTargetCity(ePlayer));
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
	const ResourceTypes eResource = static_cast<ResourceTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, GetInstance(L)->getNumResources(eResource));
	return 1;
}

AreaIntegerMethod(GetNumTotalResources, pArea->getNumTotalResources())

int CvLuaArea::lGetNumImprovements(lua_State* L)
{
	const ImprovementTypes eImprovement = static_cast<ImprovementTypes>(lua_tointeger(L, 2));
	lua_pushinteger(L, GetInstance(L)->getNumImprovements(eImprovement));
	return 1;
}
