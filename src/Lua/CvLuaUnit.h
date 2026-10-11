#pragma once

#include "CvLuaScopedInstance.h"

class CvUnit;

class CvLuaUnit : public CvLuaScopedInstance<CvLuaUnit, CvUnit>
{
public:
	static void PushMethods(lua_State* L, int t);
	static void HandleMissingInstance(lua_State* L);
	static const char* GetTypeName();
};
