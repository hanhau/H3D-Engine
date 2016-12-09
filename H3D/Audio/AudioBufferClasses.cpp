#include "..\Audio.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of AudioBuffer
/////////////////////////////////////////////////////////////////
h3d::Audio::AudioBuffer::AudioBuffer()
{
	alGenBuffers(1, &m_bufferID);
}
h3d::Audio::AudioBuffer::~AudioBuffer() 
{
	alDeleteBuffers(1, &m_bufferID);
}
/////////////////////////////////////////////////////////////////
bool h3d::Audio::AudioBuffer::loadFromFile(char path[])
{
	// Check if file extension is supported
	std::string fileExtension(path);
	fileExtension.erase(0, fileExtension.find_last_of('.'));
	if (fileExtension != "wav" && fileExtension != "ogg") return false;
	
	// Open filestream
	std::ifstream file_stream(path,std::ios::in|std::ios::binary);
	if (!file_stream.is_open()) return false;
	
	// Individual loading functions
	bool loadState = false;
	

	return loadState;
}
/////////////////////////////////////////////////////////////////
// Implementation of AudioBufferStream
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////