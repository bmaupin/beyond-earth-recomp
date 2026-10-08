//------------------------------------------------------------------------------------------------
//  Copyright (c) 2004 Firaxis Games, Inc. All rights reserved.
//------------------------------------------------------------------------------------------------
#ifndef FOBJECTPOOL_H
#define FOBJECTPOOL_H
#pragma once

#include "FCriticalSection.h"

#define DEFAULT_FOBJECT_POOL_SIZE 8

template<class T>
class FObjectPool
{
public:
	FObjectPool(uint uiSize = DEFAULT_FOBJECT_POOL_SIZE, bool bGrow = true);
	FObjectPool(const FObjectPool<T>& source);
	FObjectPool<T>& operator=(const FObjectPool<T>& source);
	virtual ~FObjectPool();
	T* GetFreeObject();
	void Release(T* pObject);

protected:
	uint GetNextFreeIndex();
	void Lock() { m_Locker.Enter(); }
	void Unlock() { m_Locker.Leave(); }

	struct FPoolNode
	{
		T* pObject;
		bool bFree;
	};

	FPoolNode* m_pStorage;
	FCriticalSection m_Locker;
	uint m_uiSize;
	bool m_bGrow;
	bool m_bFull;
	uint m_uiFirstFreeIndex;
};

// TODO: FObjectPool (SDK method definitions; calls remain external).
#endif // FOBJECTPOOL_H
