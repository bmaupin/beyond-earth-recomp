//---------------------------------------------------------------------------------------
//
//  *****************   FIRAXIS GAME ENGINE   ********************
//
//  FILE:		FAutoVariable.h
//
//  AUTHOR:		Justin Randall	--  07/20/2009
//
//  PURPOSE:	Wraps serializeable types to intercept write operations, tracks changes
//              to the serializeable type, notifies an AutoArchive if a change has been
//              made, and registers itself with the containing AutoArchive for automatic
//              serialization.
//
//---------------------------------------------------------------------------------------
//  Copyright (c) 2009 Firaxis Games, Inc. All rights reserved.
//---------------------------------------------------------------------------------------
#ifndef _INCLUDED_FAutoVariable_H
#define _INCLUDED_FAutoVariable_H

//---------------------------------------------------------------------------------------

#include "FAutoVariableBase.h"
#include "FAutoArchiveClassContainer.h"

//---------------------------------------------------------------------------------------

// Track baselines and deltas. Currently used to track out of sync bugs
// but can be adapted for general serialization to/from stream types
// and named values (XML or SQL, for example)
template<typename ObjectType, typename ContainerType>
class FAutoVariable : public FAutoVariableBase
{
public:
	FAutoVariable(const std::string & name, FAutoArchiveClassContainer<ContainerType> &);
	FAutoVariable(const std::string & name, FAutoArchiveClassContainer<ContainerType> &, const ObjectType &);

	// used for extended debugging out of sync errors. Does nothing in release builds
	FAutoVariable(const std::string & name, FAutoArchiveClassContainer<ContainerType> &, bool callStackTracking);
	FAutoVariable(const std::string & name, FAutoArchiveClassContainer<ContainerType> &, const ObjectType &, bool callStackTracking);

	~FAutoVariable();

	const ObjectType & get() const;
	
	ObjectType & dirtyGet();

	operator const ObjectType& () const;

	void set(const ObjectType & source);
	ObjectType & operator=(const ObjectType &);

	void load(FDataStream & loadFrom);
	void loadDelta(FDataStream & loadFrom);
	void save(FDataStream & saveTo) const;
	void saveDelta(FDataStream & saveTo) const;
	void clearDelta();
	bool compare(FDataStream & otherValue) const;
	void reset();

	const std::string & name() const;
	std::string  debugDump(const std::vector<std::pair<std::string, std::string> > &) const;
	std::string toString() const;

	void setStackTraceRemark();

	FAutoVariable & operator-=(const ObjectType & rhs);
	FAutoVariable & operator+=(const ObjectType & rhs);
	FAutoVariable & operator++(int);
	FAutoVariable & operator--(int);
	FAutoVariable & operator=(const FAutoVariable &);

private:
	// keep these out of containers by value, they won't do what is expected
	FAutoVariable(const FAutoVariable &);

private:
	ObjectType  m_value;
	FAutoArchiveClassContainer<ContainerType> &  m_owner;

	// let's help the debugger find the name of the variable
	// name() still works in non-debug builds. Excluding it
	// in Release is a memory optimization. It's here strictly
	// for debugging and development purposes.
};

//---------------------------------------------------------------------------------------

template<typename ObjectType, typename ContainerType>
FDataStream & operator<<(FDataStream & archive, const FAutoVariable<ObjectType, ContainerType> & object)
{
	object.save(archive);
	return archive;
}

//---------------------------------------------------------------------------------------

template<typename ObjectType, typename ContainerType>
__forceinline FAutoVariable<ObjectType, ContainerType>::operator const ObjectType &() const
{
	return m_value;
}

#endif
