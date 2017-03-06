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
	inline base_alloc();
	inline virtual ~base_alloc();

	inline virtual void* allocate(size_t size,uint8_t alignment);				  
	inline virtual void deallocate(void* obj);
protected:
	void* _start;
	void* _end;
	
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