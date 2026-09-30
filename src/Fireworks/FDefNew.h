//-----------------------------------------------------------------------------
// Copyright (c) 2006 Firaxis Games, Inc. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef __FDEF_NEW_H__
#define __FDEF_NEW_H__

namespace Platform
{
	int GetMemBlockType();
}

void* operator new[](unsigned int size, int blockType, const char* file, int line, int mpool, int tag);

// Firaxis memory macros.  Always use these to allocate/free memory.
#define FNEW( type, mpool, tag ) new(Platform::GetMemBlockType(), __FILE__, __LINE__, mpool, tag) type

#endif // __FDEF_NEW_H__