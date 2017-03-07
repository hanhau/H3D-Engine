#pragma once
#include "../Utilities.hpp"
#include <memory>
#include <cassert>
/////////////////////////////////////////////////////////////////
// Base Alloc Classs
/////////////////////////////////////////////////////////////////
class base_alloc
{
public:
	// Constructor
	inline base_alloc(size_t size,void* start){
		_start = start;
		_size  = size;

		_usedMemory = 0;
		_allocationCount = 0;
	}
	// Virtual Destructor
	inline virtual ~base_alloc()
	{
		// Check for complete deallocation
		h3dassert(_allocationCount == 0 && _usedMemory == 0);

		_start = nullptr;
		_size = 0;
	}

	// main functions
	inline virtual void* allocate(size_t size, uint8_t alignment) = 0;
	inline virtual void deallocate(void* obj) = 0;

	// get values
	inline void* getStart()					const { return _start; }
	inline size_t getUsedMemory()			const { return _usedMemory; }
	inline size_t getSize()					const { return _size; }
	inline size_t returnAllocationCount()	const { return _allocationCount; }
	
protected:
	void*  _start;
	size_t _usedMemory;
	
	size_t _size;
	size_t _allocationCount;
};
/////////////////////////////////////////////////////////////////
inline void* alignForward(void* address, uint8_t alignment)
{
	
}

inline const void* alignForward(const void* address, uint8_t alignment)
{
	
}

inline void* alignBackward(void* address, uint8_t alignment)
{
	
}

inline const void* alignBackward(const void* address, uint8_t alignment)
{
	
}

inline uint8_t alignForwardAdjustment(const void* address, uint8_t alignment)
{
	
}

inline uint8_t alignForwardAdjustmentWithHeader(const void* address, uint8_t alignment, uint8_t headerSize)
{
	
}

inline uint8_t alignBackwardAdjustment(const void* address, uint8_t alignment)
{
	
}

inline void* add(void* p, size_t x)
{
	
}

inline const void* add(const void* p, size_t x)
{
	
}

inline void* subtract(void* p, size_t x)
{
	
}

inline const void* subtract(const void* p, size_t x)
{
	
}
/////////////////////////////////////////////////////////////////