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

#include "hashing\UniChecksum.hpp"
/////////////////////////////////////////////////////////////////
//	Resource Base class
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Resource
	{
	private:
		// Unique handle
		uint64_t m_uniqueID;
		
		// Reference count
		uint64_t m_refCount;

		// Path 
		std::string m_path;
		std::string m_filename;
		std::string m_name;
	public:
		// Con-/Destructor
		Resource(std::string name, std::string path);
		~Resource();

		// Getter
		std::string   getPath();
		std::string   getFilename();
		std::string	  getName();
		uint64_t      getUniqueID();

		// Reference counter
		void increaseRefCount();
		void decreaseRefCount();
	};
}
/////////////////////////////////////////////////////////////////
// ResourceManager
/////////////////////////////////////////////////////////////////
namespace h3d {
	template<typename T>
		class ResourceManager
		{
		private:
			std::map<uint64_t, T> m_resourceMap;
		public:
			// Con-/Destructor
			ResourceManager();
			~ResourceManager();
			
			// Utilities
			void clearMap();
			void remove(uint64_t id);
			
			// Add Resource
			uint64_t add(std::string name,std::string path);

			// Get Resource
			T* getElement(uint64_t ID);
			T* getElement(const std::string& name,const std::string& path);
			T* operator[](uint64_t ID);
		};
}
/////////////////////////////////////////////////////////////////
// Implementaion of ResourceManager
/////////////////////////////////////////////////////////////////
namespace h3d {
	// Con-/Destructor
	template<typename T> 
	ResourceManager<T>::ResourceManager() {}
	template<typename T> 
	ResourceManager<T>::~ResourceManager() {}
	// Utilities
	template<typename T>
	void ResourceManager<T>::clearMap() 
	{
		m_resourceMap.clear();
	}
	template<typename T>
	void ResourceManager<T>::remove(uint64_t ID) 
	{
		this->m_resourcemap.erase(ID);
	}
	// Add Resource
	template<typename T>
	uint64_t ResourceManager<T>::add(std::string name, std::string path) {
		this->m_resourceMap.emplace(name, path);
	}
	// Get Resources
	template<typename T>
	T* ResourceManager<T>::getElement(uint64_t ID) {
		return m_resourceMap[ID];
	}
	template<typename T>
	T* ResourceManager<T>::getElement(const std::string& name,
									  const std::string& path){
		return 
	}
	template<typename T>
	T* ResourceManager<T>::operator[](uint64_t ID) {

	}
}