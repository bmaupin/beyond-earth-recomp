#include "CvGameCoreDLLPCH.h"
#include "CvLuaSupport.h"
#include "CvLuaArea.h"
#include "CvLuaCity.h"
#include "CvLuaPlot.h"
#include "CvLuaUnit.h"
#include "CvLuaOutpost.h"
#include "CvLuaStation.h"
#include "CvLuaStrategicSite.h"
#include "CvUnit.h"
#include "CvCityStrategicSite.h"

const char* hks_obj_tolstring(lua_State* L, HksObject* object, unsigned int* length);

#define Method(Name) \
	lua_pushcclosure(L, l##Name, 0); \
	lua_setfield(L, t, #Name)

void CvLuaPlot::PushMethods(lua_State* L, int t)
{
	Method(CanHaveFeature);
	Method(GetFeatureType);
	Method(GetTerrainType);
	Method(IsRiver);
	Method(IsWater);
	Method(IsTrench);
	Method(SetFeatureType);
	Method(SetTerrainType);
	Method(GetMapRegionType);
	Method(GetMapRegionIndex);
	Method(CanHaveMiasma);
	Method(HasMiasma);
	Method(SetMiasma);
	Method(HasBubbles);
	Method(SetBubbles);
	Method(CanHaveAnchorage);
	Method(HasAnchorage);
	Method(SetAnchorage);
	Method(IsNone);
	Method(Erase);
	Method(GetTeam);
	Method(NukeExplosion);
	Method(GetInlandCorner);
	Method(UpdateFog);
	Method(UpdateVisibility);
	Method(IsAdjacentToArea);
	Method(ShareAdjacentArea);
	Method(IsAdjacentToLand);
	Method(IsAdjacentToShallowWater);
	Method(IsCoastalLand);
	Method(IsAllowsWalkWater);
	Method(IsWithinTeamCityRadius);
	Method(IsLake);
	Method(IsFreshWater);
	Method(IsRiverSide);
	Method(IsRiverConnection);
	Method(IsRiverCrossingFlowClockwise);
	Method(GetNearestLandArea);
	Method(SeeFromLevel);
	Method(GetNearestLandPlot);
	Method(SeeThroughLevel);
	Method(CanHaveResource);
	Method(CanHaveImprovement);
	Method(CanBuild);
	Method(GetBuildTime);
	Method(GetBuildTurnsLeft);
	Method(GetBuildTurnsTotal);
	Method(GetFeatureProduction);
	Method(GetPlotMaintenance);
	Method(GetBestDefender);
	Method(GetSelectedUnit);
	Method(GetUnitPower);
	Method(DefenseModifier);
	Method(MovementCost);
	Method(GetExtraMovePathCost);
	Method(ChangeExtraMovePathCost);
	Method(IsAdjacentOwned);
	Method(IsAdjacentPlayer);
	Method(IsAdjacentTeam);
	Method(IsOwned);
	Method(IsAlien);
	Method(HasAlienNest);
	Method(IsVisible);
	Method(IsActiveVisible);
	Method(IsVisibleToWatchingHuman);
	Method(IsAdjacentVisible);
	Method(IsAdjacentNonvisible);
	Method(IsAdjacentRevealed);
	Method(IsAdjacentNonrevealed);
	Method(RemoveGoody);
	Method(IsGoody);
	Method(IsRevealedGoody);
	Method(IsFriendlyTerritory);
	Method(IsNeutralTerritory);
	Method(IsEnemyTerritory);
	Method(IsCity);
	Method(IsFriendlyCity);
	Method(IsEnemyCity);
	Method(IsBeingWorked);
	Method(IsUnit);
	Method(IsImmobileUnit);
	Method(IsUnlaunchedOrbitalUnit);
	Method(IsEnemyUnit);
	Method(IsVisibleEnemyDefender);
	Method(GetNumDefenders);
	Method(GetNumVisibleEnemyDefenders);
	Method(GetNumVisiblePotentialEnemyDefenders);
	Method(IsVisibleEnemyUnit);
	Method(IsVisibleOtherUnit);
	Method(GetNumFriendlyUnitsOfType);
	Method(IsFighting);
	Method(IsUnitBlockingCityWork);
	Method(IsRoute);
	Method(IsTradeRoute);
	Method(IsValidDomainForLocation);
	Method(IsValidDomainForAction);
	Method(IsImpassable);
	Method(GetX);
	Method(GetY);
	Method(At);
	Method(GetPlotIndex);
	Method(GetLatitude);
	Method(Area);
	Method(WaterArea);
	Method(GetArea);
	Method(SetArea);
	Method(GetWildness);
	Method(SetWildness);
	Method(ChangeWildness);
	Method(GetFeatureVariety);
	Method(GetOwnershipDuration);
	Method(IsOwnershipScore);
	Method(SetOwnershipDuration);
	Method(ChangeOwnershipDuration);
	Method(GetImprovementDuration);
	Method(SetImprovementDuration);
	Method(ChangeImprovementDuration);
	Method(GetUpgradeProgress);
	Method(GetUpgradeTimeLeft);
	Method(SetUpgradeProgress);
	Method(ChangeUpgradeProgress);
	Method(GetCityRadiusCount);
	Method(IsCityRadius);
	Method(IsStartingPlot);
	Method(SetStartingPlot);
	Method(IsNEOfRiver);
	Method(SetNEOfRiver);
	Method(IsWOfRiver);
	Method(SetWOfRiver);
	Method(IsNWOfRiver);
	Method(SetNWOfRiver);
	Method(GetRiverEFlowDirection);
	Method(GetRiverSEFlowDirection);
	Method(GetRiverSWFlowDirection);
	Method(GetOwner);
	Method(SetOwner);
	Method(GetPlotType);
	Method(GetSiteName);
	Method(GetLogString);
	Method(IsFlatlands);
	Method(IsHills);
	Method(IsOpenGround);
	Method(IsRoughGround);
	Method(IsMountain);
	Method(IsCanyon);
	Method(SetPlotType);
	Method(HasResource);
	Method(GetResourceType);
	Method(GetNonObsoleteResourceType);
	Method(SetResourceType);
	Method(SetLayerResourceType);
	Method(GetNumResource);
	Method(SetNumResource);
	Method(ChangeNumResource);
	Method(SetPrimaryResourceType);
	Method(GetPrimaryResourceType);
	Method(SetSecondaryResourceType);
	Method(GetSecondaryResourceType);
	Method(HasImprovement);
	Method(GetImprovementType);
	Method(SetImprovementType);
	Method(ClearImprovementType);
	Method(SetImprovementPillaged);
	Method(SetPrimaryImprovementType);
	Method(GetPrimaryImprovementType);
	Method(SetSecondaryImprovementType);
	Method(GetSecondaryImprovementType);
	Method(GetRouteType);
	Method(SetRouteType);
	Method(IsRoutePillaged);
	Method(GetPlotCity);
	Method(GetWorkingCity);
	Method(GetWorkingCityOverride);
	Method(GetReconCount);
	Method(GetRiverCrossingCount);
	Method(GetYield);
	Method(CalculateNatureYield);
	Method(CalculateBestNatureYield);
	Method(CalculateTotalBestNatureYield);
	Method(CalculateImprovementYieldChange);
	Method(CalculateYield);
	Method(HasYield);
	Method(GetYieldWithBuild);
	Method(GetHealth);
	Method(GetUnhealth);
	Method(CountNumAirUnits);
	Method(GetFoundValue);
	Method(IsBestAdjacentFound);
	Method(GetPlayerCityRadiusCount);
	Method(IsPlayerCityRadius);
	Method(GetVisibilityCount);
	Method(ChangeVisibilityCount);
	Method(GetRevealedOwner);
	Method(GetRevealedTeam);
	Method(IsRiverCrossing);
	Method(IsRiverCrossingToPlot);
	Method(IsRevealed);
	Method(SetRevealed);
	Method(GetRevealedImprovementType);
	Method(SetRevealedImprovementType);
	Method(GetRevealedRouteType);
	Method(GetBuildProgress);
	Method(ChangeBuildProgress);
	Method(GetInvisibleVisibilityCount);
	Method(ChangeInvisibleVisibilityCount);
	Method(IsInvisibleVisibleToTeam);
	Method(IsInvisibleVisibleToAnyEnemyTeam);
	Method(GetNumUnits);
	Method(GetUnit);
	Method(GetNumLayerUnits);
	Method(GetLayerUnit);
	Method(GetScriptData);
	Method(SetScriptData);
	Method(GetActiveFogOfWarMode);
	Method(IsImprovementPillaged);
	Method(CanSeePlot);
	Method(GetContinentArtType);
	Method(SetContinentArtType);
	Method(IsResourceConnectedByImprovement);
	Method(IsBuildRemovesFeature);
	Method(GetArchaeologyArtifactType);
	Method(GetArchaeologyArtifactEra);
	Method(GetArchaeologyArtifactPlayer1);
	Method(GetArchaeologyArtifactPlayer2);
	Method(GetArchaeologyArtifactWork);
	Method(HasWrittenArtifact);
	Method(GetCityPurchaseID);
	Method(SetCityPurchaseID);
	Method(IsOutpost);
	Method(IsFriendlyOutpost);
	Method(IsEnemyOutpost);
	Method(GetPlotOutpost);
	Method(IsStation);
	Method(GetPlotStation);
	Method(IsStrategicSite);
	Method(IsEnemyStrategicSite);
	Method(GetPlotStrategicSite);
	Method(GetPlotStrategicSiteData);
	Method(GetTradeSiteOwnerID);
	Method(IsOrbitalUnit);
	Method(IsEnemyOrbitalUnit);
	Method(GetOrbitalUnit);
	Method(HasInfluencingOrbitalUnit);
	Method(GetInfluencingOrbitalUnitsText);
	Method(GetCityIntrigueModFromOrbitalUnits);
	Method(IsCityCovertOpsPreventedByOrbitalUnits);
	Method(GetOrbitalUnitAbovePlot);
	Method(GetOrbitalUnitInfluencingPlot);
	Method(GetLandmarkActionPerformed);
	Method(SetLandmarkActionPerformed);
	Method(GetHeroLandmark);
}

void CvLuaPlot::HandleMissingInstance(lua_State* L) { DefaultHandleMissingInstance(L); }
const char* CvLuaPlot::GetTypeName() { return "Plot"; }

int CvLuaPlot::lCanHaveFeature(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);

	const int featureType = lua_tointeger(L, 2);
	const bool canHasFeature = pkPlot->canHaveFeature((FeatureTypes)featureType);

	lua_pushboolean(L, canHasFeature);

	return 1;
}
int CvLuaPlot::lGetFeatureType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);

	const int featureType = (int)pkPlot->getFeatureType();
	lua_pushinteger(L, featureType);

	return 1;
}
int CvLuaPlot::lGetTerrainType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);

	lua_pushinteger(L, pkPlot->getTerrainType());

	return 1;
}
int CvLuaPlot::lIsRiver(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);

	lua_pushboolean(L, pkPlot->isRiver());

	return 1;
}
int CvLuaPlot::lIsWater(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);

	lua_pushboolean(L, pkPlot->isWater());

	return 1;
}
int CvLuaPlot::lSetFeatureType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);

	const int featureType = lua_tointeger(L, 2);
	const int variety = luaL_optinteger(L, 3, -1);


	pkPlot->setFeatureType((FeatureTypes)featureType, variety);

	return 0;
}
int CvLuaPlot::lSetTerrainType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);

	const int terrainType = lua_tointeger(L, 2);
	const bool bRecalculate = lua_toboolean(L, 3);
	const bool bRebuildGraphics = lua_toboolean(L, 4);

	pkPlot->setTerrainType((TerrainTypes)terrainType, bRecalculate, bRebuildGraphics);

	return 0;
}
int CvLuaPlot::lIsNone(lua_State* L)
{
	const bool bDoesNotExist = (GetInstance(L, false) == NULL);
	lua_pushboolean(L, bDoesNotExist);

	return 1;
}
int CvLuaPlot::lUpdateVisibility(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)()>(&CvPlot::updateVisibility));
}
int CvLuaPlot::lIsAdjacentToArea(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvArea* pkArea = CvLuaArea::GetInstance(L, 2);

	const bool bResult = pkPlot->isAdjacentToArea(pkArea);
	lua_pushboolean(L, bResult);

	return 1;
}
int CvLuaPlot::lShareAdjacentArea(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvPlot* pkPlot2 = GetInstance(L, 2);

	const bool bResult = pkPlot->shareAdjacentArea(pkPlot2);
	lua_pushboolean(L, bResult);

	return 1;
}
int CvLuaPlot::lIsRiverCrossingFlowClockwise(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const DirectionTypes eDirection = (DirectionTypes)lua_tointeger(L, 2);
	const bool bResult = pkPlot->isRiverCrossingFlowClockwise(eDirection);
	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lGetNearestLandPlot(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvPlot* pkNearestPlot = pkPlot->getNearestLandPlot();
	CvLuaPlot::Push(L, pkNearestPlot);
	return 1;
}
int CvLuaPlot::lGetFeatureProduction(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const BuildTypes eBuild = (BuildTypes)lua_tointeger(L, 2);
	const PlayerTypes ePlayer = (PlayerTypes)lua_tointeger(L, 3);
	CvCity* pCity;

	const int iResult = pkPlot->getFeatureProduction(eBuild, ePlayer, &pCity);

	lua_pushinteger(L, iResult);
	return 1;
}
int CvLuaPlot::lGetBestDefender(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const PlayerTypes eOwner = (PlayerTypes)lua_tointeger(L, 2);
	const PlayerTypes eAttackingPlayer = (PlayerTypes)lua_tointeger(L, 3);
	CvUnit* pkAttacker = CvLuaUnit::GetInstance(L, 4, false);
	const bool bTestAtWar = luaL_optbool(L, 5, false);
	const bool bTestPotentialEnemy = luaL_optbool(L, 6, false);
	const bool bTestCanMove = luaL_optbool(L, 7, false);
	UnitHandle pkUnit = pkPlot->getBestDefender(eOwner, eAttackingPlayer, pkAttacker, bTestAtWar, bTestPotentialEnemy, bTestCanMove, false);
	CvLuaUnit::Push(L, pkUnit.pointer());
	return 1;
}
int CvLuaPlot::lGetSelectedUnit(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = pkPlot->getSelectedUnit();
	CvLuaUnit::Push(L, pkUnit);
	return 1;
}
int CvLuaPlot::lIsVisible(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const bool bDebug = luaL_optbool(L, 3, false);

	lua_pushboolean(L, pkPlot->isVisible(eTeam, bDebug));
	return 1;
}
int CvLuaPlot::lIsActiveVisible(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const bool bDebug = luaL_optbool(L, 2, false);

	if (!bDebug)
		lua_pushboolean(L, pkPlot->isActiveVisible());
	else
		lua_pushboolean(L, pkPlot->isActiveVisible(true));

	return 1;
}
int CvLuaPlot::lIsAdjacentVisible(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const bool bDebug = luaL_optbool(L, 3, false);

	if (!bDebug)
		lua_pushboolean(L, pkPlot->isAdjacentVisible(eTeam));
	else
		lua_pushboolean(L, pkPlot->isAdjacentVisible(eTeam, true));

	return 1;
}
int CvLuaPlot::lRemoveGoody(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)()>(&CvPlot::removeGoody));
}
int CvLuaPlot::lIsFriendlyTerritory(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const PlayerTypes ePlayer = (PlayerTypes) lua_tointeger(L, 2);

	const bool bResult = pkPlot->IsFriendlyTerritory(ePlayer);
	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lIsFriendlyCity(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);
	const bool bCheckImprovement = lua_toboolean(L, 3);

	const bool bResult = pkPlot->isFriendlyCity(*pkUnit, bCheckImprovement);
	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lIsEnemyCity(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);
	const bool bResult = pkPlot->isEnemyCity(*pkUnit);
	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lIsVisibleEnemyDefender(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);
	const bool bResult = pkPlot->isVisibleEnemyDefender(pkUnit);
	lua_pushboolean(L, bResult);

	return 1;
}
int CvLuaPlot::lIsVisibleEnemyUnit(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const PlayerTypes ePlayer = (PlayerTypes)lua_tointeger(L, 2);
	const bool bResult = pkPlot->isVisibleEnemyUnit(ePlayer);
	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lGetNumFriendlyUnitsOfType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);

	bool bBreakOnUnitLimit = luaL_optbool(L, 3, true);
	int iResult = pkPlot->getNumFriendlyUnitsOfType(pkUnit, bBreakOnUnitLimit, false);

	lua_pushinteger(L, iResult);
	return 1;
}
int CvLuaPlot::lIsTradeRoute(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	PlayerTypes ePlayer = (PlayerTypes)luaL_optint(L, 2, -1);
	bool bResult = pkPlot->IsTradeRoute(ePlayer);
	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lIsValidDomainForLocation(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);

	const bool bResult = pkPlot->isValidDomainForLocation(*pkUnit);
	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lIsValidDomainForAction(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);

	const bool bResult = pkPlot->isValidDomainForAction(*pkUnit);
	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lArea(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvArea* pkArea = pkPlot->area();
	CvLuaArea::Push(L, pkArea);
	return 1;
}
int CvLuaPlot::lWaterArea(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvArea* pkArea = pkPlot->waterArea();
	CvLuaArea::Push(L, pkArea);
	return 1;
}
int CvLuaPlot::lGetInlandCorner(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvPlot* pkInlandCorner = pkPlot->getInlandCorner();

	CvLuaPlot::Push(L, pkInlandCorner);
	return 1;
}
int CvLuaPlot::lGetResourceType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	if(pkPlot != NULL)
	{
		if(lua_gettop(L) >= 2)
		{
			TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
			ResourceTypes eResource = pkPlot->getResourceType(eTeam);
			lua_pushinteger(L, eResource);
			return 1;
		}
		else
		{
			ResourceTypes eResource = pkPlot->getResourceType(NO_TEAM);
			lua_pushinteger(L, eResource);
			return 1;
		}
	}
	else
	{
		lua_pushinteger(L, -1);
		return 1;
	}
}
int CvLuaPlot::lIsRoutePillaged(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	lua_pushboolean(L, pkPlot->IsRoutePillaged());
	return 1;
}
int CvLuaPlot::lGetPlotCity(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvCity* pkCity = pkPlot->getPlotCity();
	CvLuaCity::Push(L, pkCity);
	return 1;
}
int CvLuaPlot::lGetWorkingCity(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvCity* pkCity = pkPlot->getWorkingCity();
	CvLuaCity::Push(L, pkCity);
	return 1;
}
int CvLuaPlot::lGetWorkingCityOverride(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvCity* pkCity = pkPlot->getWorkingCityOverride();
	CvLuaCity::Push(L, pkCity);
	return 1;
}
int CvLuaPlot::lGetYield(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const YieldTypes eIndex = (YieldTypes)lua_tointeger(L, 2);
	const int iResult = pkPlot->getYield(eIndex);
	lua_pushinteger(L, iResult);
	return 1;
}
int CvLuaPlot::lCalculateImprovementYieldChange(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const ImprovementTypes eImprovement = (ImprovementTypes)lua_tointeger(L, 2);
	const YieldTypes eYield = (YieldTypes)lua_tointeger(L,3);
	const PlayerTypes ePlayer = (PlayerTypes)lua_tointeger(L, 4);
	const bool bOptional = luaL_optbool(L, 5, false);
	const RouteTypes eRoute = (RouteTypes)luaL_optint(L, 5, NUM_ROUTE_TYPES);

	const int iResult = pkPlot->calculateImprovementYieldChange(eImprovement, eYield, ePlayer, bOptional, eRoute);
	lua_pushinteger(L, iResult);
	return 1;
}
int CvLuaPlot::lChangeVisibilityCount(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const int iChange = lua_toboolean(L, 3);
	const bool bInformExplorationTracking = lua_toboolean(L, 4);
	const bool bAlwaysSeeInvisible = lua_toboolean(L, 5);

	pkPlot->changeVisibilityCount(eTeam, iChange, bInformExplorationTracking, bAlwaysSeeInvisible);

	return 0;
}
int CvLuaPlot::lGetRevealedOwner(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const bool bDebug = luaL_optbool(L, 3, false);

	if (!bDebug)
		lua_pushinteger(L, pkPlot->getRevealedOwner(eTeam));
	else
		lua_pushinteger(L, pkPlot->getRevealedOwner(eTeam, true));

	return 1;
}
int CvLuaPlot::lGetRevealedTeam(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const bool bDebug = luaL_optbool(L, 3, false);

	if (!bDebug)
		lua_pushinteger(L, pkPlot->getRevealedTeam(eTeam));
	else
		lua_pushinteger(L, pkPlot->getRevealedTeam(eTeam, true));

	return 1;
}
int CvLuaPlot::lIsRiverCrossingToPlot(lua_State* L)
{
	bool bIsCrossingRiver = false;
	CvPlot* pkMyPlot = GetInstance(L);
	CvPlot* pkOtherPlot = GetInstance(L, 2);

	if(pkMyPlot->isRiverCrossing(directionXY(pkMyPlot, pkOtherPlot)))
	{
		bIsCrossingRiver = true;
	}

	lua_pushboolean(L, bIsCrossingRiver);
	return 1;
}
int CvLuaPlot::lIsRevealed(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const bool bDebug = luaL_optbool(L, 3, false);

	if (!bDebug)
		lua_pushboolean(L, pkPlot->isRevealed(eTeam));
	else
		lua_pushboolean(L, pkPlot->isRevealed(eTeam, true));

	return 1;
}
int CvLuaPlot::lSetRevealed(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const bool bNewValue = lua_toboolean(L, 3);
	const bool bTerrainOnly = luaL_optbool(L, 4, false);
	const TeamTypes eFromTeam = (TeamTypes)luaL_optint(L, 5, NO_TEAM);
	pkPlot->setRevealed(eTeam, bNewValue, bTerrainOnly, eFromTeam);

	return 0;
}
int CvLuaPlot::lGetRevealedImprovementType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const bool bDebug = luaL_optbool(L, 3, false);

	if (!bDebug)
		lua_pushinteger(L, pkPlot->getRevealedImprovementType(eTeam));
	else
		lua_pushinteger(L, pkPlot->getRevealedImprovementType(eTeam, true));

	return 1;
}
int CvLuaPlot::lGetRevealedRouteType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const bool bDebug = luaL_optbool(L, 3, false);

	if (!bDebug)
		lua_pushinteger(L, pkPlot->getRevealedRouteType(eTeam));
	else
		lua_pushinteger(L, pkPlot->getRevealedRouteType(eTeam, true));

	return 1;
}
int CvLuaPlot::lChangeBuildProgress(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	if(!pkPlot)
		return 0;
	const BuildTypes eBuild = (BuildTypes)lua_tointeger(L, 2);
	const int iChange = lua_tointeger(L, 3);
	const PlayerTypes ePlayer = (PlayerTypes)lua_tointeger(L, 4);
	const bool bResult = pkPlot->changeBuildProgress(eBuild, iChange, ePlayer);
	pkPlot->setLayoutDirty(true);
	return bResult;
}
int CvLuaPlot::lGetUnit(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const int iIndex = lua_tointeger(L, 2);

	CvUnit* pkUnit = pkPlot->getUnitByIndex(iIndex);
	CvLuaUnit::Push(L, pkUnit);
	return 1;
}
int CvLuaPlot::lGetNumLayerUnits(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const int iLayerID = luaL_optinteger(L, 2, -1);

	lua_pushinteger(L, pkPlot->getNumLayerUnits(iLayerID));
	return 1;
}
int CvLuaPlot::lGetLayerUnit(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const int iIndex = lua_tointeger(L, 2);
	const int iLayerID = luaL_optinteger(L, 3, -1);

	CvUnit* pkUnit = pkPlot->getLayerUnit(iIndex, iLayerID);
	CvLuaUnit::Push(L, pkUnit);
	return 1;
}
int CvLuaPlot::lGetScriptData(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const CvString strResult = pkPlot->getScriptData();
	lua_pushstring(L, strResult.c_str());
	return 1;
}
int CvLuaPlot::lSetScriptData(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	HksObject* object = L->m_apistack.base + 1;
	const char* strNewValue = object < L->m_apistack.top ? hks_obj_tolstring(L, object, NULL) : NULL;

	pkPlot->setScriptData(strNewValue);
	return 0;
}
int CvLuaPlot::lGetActiveFogOfWarMode(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);

	lua_pushinteger(L, pkPlot->GetActiveFogOfWarMode());
	return 1;
}
int CvLuaPlot::lCanSeePlot(lua_State* L)
{
	CvPlot* pkThisPlot = GetInstance(L);
	CvPlot* pkThatPlot = GetInstance(L, 2);
	TeamTypes eTeam = (TeamTypes) lua_tointeger(L, 3);
	int iRange = lua_tointeger(L, 4);
	DirectionTypes eFacingDirection = (DirectionTypes) lua_tointeger(L, 5);

	bool bCanSee = false;
	if(pkThisPlot)
	{
		bCanSee = pkThisPlot->canSeePlot(pkThatPlot, eTeam, iRange, eFacingDirection);
	}

	lua_pushboolean(L, bCanSee);
	return 1;

}
int CvLuaPlot::lGetContinentArtType(lua_State* L)
{
	CvPlot* pkThisPlot = GetInstance(L);
	if(pkThisPlot)
	{
		lua_pushinteger(L, pkThisPlot->GetContinentType());
	}
	else
	{
		lua_pushinteger(L, 0);
	}
	return 1;
}
int CvLuaPlot::lSetContinentArtType(lua_State* L)
{
	CvPlot* pkThisPlot = GetInstance(L);
	if(pkThisPlot)
	{
		const int iContinentType = lua_tointeger(L, 2);
		pkThisPlot->SetContinentType((char) iContinentType);
	}
	return 0;
}
int CvLuaPlot::lIsResourceConnectedByImprovement(lua_State* L)
{
	bool bResult = false;
	CvPlot* kPlot = GetInstance(L);
	const ImprovementTypes eImprovement = (ImprovementTypes) lua_tointeger(L, 2);
	CvImprovementEntry* pkImprovementInfo = GC.getImprovementInfo(eImprovement);
	if(pkImprovementInfo)
	{
		bResult = pkImprovementInfo->IsImprovementResourceTrade(kPlot->getResourceType(GC.getGame().getActiveTeam()));
	}

	lua_pushboolean(L, bResult);
	return 1;
}
int CvLuaPlot::lIsBuildRemovesFeature(lua_State* L)
{
	CvPlot* kPlot = GetInstance(L);
	const BuildTypes eBuild = (BuildTypes) lua_tointeger(L, 2);
	bool bFeatureRemoved = false;

	CvBuildInfo* pkBuildInfo = GC.getBuildInfo(eBuild);
	if(NULL != pkBuildInfo && kPlot->getFeatureType() != NO_FEATURE)
		bFeatureRemoved = pkBuildInfo->isFeatureRemove(kPlot->getFeatureType());

	lua_pushboolean(L, bFeatureRemoved);
	return 1;
}
int CvLuaPlot::lGetArchaeologyArtifactType(lua_State* L)
{
	CvPlot* kPlot = GetInstance(L);
	int iType = kPlot->GetArchaeologicalRecord().m_eArtifactType;
	lua_pushinteger(L, iType);
	return 1;
}
int CvLuaPlot::lGetArchaeologyArtifactEra(lua_State* L)
{
	CvPlot* kPlot = GetInstance(L);
	int iEra = kPlot->GetArchaeologicalRecord().m_eEra;
	lua_pushinteger(L, iEra);
	return 1;
}
int CvLuaPlot::lGetArchaeologyArtifactPlayer1(lua_State* L)
{
	CvPlot* kPlot = GetInstance(L);
	int iPlayer = kPlot->GetArchaeologicalRecord().m_ePlayer1;
	lua_pushinteger(L, iPlayer);
	return 1;
}
int CvLuaPlot::lGetArchaeologyArtifactPlayer2(lua_State* L)
{
	CvPlot* kPlot = GetInstance(L);
	int iPlayer = kPlot->GetArchaeologicalRecord().m_ePlayer2;
	lua_pushinteger(L, iPlayer);
	return 1;
}
int CvLuaPlot::lGetArchaeologyArtifactWork(lua_State* L)
{
	CvPlot* kPlot = GetInstance(L);
	int iWork = (int)kPlot->GetArchaeologicalRecord().m_eWork;
	lua_pushinteger(L, iWork);
	return 1;
}
int CvLuaPlot::lHasBubbles(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::HasBubbles));
}

