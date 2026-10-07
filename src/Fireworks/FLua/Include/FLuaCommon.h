// Copyright (c) 2009 Firaxis Games, Inc. All rights reserved.
#pragma once

namespace Lua
{
	namespace Details
	{
		// CCallWithErrorHandling - Make a lua protected call to a c function with error handling automatically provided.
		bool CCallWithErrorHandling(lua_State* L, lua_CFunction pfn, void* pvUserData = NULL);
		// TODO: Lua::Details (remaining declarations).
	}
}

// Compatibility name for SDK headers; the target's wrapper symbols use Lua.
namespace FLua = Lua;