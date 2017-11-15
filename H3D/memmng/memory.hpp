#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT

#include <malloc.h>
#include "..\Utilities.hpp"
#include <list>

namespace h3d {
	enum class AllocationSource {
		Self, Global
	};

	class GlobalAllocator { 

		struct AllocHeader {
			size_t  m_size;
			uint8_t m_adjustment;
		};

		struct ChunkBlock {
			size_t      m_size;
			void *ptr;
		};

		struct Element {
			AllocHeader header;
			ChunkBlock block;
			Element* nextBlock;
		};
		
		static Element* elementList;

		static size_t m_size;
		static void *m_allocptr;

		static size_t m_allocations;

	public:
		inline static void allocate(size_t n)
		{
			if (m_allocptr == nullptr) {
				m_allocptr = malloc(n);

				

				if (h3d::DebugMode)
					Log.info("Allocated %d bytes of Memory",n);
			}
		}
		inline static void deallocate()
		{
			free(m_allocptr);
			m_allocptr = nullptr;
			

			if (h3d::DebugMode)
				Log.info("Deallocated %d bytes of Memory", m_size);
		}

		inline static H3D_API void* getChunk(size_t n);
	};

	void*    GlobalAllocator::m_allocptr = nullptr;
	size_t   GlobalAllocator::m_size     = 0;
	size_t   GlobalAllocator::m_allocations = 0;
	GlobalAllocator::Element* GlobalAllocator::elementList = nullptr;
}

inline void* h3d::GlobalAllocator::getChunk(size_t n)
{

}