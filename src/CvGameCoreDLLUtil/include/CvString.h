#pragma once

#ifndef CvString_h
#define CvString_h

#include <string>
#include <cstdarg>

#include "CvAssert.h"
class FDataStream;

//
// simple string classes, based on stl, but with a few helpers
//
// DON'T add any data members or virtual functions to these classes, so they stay the same size as their stl counterparts
//
// Mustafa Thamer
// Firaxis Games, copyright 2005
//
class CvString : public std::string
{
public:
	CvString() {}
	CvString(const char* s) : std::string(s ? s : "") {CvAssertMsg(s != NULL, "Passing NULL to std::string; possible heap corruption!");}

	~CvString() {}

	CvString& operator=(const char* s) { if(s) assign(s); else clear(); return *this; }
	CvString& operator=(const std::string& s) { assign(s.c_str()); return *this; }
	operator const char*() const { return c_str(); }
	const char* GetCString() const { return c_str(); }
	void Format(const char* lpszFormat, ...);

	// TODO: CvString (remaining SDK constructors and helper methods).
};

// TODO: CvStringBuffer

#endif // CvString_h