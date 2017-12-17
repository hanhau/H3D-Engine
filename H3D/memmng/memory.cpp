#include "memory.hpp"

namespace h3d {
	void GlobalAllocator::allocate(size_t n)
	{
		if (m_allocptr == nullptr) {
			
			m_allocptr = malloc(n);

			if (m_allocptr == nullptr && DebugMode) {
				::h3d::Log::error("GLOBALALLOCATOR FAILED:");
				::h3d::Log::error("Tried to allocate %d bytes", n);
			}

			if (DebugMode)
				::h3d::Log::info("Allocated %d bytes of Memory", n);

			// Create Linked List of free Blocks
			static Element first;
			first.header.m_adjustment = 32;
			first.header.m_size = sizeof(Element);
			first.block.m_size = sizeof(first.block.ptr);
			first.block.ptr = m_allocptr;


			//elementList->nextBlock = &first;

			if (DebugMode)
				::h3d::Log::info("First Chunk of memory contains %d bytes",
					first.block.m_size);
		}
	}
	void GlobalAllocator::deallocate()
	{
		free(m_allocptr);
		m_allocptr = nullptr;

		if (DebugMode)
			::h3d::Log::info("Deallocated %d bytes of Memory", m_size);
	}

	mem::Chunk GlobalAllocator::getChunk(size_t n)
	{
		return mem::Chunk();
	}

	void GlobalAllocator::freeChunk(mem::Chunk chunk) 
	{

	}

void*    GlobalAllocator::m_allocptr = nullptr;
size_t   GlobalAllocator::m_size = 0;
size_t   GlobalAllocator::m_allocations = 0;
GlobalAllocator::Element* GlobalAllocator::elementList = nullptr;
}