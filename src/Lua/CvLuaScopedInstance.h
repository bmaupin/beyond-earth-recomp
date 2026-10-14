#pragma once
#include "CvLuaMethodWrapper.h"

template<class Derived, class InstanceType>
class CvLuaScopedInstance : public CvLuaMethodWrapper<Derived, InstanceType>
{
public:
	// TODO: Push overloads and GetInstance implementation.
	static InstanceType* GetInstance(lua_State* L, int idx = 1, bool bErrorOnFail = true);
	static const int GetStartingArgIndex();

protected:
	static void DefaultHandleMissingInstance(lua_State* L)
	{
		luaL_error(L, "Instance does not exist.");
	}
};

template<class Derived, class InstanceType>
const int CvLuaScopedInstance<Derived, InstanceType>::GetStartingArgIndex()
{
	return 2;
}
