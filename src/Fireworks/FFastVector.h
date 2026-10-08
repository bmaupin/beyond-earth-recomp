/*
Fast vector class designed to be as simple as possible
while retaining the basic behavior of std::vector.  This class
should really only be used for very simple classes and structures,
since the only benefit is speed for handling large numbers of elements.
It supports standard iterators through pointer functionality.

Author: John Kloetzli
9/9/2008

version 1.3
*/
#pragma once

#include "vector"
#include "FAssert.h"
#include "new"
#include "iterator"

// Partial SDK container definitions.
template<class T, bool bPODType> class BaseVector
{
public:
	~BaseVector(){};
	void clear(){
		Destroy(m_pData, m_uiCurrSize);
		m_uiCurrSize = 0;
	};
	T& operator[](unsigned int ui) {
		FAssert(ui < m_uiCurrSize);
		return m_pData[ui];
	};
	inline const T& operator[](unsigned int ui) const{
		FAssert(ui < m_uiCurrSize);
		return m_pData[ui];
	};
	unsigned int size() const{
		return m_uiCurrSize;
	};
	inline T* begin() { return m_pData; };
	inline T* end() { return m_pData+m_uiCurrSize; };
	inline const T* begin() const { return m_pData; };
	inline const T* end() const { return m_pData+m_uiCurrSize; };

protected:
	BaseVector() : m_uiCurrSize(0), m_uiCurrMaxSize(0), m_pData(NULL) {};
	void Destroy(T* pVal, unsigned int uiNumElements)
	{
		if( !bPODType){
			for(unsigned int i = 0; i < uiNumElements; ++i){
				pVal[i].~T();
			}
		}
	};
	T* m_pData;
	unsigned int m_uiCurrSize;
	unsigned int m_uiCurrMaxSize;
	// TODO: BaseVector (remaining SDK methods).
};

template<class T, unsigned int L = 1, bool bPODType = false,
	unsigned int AllocPool = c_eMPoolTypeContainer, unsigned int nSubID = 0>
class FStaticVector : public BaseVector<T, bPODType>
{
	// Standard C++ dependent-base lookup; SDK method bodies remain unchanged.
	using BaseVector<T, bPODType>::m_uiCurrMaxSize;
	using BaseVector<T, bPODType>::m_pData;

public:
	typedef T* iterator;
	typedef const T* const_iterator;

	FStaticVector()
	{
		m_uiCurrMaxSize = L;
		m_pData = Alloc(m_uiCurrMaxSize);
#ifdef BREAK_ON_STATIC_RESIZE
		m_iNumResized = 0;
#endif
	};
	// TODO: FStaticVector::~FStaticVector and push_back (SDK definitions).
	~FStaticVector();
	unsigned int push_back(const T& element);
	// TODO: FStaticVector::erase (SDK definition).
	void erase(iterator it);

protected:
	// Allocate memory as bytes
	T* Alloc(unsigned int uiSize){
		T* pRet;
		if( uiSize > L ){
			pRet = (T*)FMALLOCALIGNED( uiSize*sizeof(T), __alignof(T), AllocPool, nSubID );
			m_uiCurrMaxSize = uiSize;
		}else{
			pRet = (T*)m_aData;
			m_uiCurrMaxSize = L;
		}
		return pRet;
	};
	unsigned char m_aData[L*sizeof(T)]; //Local memory store, used until the data will not fit inside any more.
	bool m_bIsResized; //Whether the last call to push_back called the memory store to resize.
#ifdef BREAK_ON_STATIC_RESIZE
	unsigned char m_iNumResized;
#endif
	// TODO: FStaticVector (remaining SDK methods).
};

// TODO: FFastVector (remaining SDK container types).