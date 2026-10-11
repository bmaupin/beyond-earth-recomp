#pragma once

#ifndef CIV5_WEIGHTED_VECTOR_H
#define CIV5_WEIGHTED_VECTOR_H

#include <algorithm>
#include "EventSystem/FastDelegate.h"
#include "FFastVector.h"
#include "ASLSort.h"

// Functor for random number callback routine
typedef fastdelegate::FastDelegate2<int, const char *, int> RandomNumberDelegate;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:     CvWeightedVector
//!  \brief	   Container holding objects with associated weighting
//
//!  Key Attributes:
//!  - Underlying data structure is FFastVector from Fireworks
//!  - See documentation on template parameters from FFastVector; same ones used here
//!  - Main purpose of class is use for weighted AI selection
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template< class T, unsigned int L = 1, bool bPODType = false> class CvWeightedVector
{
public:
	/// One element stored in our weighted vector
	struct WeightedElement
	{
		WeightedElement() :
		m_Element()
		, m_iWeight ()
		{
		}
		WeightedElement(const WeightedElement & source) :
		m_Element(source.m_Element)
		, m_iWeight(source.m_iWeight)
		{
		}
		T m_Element;
		int m_iWeight;
		bool operator< (const WeightedElement& b2) const
		{
			// Reverse of the normal direction because we want highest weight first in our list
			return m_iWeight > b2.m_iWeight;
		};
	};

	/// Default constructor
	CvWeightedVector(void) {};
	/// Destructor
	~CvWeightedVector(void) {};
	/// Accessor for element
	const T& GetElement (unsigned int iIndex) const
	{
		assert(iIndex < m_pItems.size());
		return m_pItems[iIndex].m_Element;
	};
	/// Accessors for weight
	int GetWeight (unsigned int iIndex) const
	{
		WeightedElement elem;
		assert(iIndex < m_pItems.size());
		elem = m_pItems[iIndex];
		return elem.m_iWeight;
	}
	void IncreaseWeight (unsigned int iIndex, int iWeight)
	{
		m_pItems[iIndex].m_iWeight += iWeight;
		CvAssertMsg(m_pItems[iIndex].m_iWeight >= 0, "Weight should not be negative.");
	}
	void SetWeight (unsigned int iIndex, int iWeight)
	{
		m_pItems[iIndex].m_iWeight = iWeight;
		CvAssertMsg(m_pItems[iIndex].m_iWeight >= 0, "Weight should not be negative.");
	}
	/// Add an item to the end of the vector
	unsigned int push_back (const T& element, int iWeight)
	{
//		FAssertMsg(iWeight >= 0, "Weight should not be negative.");
		WeightedElement weightedElem;
		weightedElem.m_Element = element;
		weightedElem.m_iWeight = iWeight;
		return m_pItems.push_back(weightedElem);
	};
	/// Clear out the vector
	void clear () { m_pItems.clear(); };
	void resize (uint uiNewSize) { m_pItems.resize(uiNewSize); };
	/// Number of items
	int size () const { return m_pItems.size(); };
	/// Sort this stuff from highest to lowest
	void SortItems ()
	{
		// Beyond Earth uses the ASL iterator sort instead of the SDK's std::sort.
		ASL::StdLib::Sort::_Sort(m_pItems.begin(), m_pItems.end(), m_pItems.end() - m_pItems.begin());
	}
	int GetTotalWeight() const
	{
		int iTotal = 0;
		for(int i = 0; i < size(); ++i) iTotal += GetWeight(i);
		return iTotal;
	}
	int ChooseAtRandom(RandomNumberDelegate* pRand, const char* szLog)
	{
		return size() ? GetElement((*pRand)(size(), szLog)) : -1;
	}
	int ChooseFromTopChoices(int iNumChoices, RandomNumberDelegate* pRand, const char* szLog)
	{
		const int iChoices = std::min(iNumChoices, size());
		int iTotal = 0;
		for(int i = 0; i < iChoices; ++i) iTotal += GetWeight(i);
		int iRoll = (*pRand)(iTotal, szLog);
		int iChoice = iChoices > 0 ? GetElement(iChoices - 1) : 0;
		for(int i = 0; i < iChoices; ++i)
		{
			iChoice = GetElement(i);
			iRoll -= GetWeight(i);
			if(iRoll < 0) break;
		}
		return iChoice;
	}
	// TODO: CvWeightedVector (remaining SDK methods).

private:
	FStaticVector<WeightedElement, L, bPODType> m_pItems;
};

#endif //CIV5_WEIGHTED_VECTOR_H