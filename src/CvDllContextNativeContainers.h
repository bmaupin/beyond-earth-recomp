#pragma once

#include "CvCityNativeContainers.h"

namespace ASL { namespace StdLib { namespace UnorderedSet {
template<class Key> struct hash {};
template<bool Multi, class Key, class Equal> class _Hash_oper2 {};
template<bool Multi, class Key, class Hasher, class Equal>
class _Hash_oper1 : public _Hash_oper2<Multi, Key, Equal> {};
template<class Key, class Hasher, class Equal>
class _Uhash_compare : public _Hash_oper1<false, Key, Hasher, Equal> {};
template<class Key, class Compare, class Alloc, bool Multi>
class _Uset_traits : public Compare
{
public:
	typedef Key key_type;
	typedef Compare key_compare;
	typedef Key value_type;
	typedef Alloc allocator_type;
};
template<class Traits> class _Hash : public Traits
{
	std::list<typename Traits::value_type, typename Traits::allocator_type> _List;
	std::vector<typename std::list<typename Traits::value_type, typename Traits::allocator_type>::iterator> _Vec;
	unsigned int _Mask;
	unsigned int _Maxidx;
	float _Max_bucket_size;
};
template<class Key, class Hasher = hash<Key>, class Equal = std::equal_to<Key>,
	class Alloc = std::allocator<Key> >
class unordered_set : public _Hash<_Uset_traits<Key, _Uhash_compare<Key, Hasher, Equal>, Alloc, false> > {};
}}}

enum PlayerVoteTypes { PLAYER_VOTE_NEVER = -5, PLAYER_VOTE_ABSTAIN,
	PLAYER_VOTE_NO, PLAYER_VOTE_YES, NO_PLAYER_VOTE };

template<class T> class FFreeListArrayBase
{
public:
	virtual ~FFreeListArrayBase();
	virtual void Init(int);
	virtual void Uninit();
	virtual T* GetAt(int);
	virtual const T* GetAt(int) const;
	virtual void RemoveAll();
protected:
	virtual void GrowArray();
	int m_iFreeListHead;
	int m_iFreeListCount;
	int m_iLastIndex;
	int m_iNumSlots;
};
template<class T> class FFreeListTrashArray : public FFreeListArrayBase<T>
{
	struct FFreeListTrashArrayNode;
	int m_iCurrentID;
	FFreeListTrashArrayNode* m_pArray;
};

namespace Firaxis {
template<class T, int N> class Array
{
	T m_akItems[N];
};
}

template<int Pool, int SubID, int Flags> struct FAllocBase
{
	unsigned char* m_pData;
};
template<class T, class Base> struct FAllocArrayType : protected Base {};
template<class T, class Base> struct FAllocArray2DType : protected Base {};
