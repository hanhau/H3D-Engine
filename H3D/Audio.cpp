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
static ALboolean gEAX20Support;
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
h3d::Audio::tagListener::tagListener() {}
h3d::Audio::tagListener::~tagListener() {}
/////////////////////////////////////////////////////////////////
void h3d::Audio::tagListener::setMasterGain(float gain) {
	alListenerf(AL_GAIN, gain);
}
void h3d::Audio::tagListener::setPosition(h3d::Vec3<float> pos) {
	alListener3f(AL_POSITION,pos.x,pos.y,pos.z);
}
void h3d::Audio::tagListener::setVelocity(h3d::Vec3<float> vel) {
	alListener3f(AL_VELOCITY,vel.x,vel.y,vel.z);
}
void h3d::Audio::tagListener::setOrientation(h3d::Vec3<float>at, h3d::Vec3<float>up) {
	float vals[] = { at.x, at.y, at.y,up.x, up.y, up.z };
	alListenerfv(AL_ORIENTATION,vals);
}
/////////////////////////////////////////////////////////////////