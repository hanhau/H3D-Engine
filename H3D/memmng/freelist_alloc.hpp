#pragma once
#include "base_alloc.hpp"
/////////////////////////////////////////////////////////////////
// FreeList Allocator
/////////////////////////////////////////////////////////////////
namespace h3d {
	class freelist_allocator : public base_alloc
	{
	private:
		freelist_allocator(const freelist_allocator&) = delete;
	public:
		inline freelist_allocator() : base_alloc() {};
		inline ~freelist_allocator() {};
	};
}
/////////////////////////////////////////////////////////////////
