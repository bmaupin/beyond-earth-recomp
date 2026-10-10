#pragma once
extern "C++" {
int luaL_error(lua_State* L, const char* fmt, ...);
void luaL_checktype(lua_State* L, int idx, int type);
lua_Integer luaL_checkinteger(lua_State* L, int idx);
const char* luaL_checklstring(lua_State* L, int idx, size_t* length);
lua_Integer luaL_optinteger(lua_State* L, int idx, lua_Integer value);
}
#define luaL_optint(L,n,d) ((int)luaL_optinteger(L, (n), (d)))
#define luaL_checkstring(L,n) luaL_checklstring(L, (n), NULL)
// TODO: Remaining Lua auxiliary-library declarations.