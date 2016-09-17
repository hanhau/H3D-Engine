#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include "Audio.hpp"
#include <fstream>
#include <Windows.h>
/////////////////////////////////////////////////////////////////
// AudioAccessories
/////////////////////////////////////////////////////////////////
namespace h3d{
	namespace Audio {
		class WaveFile
		{
		private:
			WAVEFORMATEX   m_waveFormatEx;
			XAUDIO2_BUFFER m_xa2Buffer;
			char*          m_buffer;
		public:
		   // Constructor/Destructor
			H3D_API WaveFile();
			H3D_API WaveFile(char Path[]);
			H3D_API ~WaveFile();

			// File operations
			bool H3D_API loadFromFile(char Path[]);
			bool H3D_API saveToFile(char Path[]);
		};
}}
/////////////////////////////////////////////////////////////////
