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
/////////////////////////////////////////////////////////////////
// ContainerFile containing multiple files in one
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace FileType {
		namespace ContainerFile {
			#pragma pack(push,CONTAINERFILE_HEADER,1)
			struct H3D_API Header
			{
				char formatStr[6];  // Must be "h3dcon"
				uint32_t itemCount; // Items in Container
			};
			#pragma pack(pop,CONTAINERFILE_HEADER)
			#pragma pack(push,CONTAINERFILE_ITEMLISTING,1)
			struct H3D_API ItemListing
			{				   
				char filename[48]; // normal filename
				uint64_t filesize; // size in bytes
				uint64_t begin,    // first byte in container
						 end;      // last byte in container
			};
			#pragma pack(pop,CONTAINERFILE_ITEMLISTING)
		}
	}
}
/////////////////////////////////////////////////////////////////
namespace h3d {
	class ContainerFile
	{
	private:
		// final Item struct
		struct Item : public h3d::FileType::ContainerFile::ItemListing {
			h3d::FileHandle filehandle;
		};

		// Map to the Container
		std::map<char[48], Item> m_items;
		
		// file itself
		std::string		m_path;
		h3d::FileHandle m_fh;
	public:
		H3D_API ContainerFile();
		H3D_API ContainerFile(std::string path);
		H3D_API ~ContainerFile();

		bool H3D_API openContainerFile(std::string path);
		bool H3D_API close();

		H3D_API h3d::FileHandle& getFileHandle(char filename[48]);
	};
}
/////////////////////////////////////////////////////////////////
// Create Container File
/////////////////////////////////////////////////////////////////
namespace h3d{
	bool createContainerFile(std::string output_file,
							 std::vector<std::string> input_files)
	{
		h3d::Log::info("Creating ContainerFile %s",output_file.c_str());

		// Create Output Filestream
		h3d::FileHandle fh;
		if(!fh.open(output_file)) return false;

		// Setup Header in file
		h3d::FileType::ContainerFile::Header header;
		strcpy(header.formatStr, "h3dcon");
		header.itemCount = input_files.size();
		
		fh.write((char*)&header, sizeof(header));

		h3d::Log::info("%s will contain %d items.", output_file.c_str(), header.itemCount);

		// Write until done
		static h3d::FileHandle infh;
		static h3d::FileType::ContainerFile::ItemListing itemlisting;
		static char* buffer;

		for (auto &iter : input_files)
		{
			h3d::Log::info("Copying from %s", iter.c_str());
			
			// Filestream
			infh.open(iter);
			auto file_length = infh.getFileSize();
			
			buffer = new char[file_length];
			infh.read(buffer, file_length);
			infh.close();
			
			strcpy(itemlisting.filename, iter.c_str());
			itemlisting.filesize = file_length;
			
			fh.write((char*)&itemlisting,sizeof(itemlisting));
			fh.write(buffer, file_length);
		}

		return true;
	}
}
/////////////////////////////////////////////////////////////////