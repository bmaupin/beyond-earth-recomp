// TODO: Phase1 CvLuaStaticInstance<CvLuaMap, CvMap>::pRegister(lua_State*): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 CvLuaStaticInstance<CvLuaGame, CvGame>::pRegister(lua_State*): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
#pragma once
#ifndef CVLUASUPPORT_H
#define CVLUASUPPORT_H

// Standard Lua includes
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};

// Fireworks Lua utilities
#include <Fireworks/FLua/Include/FLua.h>
#include <Fireworks/FLua/Include/FLuaFStringSupport.h>

// Utilities
#include "CvLuaArgsHandle.h"
#include <string>

class ICvEngineScriptSystem1;
class ICvEngineScriptSystemArgs1;

namespace LuaSupport
{
// TODO: Phase1 LuaSupport::RegisterScriptData(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	void RegisterScriptData(lua_State* L);
// TODO: Phase1 LuaSupport::DumpCallStack(lua_State*): MISMATCH; Non-padding instruction count: BE 97, object 80; Civ5 changed/new instruction count unverified.
	void DumpCallStack(lua_State* L);

// TODO: Phase1 LuaSupport::CallHook(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, bool&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool CallHook(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, bool& value);
// TODO: Phase1 LuaSupport::CallFunction(ICvEngineScriptSystem1*, lua_State*, char const*, ICvEngineScriptSystemArgs1*, bool&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool CallFunction(ICvEngineScriptSystem1* scriptSystem, lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, bool& value);
// TODO: Phase1 LuaSupport::CallFunction(ICvEngineScriptSystem1*, lua_State*, char const*, ICvEngineScriptSystemArgs1*, int&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool CallFunction(ICvEngineScriptSystem1* scriptSystem, lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, int& value);
// TODO: Phase1 LuaSupport::CallFunction(ICvEngineScriptSystem1*, lua_State*, char const*, ICvEngineScriptSystemArgs1*, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool CallFunction(ICvEngineScriptSystem1* scriptSystem, lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, std::string& value);
// TODO: Phase1 LuaSupport::CallTestAll(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, bool&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool CallTestAll(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, bool& value);
// TODO: Phase1 LuaSupport::CallTestAny(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, bool&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool CallTestAny(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, bool& value);
// TODO: Phase1 LuaSupport::CallAccumulator(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, int&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool CallAccumulator(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, int& value);
// TODO: Phase1 LuaSupport::CallAccumulator(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, float&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
	bool CallAccumulator(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, float& value);
}

// TODO: Phase1 luaL_optbool(lua_State*, int, bool): MISMATCH; Non-padding instruction count: BE 104, object 68; Civ5 changed/new instruction count unverified.
bool luaL_optbool(lua_State* L, int idx, bool defaultValue);

#endif //CVLUASUPPORT_H
