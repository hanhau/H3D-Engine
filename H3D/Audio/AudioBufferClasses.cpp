#include "..\Audio.hpp"
/////////////////////////////////////////////////////////////////
// Loader Prototypes
bool loadWAV(char path[],
			 ALuint& buffer, ALsizei& size, ALsizei& frequency,
			 ALenum& format);
bool loadOGG(char path[],
			 ALuint& buffer, ALsizei& size, ALsizei& frequency,
			 ALenum& format);
/////////////////////////////////////////////////////////////////
// Implementation of AudioBuffer
/////////////////////////////////////////////////////////////////
const int h3d::Audio::AudioBuffer::Type::WAV = 1;
const int h3d::Audio::AudioBuffer::Type::OGG = 2;
int h3d::Audio::AudioBuffer::getType() { return m_fileType; }
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
	fileExtension.erase(fileExtension.begin(), std::find(fileExtension.begin(),fileExtension.end(),'.'));
	if (fileExtension != ".wav" && fileExtension != ".ogg") return false;
	
	// Open filestream
	std::ifstream file_stream(path,std::ios::in|std::ios::binary);
	if (!file_stream.is_open()) return false;
	
	// Individual loading functions
	bool loadState;
	if (fileExtension == ".wav")
	{
		m_fileType = Type::WAV;
		loadState = loadWAV(path, m_bufferID, m_size, m_frequency, m_format);
	}
	else if (fileExtension == ".ogg")
	{
		m_fileType = Type::OGG;
		loadState = loadOGG(path, m_bufferID, m_size, m_frequency, m_format);
	}
	else loadState = false;

	return loadState;
}
/////////////////////////////////////////////////////////////////
// Implementation of AudioBufferStream
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////