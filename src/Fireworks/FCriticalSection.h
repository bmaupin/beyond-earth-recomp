//------------------------------------------------------------------------------------------------
//  Copyright (c) 2007 Firaxis Games, Inc. All rights reserved.
//------------------------------------------------------------------------------------------------
#ifndef FCRITICALSECTION_H
#define FCRITICALSECTION_H
#pragma once

class FCriticalSection
{
public:
	FCriticalSection(void);
	~FCriticalSection(void);
	bool Try(void);
	void Enter(void);
	void Leave(void);
	int GetLockCount() const;
	int GetRecursionCount() const;

private:
	// Beyond Earth's Linux port retains the Win32 critical-section structure.
	CRITICAL_SECTION m_kCriticalSection;
};

class FScopedCriticalSection
{
public:
	FScopedCriticalSection(FCriticalSection& kCriticalSection);
	~FScopedCriticalSection(void);

private:
	FCriticalSection& m_kCriticalSection;
};

// TODO: FCriticalSection and FScopedCriticalSection (method definitions).
#endif // FCRITICALSECTION_H
