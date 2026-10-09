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
		if(idx == LUA_ENVIRONINDEX)
		{
			cclosure* closure = (L->m_apistack.base - 1)->v.cClosure;
			L->m_cEnv.v.table = closure->m_env;
			L->m_cEnv.t = TTABLE;
			return &L->m_cEnv;
		}
		cclosure* closure = (L->m_apistack.base - 1)->v.cClosure;
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
inline void hksi_lua_setfield(lua_State* L, int idx, const char* key)
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

// Havok names C closures for debugging; preserve the macro-expanded function name.
void hks_pushnamedcclosure(lua_State* L, lua_CFunction fn, int n, const char* name, int flags);
#define HKS_STRINGIFY_IMPL(x) #x
#define HKS_STRINGIFY(x) HKS_STRINGIFY_IMPL(x)
#define lua_pushcclosure(L, fn, n) hks_pushnamedcclosure(L, fn, n, HKS_STRINGIFY(fn), 0)
#define lua_setfield hksi_lua_setfield

HksNumber hks_obj_tonumber(lua_State* L, const HksObject* obj);
inline lua_Integer lua_tointeger(lua_State* L, int idx)
{
	HksObject* obj = hks::indexToObject(L, idx);
	return obj < L->m_apistack.top ? (lua_Integer)hks_obj_tonumber(L, obj) : 0;
}
inline bool lua_toboolean(lua_State* L, int idx)
{
	HksObject* obj = hks::indexToObject(L, idx);
	return obj < L->m_apistack.top && (obj->t & 15) != TNIL &&
		((obj->t & 15) != TBOOLEAN || obj->v.boolean != 0);
}
inline void lua_pushboolean(lua_State* L, int value)
{
	HksObject* top = L->m_apistack.top;
	top->v.boolean = value != 0;
	top->t = TBOOLEAN;
	L->m_apistack.top = top + 1;
}

#define lua_newtable(L) lua_createtable(L, 0, 0)
#define lua_setglobal(L,s) lua_setfield(L, LUA_GLOBALSINDEX, (s))
#define LUA_TTABLE TTABLE
#define LUA_TUSERDATA TUSERDATA

inline void lua_settop(lua_State* L, int idx);
#define lua_pop(L,n) lua_settop(L, -(n)-1)
HksObject hks_obj_getfield(lua_State* L, HksObject table, HksObject key);
void* lua_newuserdata(lua_State* L, size_t size);
int hks_obj_setmetatable(lua_State* L, const HksObject* obj, const HksObject* metatable);

inline void lua_getfield(lua_State* L, int idx, const char* key)
{
	HksObject value;
	HksObject table = *hks::indexToObject(L, idx);
	lua_pushstring(L, key);
	value = hks_obj_getfield(L, table, L->m_apistack.top[-1]);
	lua_pop(L, 1);
	HksObject* top = L->m_apistack.top;
	*top = value;
	L->m_apistack.top = top + 1;
}
inline bool lua_isnil(lua_State* L, int idx)
{
	HksObject* obj = hks::indexToObject(L, idx);
	return (idx > 0 ? obj < L->m_apistack.top : obj >= L->m_apistack.base) && (obj->t & 15) == TNIL;
}
inline void lua_settop(lua_State* L, int idx)
{
	if(idx >= 0)
	{
		HksObject* newtop = L->m_apistack.base + idx;
		HksObject* top = L->m_apistack.top;
		while(top < newtop)
		{
			top->t = TNIL;
			++top;
		}
		L->m_apistack.top = newtop;
	}
	else
		L->m_apistack.top += idx + 1;
}
inline void* lua_touserdata(lua_State* L, int idx)
{
	HksObject* obj = hks::indexToObject(L, idx);
	if(obj < L->m_apistack.top)
	{
		if((obj->t & 15) == TUSERDATA)
			return reinterpret_cast<char*>(obj->v.userData) + sizeof(hks::UserData) - 4;
		if((obj->t & 15) == TLIGHTUSERDATA)
			return obj->v.ptr;
	}
	return NULL;
}
inline HksNumber lua_tonumber(lua_State* L, int idx)
{
	HksObject* obj = hks::indexToObject(L, idx);
	return obj < L->m_apistack.top ? hks_obj_tonumber(L, obj) : 0;
}
inline void lua_pushnumber(lua_State* L, HksNumber value)
{
	HksObject* top = L->m_apistack.top;
	top->v.number = value;
	top->t = TNUMBER;
	L->m_apistack.top = top + 1;
}
inline int lua_setmetatable(lua_State* L, int idx)
{
	HksObject* obj = hks::indexToObject(L, idx);
	if(obj >= L->m_apistack.base && obj < L->m_apistack.top)
	{
		int result = hks_obj_setmetatable(L, obj, L->m_apistack.top - 1);
		--L->m_apistack.top;
		return result;
	}
	return 0;
}
#define lua_getglobal(L,s) lua_getfield(L, LUA_GLOBALSINDEX, (s))
// TODO: Remaining Havok Script API; external VM functions are declarations only.