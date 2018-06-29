#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "Audio.hpp"
#include <fstream>
#include <Windows.h>
#include "FileDataStructures.hpp"
/////////////////////////////////////////////////////////////////
// AudioAccessories
/////////////////////////////////////////////////////////////////
namespace h3d{
	namespace Audio {
		class WaveFile
		{
		private:
			WAVEFORMATEX   m_waveFormatEx;
			char*          m_buffer;
		public:
			// Con-/Destructor
			H3D_API WaveFile();
			H3D_API WaveFile(char Path[]);
			H3D_API ~WaveFile();

			// File operations
			bool H3D_API loadFromFile(char Path[]);
		};
		class OggFile
		{
		private:
			
		public:
			// Con-/Destructor
			H3D_API OggFile();
			H3D_API OggFile(char Path[]);
			H3D_API ~OggFile();

			// File operations
			bool H3D_API loadFromFile(char Path[]);
		};
}}
/////////////////////////////////////////////////////////////////
