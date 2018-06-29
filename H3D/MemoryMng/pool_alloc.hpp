#pragma once
#include "base_alloc.hpp"
/////////////////////////////////////////////////////////////////
// Pool Allocator
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace mem {
		class pool_allocator : public base_alloc
		{
		private:
			pool_allocator(const pool_allocator&) = delete;
		public:
			inline pool_allocator(size_t size, void* start) :
				       base_alloc(size, start) {

			};
			inline ~pool_allocator() {

			};

			inline void* allocate(size_t size, uint8_t alignment) {

			}
			inline void  deallocate(void* obj) {

			}
		};
	}
}
/////////////////////////////////////////////////////////////////