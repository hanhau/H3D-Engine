#pragma once
#include "base_alloc.hpp"
/////////////////////////////////////////////////////////////////
// FreeList Allocator
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace mem {
	class freelist_allocator : public base_alloc
	{
	private:
		freelist_allocator(const freelist_allocator&) = delete;
	public:
		inline freelist_allocator(size_t size, void* start) : 
			       base_alloc(size,start) {
		
		};
		inline ~freelist_allocator() {
		
		};

		inline void* allocate(size_t size, uint8_t alignment) {

		}
		inline void  deallocate(void* obj) {

		}
	};
	}
}
/////////////////////////////////////////////////////////////////
