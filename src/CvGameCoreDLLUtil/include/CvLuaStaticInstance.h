#pragma once

#include "Lua/CvLuaSupport.h"
#include "CvLuaMethodWrapper.h"

template<class Derived, class InstanceType>
class CvLuaStaticInstance : public CvLuaMethodWrapper<Derived, InstanceType>
{
public:
	static void Register(lua_State* L)
	{
		FLua::Details::CCallWithErrorHandling(L, pRegister);
	}

	static const int GetStartingArgIndex() { return 1; }

protected:
	static int pRegister(lua_State* L)
	{
		const char* name = Derived::GetInstanceName();
		lua_getglobal(L, name);
		if(lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			lua_newtable(L);
			lua_pushvalue(L, -1);
			lua_setglobal(L, name);
		}
		Derived::RegisterMembers(L);
		return 0;
	}

	static void RegisterMethod(lua_State* L, lua_CFunction func, const char* name)
	{
		lua_pushcclosure(L, func, 0);
		lua_setfield(L, -2, name);
	}
};
