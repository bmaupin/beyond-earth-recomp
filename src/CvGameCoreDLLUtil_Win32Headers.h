//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!	 \file		CvGameCoreDLLUtil.h
//!  \brief     Public header for Civilization's use of the Win32 API.
//!
//!		Basic Win32 headers w/ necessary preprocessor defines.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef CVGAMECOREDLLUTIL_WIN32HEADERS_H
#define CVGAMECOREDLLUTIL_Win32HEADERS_H

#define UNREFERENCED_PARAMETER(P) (void)(P)

struct GUID
{
	unsigned int Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
};

struct _RTL_CRITICAL_SECTION_DEBUG;
typedef struct _RTL_CRITICAL_SECTION
{
	_RTL_CRITICAL_SECTION_DEBUG* DebugInfo;
	long LockCount;
	long RecursionCount;
	void* OwningThread;
	void* LockSemaphore;
	unsigned long SpinCount;
} RTL_CRITICAL_SECTION, CRITICAL_SECTION;

struct LARGE_INTEGER
{
	long long QuadPart;
};

extern "C" int QueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);
extern "C" int QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

// Linux compatibility declaration for the secure CRT string-copy function.
// The array overload supplies the size used by the original SDK call site.
int strcpy_s(char* destination, unsigned int size, const char* source);

template<unsigned int Size>
inline int strcpy_s(char (&destination)[Size], const char* source)
{
	return strcpy_s(destination, Size, source);
}

#endif //CVGAMECOREDLLUTIL_Win32HEADERS_H