int CvLuaPlot::lSetBubbles(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool)>(&CvPlot::SetBubbles));
}

int CvLuaPlot::lErase(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool)>(&CvPlot::erase));
}

int CvLuaPlot::lGetTeam(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<TeamTypes (CvPlot::*)() const>(&CvPlot::getTeam));
}

int CvLuaPlot::lNukeExplosion(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int, CvUnit *)>(&CvPlot::nukeExplosion));
}

int CvLuaPlot::lUpdateFog(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool)>(&CvPlot::updateFog));
}

int CvLuaPlot::lIsAdjacentToLand(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isAdjacentToLand));
}

int CvLuaPlot::lIsAdjacentToShallowWater(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isAdjacentToShallowWater));
}

int CvLuaPlot::lIsCoastalLand(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(int) const>(&CvPlot::isCoastalLand));
}

int CvLuaPlot::lIsAllowsWalkWater(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::IsAllowsWalkWater));
}

int CvLuaPlot::lIsWithinTeamCityRadius(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(TeamTypes, PlayerTypes) const>(&CvPlot::isWithinTeamCityRadius));
}

int CvLuaPlot::lIsLake(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isLake));
}

int CvLuaPlot::lIsFreshWater(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isFreshWater));
}

int CvLuaPlot::lIsRiverSide(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isRiverSide));
}

