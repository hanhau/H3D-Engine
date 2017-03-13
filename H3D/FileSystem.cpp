#include "FileSystem.hpp"
#include <Windows.h>
#include "Utilities.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of MemoryStream
/////////////////////////////////////////////////////////////////
h3d::MemoryStream::MemoryStream() {
	m_bufferPtr = NULL;
	m_bufferSize = m_currentPos = 0;
}
h3d::MemoryStream::~MemoryStream() {
	m_bufferPtr = NULL;
	m_bufferSize = m_currentPos = 0;
}
/////////////////////////////////////////////////////////////////
void h3d::MemoryStream::open(char* buffer,unsigned long size)
{
	m_bufferPtr  = &buffer;
	m_bufferSize = size;
	m_currentPos = 0;
}
void h3d::MemoryStream::close()
{
	m_bufferPtr = NULL;
	m_bufferSize = 0;
}
/////////////////////////////////////////////////////////////////
char* h3d::MemoryStream::read(unsigned long bytes) 
{
	if (bytes + m_currentPos > m_bufferSize)
	{
		static char* tempBuffer;
		tempBuffer = new char[bytes];
		memcpy(tempBuffer, *m_bufferPtr+m_currentPos, bytes);
		return tempBuffer;
	}
	else return nullptr;
}
/////////////////////////////////////////////////////////////////
// Implementations for FileHandle
/////////////////////////////////////////////////////////////////
const int h3d::FileHandle::s::LoadIntoMemory  = 0b0001;
const int h3d::FileHandle::s::ExclusiveAccess = 0b0010;
/////////////////////////////////////////////////////////////////
h3d::FileHandle::FileHandle() 
{
	
}
h3d::FileHandle::FileHandle(std::string path, int param)
{

}
h3d::FileHandle::~FileHandle() 
{

}
/////////////////////////////////////////////////////////////////
#define H3D_DEBUG
bool h3d::FileHandle::open(std::string path, int param)
{
	h3dverify(path.size() == 0);

	//  Parameter checking
	DWORD dwShareMode;
	if ((param & Params.ExclusiveAccess) == Params.ExclusiveAccess)
		dwShareMode = 0;
	else
		dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

	// Create Handle
	m_fileHandle = CreateFileA(path.c_str(),
							  GENERIC_READ | GENERIC_WRITE,
							  dwShareMode,
							  NULL,
							  OPEN_EXISTING,
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
	// Error handling
	if (m_fileHandle == INVALID_HANDLE_VALUE)
	{
		Log.error("Unable to open %s",path.c_str());
		return false;
	}
	
	// Save Intel about opened File
	m_fileSizeBytes = GetFileSize(m_fileHandle, NULL);
	m_isOpen = true;
	m_filePath = path;

	// Load into Memory if desired
	if ((param & Params.LoadIntoMemory) == Params.LoadIntoMemory)
	{
		ReadFile(m_fileHandle, m_buffer.data(), m_fileSizeBytes, NULL, NULL);
		m_inMemory = true;
	}

	// Return successfully
	return true;
}
bool h3d::FileHandle::close()
{
	if (CloseHandle(m_fileHandle)) return true;
	else return false;
}
/////////////////////////////////////////////////////////////////
// Checksum Operations
/////////////////////////////////////////////////////////////////
h3d::Checksum h3d::FileHandle::calcChecksum() {
	if (m_inMemory)
		 m_checksum.create(m_buffer.data(), m_fileSizeBytes);
	else m_checksum.create(m_filePath);

	return m_checksum;
}
h3d::Checksum h3d::FileHandle::getChecksum()  {
	return m_checksum;
}
/////////////////////////////////////////////////////////////////
unsigned long h3d::FileHandle::read(char* dst, size_t size)
{
	unsigned long readbytes = 0;
	ReadFile(m_fileHandle,
			 dst,size,
			 &readbytes,NULL);
	return readbytes;
}
unsigned long h3d::FileHandle::write(char* src, size_t size)
{
	unsigned long writtenbytes = 0;
	WriteFile(m_fileHandle,
			  src, size,
			  &writtenbytes, NULL);
	return writtenbytes;
}
/////////////////////////////////////////////////////////////////
unsigned long h3d::FileHandle::getIterPos()
{

	return 0;
}
unsigned long h3d::FileHandle::setIterPos(unsigned long val)
{
	if (!SetFilePointerEx(m_fileHandle, LARGE_INTEGER{ val },
						  nullptr, FILE_BEGIN))
	{
		Log.info("Unable to set filepointer.");
		return 0;
	}
	return val;
}
/////////////////////////////////////////////////////////////////
unsigned long h3d::FileHandle::getFileSize() {
	return m_fileSizeBytes;
}
std::string   h3d::FileHandle::getFilePath() {
	return m_filePath;
}
bool          h3d::FileHandle::isOpen() {
	return m_isOpen;
}
/////////////////////////////////////////////////////////////////