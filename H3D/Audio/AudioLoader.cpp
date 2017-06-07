#include "..\Utilities.hpp"
#include "..\FileSystem.hpp"
#include "../FileDataStructures.hpp"
#include "../Utilities.hpp"

#include "../externals.h"
#include STR(OPENAL_INCLUDE/al.h)
#include STR(OPENAL_INCLUDE/alc.h)
#include STR(LIBVORBIS_INCLUDE/vorbis/vorbisfile.h)
#include STR(LIBVORBIS_INCLUDE/vorbis/vorbisenc.h)


#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
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
		if (0 != memcmp(wavHeader.chunkID,"RIFF",4) ||
			0 != memcmp(wavHeader.riffType, "WAVE", 4) ||
			0 != memcmp(wavFormat.subChunkID, "fmt ", 4))
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
	h3d::FileHandle filehandle;
	char* file_data = NULL;

	OggVorbis_File *oggfile;
	ov_callbacks oggcallbacks = OV_CALLBACKS_DEFAULT;

	// Open file_stream
	filehandle.open(path);
	if (FALSE == filehandle.isOpen()) {
		if (h3d::DebugMode) Log.error("Unable to loadOgg(%s)",path);
		return false;
	}
	
	// Get entire file
	file_data = new char[filehandle.getFileSize()];
	filehandle.read(file_data, filehandle.getFileSize());
	
	// OGG specific loading
	if (0 > ov_open_callbacks(file_data,
							  oggfile, NULL, 0,
							  oggcallbacks)) {
		if (h3d::DebugMode) Log.error("%s is not a OGG File",path);
		return false;
	}

	// Get OGG Info
	vorbis_info *vi = ov_info(oggfile,-1);

	// Decode Data
	bool eof = false;
	char pcmdata[CHUNK_SIZE];
	int curr;
	std::vector<char> finalpcm;

	while (!eof)
	{
		long ret = ov_read(oggfile,
						   pcmdata,
						   sizeof(pcmdata),
						   0, 2, 1, &curr);
		if (ret == 0) eof = true;
		else if (ret < 0);

		// give pcm further
		std::move(pcmdata,pcmdata+ret,finalpcm.end());
	}

	// Set OpenAL param settings
	frequency = vi->rate;
	if (vi->channels == 1)
		format = AL_FORMAT_MONO16;
	else if (vi->channels == 2)
		format = AL_FORMAT_STEREO16;
	else {
		if (h3d::DebugMode) Log.error("Unsupported channel count in %s",path);
		return false;
	}
	size = finalpcm.size();

	// Set OpenAL buffer
	alBufferData(buffer, format, finalpcm.data(), size, frequency);

	// Exit successful
	ov_clear(oggfile);
	filehandle.close();
	return true;
}