int CvLuaPlot::lIsRiverConnection(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(DirectionTypes) const>(&CvPlot::isRiverConnection));
}

int CvLuaPlot::lGetNearestLandArea(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getNearestLandArea));
}

int CvLuaPlot::lSeeFromLevel(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(TeamTypes) const>(&CvPlot::seeFromLevel));
}

int CvLuaPlot::lSeeThroughLevel(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(bool) const>(&CvPlot::seeThroughLevel));
}

int CvLuaPlot::lCanHaveResource(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(ResourceTypes) const>(&CvPlot::canHaveResource));
}

int CvLuaPlot::lCanHaveImprovement(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(ImprovementTypes, TeamTypes, bool) const>(&CvPlot::canHaveImprovement));
}

int CvLuaPlot::lCanBuild(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(BuildTypes, PlayerTypes, bool, bool) const>(&CvPlot::canBuild));
}

int CvLuaPlot::lGetBuildTime(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(BuildTypes, PlayerTypes) const>(&CvPlot::getBuildTime));
}

int CvLuaPlot::lGetBuildTurnsLeft(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(BuildTypes, PlayerTypes, int, int) const>(&CvPlot::getBuildTurnsLeft));
}

int CvLuaPlot::lGetBuildTurnsTotal(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(BuildTypes, PlayerTypes) const>(&CvPlot::getBuildTurnsTotal));
}

