//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!	 \file		CvGameCoreDLLUtil.h
//!  \brief     Public header for Civilization's use of the Win32 API.
//!
//!		Basic Win32 headers w/ necessary preprocessor defines.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef CVGAMECOREDLLUTIL_WIN32HEADERS_H
#define CVGAMECOREDLLUTIL_Win32HEADERS_H

struct LARGE_INTEGER
{
	long long QuadPart;
};

extern "C" int QueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);
extern "C" int QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

#endif //CVGAMECOREDLLUTIL_Win32HEADERS_H
