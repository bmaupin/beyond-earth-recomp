#pragma once

struct lua_State;

class CvLuaPlayer
{
public:
	static void Register(lua_State* L);
};
