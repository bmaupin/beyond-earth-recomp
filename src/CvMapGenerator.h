// TODO: Phase1 std::__1::__vector_base_common<true>::__throw_length_error() const: MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<CvMapRegionData, std::__1::allocator<CvMapRegionData> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__split_buffer<CvMapRegionData, std::__1::allocator<CvMapRegionData>&>::~__split_buffer(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 void std::__1::vector<CvMapRegionData, std::__1::allocator<CvMapRegionData> >::__push_back_slow_path<CvMapRegionData>(CvMapRegionData&&): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
/*	-------------------------------------------------------------------------------------------------------
	� 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#pragma once

#ifndef CIV5_MAPGENERATOR_H
#define CIV5_MAPGENERATOR_H

struct CvMapInitData;
struct CvGameInitialItemsOverrides;

class CvMapGenerator
{
public:
// TODO: Phase1 CvMapGenerator::CvMapGenerator(char const*): MISMATCH; Non-padding instruction count: BE 38, object 27; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvMapGenerator::CvMapGenerator(char const*): MISMATCH; Non-padding instruction count: BE 38, object 27; Civ5 changed/new instruction count unverified.
	CvMapGenerator(const char* szMapScriptName);
// TODO: Phase1 CvMapGenerator::~CvMapGenerator(): MISMATCH; Non-padding instruction count: BE 16, object 25; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvMapGenerator::~CvMapGenerator(): MISMATCH; Non-padding instruction count: BE 28, object 24; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvMapGenerator::~CvMapGenerator(): MISMATCH; Non-padding instruction count: BE 28, object 24; Civ5 changed/new instruction count unverified.
	virtual ~CvMapGenerator();

	//! Call Lua function to obtain map overrides.
// TODO: Phase1 CvMapGenerator::GetMapInitData(CvMapInitData&, WorldSizeTypes): MISMATCH; Non-padding instruction count: BE 90, object 36; Civ5 changed/new instruction count unverified.
	bool GetMapInitData(CvMapInitData& kData, WorldSizeTypes eWorldSize);

	//! Call Lua function to generate random map.
// TODO: Phase1 CvMapGenerator::GenerateRandomMap(): MISMATCH; Non-padding instruction count: BE 35, object 31; Civ5 changed/new instruction count unverified.
	void GenerateRandomMap();

	//! Call Lua function to obtain initial game items overrides.
// TODO: Phase1 CvMapGenerator::GetGameInitialItemsOverrides(CvGameInitialItemsOverrides&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool GetGameInitialItemsOverrides(CvGameInitialItemsOverrides& kOverrides);

// TODO: Phase1 CvMapGenerator::RegisterLua(): MISMATCH; Non-padding instruction count: BE 432, object 380; Civ5 changed/new instruction count unverified.
	void RegisterLua();
// TODO: Phase1 CvMapGenerator::lCalculateRegions(lua_State*): MISMATCH; Non-padding instruction count: BE 120, object 137; Civ5 changed/new instruction count unverified.
	static int lCalculateRegions(lua_State* L);
// TODO: Phase1 CvMapGenerator::lGetNumRegions(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	static int lGetNumRegions(lua_State* L);
// TODO: Phase1 CvMapGenerator::lGetNumMatchingNeighborPlots(lua_State*): MISMATCH; Non-padding instruction count: BE 342, object 12; Civ5 changed/new instruction count unverified.
	static int lGetNumMatchingNeighborPlots(lua_State* L);
// TODO: Phase1 DoForEachNeighborPlot(lua_State*, bool, bool): UNVERIFIED; Object export outside source-attributed target inventory; target presence checked separately; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvMapGenerator::lDoForEachNeighborPlot(lua_State*): MISMATCH; Non-padding instruction count: BE 296, object 12; Civ5 changed/new instruction count unverified.
	static int lDoForEachNeighborPlot(lua_State* L);
// TODO: Phase1 CvMapGenerator::lDoForEachRingPlot(lua_State*): MISMATCH; Non-padding instruction count: BE 296, object 12; Civ5 changed/new instruction count unverified.
	static int lDoForEachRingPlot(lua_State* L);
// TODO: Phase1 CvMapGenerator::lGetPlotLinearDistanceFromRegionCentroid(lua_State*): MISMATCH; Non-padding instruction count: BE 50, object 58; Civ5 changed/new instruction count unverified.
	static int lGetPlotLinearDistanceFromRegionCentroid(lua_State* L);
// TODO: Phase1 CvMapGenerator::lGetPlotHexDistanceFromRegionCentroid(lua_State*): MISMATCH; Non-padding instruction count: BE 125, object 133; Civ5 changed/new instruction count unverified.
	static int lGetPlotHexDistanceFromRegionCentroid(lua_State* L);

protected:

	//! Protected Lua continuation of GetMapInitData.
// TODO: Phase1 CvMapGenerator::pGetMapInitData(lua_State*): MISMATCH; Non-padding instruction count: BE 647, object 539; Civ5 changed/new instruction count unverified.
	static int pGetMapInitData(lua_State* L);

	//! Protected Lua continuation of GenerateRandomMap.
// TODO: Phase1 CvMapGenerator::pGenerateRandomMap(lua_State*): MISMATCH; Non-padding instruction count: BE 83, object 72; Civ5 changed/new instruction count unverified.
	static int pGenerateRandomMap(lua_State* L);

	//! Protected Lua continuation of GetGameInitialItemsOverrides
// TODO: Phase1 CvMapGenerator::pGetGameInitialItemsOverrides(lua_State*): MISMATCH; Non-padding instruction count: BE 929, object 125; Civ5 changed/new instruction count unverified.
	static int pGetGameInitialItemsOverrides(lua_State* L);

private:
	CvMapGenerator(const CvMapGenerator&);	//Stub to prevent compiler generated function.
	CvMapGenerator& operator=(const CvMapGenerator&);	//Stub to prevent compiler generated function.

	lua_State* m_pkLuaState;
};

#endif
