#include "..\Audio.hpp"
#include "..\FileSystem.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of AudioBufferStream
namespace h3d {
	/////////////////////////////////////////////////////////////
	Audio::AudioBufferStream::AudioBufferStream() {}
	Audio::AudioBufferStream::~AudioBufferStream() {}
	/////////////////////////////////////////////////////////////
	bool Audio::AudioBufferStream::open(char Path[])
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
		}
		else if (fileExtension == "ogg")
		{
			m_fileType = FileType::OGG;
		}
		else loadState = false;

		return loadState;

		return true;
	}
}
/////////////////////////////////////////////////////////////////
bool openOGGStream(h3d::FileHandle& fh, char path[],
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
struct PCMChunk{
	char *data;
	bool finished;
};
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
	bool running;
	PCMChunk chunks[4];	

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


		break;
	}
}
/////////////////////////////////////////////////////////////////