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
#include "hashing\UniChecksum.hpp"
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
		char* H3D_API read(unsigned long bytes);
	};
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
			const int LoadIntoMemory  = 0b0001;
			const int ExclusiveAccess = 0b0010;
		};
		static s H3D_API Parameters;

		// Con-/Destructor
		H3D_API FileHandle();
		H3D_API FileHandle(std::string path,int param=0);
		H3D_API ~FileHandle();

		// Create/Destroy Handle to File
		bool H3D_API open(std::string path,int param=0);
		bool H3D_API close();

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