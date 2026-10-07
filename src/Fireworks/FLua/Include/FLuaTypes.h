// Copyright (c) 2009 Firaxis Games, Inc. All rights reserved.
#pragma once
#ifndef FLuaTypes_h
#define FLuaTypes_h

#include "FLuaCommon.h"

namespace Lua
{
	class Value
	{
	public:
		Value();
		Value(lua_State* L, int iStackIndex);
		~Value();
		inline lua_State* GetLuaState() const { return m_pkLuaState; }
		// TODO: FLua::Value (remaining SDK methods).
	private:
		lua_State* m_pkLuaState;
		int m_iRef;
	};

	class Table
	{
	public:
		Table(lua_State* L, int iStackIndex) : m_kLuaVal(L, iStackIndex) {}
		~Table() {}
		inline lua_State* GetLuaState() const { return m_kLuaVal.GetLuaState(); }

		// Represents a field for the [const char*] operator
		class Field
		{
		private:
			friend class Table;
			// TODO: FLua::Table::Field constructor (SDK template body).
			template<class T> Field(const Table& kTable, T key);
		public:
			template<class T> inline const Field& operator=(T val) { m_kTable.SetField<T>(m_kKey, val); return *this; }
		private:
			Table& m_kTable;
			Value m_kKey;
		};

		// [] operators
		template<class T> inline Field operator[](T key) { return Field(*this, key); }
		// TODO: FLua::Table::SetField (SDK template body).
		template<class T> void SetField(const Value& kKey, T val);
		// TODO: FLua::Table (remaining SDK methods).
	private:
		Value m_kLuaVal;
	};
}

#endif //FLuaTypes_h