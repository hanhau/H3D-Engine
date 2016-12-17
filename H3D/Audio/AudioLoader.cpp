#include "../FileDataStructures.hpp"
#include "../Utilities.hpp"
#include <al.h>
#include <alc.h>
#include <vorbisfile.h>
#include <vorbisenc.h>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
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

	
	// Open Filestream
	file_stream.open(path, std::ios::in | std::ios::binary);
	if (!file_stream.is_open())
		return false;

	// Check wavHeader
	file_stream.read((char*)&wavHeader, sizeof(wavHeader));
	if (wavHeader.chunkID != "RIFF" || wavHeader.riffType != "WAVE")
		return false;
		
		// Check wavFormat
	file_stream.read((char*)&wavFormat, sizeof(wavFormat));
	if (wavFormat.subChunkID != "fmt ")
		return false;
		


	file_stream.read((char*)&wavData, sizeof(wavData));

	// Loading final Data
	audioData = new unsigned char[1];
		
	// Set OpenAL Properties
	frequency = wavFormat.sampleRate;

	if (wavFormat.numChannels == 1)
	{
		if (wavFormat.bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else if (wavFormat.bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
		else return false;
	}
	else if (wavFormat.numChannels == 2)
	{
		if (wavFormat.bitsPerSample == 8)
			format = AL_FORMAT_STEREO8;
		else if (wavFormat.bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;
		else return false;
	}
	return false;

	// Free resources
	delete audioData;
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
// .ogg Loading	
/////////////////////////////////////////////////////////////////
#define CHUNK_SIZE 4096
extern bool loadOGG(char path[],
					ALuint& buffer, ALsizei& size, ALsizei& frequency,
					ALenum& format)
{
	// Temporary variables
	OggVorbis_File oggFile;
	vorbis_info    vorbisInfo;
	FILE* file_stream;
	std::vector<char> audioBuffer;
	std::vector<char> finalAudio;
	long bytes_read = 0;

	// Open file_stream
	file_stream = fopen(path, "br");
	if (file_stream == NULL)
		throw("Unable to open File");
		
	// Start vorbis encoding for this file
	ov_fopen(path, &oggFile);
	vorbis_info_init(&vorbisInfo);

	// Prepare Buffers
	audioBuffer.clear();
	audioBuffer.resize(CHUNK_SIZE);
	finalAudio.clear();
		
	// Read complete file
	do {
		bytes_read = ov_read(&oggFile, audioBuffer.data(), CHUNK_SIZE, 0, 2, 1, NULL);
		finalAudio.insert(std::end(finalAudio),
						  std::begin(audioBuffer),
						  std::end(audioBuffer));
		
	} while (bytes_read != 0);
	
	// Set Information for OpenAL
	size = finalAudio.size();
	frequency = vorbisInfo.rate;
	if (vorbisInfo.channels == 1)
	{
		format = AL_FORMAT_MONO16;
	}
	else if (vorbisInfo.channels == 2)
	{
		format = AL_FORMAT_STEREO16;
	}
	else throw ("Error detecting channel count");

	// Fill OpenAL Buffers
	alBufferData(buffer, format, (ALvoid*)finalAudio.data(), finalAudio.size(), frequency);

	// Clear up variables
	ov_clear(&oggFile);
	return true;
}
/////////////////////////////////////////////////////////////////
// .ogg Streaming
/////////////////////////////////////////////////////////////////
extern bool openStreamOGG()
{

}
/////////////////////////////////////////////////////////////////