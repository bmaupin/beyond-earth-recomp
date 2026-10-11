#pragma once

#include "CvGameCoreDLLUtil/include/CvString.h"

namespace Localization
{
class String
{
public:
	String(const char* text);
	~String();
	CvString toUTF8() const;
	const char* toUTF8(unsigned int& length, int flags);

private:
	// The external localization library owns this 72-byte i386 representation.
	unsigned int m_storage[18];
};
String Lookup(const char* text);
}
