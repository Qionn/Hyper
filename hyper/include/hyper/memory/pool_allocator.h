#ifndef __HYPER_POOL_ALLOCATOR_H__
#define __HYPER_POOL_ALLOCATOR_H__

#include <cstdint>

namespace hyper
{
	template<class T, size_t PoolSize>
	class PoolAllocator final
	{
	public:
		PoolAllocator();

		T* Aquire(size_t count);
		void Release(T* ptr);

		PoolAllocator(const PoolAllocator&)				= delete;
		PoolAllocator(PoolAllocator&&)					= delete;
		PoolAllocator& operator=(const PoolAllocator&)	= delete;
		PoolAllocator& operator=(PoolAllocator&&)		= delete;

		~PoolAllocator();

	private:
		struct Block
		{
			int8_t data[sizeof(T)];
			Block* pNext;
			bool inUse;
		};

		struct Pool
		{
			Block blocks[PoolSize];
			Pool* pNext;
		};

	private:

		Pool* m_pHead = nullptr;
		Block* m_pFreeList = nullptr;

	private:
		void AllocatePool();
	};
}

#include "hyper/details/memory/pool_allocator.inl"

#endif // !__HYPER_POOL_ALLOCATOR_H__
