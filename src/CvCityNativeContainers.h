#pragma once

#include "Fireworks/FFastVector.h"
#include "Fireworks/hash_map"
#include <list>
#include <vector>
#include <functional>

struct OperationSlot
{
	int m_iOperationID;
	int m_iArmyID;
	int m_iSlotID;
};

struct GenericYieldHealthChange
{
	int m_yieldChanges[7];
	int m_healthChange;
};

struct OrderData
{
	OrderTypes eOrderType;
	int iPlotIndex;
	int iSpecificType;
	int iData2;
	bool bSave;
	bool bRush;
};

// FFastSmallFixedList is declared in its SDK home, Fireworks/FFastVector.h.

namespace ASL { namespace StdLib { namespace HashMap {
template<class T> struct hash {};
template<bool Multi, class Key, class Equal> class _Hash_oper2 {};
template<bool Multi, class Key, class Hasher, class Equal>
class _Hash_oper1 : public _Hash_oper2<Multi, Key, Equal> {};
template<class Key, class Hasher, class Equal>
class _Uhash_compare : public _Hash_oper1<false, Key, Hasher, Equal> {};
template<class Key, class Value, class Compare, class Alloc, bool Multi>
class _Umap_traits : public Compare
{
public:
	typedef Key key_type;
	typedef Compare key_compare;
	typedef std::pair<const Key, Value> value_type;
	typedef Alloc allocator_type;
};
template<class Key, class Value, class Hasher = hash<Key>, class Equal = std::equal_to<Key>,
	class Alloc = std::allocator<std::pair<const Key, Value> > >
class unordered_map : public _Hash<_Umap_traits<Key, Value, _Uhash_compare<Key, Hasher, Equal>, Alloc, false> > {};
}}}
