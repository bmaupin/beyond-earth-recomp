//---------------------------------------------------------------------------------------
//
//  *****************   FIRAXIS GAME ENGINE   ********************
//
//  FILE:		FStlContainerSerialization.h
//
//  AUTHOR:		Justin Randall
//
//  PURPOSE:	Support STL containers with any type serializable with FDataStream.
//
//---------------------------------------------------------------------------------------
//  Copyright (c) 2009 Firaxis Games, Inc. All rights reserved.
//---------------------------------------------------------------------------------------

#ifndef _INCLUDED_FStlContainerSerialization_H
#define _INCLUDED_FStlContainerSerialization_H

#include <vector>

template<typename ElementType, typename ContainerType>
struct SerializeFromSequenceContainer
{
	SerializeFromSequenceContainer(FDataStream & saveTo, const ContainerType & container) :
	m_saveTo(saveTo)
	, m_container(container)
	{
		m_saveTo << container.size();
	}

	void operator() (ElementType & i)
	{
		m_saveTo << i;
	}

	FDataStream & m_saveTo;
	const ContainerType & m_container;
};

template<typename ElementType, typename ContainerType>
void SerializeToSequenceContainer(FDataStream & loadFrom, ContainerType & container)
{
	container.clear();
	typename ContainerType::size_type count = 0;
	loadFrom >> count;
	typename ContainerType::size_type i = 0;
	for(i = 0; i < count; ++i)
	{
		ElementType v;
		loadFrom >> v;
		container.push_back(v);
	}
}

template<typename ElementType>
FDataStream & operator<<(FDataStream & saveTo, const std::vector<ElementType> & readFrom)
{
	std::for_each(readFrom.begin(), readFrom.end(), SerializeFromSequenceContainer<const ElementType, const std::vector<ElementType> >(saveTo, readFrom));
	return saveTo;
}

template<typename ElementType>
FDataStream & operator>>(FDataStream & loadFrom, std::vector<ElementType> & writeTo)
{
	// The functor needs to be instantiated to properly resize the container based
	// on how many elements the stream says it should have before passing it along
	// to std::for_each
	SerializeToSequenceContainer<ElementType, std::vector<ElementType> >(loadFrom, writeTo);

	//std::for_each(writeTo.begin(), writeTo.end(), func);
	return loadFrom;
}

// TODO: FStlContainerSerialization.h (remaining SDK containers).

#endif // _INCLUDED_FStlContainerSerialization_H