#pragma once

class CvCity;

class CvLuaCity
{
public:
	static void Push(lua_State* L, CvCity* pCity);
};