int CvLuaPlot::lGetUnitPower(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(PlayerTypes) const>(&CvPlot::getUnitPower));
}

int CvLuaPlot::lDefenseModifier(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(TeamTypes, bool, bool) const>(&CvPlot::defenseModifier));
}

int CvLuaPlot::lMovementCost(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(const CvUnit *, const CvPlot *, int) const>(&CvPlot::movementCost));
}

int CvLuaPlot::lGetExtraMovePathCost(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getExtraMovePathCost));
}

int CvLuaPlot::lChangeExtraMovePathCost(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::changeExtraMovePathCost));
}

int CvLuaPlot::lIsAdjacentOwned(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isAdjacentOwned));
}

int CvLuaPlot::lIsAdjacentPlayer(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(PlayerTypes, bool) const>(&CvPlot::isAdjacentPlayer));
}

int CvLuaPlot::lIsAdjacentTeam(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(TeamTypes, bool) const>(&CvPlot::isAdjacentTeam));
}

int CvLuaPlot::lIsOwned(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isOwned));
}

int CvLuaPlot::lIsAlien(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isAlien));
}

int CvLuaPlot::lHasAlienNest(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::HasAlienNest));
}

int CvLuaPlot::lIsVisibleToWatchingHuman(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isVisibleToWatchingHuman));
}

