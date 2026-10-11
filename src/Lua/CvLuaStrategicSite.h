#pragma once

#include "CvLuaScopedInstance.h"

class CvStrategicSite;

class CvLuaStrategicSite : public CvLuaScopedInstance<CvLuaStrategicSite, CvStrategicSite>
{
public:
	static void PushMethods(lua_State* L, int t);
	static void HandleMissingInstance(lua_State* L);
	static const char* GetTypeName();
};
