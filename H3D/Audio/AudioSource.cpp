#include "..\Audio.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of AudioSource
/////////////////////////////////////////////////////////////////
h3d::Audio::AudioSource::AudioSource()
{
	alGenSources(1, &m_sourceID);
}
h3d::Audio::AudioSource::~AudioSource()
{
	alDeleteSources(1, &m_sourceID);
}
/////////////////////////////////////////////////////////////////
bool h3d::Audio::AudioSource::queueBuffer(const h3d::Audio::AudioBuffer& ab_static)
{
	alSourceQueueBuffers(m_sourceID, 1, &ab_static.m_bufferID);
	return true;
}
bool h3d::Audio::AudioSource::queueBuffer(const h3d::Audio::AudioBufferStream& ab_stream)
{
	return false;
}
/////////////////////////////////////////////////////////////////
bool h3d::Audio::AudioSource::unqueueBuffer(const h3d::Audio::AudioBuffer& ab_static)
{
	return false;
}
bool h3d::Audio::AudioSource::unqueueBuffer(const h3d::Audio::AudioBufferStream& ab_stream)
{
	return false;
}
/////////////////////////////////////////////////////////////////
// Actions
void h3d::Audio::AudioSource::play() {
	alSourcePlay(m_sourceID);
}
void h3d::Audio::AudioSource::pause() {
	alSourcePause(m_sourceID);
}
void h3d::Audio::AudioSource::stop() {
	alSourceStop(m_sourceID);
}
void h3d::Audio::AudioSource::rewind() {
	alSourceRewind(m_sourceID);
}
/////////////////////////////////////////////////////////////////
void h3d::Audio::AudioSource::setPosition(h3d::Vec3<float> pos) {
	alSource3f(m_sourceID,AL_POSITION, pos.x, pos.y, pos.z);
}
void h3d::Audio::AudioSource::setVelocity(h3d::Vec3<float> vel) {
	alSource3f(m_sourceID, AL_VELOCITY, vel.x, vel.y, vel.z);
}
void h3d::Audio::AudioSource::setDirection(h3d::Vec3<float> dir) {
	alSource3f(m_sourceID,AL_DIRECTION,dir.x,dir.y,dir.z);
}
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////