int CvLuaPlot::lIsAdjacentNonvisible(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(TeamTypes) const>(&CvPlot::isAdjacentNonvisible));
}

int CvLuaPlot::lIsAdjacentRevealed(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(TeamTypes) const>(&CvPlot::isAdjacentRevealed));
}

int CvLuaPlot::lIsAdjacentNonrevealed(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(TeamTypes) const>(&CvPlot::isAdjacentNonrevealed));
}

int CvLuaPlot::lIsGoody(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(TeamTypes) const>(&CvPlot::isGoody));
}

int CvLuaPlot::lIsRevealedGoody(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(TeamTypes) const>(&CvPlot::isRevealedGoody));
}

int CvLuaPlot::lIsCity(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isCity));
}

int CvLuaPlot::lIsBeingWorked(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isBeingWorked));
}

int CvLuaPlot::lIsUnit(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isUnit));
}

int CvLuaPlot::lIsImmobileUnit(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isImmobileUnit));
}

int CvLuaPlot::lIsUnlaunchedOrbitalUnit(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isUnlaunchedOrbitalUnit));
}

int CvLuaPlot::lGetNumDefenders(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(PlayerTypes) const>(&CvPlot::getNumDefenders));
}

int CvLuaPlot::lGetNumVisibleEnemyDefenders(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(const CvUnit *) const>(&CvPlot::getNumVisibleEnemyDefenders));
}

