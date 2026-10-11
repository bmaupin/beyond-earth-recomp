#pragma once

#include "CvLuaScopedInstance.h"

class CvOutpost;

class CvLuaOutpost : public CvLuaScopedInstance<CvLuaOutpost, CvOutpost>
{
public:
	static void PushMethods(lua_State* L, int t);
	static void HandleMissingInstance(lua_State* L);
	static const char* GetTypeName();
};
