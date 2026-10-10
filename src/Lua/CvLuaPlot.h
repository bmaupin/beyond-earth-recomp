#pragma once

#include "CvLuaScopedInstance.h"
#include "CvPlot.h"

class CvLuaPlot : public CvLuaScopedInstance<CvLuaPlot, CvPlot>
{
public:
	static void PushMethods(lua_State* L, int t);
	static void HandleMissingInstance(lua_State* L);
	static const char* GetTypeName();
};
