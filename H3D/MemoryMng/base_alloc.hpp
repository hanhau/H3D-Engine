#pragma once
#include "../Utilities.hpp"
#include <memory>
#include <cassert>
/////////////////////////////////////////////////////////////////
// Base Alloc Classs
/////////////////////////////////////////////////////////////////
namespace h3d { namespace mem {
	class base_alloc : Uncopyable
	{
		public:
		// Constructor
		inline base_alloc(size_t size, void* start) {
			_start = start;
			_size = size;

			_usedMemory = 0;
			_allocationCount = 0;
		}
		// Virtual Destructor
		inline virtual ~base_alloc()
		{
			h3dassert(_allocationCount == 0 && 
					  _usedMemory      == 0);

			_start = nullptr;
			_size = 0;
		}

		inline virtual void* allocate(size_t size, uint8_t alignment) = 0;
		inline virtual void deallocate(void* obj) = 0;

		inline void* getStart()				  const { return _start; }
		inline size_t getUsedMemory()		  const { return _usedMemory; }
		inline size_t getSize()				  const { return _size; }
		inline size_t returnAllocationCount() const { return _allocationCount; }

	protected:
		void*  _start;
		size_t _usedMemory;

		size_t _size;
		size_t _allocationCount;
	};
}}
/////////////////////////////////////////////////////////////////
namespace h3d {namespace mem {namespace math {
/////////////////////////////////////////////////////////////////
	inline void* add(void* p, size_t x) {
		return (void*)(reinterpret_cast<uintptr_t>(p) + x);
	}
	inline const void* add(const void* p, size_t x) {
		return (const void*)(reinterpret_cast<uintptr_t>(p) + x);
	}
	inline void* subtract(void* p, size_t x) {
		return (void*)(reinterpret_cast<uintptr_t>(p) - x);
	}
	inline const void* subtract(const void* p, size_t x) {
		return (const void*)(reinterpret_cast<uintptr_t>(p) - x);
	}
	/////////////////////////////////////////////////////////////////
	inline void* alignForward(void* addr, uint8_t al)
	{
		size_t offset = (uintptr_t)addr % al;
		return add(addr, offset);
	}
	inline const void* alignForward(const void* addr, uint8_t al)
	{
		size_t offset = (uintptr_t)addr % al;
		return add(addr, offset);
	}
	inline void* alignBackward(void* addr, uint8_t al)
	{
		size_t negative_offset = al - ((uintptr_t)addr % al);
		return subtract(addr, negative_offset);
	}
	inline const void* alignBackward(const void* addr, uint8_t al)
	{
		size_t negative_offset = al - ((uintptr_t)addr % al);
		return subtract(addr, negative_offset);
	}
	inline uint8_t alignForwardAdjustment(const void* address, 
										  uint8_t alignment)
	{

	}
	inline uint8_t alignForwardAdjustmentWithHeader(const void* address, 
													uint8_t alignment, 
													uint8_t headerSize)
	{

	}
	inline uint8_t alignBackwardAdjustment(const void* address, 
										   uint8_t alignment)
	{

	}
/////////////////////////////////////////////////////////////////
		}
	}
}