// Minimal inline API reconstructed from CvLuaGameInfo's target instructions.
#pragma once
#include "hksStruct.h"
#include <string.h>

#define LUA_REGISTRYINDEX (-10000)
#define LUA_ENVIRONINDEX (-10001)
#define LUA_GLOBALSINDEX (-10002)

void lua_createtable(lua_State* L, int narr, int nrec);
void hksi_lua_pushlstring(lua_State* L, const char* str, size_t len);
void hks_obj_settable(lua_State* L, const HksObject* table, const HksObject* key, const HksObject* value);
void hks_obj_rawseti(lua_State* L, const HksObject* table, int index, const HksObject* value);

namespace hks
{
	inline HksObject* indexToObject(lua_State* L, int idx)
	{
		if(idx > LUA_REGISTRYINDEX)
			return idx > 0 ? L->m_apistack.base + idx - 1 : L->m_apistack.top + idx;
		if(idx == LUA_GLOBALSINDEX)
			return &L->globals;
		if(idx == LUA_REGISTRYINDEX)
			return &L->m_global->m_registry;
		cclosure* closure = (L->m_apistack.base - 1)->v.cClosure;
		if(idx == LUA_ENVIRONINDEX)
		{
			L->m_cEnv.v.table = closure->m_env;
			L->m_cEnv.t = TTABLE;
			return &L->m_cEnv;
		}
		return &closure->m_upvalues[LUA_GLOBALSINDEX - idx - 1];
	}
	inline void reserveApiStack(lua_State* L)
	{
		if(L->m_apistack.top + 2 > L->m_apistack.alloc_top)
			L->m_callStack.growApiStack(L, 2);
	}
}

inline int lua_gettop(lua_State* L)
{
	return L->m_apistack.top - L->m_apistack.base;
}
inline void lua_pushvalue(lua_State* L, int idx)
{
	HksObject* top = L->m_apistack.top;
	*top = *hks::indexToObject(L, idx);
	L->m_apistack.top = top + 1;
}
inline void lua_pushinteger(lua_State* L, lua_Integer n)
{
	HksObject* top = L->m_apistack.top;
	top->v.number = n;
	top->t = TNUMBER;
	L->m_apistack.top = top + 1;
}
inline void lua_pushstring(lua_State* L, const char* str)
{
	if(str)
		hksi_lua_pushlstring(L, str, strlen(str));
	else
	{
		L->m_apistack.top->t = TNIL;
		++L->m_apistack.top;
	}
}
inline void lua_setfield(lua_State* L, int idx, const char* key)
{
	hks::reserveApiStack(L);
	lua_pushstring(L, key);
	HksObject* top = L->m_apistack.top;
	HksObject value = top[-1];
	top[-1] = top[-2];
	top[-2] = value;
	L->m_apistack.top = top;
	hks_obj_settable(L, hks::indexToObject(L, idx < 0 && idx > LUA_REGISTRYINDEX ? idx - 1 : idx), top - 2, top - 1);
	L->m_apistack.top -= 2;
}
inline void lua_rawseti(lua_State* L, int idx, int n)
{
	hks_obj_rawseti(L, hks::indexToObject(L, idx), n, L->m_apistack.top - 1);
	--L->m_apistack.top;
}

#define lua_newtable(L) lua_createtable(L, 0, 0)
#define lua_setglobal(L,s) lua_setfield(L, LUA_GLOBALSINDEX, (s))
// TODO: Remaining Havok Script API; external VM functions are declarations only.