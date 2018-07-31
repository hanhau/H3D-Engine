#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/Utilities.hpp"
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
h3d::FileHandle::FileHandle() 
{
	
}
h3d::FileHandle::FileHandle(std::string path, bool filemapping){
	open(path, filemapping);
}
h3d::FileHandle::~FileHandle() 
{

}
h3d::FileHandle& h3d::FileHandle::operator=(h3d::FileHandle& otherFh) {
	
	return *this;
}
/////////////////////////////////////////////////////////////////
bool h3d::FileHandle::open(std::string path, 
						   std::initializer_list<h3d::FileHandle::Mode> il, 
						   bool a)
{
	bool read = false, write = false, trunc = false;
	for (auto &iter : il) {
		if (iter == h3d::FileHandle::Mode::Read)
			read = true;
		if (iter == h3d::FileHandle::Mode::Write)
			write = true;
		if (iter == h3d::FileHandle::Mode::Trunc)
			trunc = true;
	}

	h3dverify(path.size() == 0);

	return false;
}
bool h3d::FileHandle::open(std::string path, bool filemapping)
{
	h3dverify(path.size() == 0);

#ifdef __linux__
	// TODO 
#elif defined _WIN32 || _WIN64
		
	//  Parameter checking
	DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

	// Create Handle
	m_fileHandle = CreateFileA(path.c_str(),
							  GENERIC_READ | GENERIC_WRITE,
							  FILE_SHARE_WRITE,
							  NULL,
							  CREATE_NEW,
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
	if (m_fileHandle == INVALID_HANDLE_VALUE) {
		h3d::Log::debug("Cannot create new file %s",GetLastError());
	m_fileHandle = CreateFileA(path.c_str(),
							  GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE,
							  dwShareMode,
							  NULL,
							  OPEN_EXISTING,
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
	}
	// Error handling
	if (m_fileHandle == INVALID_HANDLE_VALUE)
	{
		h3d::Log::error("Unable to open %s",path.c_str());
		return false;
	}
	
	// Save Intel about opened File
	m_fileSizeBytes = GetFileSize(m_fileHandle, NULL);
	m_isOpen = true;
	m_filePath = path;
	
	if (filemapping)
	{
		m_mappedFileHandle = CreateFileMapping(m_fileHandle,
											   NULL,
											   PAGE_EXECUTE_READWRITE,
											   0, 0,
											   NULL);
		if (m_mappedFileHandle == NULL) {
			if (h3d::DebugMode)
				h3d::Log::error("Error @ CreateFileMapping");
			return false;
		}

		m_mappedData = std::make_shared<void*>(
								MapViewOfFileEx(m_mappedFileHandle,
												FILE_MAP_ALL_ACCESS,
												0, 0,
												0,
												NULL)
												);
		if (m_mappedData.get() == NULL) {
			if (h3d::DebugMode)
				h3d::Log::error("Error @ MapViewOfFileEx");
			return false;
		}

		m_isMapped = true;
	}
#endif

	// Return successfully
	return true;
}
bool h3d::FileHandle::close()
{
	if (m_isMapped)
		UnmapViewOfFile(m_mappedData.get());

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
		h3d::Log::info("Unable to set filepointer.");
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