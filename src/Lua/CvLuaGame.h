#pragma once

#include "CvLuaStaticInstance.h"

class CvGame;

class CvLuaGame : public CvLuaStaticInstance<CvLuaGame, CvGame>
{
public:
	static const char* GetInstanceName();
	static CvGame* GetInstance(lua_State* L, int idx = 1);
	static void RegisterMembers(lua_State* L);
};
