#ifndef FSTRING_H
#define FSTRING_H
#pragma once

#include "FCrc32.h"

class FStringA
{
public:
	static int SafeStrlen(const char* lpsz)
	{
		return (lpsz ? (int)strlen(lpsz) : 0);
	}

	// Beyond Earth expands this SDK hashing helper at both notification call sites.
	__attribute__((always_inline)) static inline unsigned int Hash(const char* pszStr)
	{
		FAssert(pszStr != NULL);
		return (g_CRC32.Calc((void*)pszStr, SafeStrlen(pszStr) * sizeof(char)));
	}
	// TODO: FStringA (remaining SDK members).
};

typedef FStringA FString;

#endif // FSTRING_H
