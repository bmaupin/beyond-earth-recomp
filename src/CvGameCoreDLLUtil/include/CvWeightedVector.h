#pragma once

#ifndef CIV5_WEIGHTED_VECTOR_H
#define CIV5_WEIGHTED_VECTOR_H

#include <algorithm>
#include "EventSystem/FastDelegate.h"
#include "FFastVector.h"

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
	/// Number of items
	int size () { return m_pItems.size(); };
	/// Sort this stuff from highest to lowest
	void SortItems () { std::sort(m_pItems.begin(), m_pItems.end()); }
	// TODO: CvWeightedVector (remaining SDK methods).

private:
	FStaticVector<WeightedElement, L, bPODType> m_pItems;
};

#endif //CIV5_WEIGHTED_VECTOR_H