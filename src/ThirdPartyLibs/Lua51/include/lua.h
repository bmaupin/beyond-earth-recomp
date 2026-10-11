/* Preserve the SDK include path, but use Beyond Earth's Havok Script API. */
#ifndef lua_h
#define lua_h

// CvLuaSupport retains the Civ 5 extern "C" include block. Havok's API and
// runtime entry points have C++ linkage in the Linux Beyond Earth game core.
extern "C++" {
#include <ThirdPartyLibs/HavokScript/include/hksApi.h>

// Havok retains the Lua 5.1 debug prefix but expands the source buffer to 512.
struct lua_Debug
{
	int event;
	const char* name;
	const char* namewhat;
	const char* what;
	const char* source;
	int currentline;
	int nups;
	int linedefined;
	int lastlinedefined;
	char short_src[512];
	int i_ci;
};

int lua_getstack(lua_State* L, int level, lua_Debug* ar);
int lua_getinfo(lua_State* L, const char* what, lua_Debug* ar);
}
#endif