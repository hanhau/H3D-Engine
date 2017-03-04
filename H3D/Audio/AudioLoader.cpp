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
#include "..\Utilities.hpp"
#include "..\FileSystem.hpp"
/////////////////////////////////////////////////////////////////
// .wav Loading
/////////////////////////////////////////////////////////////////
extern bool loadWAV(char path[],
					ALuint& buffer,ALsizei& size,ALsizei& frequency,
					ALenum& format)
{
	// Info Log
	Log.info("Loading %s now ...",path);

	// Temporary buffers
	std::vector<char> fileBuffer;

	// Loading whole file into a temporary buffer
	h3d::FileHandle fileHandle;
	if (!fileHandle.open(path, 0)) {
		Log.error("Unable to open h3d::FileHandle for %s", path);
		return false;
	}

	/////////////////////////////////////////////////////////////
	// Actual file loading
	h3d::FileType::WAV::Header wavHeader;
	h3d::FileType::WAV::Format wavFormat;
	h3d::FileType::WAV::Data   wavData;
	
	h3d::setObjectFromFileHandle(wavHeader, fileHandle);
	h3d::setObjectFromFileHandle(wavFormat, fileHandle);
	h3d::setObjectFromFileHandle(wavData, fileHandle);
	
	// Validate file contents
		if (0 != memcmp(wavHeader.chunkID,new char[4]{'R','I','F','F'},4) ||
			0 != memcmp(wavHeader.riffType, new char[4]{ 'W','A','V','E' }, 4) ||
			0 != memcmp(wavFormat.subChunkID, new char[4]{ 'f','m','t',' ' }, 4))
	{
		Log.error("%s is probably a invalid format",path);
	}
	if (wavFormat.audioFormat != 1) { // Check for PCM
		Log.error("%s is not PCM audio data !",path);
		return false;
	}

	// Load PCM from file
	auto *pcmdata = new char[wavData.subChunk2Size];
	fileHandle.read(pcmdata, wavData.subChunk2Size);
	
	// Set OpenAL format
	if (wavFormat.numChannels == 1)
	{
		if (wavFormat.bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else if (wavFormat.bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
	}
	else if (wavFormat.numChannels == 2)
	{
		if (wavFormat.bitsPerSample == 8)
			format = AL_FORMAT_STEREO8;
		else if (wavFormat.bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;
	}
	else{
		Log.error("%s has a unsupported amount of channels (%d)", path, wavFormat.numChannels);
		return  false;
	}

	// Set OpenAL Buffer accordingly
	alBufferData(buffer, format, pcmdata, size = wavData.subChunk2Size,
				 frequency = wavFormat.sampleRate);

	// cleanup
	fileHandle.close();
	delete[] pcmdata;

	// Return
	if (h3d::DebugMode)
		Log.info("Finished loading %s.",path);
	return true;
}
/////////////////////////////////////////////////////////////////
// .ogg Loading	
/////////////////////////////////////////////////////////////////
#define CHUNK_SIZE 4096
extern bool loadOGG(char path[],
					ALuint& buffer, ALsizei& size, 
					ALsizei& frequency,
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