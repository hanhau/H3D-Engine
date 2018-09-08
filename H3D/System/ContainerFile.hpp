#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "../../H3D/System/Utilities.hpp"
#include <map>
#include <string>
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/FileDataStructures.hpp"
/////////////////////////////////////////////////////////////////
// ContainerFile containing multiple files in one
/////////////////////////////////////////////////////////////////
namespace h3d {
	class ContainerFile
	{
	private:
		// final Item struct
		struct Item : public h3d::FileType::CH3D::ItemListing {
			h3d::MemoryStream m_memoryStream;
		};

		// Map to the Container
		std::map<std::string, Item> m_items;
		
		// file itself
		std::string		m_path;
		h3d::FileHandle m_fh;
	public:
		H3D_API ContainerFile();
		H3D_API ContainerFile(std::string path,bool filemapping = false);
		H3D_API ContainerFile(h3d::FileHandle& filehandle);
		H3D_API ~ContainerFile();

		bool H3D_API openContainerFile(std::string path);
		bool H3D_API openContainerFile(h3d::FileHandle& filehandle);
		bool H3D_API close();

		H3D_API h3d::MemoryStream& const getMemoryStream(std::string filename);
	};
}
/////////////////////////////////////////////////////////////////
// Create Container File
/////////////////////////////////////////////////////////////////
namespace h3d{
	bool createContainerFile(std::string output_file,
		std::vector<std::string> input_files);
}
/////////////////////////////////////////////////////////////////