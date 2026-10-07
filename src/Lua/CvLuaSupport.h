#pragma once
#ifndef CVLUASUPPORT_H
#define CVLUASUPPORT_H

// Standard Lua includes
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};

// Fireworks Lua utilities
#include <Fireworks/FLua/Include/FLua.h>
#include <Fireworks/FLua/Include/FLuaFStringSupport.h>

// Utilities
#include "CvLuaArgsHandle.h"
// TODO: CvLuaSupport (remaining SDK declarations).

#endif //CVLUASUPPORT_H