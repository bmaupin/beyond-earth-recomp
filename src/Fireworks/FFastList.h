#ifndef FAST_LIST
#define FAST_LIST

#include <iterator>
#include "FFastAllocator.h"

#define ANCHOR_NODE_INDEX 0x0fffffff
#define DELETED_MASK (0x80000000)

struct ListNode
{
	unsigned int uiNext;
	unsigned uiPrev : 31;
	unsigned bValid : 1;
};

struct NullMultiListNodePolicy
{
	ListNode node;
	unsigned int LIST_GetNext() const { return node.uiNext; };
	unsigned int LIST_GetPrev() const { return node.uiPrev; };
	void LIST_SetNext(unsigned int uiNodeIndex) { node.uiNext = uiNodeIndex; };
	void LIST_SetPrev(unsigned int uiNodeIndex) { node.uiPrev = uiNodeIndex; };
	bool LIST_GetDeleted() const { return !node.bValid; };
	void LIST_SetDeleted(bool bDeleted) { node.bValid = !bDeleted; };
	unsigned int ALLOC_GetNext() const { return node.uiNext; };
	void ALLOC_SetNext(unsigned int uiNodeIndex) { node.uiNext = uiNodeIndex; };
	bool ALLOC_GetDeleted() const { return LIST_GetDeleted(); };
	void ALLOC_SetDeleted(bool bDeleted) { LIST_SetDeleted(bDeleted); };
};

template<class T> struct MultiListNodePolicy : public NullMultiListNodePolicy
{
	MultiListNodePolicy() {};
	MultiListNodePolicy(const T& x) : data(x) {};
	T data;
};

template<class T_ALLOCATOR> class FCustomList_Tail_Member
{
protected:
	typedef FCustomList_Tail_Member<T_ALLOCATOR> TYPE;
	FCustomList_Tail_Member() {};
	FCustomList_Tail_Member(unsigned int uiCapacity) : m_kAllocator(uiCapacity) {};
	~FCustomList_Tail_Member() { m_kAllocator.clear(); };
	T_ALLOCATOR m_kAllocator;
public:
	const T_ALLOCATOR& get_allocator() const { return m_kAllocator; };
	T_ALLOCATOR& get_allocator() { return m_kAllocator; };
	// TODO: FCustomList_Tail_Member SDK copy operations.
};

template<class T, class T_ALLOCATOR, class TAIL> class FCustomList_Core : public TAIL
{
public:
	typedef FCustomList_Core<T, T_ALLOCATOR, TAIL> TYPE;
	class base_iterator_tail_const
	{
	public:
		base_iterator_tail_const(const TYPE* pFastList) : m_pFastList(pFastList) {};
		const TYPE* m_pFastList;
	};
	class base_iterator_tail
	{
	public:
		base_iterator_tail(TYPE* pFastList) : m_pFastList(pFastList) {};
		TYPE* m_pFastList;
	};

	template<class ITERATOR_TAIL> class base_iterator
		: public std::iterator<std::bidirectional_iterator_tag, MultiListNodePolicy<T> >,
		  public ITERATOR_TAIL
	{
	public:
		using ITERATOR_TAIL::m_pFastList;
		explicit base_iterator() : ITERATOR_TAIL(NULL), m_uiCurrPos(ANCHOR_NODE_INDEX) {};
		explicit base_iterator(unsigned int uiPos, TYPE* pVec)
			: ITERATOR_TAIL(pVec), m_uiCurrPos(uiPos) {};
		explicit base_iterator(unsigned int uiPos, const TYPE* pVec)
			: ITERATOR_TAIL(pVec), m_uiCurrPos(uiPos) {};
		~base_iterator() {};
		const base_iterator operator++(int)
		{
			base_iterator temp = *this;
			++(*this);
			return temp;
		};
		base_iterator& operator++()
		{
			if (m_uiCurrPos == ANCHOR_NODE_INDEX)
				m_uiCurrPos = m_pFastList->m_uiFirst;
			else
				m_uiCurrPos = m_pFastList->get_allocator()[m_uiCurrPos].LIST_GetNext();
			return *this;
		};
		bool operator==(const base_iterator& rhs) const { return m_uiCurrPos == rhs.m_uiCurrPos; };
		bool operator!=(const base_iterator& rhs) const { return m_uiCurrPos != rhs.m_uiCurrPos; };
		unsigned int get_index() const { return m_uiCurrPos; };
	protected:
		unsigned int m_uiCurrPos;
		friend class FCustomList_Core;
		// TODO: base_iterator decrement, prefetch, and validity SDK methods.
	};

	class iterator : public base_iterator<base_iterator_tail>
	{
	public:
		typedef base_iterator<base_iterator_tail> BASE;
		explicit iterator() {};
		explicit iterator(unsigned int uiPos, TYPE* pVec) : BASE(uiPos, pVec) {};
		~iterator() {};
		T& operator*() { return this->m_pFastList->get_allocator()[this->m_uiCurrPos]; };
		T* operator->() { return &this->m_pFastList->get_allocator()[this->m_uiCurrPos]; };
	};
	class const_iterator : public base_iterator<base_iterator_tail_const>
	{
	public:
		typedef base_iterator<base_iterator_tail_const> BASE;
		explicit const_iterator() {};
		explicit const_iterator(unsigned int uiPos, const TYPE* pVec) : BASE(uiPos, pVec) {};
		~const_iterator() {};
		const T& operator*() const { return this->m_pFastList->get_allocator()[this->m_uiCurrPos]; };
		const T* operator->() const { return &this->m_pFastList->get_allocator()[this->m_uiCurrPos]; };
	};

	bool empty() const { return m_uiSize == 0; };
	unsigned int size() const { return m_uiSize; };
protected:
	explicit FCustomList_Core()
		: TAIL(), m_uiSize(0), m_uiFirst(ANCHOR_NODE_INDEX), m_uiLast(ANCHOR_NODE_INDEX) {};
	explicit FCustomList_Core(unsigned int uiCapacity)
		: TAIL(uiCapacity), m_uiSize(0), m_uiFirst(ANCHOR_NODE_INDEX), m_uiLast(ANCHOR_NODE_INDEX) {};
	unsigned int m_uiSize, m_uiFirst, m_uiLast;
	// TODO: FCustomList_Core mutation, copy, and remaining SDK methods.
};

