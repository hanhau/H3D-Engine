#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <vector>
#include <map>
#include <type_traits>
#include <cstdint>
/////////////////////////////////////////////////////////////////
//	ResourceManager
/////////////////////////////////////////////////////////////////
namespace h3d {
	// ResourceHashID
	class ResourceHashID final {
	private:
		uint32_t m_ID;
	public: 
		// Con-/Destructor
		H3D_API ResourceHashID();
		H3D_API ~ResourceHashID();

		// Operations
		uint32_t H3D_API getID();
		uint32_t H3D_API calcHashID(unsigned char* data, size_t size);
	};
	// Lookup table for Hashes
	
	// ResourceBase
	class ResourceBase
	{
	public:
		// Con-/Destructor
		H3D_API ResourceBase();
		H3D_API ~ResourceBase();

		// Loading Operations
		virtual bool H3D_API loadFromFile(char Path[]);
		virtual bool H3D_API process();
		virtual bool H3D_API update();
		// Free Memory
		virtual bool H3D_API freeMemory();
	};
	// ResourceManager
	template<class T>
	class ResourceManager
	{
	private:
		// ResourceMap
		std::map<ResourceHashID, T> m_resourceMap;

	public:
		// Constructor/Deconstructor
		H3D_API ResourceManager();
		H3D_API ~ResourceManager();

		const T& getResource(char Path[]);
		const T& getResource();
	};
}
/////////////////////////////////////////////////////////////////