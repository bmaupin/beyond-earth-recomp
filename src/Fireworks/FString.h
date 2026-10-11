#ifndef FSTRING_H
#define FSTRING_H
#pragma once

#include "FCrc32.h"
#include <cstddef>
#include <cstring>

class FStringA;
struct FStringAData;
extern "C" FStringAData* FStringA_GetStringInitData();

// Beyond Earth puts the fixed-buffer flag before the lock flag.
struct FStringAData
{
	int m_iAllocLength;
	int m_iDataLength;
	unsigned short m_bFixed;
	unsigned short m_bLocked;
	char* StringData() { return reinterpret_cast<char*>(this + 1); }
};

class FStringA
{
public:
	typedef ::FStringAData FStringAData;

	template<size_t Length>
	class FStringAFixedBuffer
	{
	public:
		__attribute__((always_inline)) explicit FStringAFixedBuffer(FStringA& str)
		{
			// Beyond Earth's fixed-buffer constructor leaves the lock flag untouched.
			m_kStringData.m_bFixed = 1;
			m_kStringData.m_iAllocLength = Length;
			m_kStringData.m_iDataLength = 0;
			m_szStringBuffer[0] = 0;
			str.SetFixedBuffer(&m_kStringData);
		}

	private:
		FStringAData m_kStringData;
		char m_szStringBuffer[Length];
	};

	__attribute__((always_inline)) FStringA() { Init(); }
	__attribute__((always_inline)) ~FStringA() { Release(); }
	const char* c_str() const { return m_pszString; }
	void Format(const char* format, ...);

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

private:
	__attribute__((always_inline)) void Init() { m_pszString = FStringA_GetStringInitData()->StringData(); }
	__attribute__((always_inline)) void Release()
	{
		FStringAData* data = reinterpret_cast<FStringAData*>(m_pszString) - 1;
		if(data && FStringA_GetStringInitData() != data && !data->m_bFixed)
			delete[] reinterpret_cast<unsigned char*>(data);
		m_pszString = NULL;
		Init();
	}
	__attribute__((always_inline)) void SetFixedBuffer(FStringAData* data)
	{
		Release();
		m_pszString = data->StringData();
	}

	char* m_pszString;
};

typedef FStringA FString;

#define FStringFixedBuffer(varname, size) FString varname; FStringA::FStringAFixedBuffer<size> FStringFixedBuffer_##varname(varname); varname

#endif // FSTRING_H
