#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "../../H3D/MemoryMng/memory.hpp"
#include "../../H3D/Hashing/UniChecksum.hpp"
#include "Resource.hpp"
#include <vector>
/////////////////////////////////////////////////////////////////
// ResourceManager
/////////////////////////////////////////////////////////////////
namespace h3d {
	struct ResourceManager
	{
		H3D_API ResourceManager();
		H3D_API ~ResourceManager();

		static void H3D_API initialize(size_t bytesToAllocate);
		static void H3D_API shutdown();

		static void H3D_API registerResource(Resource &&res);
		static void H3D_API detachResource(std::string name,std::string path);

		static H3D_API Resource& getResource(std::string name,std::string path);
	};
}