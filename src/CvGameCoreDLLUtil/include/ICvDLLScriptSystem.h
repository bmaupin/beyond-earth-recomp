#pragma once
#ifndef ICVDLLSCRIPTSYSTEM_H
#define ICVDLLSCRIPTSYSTEM_H

struct lua_State;
class ICvEngineScriptSystemArgs1;

// Partial SDK interface prefix required by CvLuaArgsHandle.
// TODO: ICvEngineScriptSystemArgs1 (only an opaque pointer is required here).
// TODO: ICvEngineScriptSystem1 (remaining methods and Beyond Earth differences).
// SAL annotations from the Windows SDK declarations are omitted on Linux.
class ICvEngineScriptSystem1
{
public:
	virtual lua_State* CreateLuaThread(const char* szName) = 0;
	virtual void FreeLuaThread(lua_State*) = 0;

	// File IO
	virtual bool LoadFile(lua_State* L, const char* szFilename) = 0;

	// TODO: Identify Beyond Earth's additional virtual method before CreateArgs.

	//Arguments
	virtual ICvEngineScriptSystemArgs1* CreateArgs() = 0;
	virtual ICvEngineScriptSystemArgs1* CreateArgs(uint uiReserve) = 0;
	virtual void DestroyArgs(ICvEngineScriptSystemArgs1* pkArgs) = 0;
};

#endif //ICVDLLSCRIPTSYSTEM_H