#pragma once
#include "base_alloc.hpp"
/////////////////////////////////////////////////////////////////
// Linear Allocator
/////////////////////////////////////////////////////////////////
namespace h3d {
	class linear_allocator : public base_alloc
	{
	private:
		linear_allocator(const linear_allocator&) = delete;
		linear_allocator& operator=(const linear_allocator&) = delete;

		void* _currentPos;
	public:
		inline linear_allocator(size_t size, void* start);
		inline ~linear_allocator();

		inline void clear();

		inline void* allocate(size_t size,uint8_t alignment) override;
		inline void deallocate(void *data) override;
	};
}
/////////////////////////////////////////////////////////////////
namespace allocator{
	inline h3d::linear_allocator* newLinear(size_t size, base_alloc& alloc)
	{
		void* p = alloc.allocate(size + sizeof(h3d::linear_allocator),
								 __alignof(h3d::linear_allocator));
		return new (p) h3d::linear_allocator(size, 0);
	}
	inline void deleteLinear(h3d::linear_allocator& linear, base_alloc& alloc)
	{
		linear.~linear_allocator();
		alloc.deallocate(&linear);
	}
}
/////////////////////////////////////////////////////////////////