int CvLuaPlot::lGetNumVisiblePotentialEnemyDefenders(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(const CvUnit *) const>(&CvPlot::getNumVisiblePotentialEnemyDefenders));
}

int CvLuaPlot::lIsVisibleOtherUnit(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(PlayerTypes) const>(&CvPlot::isVisibleOtherUnit));
}

int CvLuaPlot::lIsFighting(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isFighting));
}

int CvLuaPlot::lIsRoute(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isRoute));
}

int CvLuaPlot::lIsImpassable(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isImpassable));
}

int CvLuaPlot::lGetX(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getX));
}

int CvLuaPlot::lGetY(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getY));
}

int CvLuaPlot::lAt(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(int, int) const>(&CvPlot::at));
}

int CvLuaPlot::lGetPlotIndex(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::GetPlotIndex));
}

int CvLuaPlot::lGetLatitude(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getLatitude));
}

int CvLuaPlot::lGetArea(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getArea));
}

int CvLuaPlot::lSetArea(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::setArea));
}

int CvLuaPlot::lGetWildness(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getWildness));
}

int CvLuaPlot::lSetWildness(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::setWildness));
}

int CvLuaPlot::lChangeWildness(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::changeWildness));
}

int CvLuaPlot::lGetFeatureVariety(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getFeatureVariety));
}

int CvLuaPlot::lGetOwnershipDuration(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getOwnershipDuration));
}

int CvLuaPlot::lIsOwnershipScore(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isOwnershipScore));
}

int CvLuaPlot::lSetOwnershipDuration(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::setOwnershipDuration));
}

int CvLuaPlot::lChangeOwnershipDuration(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::changeOwnershipDuration));
}

int CvLuaPlot::lGetImprovementDuration(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getImprovementDuration));
}

int CvLuaPlot::lSetImprovementDuration(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::setImprovementDuration));
}

int CvLuaPlot::lChangeImprovementDuration(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::changeImprovementDuration));
}

int CvLuaPlot::lGetUpgradeProgress(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getUpgradeProgress));
}

int CvLuaPlot::lGetUpgradeTimeLeft(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(ImprovementTypes, PlayerTypes) const>(&CvPlot::getUpgradeTimeLeft));
}

int CvLuaPlot::lSetUpgradeProgress(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::setUpgradeProgress));
}

int CvLuaPlot::lChangeUpgradeProgress(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::changeUpgradeProgress));
}

int CvLuaPlot::lGetCityRadiusCount(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getCityRadiusCount));
}

int CvLuaPlot::lIsCityRadius(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::isCityRadius));
}

int CvLuaPlot::lIsStartingPlot(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isStartingPlot));
}

int CvLuaPlot::lSetStartingPlot(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool)>(&CvPlot::setStartingPlot));
}

int CvLuaPlot::lIsNEOfRiver(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isNEOfRiver));
}

int CvLuaPlot::lSetNEOfRiver(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool, FlowDirectionTypes)>(&CvPlot::setNEOfRiver));
}

int CvLuaPlot::lIsWOfRiver(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isWOfRiver));
}

int CvLuaPlot::lSetWOfRiver(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool, FlowDirectionTypes)>(&CvPlot::setWOfRiver));
}

int CvLuaPlot::lIsNWOfRiver(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isNWOfRiver));
}

int CvLuaPlot::lSetNWOfRiver(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool, FlowDirectionTypes)>(&CvPlot::setNWOfRiver));
}

int CvLuaPlot::lGetRiverEFlowDirection(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<FlowDirectionTypes (CvPlot::*)() const>(&CvPlot::getRiverEFlowDirection));
}

int CvLuaPlot::lGetRiverSEFlowDirection(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<FlowDirectionTypes (CvPlot::*)() const>(&CvPlot::getRiverSEFlowDirection));
}

int CvLuaPlot::lGetRiverSWFlowDirection(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<FlowDirectionTypes (CvPlot::*)() const>(&CvPlot::getRiverSWFlowDirection));
}

int CvLuaPlot::lGetOwner(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<PlayerTypes (CvPlot::*)() const>(&CvPlot::getOwner));
}

int CvLuaPlot::lSetOwner(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(PlayerTypes, int, bool, bool)>(&CvPlot::setOwner));
}

int CvLuaPlot::lGetPlotType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<PlotTypes (CvPlot::*)() const>(&CvPlot::getPlotType));
}

int CvLuaPlot::lIsFlatlands(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isFlatlands));
}

int CvLuaPlot::lIsHills(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isHills));
}

int CvLuaPlot::lIsOpenGround(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isOpenGround));
}

int CvLuaPlot::lIsRoughGround(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isRoughGround));
}

int CvLuaPlot::lIsMountain(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isMountain));
}

int CvLuaPlot::lIsCanyon(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isCanyon));
}

int CvLuaPlot::lSetPlotType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(PlotTypes, bool, bool, bool)>(&CvPlot::setPlotType));
}

int CvLuaPlot::lGetNonObsoleteResourceType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<ResourceTypes (CvPlot::*)(TeamTypes) const>(&CvPlot::getNonObsoleteResourceType));
}

int CvLuaPlot::lSetResourceType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(ResourceTypes, int)>(&CvPlot::setResourceType));
}

int CvLuaPlot::lSetLayerResourceType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(ResourceLayers, ResourceTypes, int)>(&CvPlot::SetResourceType));
}

int CvLuaPlot::lGetNumResource(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getNumResource));
}

int CvLuaPlot::lSetNumResource(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::setNumResource));
}

int CvLuaPlot::lChangeNumResource(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::changeNumResource));
}

