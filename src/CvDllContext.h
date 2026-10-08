#pragma once

// TODO: CvDllGameContext (remaining SDK interfaces and implementation).
class CvDllGameContext
{
public:
	static void* Allocate(size_t bytes);
	static void Free(void* p);
};
