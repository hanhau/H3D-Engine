#include "../FileDataStructures.hpp"
#include "../Utilities.hpp"
#include <al.h>
#include <alc.h>
#include <fstream>
#include <iostream>
/////////////////////////////////////////////////////////////////
// .wav Loading
/////////////////////////////////////////////////////////////////
extern bool loadWAV(char path[],
					ALuint& buffer,ALsizei& size,ALsizei& frequency,
					ALenum& format)
{
	// Temporary values
	h3d::FileType::WAV::Header wavHeader;
	h3d::FileType::WAV::Format wavFormat;
	h3d::FileType::WAV::Data   wavData;
	unsigned char*			   audioData;
	std::ifstream file_stream;

	try {
		// Open Filestream
		file_stream.open(path, std::ios::in | std::ios::binary);
		if (!file_stream.is_open())
			throw("Couldn´t open File");

		// Check wavHeader
		file_stream.read((char*)&wavHeader, sizeof(wavHeader));
		if (wavHeader.chunkID != "RIFF" || wavHeader.riffType != "WAVE")
			throw("Invalid Header");
		
		// Check wavFormat
		file_stream.read((char*)&wavFormat, sizeof(wavFormat));
		if (wavFormat.subChunkID != "fmt ")
			throw("Invalid wavFormat");

		file_stream.read((char*)&wavData, sizeof(wavData));

		// Loading final Data
	}
	catch (std::string error) {
		std::cout << error << " : trying to load " << path << std::endl;
		file_stream.close();
		return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////
// .ogg Loading	
/////////////////////////////////////////////////////////////////
extern bool loadOGG()
{

}
/////////////////////////////////////////////////////////////////