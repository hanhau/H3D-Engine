#pragma once
#include "../../H3D/MemoryMng/linear_alloc.hpp"
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
		// Check for size
		h3dassert(size != 0);

		// Get adjustment
		uint8_t adjustment;

		// return mullptr when no space left
		if (_usedMemory + alignment + size > _size)
			return nullptr;

		uintptr_t aligned_address = (uintptr_t)_currentPos + adjustment;
		
		_currentPos = (void*)(aligned_address + size);
		
		_usedMemory += size + alignment;
		_allocationCount++;

		// return address
		return (void*)aligned_address;
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