int CvLuaPlot::lSetPrimaryResourceType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(ResourceTypes, int)>(&CvPlot::SetPrimaryResourceType));
}

int CvLuaPlot::lGetPrimaryResourceType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<ResourceTypes (CvPlot::*)(TeamTypes) const>(&CvPlot::GetPrimaryResourceType));
}

int CvLuaPlot::lSetSecondaryResourceType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(ResourceTypes, int)>(&CvPlot::SetSecondaryResourceType));
}

int CvLuaPlot::lGetSecondaryResourceType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<ResourceTypes (CvPlot::*)(TeamTypes) const>(&CvPlot::GetSecondaryResourceType));
}

int CvLuaPlot::lHasImprovement(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::hasImprovement));
}

int CvLuaPlot::lGetImprovementType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<ImprovementTypes (CvPlot::*)() const>(&CvPlot::getImprovementType));
}

int CvLuaPlot::lSetImprovementType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(ImprovementTypes, PlayerTypes)>(&CvPlot::setImprovementType));
}

int CvLuaPlot::lSetImprovementPillaged(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool)>(&CvPlot::SetImprovementPillaged));
}

int CvLuaPlot::lSetPrimaryImprovementType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(ImprovementTypes, PlayerTypes)>(&CvPlot::SetPrimaryImprovementType));
}

int CvLuaPlot::lGetPrimaryImprovementType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<ImprovementTypes (CvPlot::*)() const>(&CvPlot::GetPrimaryImprovementType));
}

int CvLuaPlot::lSetSecondaryImprovementType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(ImprovementTypes, PlayerTypes)>(&CvPlot::SetSecondaryImprovementType));
}

int CvLuaPlot::lGetSecondaryImprovementType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<ImprovementTypes (CvPlot::*)() const>(&CvPlot::GetSecondaryImprovementType));
}

int CvLuaPlot::lGetRouteType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<RouteTypes (CvPlot::*)() const>(&CvPlot::getRouteType));
}

int CvLuaPlot::lSetRouteType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(RouteTypes)>(&CvPlot::setRouteType));
}

int CvLuaPlot::lGetReconCount(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getReconCount));
}

int CvLuaPlot::lGetRiverCrossingCount(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getRiverCrossingCount));
}

int CvLuaPlot::lCalculateNatureYield(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(YieldTypes, TeamTypes, bool) const>(&CvPlot::calculateNatureYield));
}

int CvLuaPlot::lCalculateBestNatureYield(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(YieldTypes, TeamTypes) const>(&CvPlot::calculateBestNatureYield));
}

int CvLuaPlot::lCalculateTotalBestNatureYield(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(TeamTypes) const>(&CvPlot::calculateTotalBestNatureYield));
}

int CvLuaPlot::lCalculateYield(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(YieldTypes, bool)>(&CvPlot::calculateYield));
}

int CvLuaPlot::lHasYield(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::hasYield));
}

int CvLuaPlot::lGetYieldWithBuild(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(BuildTypes, YieldTypes, bool, PlayerTypes) const>(&CvPlot::getYieldWithBuild));
}

int CvLuaPlot::lGetHealth(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(PlayerTypes) const>(&CvPlot::getHealth));
}

int CvLuaPlot::lGetUnhealth(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(PlayerTypes) const>(&CvPlot::getUnhealth));
}

int CvLuaPlot::lCountNumAirUnits(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(TeamTypes) const>(&CvPlot::countNumAirUnits));
}

int CvLuaPlot::lGetFoundValue(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(PlayerTypes)>(&CvPlot::getFoundValue));
}

int CvLuaPlot::lIsBestAdjacentFound(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(PlayerTypes)>(&CvPlot::isBestAdjacentFound));
}

int CvLuaPlot::lGetPlayerCityRadiusCount(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(PlayerTypes) const>(&CvPlot::getPlayerCityRadiusCount));
}

int CvLuaPlot::lIsPlayerCityRadius(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(PlayerTypes) const>(&CvPlot::isPlayerCityRadius));
}

int CvLuaPlot::lGetVisibilityCount(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(TeamTypes) const>(&CvPlot::getVisibilityCount));
}

int CvLuaPlot::lIsRiverCrossing(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(DirectionTypes) const>(&CvPlot::isRiverCrossing));
}

int CvLuaPlot::lGetBuildProgress(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(BuildTypes) const>(&CvPlot::getBuildProgress));
}

int CvLuaPlot::lGetInvisibleVisibilityCount(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)(TeamTypes) const>(&CvPlot::getInvisibleVisibilityCount));
}

int CvLuaPlot::lChangeInvisibleVisibilityCount(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(TeamTypes, int)>(&CvPlot::changeInvisibleVisibilityCount));
}

int CvLuaPlot::lIsInvisibleVisibleToAnyEnemyTeam(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)(TeamTypes) const>(&CvPlot::isInvisibleVisibleToAnyEnemyTeam));
}

int CvLuaPlot::lGetNumUnits(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::getNumUnits));
}

int CvLuaPlot::lIsImprovementPillaged(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::IsImprovementPillaged));
}

int CvLuaPlot::lHasWrittenArtifact(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::HasWrittenArtifact));
}

int CvLuaPlot::lGetCityPurchaseID(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)()>(&CvPlot::GetCityPurchaseID));
}

int CvLuaPlot::lSetCityPurchaseID(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(int)>(&CvPlot::SetCityPurchaseID));
}

int CvLuaPlot::lIsOutpost(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isOutpost));
}

int CvLuaPlot::lIsStation(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isStation));
}

int CvLuaPlot::lIsStrategicSite(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isStrategicSite));
}

int CvLuaPlot::lIsOrbitalUnit(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::isOrbitalUnit));
}

int CvLuaPlot::lGetCityIntrigueModFromOrbitalUnits(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<int (CvPlot::*)() const>(&CvPlot::GetCityIntrigueModFromOrbitalUnits));
}

int CvLuaPlot::lIsCityCovertOpsPreventedByOrbitalUnits(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::IsCityCovertOpsPreventedByOrbitalUnits));
}

int CvLuaPlot::lGetLandmarkActionPerformed(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<bool (CvPlot::*)() const>(&CvPlot::GetLandmarkActionPerformed));
}

int CvLuaPlot::lSetLandmarkActionPerformed(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)(bool)>(&CvPlot::SetLandmarkActionPerformed));
}

int CvLuaPlot::lGetHeroLandmark(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<HeroLandmarkTypes (CvPlot::*)() const>(&CvPlot::getHeroLandmark));
}

