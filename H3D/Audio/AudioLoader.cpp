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
	h3d::Log.info("Loading %s now ...",path);

	// Temporary buffers
	std::vector<char> fileBuffer;

	// Loading whole file into a temporary buffer
	h3d::FileHandle fileHandle;
	fileHandle.open(path, h3d::FileHandle::Params.LoadIntoMemory |
	                      h3d::FileHandle::Params.ExclusiveAccess);

	/////////////////////////////////////////////////////////////
	// Actual file loading
	h3d::FileType::WAV::Header wavHeader;
	h3d::FileType::WAV::Format wavFormat;
	h3d::FileType::WAV::Data   wavData;
	
	h3d::setObjectFromFileHandle(wavHeader, fileHandle);
	h3d::setObjectFromFileHandle(wavFormat, fileHandle);
	h3d::setObjectFromFileHandle(wavData, fileHandle);
	
	fileHandle.close();

	/////////////////////////////////////////////////////////////
	// Return
	if (h3d::DebugMode)
		h3d::Log.info("Finished loading %s.",path);
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