#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
// external
#include <al.h>
#include <alc.h>
#include <vorbisenc.h>
#include <vorbisfile.h>
// cpp headers
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
// internal 
#include "Utilities.hpp"
#include "Vector.hpp"
#include "AudioAccessories.hpp"
/////////////////////////////////////////////////////////////////
// Audio Module
/////////////////////////////////////////////////////////////////
namespace h3d{
	namespace Audio {
		/////////////////////////////////////////////////////////
		// Audio Engine Functions
		/////////////////////////////////////////////////////////
		bool H3D_API initialize(char* default_device = NULL);
		bool H3D_API shutdown();
		/////////////////////////////////////////////////////////
		// global Listener Class
		/////////////////////////////////////////////////////////
		class tagListener 
		{
		public:
			tagListener();
			~tagListener();

			void setMasterGain(float gain);
			void setPosition(h3d::Vec3<float> pos);
			void setVelocity(h3d::Vec3<float> vel);
			void setOrientation(h3d::Vec3<float>at,h3d::Vec3<float>up);
		};
		extern tagListener H3D_API Listener;
		/////////////////////////////////////////////////////////
		// Audio Scene
		/////////////////////////////////////////////////////////
		class Scene
		{
		public:

		private:

		};
		/////////////////////////////////////////////////////////
		// Audio Buffer Classes
		/////////////////////////////////////////////////////////
		// static Audio Object
		class AudioSource;
		class AudioBuffer
		{
			friend AudioSource;
		private:
			ALuint  m_bufferID;
			ALsizei m_size;
			ALsizei m_frequency;
			ALenum  m_format;
			int     m_fileType;
		public:
			// Con-/Destructor
			H3D_API AudioBuffer();
			H3D_API ~AudioBuffer();
			
			// Identify Type
			struct Type{
				static const int WAV;
				static const int OGG;
			};
			int H3D_API getType();

			// File Loading
			bool H3D_API loadFromFile(char path[]);
		};
		/////////////////////////////////////////////////////////
		// streamed Audio Object
		class AudioBufferStream
		{
		private:
			
		public:
			H3D_API AudioBufferStream();
			H3D_API ~AudioBufferStream();

			bool H3D_API open(char Path[]);
		};
		/////////////////////////////////////////////////////////
		// Audio Sources
		/////////////////////////////////////////////////////////
		class AudioSource
		{
		private:
			ALuint m_sourceID;
		public:
			// Con-/Destructor
			H3D_API AudioSource();
			H3D_API ~AudioSource();

			// Add Buffers to queue
			bool H3D_API queueBuffer(const AudioBuffer& ab_static);
			bool H3D_API queueBuffer(const AudioBufferStream& ab_stream);
			bool H3D_API unqueueBuffer(const AudioBuffer& ab_static);
			bool H3D_API unqueueBuffer(const AudioBufferStream& ab_stream);

			// Actions
			void H3D_API play();
			void H3D_API pause();
			void H3D_API stop();
			void H3D_API rewind();

			// Set Properties
			void H3D_API setPosition(h3d::Vec3<float> pos);
			void H3D_API setVelocity(h3d::Vec3<float> vel);
			void H3D_API setDirection(h3d::Vec3<float> dir);

			void H3D_API setPitch(float val);
			void H3D_API setGain(float val);
		};
		/////////////////////////////////////////////////////////
	}
	
}