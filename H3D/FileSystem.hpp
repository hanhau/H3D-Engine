#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <string>
#include <fstream>
#include <cstdint>
#include <thread>
/////////////////////////////////////////////////////////////////
//	FileSystem
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace File {
	/////////////////////////////////////////////////////////////
	//	Checksum Class
	/////////////////////////////////////////////////////////////
		class Checksum
		{
			uint64_t m_key;
		public:
			// Con-/Destructor
			H3D_API Checksum();
			H3D_API Checksum();
			H3D_API ~Checksum();

			// Create Checksum 
			void H3D_API create(std::string path);
			void H3D_API create(void* buffer,uint64_t buffer_size);

			// Key Operations
			uint64_t H3D_API getKey();
			bool     H3D_API compareKey(uint64_t key);
		};
	/////////////////////////////////////////////////////////////
	// Encryption Class
	/////////////////////////////////////////////////////////////
		class Crypter
		{
			
		};
	}
	/////////////////////////////////////////////////////////////
	//	Class for File handling and loading
	/////////////////////////////////////////////////////////////
	class FileHandle
	{
		// File relevant stuff
		std::string m_path;
		std::fstream m_fileStream;
		char *m_buffer;

		// File Techniques
		h3d::File::Checksum *m_checksum;
		h3d::File::Crypter  *m_crypter;

		// Read/Write Treads
		std::thread m_writeThread;
		std::thread m_readThread;
	public:
		// Con-/Destructor
		H3D_API FileHandle();
		H3D_API FileHandle(std::string path,int param);
		H3D_API ~FileHandle();

		// Create/Destroy Handle to File
		bool H3D_API open(std::string path,int param);
		bool H3D_API close();

		// File Operations
		int H3D_API read(char* dst,size_t size);
		int H3D_API write(char* src, size_t size);

		// File Operations in Threads
		bool H3D_API addToWriteQueue(char *buffer,size_t size);
		bool H3D_API addToReadQueue(char *buffer,size_t size);
	};
}
/////////////////////////////////////////////////////////////////