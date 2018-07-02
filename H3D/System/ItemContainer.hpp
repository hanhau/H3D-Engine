#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <vector>
#include <cstdint>
#include "../../H3D/MemoryMng/memory.hpp"

// TODO : ITERATOR ?!

/////////////////////////////////////////////////////////////////
// ItemContainer
/////////////////////////////////////////////////////////////////
namespace h3d {
	typedef int32_t ItemID;

		class ItemContainer {
			h3d::AllocationSource m_as;
			ItemID *m_ItemIDList;
		public:
			H3D_API ItemContainer(size_t typesize,
								  AllocationSource as);
			H3D_API ~ItemContainer();

			ItemID H3D_API add(void* item);
			bool   H3D_API del(ItemID id);

			H3D_API void* get(ItemID id) const;
			H3D_API void* pop(ItemID id);
	};
}
/////////////////////////////////////////////////////////////////