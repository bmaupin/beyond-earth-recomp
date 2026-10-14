#pragma once
extern "C++" {
int luaL_error(lua_State* L, const char* fmt, ...);
void luaL_checktype(lua_State* L, int idx, int type);
lua_Integer luaL_optinteger(lua_State* L, int idx, lua_Integer value);
}
#define luaL_optint(L,n,d) ((int)luaL_optinteger(L, (n), (d)))
// TODO: Remaining Lua auxiliary-library declarations.