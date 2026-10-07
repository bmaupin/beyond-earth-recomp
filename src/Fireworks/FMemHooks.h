#pragma once

// Partial SDK allocation declarations.
typedef enum eMPoolType
{
	c_eMPoolTypeContainer = 0,
	// TODO: eMPoolType (remaining values).
} eMPoolType;

void* FireMallocAligned(size_t nSize, size_t nAlignment, const char* szFile, int nLine, int nPoolType, int nPoolTag);
// TODO: FMemHooks (remaining allocation declarations).