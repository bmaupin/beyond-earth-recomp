#ifndef FFAST_ALLOCATOR_H
#define FFAST_ALLOCATOR_H

#include <cassert>
#include "FFastVector.h"

template<class T, bool bPODType = false,
	unsigned int AllocPool = c_eMPoolTypeContainer, unsigned int nSubID = 0,
	class BASE_ALLOC = typename BaseVector<T, bPODType>::FDefaultFastVectorAllocator>
class FFastAllocator
{
	static const unsigned int ms_uiAnchorNodeIndex = 0x0fffffff;
protected:
	typedef FFastVector<T, bPODType, AllocPool, nSubID, BASE_ALLOC> VectorType;
public:
	FFastAllocator() : m_uiFirstEmpty(ms_uiAnchorNodeIndex), m_uiSize(0) {};
	FFastAllocator(unsigned int uiReserve)
		: m_vec(uiReserve), m_uiFirstEmpty(ms_uiAnchorNodeIndex), m_uiSize(0) {};
	~FFastAllocator() { assert(m_uiSize == 0); };

	T& operator[](unsigned int ui) { return m_vec[ui]; };
	const T& operator[](unsigned int ui) const { return m_vec[ui]; };
	unsigned int size() const { return m_uiSize; };
	void clear()
	{
		m_uiFirstEmpty = ms_uiAnchorNodeIndex;
		m_vec.clear();
		m_uiSize = 0;
	};

protected:
	unsigned int m_uiFirstEmpty;
	unsigned int m_uiSize;
	VectorType m_vec;
	// TODO: FFastAllocator allocation, recycling, and remaining SDK methods.
};

#endif
