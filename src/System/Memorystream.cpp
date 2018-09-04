#include "../../H3D/System/Memorystream.hpp"
#include <memory.h>
/////////////////////////////////////////////////////////////////
// Implementation of MemoryStream
/////////////////////////////////////////////////////////////////
h3d::MemoryStream::MemoryStream() {
	m_bufferPtr = nullptr;
	m_bufferSize = m_currentPos = 0;
}
h3d::MemoryStream::~MemoryStream() {
	m_bufferPtr = nullptr;
	m_bufferSize = m_currentPos = 0;
}
/////////////////////////////////////////////////////////////////
void h3d::MemoryStream::open(char* buffer, unsigned long size)
{
	m_bufferPtr = &buffer;
	m_bufferSize = size;
	m_currentPos = 0;
}
void h3d::MemoryStream::close()
{
	m_bufferPtr = nullptr;
	m_bufferSize = 0;
}
/////////////////////////////////////////////////////////////////
uint32_t h3d::MemoryStream::read(uint32_t bytes,void* output)
{
	if (bytes + m_currentPos > m_bufferSize)
	{
		memcpy(output, *m_bufferPtr + m_currentPos, bytes);
		return bytes;
	}
	else {
		output = nullptr;
		return 0;
	}
}