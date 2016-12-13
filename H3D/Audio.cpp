#include "Audio.hpp"
#include <fstream>
#include <algorithm>
#include <vorbisenc.h>
#include <vorbisfile.h>
/////////////////////////////////////////////////////////////////
// Implementation of Audio Engine Functions
/////////////////////////////////////////////////////////////////
// Hidden global data
static bool gInitialized = false;

static ALCdevice* gDevice;
static ALCcontext* gContext;
static bool gEAX20Support;

static vorbis_info* vorbisInfo;
/////////////////////////////////////////////////////////////////
bool h3d::Audio::initialize(char* default_device)
{
	if (gInitialized) shutdown();

	// OpenAL
	gDevice = alcOpenDevice(default_device);
	if (gDevice)
	{
		gContext = alcCreateContext(gDevice, 0);
		alcMakeContextCurrent(gContext);
	}
	else return false;
	gEAX20Support = alIsExtensionPresent("EAX2.0");

	// libvorbis
	vorbis_info_init(vorbisInfo);

	return gInitialized = true;
}
bool h3d::Audio::shutdown()
{	  
	gContext = alcGetCurrentContext();
	gDevice = alcGetContextsDevice(gContext);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(gContext);
	alcCloseDevice(gDevice);

	gInitialized = false;
	return true;
}
/////////////////////////////////////////////////////////////////
// Listener Implementations
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////