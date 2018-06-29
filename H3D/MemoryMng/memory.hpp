#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT

#include <malloc.h>
#include "..\Utilities.hpp"
#include <list>

namespace {
	struct AllocHeader {
		size_t  m_size;
		uint8_t m_adjustment;
	};

	struct ChunkBlock {
		size_t      m_size;
		void *ptr;
	};
}

namespace h3d { namespace mem {
		struct Chunk {
			size_t size;
			void*  start;
		};
	}
}

namespace h3d {
	enum class AllocationSource {
		Self,        // Object handles its own memory
		Global       // Object gets memory from global
	};

	class GlobalAllocator { 
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
		static void H3D_API allocate(size_t n);
		static void H3D_API deallocate();

		static H3D_API mem::Chunk getChunk(size_t n);
		static H3D_API void  freeChunk(mem::Chunk chunk);
	};
}