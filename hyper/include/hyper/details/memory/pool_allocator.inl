#ifndef __HYPER_POOL_ALLOCATOR_INL__
#define __HYPER_POOL_ALLOCATOR_INL__

#include <cstdlib>
#include <new>

namespace hyper
{
	template<class T, size_t PoolSize>
	PoolAllocator<T, PoolSize>::PoolAllocator()
	{
		AllocatePool();
	}

	template<class T, size_t PoolSize>
	PoolAllocator<T, PoolSize>::~PoolAllocator()
	{
		Pool* pCurrent = m_pHead;
		while (pCurrent != nullptr)
		{
			for (size_t i = 0; i < PoolSize; ++i)
			{
				Block* pBlock = &pCurrent->blocks[i];

				if (pBlock->inUse)
				{
					auto ptr = reinterpret_cast<T*>(&pCurrent->blocks[i]);
					ptr->~T();
				}
			}

			Pool* pNextPool = pCurrent->pNext;
			std::free(pCurrent);
			pCurrent = pNextPool;
		}
	}

	template<class T, size_t PoolSize>
	T* PoolAllocator<T, PoolSize>::Aquire(size_t count)
	{
		if (count != 1)
		{
			throw std::bad_alloc();
		}

		if (m_pFreeList == nullptr)
		{
			AllocatePool();
		}

		Block* pFreeBlock = m_pFreeList;
		pFreeBlock->inUse = true;

		m_pFreeList = m_pFreeList->pNext;
		pFreeBlock->pNext = nullptr;

		return reinterpret_cast<T*>(pFreeBlock);
	}

	template<class T, size_t PoolSize>
	void PoolAllocator<T, PoolSize>::Release(T* ptr)
	{
		if (ptr != nullptr)
		{
			Block* pBlock = reinterpret_cast<Block*>(ptr);
			pBlock->inUse = false;
			pBlock->pNext = m_pFreeList;
			m_pFreeList = pBlock;
		}
	}

	template<class T, size_t PoolSize>
	void PoolAllocator<T, PoolSize>::AllocatePool()
	{
		Pool* pPool = static_cast<Pool*>(std::malloc(sizeof(Pool)));

		for (size_t i = 0; i < PoolSize; ++i)
		{
			Release(reinterpret_cast<T*>(&pPool->blocks[i]));
		}

		pPool->pNext = m_pHead;
		m_pHead = pPool;
	}
}

#endif // !__HYPER_POOL_ALLOCATOR_INL__
