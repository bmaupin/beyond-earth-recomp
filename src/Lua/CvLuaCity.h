#pragma once

#include "CvLuaScopedInstance.h"

class CvCity;

class CvLuaCity : public CvLuaScopedInstance<CvLuaCity, CvCity>
{
public:
	static void PushMethods(lua_State* L, int t);
	static void HandleMissingInstance(lua_State* L);
	static const char* GetTypeName();
};
