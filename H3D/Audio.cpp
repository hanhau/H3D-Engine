#include "Audio.hpp"
#include <fstream>
#include <algorithm>
/////////////////////////////////////////////////////////////////
// Implementation of Audio Engine Functions
/////////////////////////////////////////////////////////////////
// Hidden global data
static bool gInitialized = false;
static ALCdevice* gDevice;
static ALCcontext* gContext;
static bool gEAX20Support;
/////////////////////////////////////////////////////////////////
bool h3d::Audio::initialize(char* default_device)
{
	if (gInitialized) shutdown();
	gDevice = alcOpenDevice(default_device);

	if (gDevice)
	{
		gContext = alcCreateContext(gDevice, 0);
		alcMakeContextCurrent(gContext);
	}

	gEAX20Support = alIsExtensionPresent("EAX2.0");
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