#include "../../H3D/Audio/Audio.hpp"
#include "../../H3D/System/FileSystem.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>
#include <vorbis/codec.h>
/////////////////////////////////////////////////////////////////
// Implementation of AudioBufferStream
namespace h3d {
	/////////////////////////////////////////////////////////////
	Audio::AudioBufferStream::AudioBufferStream() {}
	Audio::AudioBufferStream::~AudioBufferStream() {}
	/////////////////////////////////////////////////////////////
	bool Audio::AudioBufferStream::open(const char Path[])
	{
		// Check if file extension is supported
		std::string fileExtension(Path);

		fileExtension.erase(fileExtension.begin(),
							std::find(fileExtension.begin(), fileExtension.end(), '.') + 1);
		if (fileExtension != "wav" && fileExtension != "ogg") return false;

		// Individual loading functions
		bool loadState;
		if (fileExtension == "wav")
		{
			m_fileType = FileType::WAV;			
			loadState = true;
		}
		else if (fileExtension == "ogg")
		{
			m_fileType = FileType::OGG;
			loadState = true;
		}
		else loadState = false;

		return loadState;
	}
}
/////////////////////////////////////////////////////////////////
bool openOGGStream(h3d::FileHandle& fh,const char path[],
				   // OpenAL params
				   ALsizei &frequency,
				   ALenum  &format,
				   // OGG specific
				   OggVorbis_File* oggfile,
				   ov_callbacks oggcallbacks);
bool closeOGGStream(h3d::FileHandle &fh);
unsigned long catchOGGStream(h3d::FileHandle& fh, long size, char* dst);
bool openWAVStream(h3d::FileHandle& fh, char path[],
				   // OpenAL params
				   ALsizei &frequency,
				   ALenum  &format);
bool closeWAVStream(h3d::FileHandle &fh);
unsigned long catchWAVStream(h3d::FileHandle& fh, long size, char* dst);
/////////////////////////////////////////////////////////////////
namespace {
	struct PCMChunk {
		char *data;
		bool finished;
	};
}
namespace h3d { 
	class FileHandle; 
}
enum class thread_action {
	next_chunk,finish
};
/////////////////////////////////////////////////////////////////
// Fishing Thread
void ABfishingThread(thread_action &ta,
					 h3d::FileHandle &input_file,char path[],
					 h3d::Audio::FileType m_fileType,
					 ALsizei &freq,ALenum &form)
{
	// Temp vars
	bool running = true;
	PCMChunk chunks[4] = { 0 };

	switch (m_fileType)
	{
	/////////////////////////////////////////////////////////////
	// OGG Streaming
	case h3d::Audio::FileType::OGG:
		
		break;
	/////////////////////////////////////////////////////////////
	// WAV Streaming
	case h3d::Audio::FileType::WAV:
		// open
		openWAVStream(input_file, path, freq, form);

		// processing


		// clean up
		closeWAVStream(input_file);
		break;
	}
}
/////////////////////////////////////////////////////////////////