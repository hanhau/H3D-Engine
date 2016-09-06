#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
// Taking XAudio2 Version
/////////////////////////////////////////////////////////////////
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <x3daudio.h>
#include <xapofx.h>
#pragma comment(lib,"xaudio2.lib")
/////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <string>
#include <map>
#include <vector>

#include "Utilities.hpp"
#include "Vector.hpp"
/////////////////////////////////////////////////////////////////
// Audio Module
/////////////////////////////////////////////////////////////////
namespace h3d{
	namespace Audio {
		/////////////////////////////////////////////////////////
		//	Global Stuff		
		/////////////////////////////////////////////////////////
		IXAudio2*				g_engine;
		IXAudio2MasteringVoice* g_master;
		X3DAUDIO_HANDLE*        g_x3dAudioHandle;
		/////////////////////////////////////////////////////////
		// Audiomanagment and Settings
		/////////////////////////////////////////////////////////
		namespace Settings {
			// Values
			uint32_t					 g_speakerMask;
			float						 g_speedOfSound;
			std::map<std::string, float> g_volumeGroupMap;

			// Functions
			void _declspec(dllexport) setVolumeArea(char area[],float val);
			bool _declspec(dllexport) getVolumeArea(char area[], float *val);
			void _declspec(dllexport) setSpeakerChannelMask(char config[]);
			void _declspec(dllexport) setSpeedOfSound(float val);

			// Save and load from a File (txt or binary)
			bool _declspec(dllexport) loadFromFile(char path[]);
			bool _declspec(dllexport) saveToFile  (char path[]);
		}
		bool _declspec(dllexport) init();
		bool _declspec(dllexport) shutdown();

		/////////////////////////////////////////////////////////
		// Class Effect
		/////////////////////////////////////////////////////////
		class Effect
		{
		private:
			IXAudio2SubmixVoice *m_subMix;
			
		public:
			// Con-/Destructor
			Effect();
			~Effect();
		};
		/////////////////////////////////////////////////////////
		// Class EffectChain
		/////////////////////////////////////////////////////////
		class EffectChain
		{
		private:
			std::vector<Effect> m_effectVec;
		public:
			bool addEffect(h3d::Audio::Effect &effect);
		};
		/////////////////////////////////////////////////////////
		// Class Sound
		/////////////////////////////////////////////////////////
		class Sound
		{
		private:
			// XAudio2 Stuff
			IXAudio2SourceVoice* m_voice;
			
			// Sound Volume
			std::string m_volumegroup;
		public:
			// Con-/Destructor
			Sound();
			~Sound();

			// Loading and Streaming
			bool loadFromFile(char Path[]);

			// Effect Handling
			void addEffect(h3d::Audio::Effect effect);
			
		};
		/////////////////////////////////////////////////////////
		//	Class Audio Stream
		/////////////////////////////////////////////////////////
		class AudioStream
		{
		private:

		public:
			
		};
		/////////////////////////////////////////////////////////
		// Class AudioObject
		/////////////////////////////////////////////////////////
		class tag3DAudioObject
		{
		private:
			X3DAUDIO_EMITTER m_x3daudioEmitter;
			X3DAUDIO_CONE    m_x3daudioCone;
		public:
			// Updating the Emitter
			void updatePos(h3d::Vec3<float> Pos);
			void update();

			// get Information

		};
		/////////////////////////////////////////////////////////
		// Class Listener
		/////////////////////////////////////////////////////////
		class Listener
		{
		private:
			// XAudio2 Stuff
			X3DAUDIO_LISTENER m_x3daudioListener;
			
		public:
			void updatePos(h3d::Vec3<float> Pos);
		};
		/////////////////////////////////////////////////////////
	}
}