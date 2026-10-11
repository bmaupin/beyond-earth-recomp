#pragma once
#ifndef ICVDLLSCRIPTSYSTEM_H
#define ICVDLLSCRIPTSYSTEM_H

#include <string>

struct lua_State;
class ICvEngineScriptSystemArgs1
{
public:
 enum ArgType { ARGTYPE_NONE, ARGTYPE_NULL, ARGTYPE_BOOL, ARGTYPE_STRING, ARGTYPE_INT, ARGTYPE_FLOAT };
 virtual ~ICvEngineScriptSystemArgs1() {}
 virtual unsigned int Push(bool value) = 0;
 virtual unsigned int Push(const char* value, size_t length) = 0;
 virtual unsigned int Push(int value) = 0;
 virtual unsigned int Push(float value) = 0;
 virtual unsigned int PushNULL() = 0;
 virtual unsigned int Count() = 0;
 virtual ArgType GetType(unsigned int index) = 0;
 virtual bool GetBool(unsigned int index, bool& value) = 0;
 virtual bool GetFloat(unsigned int index, float& value) = 0;
 virtual bool GetInt(unsigned int index, int& value) = 0;
 virtual bool GetString(unsigned int index, char*& value) = 0;
};

// Beyond Earth script-system vtable prefix through the event dispatch methods.
// SAL annotations from the Windows SDK declarations are omitted on Linux.
class ICvEngineScriptSystem1
{
public:
	virtual lua_State* CreateLuaThread(const char* szName) = 0;
	virtual void FreeLuaThread(lua_State*) = 0;

	// File IO
	virtual bool LoadFile(lua_State* L, const char* szFilename) = 0;

	virtual bool CallCFunction(lua_State* L, int (*pfn)(lua_State*), void* pArgs) = 0;
	virtual bool CallFunction(lua_State* L, unsigned int iArgs, unsigned int iResults) = 0;

	// Unidentified Beyond Earth slot at 0x14; keeps the argument factory ABI intact.
	virtual void ReservedScriptMethod() = 0;

	//Arguments
	virtual ICvEngineScriptSystemArgs1* CreateArgs() = 0;
	virtual ICvEngineScriptSystemArgs1* CreateArgs(uint uiReserve) = 0;
	virtual void DestroyArgs(ICvEngineScriptSystemArgs1* pkArgs) = 0;

	virtual bool CallFunction(lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, bool& value) = 0;
	virtual bool CallFunction(lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, int& value) = 0;
	virtual bool CallFunction(lua_State* L, const char* name, ICvEngineScriptSystemArgs1* args, std::string& value) = 0;
	virtual bool CallHook(const char* name, ICvEngineScriptSystemArgs1* args, bool& value) = 0;
	virtual bool CallAccumulator(const char* name, ICvEngineScriptSystemArgs1* args, int& value) = 0;
	virtual bool CallAccumulator(const char* name, ICvEngineScriptSystemArgs1* args, float& value) = 0;
	virtual bool CallTestAll(const char* name, ICvEngineScriptSystemArgs1* args, bool& value) = 0;
	virtual bool CallTestAny(const char* name, ICvEngineScriptSystemArgs1* args, bool& value) = 0;
};

#endif //ICVDLLSCRIPTSYSTEM_H