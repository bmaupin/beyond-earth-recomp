// TODO: Phase1 CvLuaStaticInstance<CvLuaMap, CvMap>::pRegister(lua_State*): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 CvLuaStaticInstance<CvLuaGame, CvGame>::pRegister(lua_State*): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
#include <vector>
#include <cassert>
#include "CvGameCoreDLLUtil_Win32Headers.h"
#include "CvGameCoreDLLUtil/CvDLLUtilDefines.h"
#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvGameCoreEnums.h"
#include "CvGameCoreDLLUtil/include/CvString.h"
#include "CvStructs.h"
#include "Fireworks/FFreeListArrayBase.h"
#include "CvGameCoreDLLUtil/include/CvStructs.h"
#include "Fireworks/hash_map"
#include "CvGameDatabase/include/DatabaseResults.h"
#include "CvGameCoreDLLUtil/include/ICvDLLUtility.h"
#include "CvGameCoreDLLUtil/include/ICvDLLScriptSystem.h"
#include "CvGlobals.h"
#include "Fireworks/FAssert.h"
#include "Fireworks/FString.h"
#include "CvLuaSupport.h"
#include "CvLuaEnums.h"
#include "CvLuaFractal.h"
#include "CvLuaGameInfo.h"
#include "CvLuaMap.h"
#include "CvLuaGame.h"
#include "CvLuaPlayer.h"
class CvTeam;
#include "CvLuaTeam.h"
#include "CvLuaAliens.h"

// TODO: Phase1 luaL_optbool(lua_State*, int, bool): MISMATCH; Non-padding instruction count: BE 104, object 68; Civ5 changed/new instruction count unverified.
bool luaL_optbool(lua_State* L, int idx, bool defaultValue)
{
	// Pseudo-indices are outside the API stack; the current shared Lua helpers
	// incorrectly apply stack bounds to those objects and omit the lower bound.
	if(idx >= LUA_REGISTRYINDEX)
	{
		if(idx == 0)
			return defaultValue;
		if(idx > 0 && L->m_apistack.base + idx - 1 >= L->m_apistack.top)
			return defaultValue;
		if(idx < 0 && L->m_apistack.top + idx < L->m_apistack.base)
			return defaultValue;
	}
	HksObject* object = hks::indexToObject(L, idx);
	if((object->t & 15) == TNIL)
		return defaultValue;
	return (object->t & 15) != TBOOLEAN || object->v.boolean != 0;
}

// TODO: Phase1 LuaSupport::RegisterScriptData(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void LuaSupport::RegisterScriptData(lua_State* L)
{
	CvLuaEnums::Register(L);
	CvLuaFractal::Register(L);
	CvLuaGameInfo::Register(L);
	CvLuaMap::Register(L);
	CvLuaGame::Register(L);
	CvLuaPlayer::Register(L);
	CvLuaTeam::Register(L);
	CvLuaAliens::Register(L);
}

// TODO: Phase1 LuaSupport::DumpCallStack(lua_State*): MISMATCH; Non-padding instruction count: BE 97, object 80; Civ5 changed/new instruction count unverified.
void LuaSupport::DumpCallStack(lua_State* L)
{
	for(int i = 1; i < 10; ++i)
	{
		lua_Debug ar;
		if(lua_getstack(L, i, &ar))
		{
			lua_getinfo(L, "Sl", &ar);
			if(ar.currentline > 0)
			{
				FStringFixedBuffer(message, 512);
				message.Format("%s:%d\n", ar.source ? ar.source : "", ar.currentline);
				// Beyond Earth's Linux build formats the stack entry without an output call.
			}
		}
	}
}

// TODO: Phase1 LuaSupport::CallHook(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, bool&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool LuaSupport::CallHook(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, bool& value)
{
	// Release the game-core lock before Lua to avoid reversing the engine's lock order.
	bool hadLock = gDLL->HasGameCoreLock();
	if(hadLock)
		gDLL->ReleaseGameCoreLock();
	bool result = scriptSystem->CallHook(name, args, value);
	if(hadLock)
		gDLL->GetGameCoreLock();
	return result;
}

// TODO: Phase1 LuaSupport::CallFunction(ICvEngineScriptSystem1*, lua_State*, char const*, ICvEngineScriptSystemArgs1*, bool&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool LuaSupport::CallFunction(ICvEngineScriptSystem1* scriptSystem, lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, bool& value)
{
	bool hadLock = gDLL->HasGameCoreLock();
	if(hadLock)
		gDLL->ReleaseGameCoreLock();
	bool result = scriptSystem->CallFunction(L, name, args, value);
	if(hadLock)
		gDLL->GetGameCoreLock();
	return result;
}

// TODO: Phase1 LuaSupport::CallFunction(ICvEngineScriptSystem1*, lua_State*, char const*, ICvEngineScriptSystemArgs1*, int&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool LuaSupport::CallFunction(ICvEngineScriptSystem1* scriptSystem, lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, int& value)
{
	bool hadLock = gDLL->HasGameCoreLock();
	if(hadLock)
		gDLL->ReleaseGameCoreLock();
	bool result = scriptSystem->CallFunction(L, name, args, value);
	if(hadLock)
		gDLL->GetGameCoreLock();
	return result;
}

// TODO: Phase1 LuaSupport::CallFunction(ICvEngineScriptSystem1*, lua_State*, char const*, ICvEngineScriptSystemArgs1*, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool LuaSupport::CallFunction(ICvEngineScriptSystem1* scriptSystem, lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, std::string& value)
{
	bool hadLock = gDLL->HasGameCoreLock();
	if(hadLock)
		gDLL->ReleaseGameCoreLock();
	bool result = scriptSystem->CallFunction(L, name, args, value);
	if(hadLock)
		gDLL->GetGameCoreLock();
	return result;
}

// TODO: Phase1 LuaSupport::CallTestAll(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, bool&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool LuaSupport::CallTestAll(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, bool& value)
{
	bool hadLock = gDLL->HasGameCoreLock();
	if(hadLock)
		gDLL->ReleaseGameCoreLock();
	bool result = scriptSystem->CallTestAll(name, args, value);
	if(hadLock)
		gDLL->GetGameCoreLock();
	return result;
}

// TODO: Phase1 LuaSupport::CallTestAny(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, bool&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool LuaSupport::CallTestAny(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, bool& value)
{
	bool hadLock = gDLL->HasGameCoreLock();
	if(hadLock)
		gDLL->ReleaseGameCoreLock();
	bool result = scriptSystem->CallTestAny(name, args, value);
	if(hadLock)
		gDLL->GetGameCoreLock();
	return result;
}

// TODO: Phase1 LuaSupport::CallAccumulator(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, int&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool LuaSupport::CallAccumulator(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, int& value)
{
	bool hadLock = gDLL->HasGameCoreLock();
	if(hadLock)
		gDLL->ReleaseGameCoreLock();
	bool result = scriptSystem->CallAccumulator(name, args, value);
	if(hadLock)
		gDLL->GetGameCoreLock();
	return result;
}

// TODO: Phase1 LuaSupport::CallAccumulator(ICvEngineScriptSystem1*, char const*, ICvEngineScriptSystemArgs1*, float&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
bool LuaSupport::CallAccumulator(ICvEngineScriptSystem1* scriptSystem, const char* name, ICvEngineScriptSystemArgs1* args, float& value)
{
	bool hadLock = gDLL->HasGameCoreLock();
	if(hadLock)
		gDLL->ReleaseGameCoreLock();
	bool result = scriptSystem->CallAccumulator(name, args, value);
	if(hadLock)
		gDLL->GetGameCoreLock();
	return result;
}
