//---------------------------------------------------------------------------------------
//  FILE:    FFireTypes.h
//  PURPOSE: FireEngine data types and macros
//---------------------------------------------------------------------------------------
//  Copyright (c) 2004 Firaxis Games, Inc. All rights reserved.
//---------------------------------------------------------------------------------------
#ifndef FFIRETYPES_H
#define FFIRETYPES_H
#pragma once

typedef unsigned int uint;

template<class T> inline void SAFE_DELETE_ARRAY( T *& pkInstanceArray )
{
	delete[] pkInstanceArray;
	pkInstanceArray = NULL;
};

#endif // FFIRETYPES_H