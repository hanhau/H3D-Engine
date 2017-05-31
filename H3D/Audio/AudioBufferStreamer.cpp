#include "..\FileSystem.hpp"
#include "..\FileDataStructures.hpp"
#include "..\Utilities.hpp"
#include <al.h>
#include <vorbisfile.h>
/////////////////////////////////////////////////////////////////
// OGG Streaming Utils
/////////////////////////////////////////////////////////////////
extern bool openOGGStream(h3d::FileHandle& fh, char path[],
						  // OpenAL params
						  ALsizei &frequency,
						  ALenum  &format,
						  // OGG specific
						  OggVorbis_File* oggfile,
						  ov_callbacks oggcallbacks)
{
	// Open File
	if (FALSE == fh.open(path)) {
		if (h3d::DebugMode) Log.error("Unable to open OGG Stream");
		return false;
	}

	// Get OGG Intel
	

	// Set OpenAL params
	

	return true;
}
extern bool closeOGGStream(h3d::FileHandle &fh)
{

}
extern unsigned long catchOGGStream(h3d::FileHandle& fh, long size, char* dst)
{																				 
	
}
/////////////////////////////////////////////////////////////////
// WAV Streaming Utils
/////////////////////////////////////////////////////////////////
extern bool openWAVStream(h3d::FileHandle& fh, char path[],
						  // OpenAL params
						  ALsizei &frequency,
						  ALenum  &format)
{
	// Open File
	if (FALSE == fh.open(path)) {
		if (h3d::DebugMode) Log.error("Unable to open OGG Stream");
		return false;
	}

	h3d::FileType::WAV::Header wavHeader;
	h3d::FileType::WAV::Format wavFormat;

	h3d::setObjectFromFileHandle(wavHeader, fh);
	h3d::setObjectFromFileHandle(wavFormat, fh);

	// Validate file contents
	if (0 != memcmp(wavHeader.chunkID, "RIFF", 4) ||
		0 != memcmp(wavHeader.riffType, "WAVE", 4) ||
		0 != memcmp(wavFormat.subChunkID, "fmt ", 4))
	{
		Log.error("%s is probably a invalid format", path);
	}
	if (wavFormat.audioFormat != 1) { // Check for PCM
		Log.error("%s is not PCM audio data !", path);
		return false;
	}

	// Set OpenAL params
	frequency = wavFormat.sampleRate;
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
	else {
		Log.error("%s has a unsupported amount of channels (%d)", path, wavFormat.numChannels);
		return  false;
	}

	// Opened successfully
	return true;
}
extern bool closeWAVStream(h3d::FileHandle& fh)
{
	fh.close();
	return true;
}
extern unsigned long catchWAVStream(h3d::FileHandle& fh, long size, char* dst)
{
	return fh.read(dst, size);
}
/////////////////////////////////////////////////////////////////