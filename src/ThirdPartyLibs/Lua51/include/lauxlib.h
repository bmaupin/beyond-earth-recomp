#pragma once
extern "C++" {
int luaL_error(lua_State* L, const char* fmt, ...);
}
// TODO: Remaining Lua auxiliary-library declarations.