template<class T, class T_ALLOCATOR = FFastAllocator<T>, bool bReferenceToAlloc = false>
class FCustomList : public FCustomList_Core<T, T_ALLOCATOR, FCustomList_Tail_Member<T_ALLOCATOR> >
{
public:
	typedef FCustomList<T, T_ALLOCATOR> TYPE;
	typedef FCustomList_Core<T, T_ALLOCATOR, FCustomList_Tail_Member<T_ALLOCATOR> > CORE;
	typedef FCustomList_Tail_Member<T_ALLOCATOR> TAIL;
	FCustomList() : CORE() {};
	FCustomList(unsigned int uiCapacity) : CORE(uiCapacity) {};
	// TODO: FCustomList SDK copy operations and reference-allocator specialization.
};

template<class T, unsigned int AllocPool = c_eMPoolTypeContainer, unsigned int SubID = 0>
class FFastList : protected FCustomList<MultiListNodePolicy<T>, FFastAllocator<MultiListNodePolicy<T>, false, AllocPool, SubID> >
{
public:
	typedef FFastList<T, AllocPool, SubID> TYPE;
	typedef FFastAllocator<MultiListNodePolicy<T>, false, AllocPool, SubID> ALLOC_TYPE;
	typedef FCustomList<MultiListNodePolicy<T>, ALLOC_TYPE> BASE_TYPE;

	class iterator : public BASE_TYPE::iterator
	{
	public:
		explicit iterator() {};
		explicit iterator(unsigned int uiPos, TYPE* pVec) : BASE_TYPE::iterator(uiPos, (BASE_TYPE*)pVec) {};
		~iterator() {};
		T& operator*() { return BASE_TYPE::iterator::operator*().data; };
		T* operator->() { return &BASE_TYPE::iterator::operator*().data; };
	};
	class const_iterator : public BASE_TYPE::const_iterator
	{
	public:
		explicit const_iterator() {};
		explicit const_iterator(unsigned int uiPos, const TYPE* pVec) : BASE_TYPE::const_iterator(uiPos, (const BASE_TYPE*)pVec) {};
		~const_iterator() {};
		const T& operator*() const { return BASE_TYPE::const_iterator::operator*().data; };
		const T* operator->() const { return &BASE_TYPE::const_iterator::operator*().data; };
	};

	explicit FFastList() : BASE_TYPE() {};
	explicit FFastList(unsigned int uiCapacity) : BASE_TYPE(uiCapacity) {};
	bool empty() const { return BASE_TYPE::empty(); };
	unsigned int size() const { return BASE_TYPE::size(); };
	iterator begin() { return iterator(this->m_uiFirst, this); };
	iterator end() { return iterator(ANCHOR_NODE_INDEX, this); };
	const_iterator begin() const { return const_iterator(this->m_uiFirst, this); };
	const_iterator end() const { return const_iterator(ANCHOR_NODE_INDEX, this); };
	const_iterator begin_const() const { return const_iterator(this->m_uiFirst, this); };
	const_iterator end_const() const { return const_iterator(ANCHOR_NODE_INDEX, this); };
	// TODO: FFastList mutation, copy, and remaining SDK methods.
};

#endif
