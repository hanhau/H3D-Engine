#pragma once
#include "linear_alloc.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of linear_alloc
/////////////////////////////////////////////////////////////////
namespace h3d {
	linear_allocator::linear_allocator(size_t size, void* start):
		base_alloc(size,start), _currentPos(start)
	{
		// Check if not empty
		h3dassert(size > 0);
	}
	linear_allocator::~linear_allocator() {
		_currentPos = nullptr;
	}
}
/////////////////////////////////////////////////////////////////
namespace h3d {
	// allocate
	void* linear_allocator::allocate(size_t size, uint8_t alignment)
	{
		
	}
	// deallocate
	void linear_allocator::deallocate(void* data){
		h3dverify(false && "Use clear()");
	}
	// clear 
	void linear_allocator::clear(){
		_allocationCount = 0;
		_usedMemory = 0;

		_currentPos = nullptr;
	}
}
/////////////////////////////////////////////////////////////////
