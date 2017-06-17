#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <thread>
#include "hashing\UniChecksum.hpp"
#include <windows.h>
/////////////////////////////////////////////////////////////////
namespace h3d {
	class FileHandle;
	class ContainerFile;
}
/////////////////////////////////////////////////////////////////
//	FileSystem
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace File {
	/////////////////////////////////////////////////////////////
	// Encryption Class
	/////////////////////////////////////////////////////////////
		class Crypter
		{
			
		};
	}
	/////////////////////////////////////////////////////////////
	// MemoryStream 	
	/////////////////////////////////////////////////////////////
	class MemoryStream 
	{
	private:
		char**        m_bufferPtr;
		unsigned long m_bufferSize;
		unsigned long m_currentPos;
	public:
		// Con-/Destructor
		H3D_API MemoryStream();
		H3D_API ~MemoryStream();

		// Open & Close
		void H3D_API open(char* buffer, unsigned long size);
		void H3D_API close();

		// Read bytes
		H3D_API char* read(unsigned long bytes);
	};
	/////////////////////////////////////////////////////////////
	// Template function to set struct from buffer
	/////////////////////////////////////////////////////////////
	template<typename T> 
	unsigned long setObjectFromFileHandle(T& object,h3d::FileHandle& fh) 
	{
		return fh.read((char*)&object, sizeof(object));
	}
	template<typename T>
	unsigned long setObjectFromMemory(T& object, const void* buffer)
	{
		unsigned long objectSize = sizeof(object);
		memcpy((char*)&object,buffer,objectSize);
		return objectSize;
	}
	/////////////////////////////////////////////////////////////
	//	Class for File handling and loading
	/////////////////////////////////////////////////////////////
	class FileHandle
	{
		friend ContainerFile;

		// File relevant stuff
		std::string m_path;
		std::fstream m_fileStream;
		std::vector<unsigned char> m_buffer;

		// File Techniques
		h3d::Checksum        m_checksum;
		h3d::File::Crypter  *m_crypter;
		
		// winapi stuff
		HANDLE m_fileHandle;

		// Read/Write Treads
		std::thread m_writeThread;
		std::thread m_readThread;

		// Current avaliable Intel
		unsigned long m_fileSizeBytes;
		std::string   m_filePath;
		bool          m_isOpen;

		bool          m_inMemory;
		MemoryStream  m_memoryStream;
		unsigned long m_actualIterPos;
	public:
		// setable Parameters for opening
		struct s{
			static const int LoadIntoMemory;
			static const int ExclusiveAccess;
		};
		static s H3D_API Params;

		// Con-/Destructor
		H3D_API FileHandle();
		H3D_API FileHandle(std::string path,int param=0);
		H3D_API ~FileHandle();

		// Create/Destroy Handle to File
		bool H3D_API open(std::string path,int param=0);
		bool H3D_API close();

		// Checksum operations
		h3d::Checksum H3D_API calcChecksum();
		h3d::Checksum H3D_API getChecksum();

		// File Operations
		unsigned long H3D_API read (char* dst, size_t size);
		unsigned long H3D_API write(char* src, size_t size);

		// Moving Iterator
		unsigned long H3D_API getIterPos();
		unsigned long H3D_API setIterPos(unsigned long val);

		// Get Intel about file
		unsigned long getFileSize();
		std::string   getFilePath();
		bool          isOpen();
	};
}
/////////////////////////////////////////////////////////////////