// TODO: Phase1 (anonymous namespace)::OffsetPlot(int, int, int, int): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 CvLuaStaticInstance<CvLuaMap, CvMap>::RegisterMethod(lua_State*, int (*)(lua_State*), char const*): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 CvLuaStaticInstance<CvLuaMap, CvMap>::pRegister(lua_State*): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
#pragma once

#include "CvLuaStaticInstance.h"

class CvMap;

class CvLuaMap : public CvLuaStaticInstance<CvLuaMap, CvMap>
{
public:
// TODO: Phase1 CvLuaMap::GetInstanceName(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static const char* GetInstanceName();
// TODO: Phase1 CvLuaMap::GetInstance(lua_State*, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static CvMap* GetInstance(lua_State* L, int idx = 1);
// TODO: Phase1 CvLuaMap::RegisterMembers(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static void RegisterMembers(lua_State* L);

protected:
// TODO: Phase1 CvLuaMap::lAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lAreas(lua_State* L);
// TODO: Phase1 CvLuaMap::lAreasAux(lua_State*): MISMATCH; Non-padding instruction count: BE 58, object 53; Civ5 changed/new instruction count unverified.
	static int lAreasAux(lua_State* L);
// TODO: Phase1 CvLuaMap::lFindBiggestArea(lua_State*): MISMATCH; Non-padding instruction count: BE 41, object 43; Civ5 changed/new instruction count unverified.
	static int lFindBiggestArea(lua_State* L);
// TODO: Phase1 CvLuaMap::lFindWater(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lFindWater(lua_State* L);
// TODO: Phase1 CvLuaMap::lFindNearestStartPlot(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lFindNearestStartPlot(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetClimate(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetClimate(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetFractalFlags(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetFractalFlags(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetGridSize(lua_State*): MISMATCH; Mnemonic divergence at BE #9 cvtsi2sd, object #9 movsd; Civ5 changed/new instruction count unverified.
	static int lGetGridSize(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetNumPlots(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetNumPlots(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetNumResources(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetNumResources(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetNumResourcesOnLand(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetNumResourcesOnLand(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetPlot(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetPlot(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetPlotByIndex(lua_State*): MISMATCH; Non-padding instruction count: BE 37, object 39; Civ5 changed/new instruction count unverified.
	static int lGetPlotByIndex(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetPlotXY(lua_State*): MISMATCH; Non-padding instruction count: BE 174, object 85; Civ5 changed/new instruction count unverified.
	static int lGetPlotXY(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetArea(lua_State*): MISMATCH; Non-padding instruction count: BE 35, object 37; Civ5 changed/new instruction count unverified.
	static int lGetArea(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetIndexAfterLastArea(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetIndexAfterLastArea(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetLandPlots(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetLandPlots(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetWaterPlots(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetWaterPlots(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetLakePlots(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetLakePlots(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetNumAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetNumAreas(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetNumLandAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetNumLandAreas(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetRandomResourceQuantity(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetRandomResourceQuantity(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetSeaLevel(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetSeaLevel(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetWorldSize(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetWorldSize(lua_State* L);
// TODO: Phase1 CvLuaMap::lIsPlot(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lIsPlot(lua_State* L);
// TODO: Phase1 CvLuaMap::lIsWrapX(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lIsWrapX(lua_State* L);
// TODO: Phase1 CvLuaMap::lIsWrapY(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lIsWrapY(lua_State* L);
// TODO: Phase1 CvLuaMap::lMaxPlotDistance(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lMaxPlotDistance(lua_State* L);
// TODO: Phase1 CvLuaMap::lRand(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lRand(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetMapSeed(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetMapSeed(lua_State* L);
// TODO: Phase1 CvLuaMap::lCalculateAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lCalculateAreas(lua_State* L);
// TODO: Phase1 CvLuaMap::lRecalculateAreas(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lRecalculateAreas(lua_State* L);
// TODO: Phase1 CvLuaMap::lPlotDistance(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lPlotDistance(lua_State* L);
// TODO: Phase1 CvLuaMap::lPlotXYWithRangeCheck(lua_State*): MISMATCH; Non-padding instruction count: BE 176, object 101; Civ5 changed/new instruction count unverified.
	static int lPlotXYWithRangeCheck(lua_State* L);
// TODO: Phase1 CvLuaMap::lPlotDirection(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lPlotDirection(lua_State* L);
// TODO: Phase1 CvLuaMap::lDefaultContinentStamper(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lDefaultContinentStamper(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetCustomOption(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetCustomOption(lua_State* L);
// TODO: Phase1 CvLuaMap::lUpdateDeferredFog(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lUpdateDeferredFog(lua_State* L);
// TODO: Phase1 CvLuaMap::lChangeAIMapHint(lua_State*): MISMATCH; Non-padding instruction count: BE 24, object 26; Civ5 changed/new instruction count unverified.
	static int lChangeAIMapHint(lua_State* L);
// TODO: Phase1 CvLuaMap::lGetAIMapHint(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetAIMapHint(lua_State* L);
};
