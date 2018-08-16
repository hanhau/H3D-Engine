#include "../../H3D/Audio/Audio.hpp"
#include "../../H3D/MemoryMng/base_alloc.hpp"
#include <algorithm>
#include <AL/al.h>
/////////////////////////////////////////////////////////////////
// Loader Prototypes
bool loadWAV(const char path[],
			 ALuint& buffer, ALsizei& size, ALsizei& frequency,
			 ALenum& format);
bool loadOGG(const char path[],
			 ALuint& buffer, ALsizei& size, ALsizei& frequency,
			 ALenum& format);
/////////////////////////////////////////////////////////////////
// Implementation of AudioBuffer
/////////////////////////////////////////////////////////////////
h3d::Audio::FileType h3d::Audio::AudioBuffer::getType() { return m_fileType; }
/////////////////////////////////////////////////////////////////
h3d::Audio::AudioBuffer::AudioBuffer(){
	alGenBuffers(1, &m_bufferID);
}
h3d::Audio::AudioBuffer::~AudioBuffer() {
	alDeleteBuffers(1, &m_bufferID);
}
/////////////////////////////////////////////////////////////////
bool h3d::Audio::AudioBuffer::loadFromFile(char path[])
{
	// Check if file extension is supported
	std::string fileExtension(path);

	fileExtension.erase(fileExtension.begin(),
						std::find(fileExtension.begin(),fileExtension.end(),'.')+1);
	if (fileExtension != "wav" && fileExtension != "ogg") return false;
	
	// Individual loading functions
	bool loadState;
	if (fileExtension == "wav")
	{
		m_fileType = FileType::WAV;
		loadState = loadWAV(path, m_bufferID, m_size, m_frequency, m_format);
	}
	else if (fileExtension == "ogg")
	{
		m_fileType = FileType::OGG;
		loadState = loadOGG(path, m_bufferID, m_size, m_frequency, m_format);
	}
	else loadState = false;

	return loadState;
}
/////////////////////////////////////////////////////////////////
