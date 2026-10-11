#pragma once

#include "CvLuaScopedInstance.h"

class CvStation;

class CvLuaStation : public CvLuaScopedInstance<CvLuaStation, CvStation>
{
public:
	static void PushMethods(lua_State* L, int t);
	static void HandleMissingInstance(lua_State* L);
	static const char* GetTypeName();
};