#define PlotIntegerMethod(Name, Expression) \
int CvLuaPlot::l##Name(lua_State* L) { \
	CvPlot* pkPlot = GetInstance(L); \
	lua_pushinteger(L, (Expression)); \
	return 1; \
}
#define PlotBooleanMethod(Name, Expression) \
int CvLuaPlot::l##Name(lua_State* L) { \
	CvPlot* pkPlot = GetInstance(L); \
	lua_pushboolean(L, (Expression)); \
	return 1; \
}

PlotIntegerMethod(GetMapRegionType, pkPlot->GetMapRegionType())
PlotIntegerMethod(GetMapRegionIndex, pkPlot->GetMapRegionIndex())
PlotIntegerMethod(GetPlotMaintenance, pkPlot->getPlotEnergyMaintenance((PlayerTypes)lua_tointeger(L, 2)))
// Stations use the trade-site pseudo-player ID encoded in the target.
PlotIntegerMethod(GetTradeSiteOwnerID, pkPlot->isStation() ? 63 : pkPlot->getOwner())
PlotBooleanMethod(IsTrench, pkPlot->isTrench())
PlotBooleanMethod(CanHaveMiasma, pkPlot->CanHaveMiasma())
PlotBooleanMethod(HasMiasma, pkPlot->HasMiasma())
PlotBooleanMethod(CanHaveAnchorage, pkPlot->CanHaveAnchorage())
PlotBooleanMethod(HasAnchorage, pkPlot->HasAnchorage())
PlotBooleanMethod(HasResource, pkPlot->hasResource((TeamTypes)luaL_optinteger(L, 2, NO_TEAM)))
PlotBooleanMethod(IsUnitBlockingCityWork, pkPlot->isUnitBlockingCityWork((PlayerTypes)lua_tointeger(L, 2)))
PlotBooleanMethod(IsNeutralTerritory, pkPlot->IsNeutralTerritory((PlayerTypes)lua_tointeger(L, 2)))
PlotBooleanMethod(IsEnemyTerritory, pkPlot->IsEnemyTerritory((PlayerTypes)lua_tointeger(L, 2)))
PlotBooleanMethod(IsEnemyOrbitalUnit, pkPlot->isEnemyOrbitalUnit((TeamTypes)lua_tointeger(L, 2)))
PlotBooleanMethod(HasInfluencingOrbitalUnit, pkPlot->HasInfluencingOrbitalUnit())

int CvLuaPlot::lSetMiasma(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	pkPlot->SetMiasma(lua_toboolean(L, 2));
	return 0;
}
int CvLuaPlot::lSetAnchorage(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	pkPlot->SetAnchorage(lua_toboolean(L, 2));
	return 0;
}
int CvLuaPlot::lClearImprovementType(lua_State* L)
{
	return BasicLuaMethod(L, static_cast<void (CvPlot::*)()>(&CvPlot::clearImprovementType));
}
int CvLuaPlot::lSetRevealedImprovementType(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 2);
	const ImprovementTypes eImprovement = (ImprovementTypes)lua_tointeger(L, 3);
	lua_pushinteger(L, pkPlot->setRevealedImprovementType(eTeam, eImprovement));
	return 1;
}
int CvLuaPlot::lIsInvisibleVisibleToTeam(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	const TeamTypes eInvisibleTeam = (TeamTypes)lua_tointeger(L, 2);
	const TeamTypes eTeam = (TeamTypes)lua_tointeger(L, 3);
	lua_pushboolean(L, pkPlot->isInvisibleVisibleToTeam(eInvisibleTeam, eTeam));
	return 1;
}
int CvLuaPlot::lIsEnemyUnit(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);
	lua_pushboolean(L, pkPlot->IsActualEnemyUnit(pkUnit->getOwner(), true));
	return 1;
}
int CvLuaPlot::lIsFriendlyOutpost(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);
	const bool bCheckImprovement = lua_toboolean(L, 3);
	lua_pushboolean(L, pkPlot->isFriendlyOutpost(*pkUnit, bCheckImprovement));
	return 1;
}
int CvLuaPlot::lIsEnemyOutpost(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);
	lua_pushboolean(L, pkPlot->isEnemyOutpost(*pkUnit));
	return 1;
}
int CvLuaPlot::lIsEnemyStrategicSite(lua_State* L)
{
	CvPlot* pkPlot = GetInstance(L);
	CvUnit* pkUnit = CvLuaUnit::GetInstance(L, 2);
	lua_pushboolean(L, pkPlot->isEnemyStrategicSite(*pkUnit));
	return 1;
}

#define PlotStringMethod(Name, MethodName) \
int CvLuaPlot::l##Name(lua_State* L) { \
	CvPlot* pkPlot = GetInstance(L); \
	const CvString str = pkPlot->MethodName(); \
	lua_pushstring(L, str.c_str()); \
	return 1; \
}
PlotStringMethod(GetSiteName, getSiteName)
PlotStringMethod(GetLogString, getLogString)
PlotStringMethod(GetInfluencingOrbitalUnitsText, GetInfluencingOrbitalUnitsText)

int CvLuaPlot::lGetPlotOutpost(lua_State* L)
{
	CvLuaOutpost::Push(L, GetInstance(L)->getPlotOutpost());
	return 1;
}
int CvLuaPlot::lGetPlotStation(lua_State* L)
{
	CvLuaStation::Push(L, GetInstance(L)->getPlotStation());
	return 1;
}
int CvLuaPlot::lGetPlotStrategicSite(lua_State* L)
{
	CvLuaStrategicSite::Push(L, GetInstance(L)->getPlotStrategicSite());
	return 1;
}
int CvLuaPlot::lGetPlotStrategicSiteData(lua_State* L)
{
	CvStrategicSite* pkSite = GetInstance(L)->getPlotStrategicSite();
	if(pkSite)
	{
		lua_newtable(L);
		pkSite->LuaPushStrategicSiteData(L);
	}
	else
		lua_pushnil(L);
	return 1;
}
int CvLuaPlot::lGetOrbitalUnit(lua_State* L)
{
	CvLuaUnit::Push(L, GetInstance(L)->getPlotOrbitalUnit());
	return 1;
}
int CvLuaPlot::lGetOrbitalUnitAbovePlot(lua_State* L)
{
	CvUnit* pkUnit = GetInstance(L)->GetOrbitalUnitAbovePlot();
	if(pkUnit)
		CvLuaUnit::Push(L, pkUnit);
	else
		lua_pushnil(L);
	return 1;
}
int CvLuaPlot::lGetOrbitalUnitInfluencingPlot(lua_State* L)
{
	CvUnit* pkUnit = GetInstance(L)->GetOrbitalUnitInfluencingPlot();
	if(pkUnit)
		CvLuaUnit::Push(L, pkUnit);
	else
		lua_pushnil(L);
	return 1;
}
