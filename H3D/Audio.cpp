#include "Audio.hpp"
#include <fstream>
#include <algorithm>
/////////////////////////////////////////////////////////////////
//	Implementations of Audio Lib
/////////////////////////////////////////////////////////////////
void _declspec(dllexport) h3d::Audio::Settings::setVolumeArea(char area[], float val) {
	g_volumeGroupMap[area] = val;
}
bool _declspec(dllexport) h3d::Audio::Settings::getVolumeArea(char area[], float *val) {
	auto iter = g_volumeGroupMap.find(area);
	if (iter != g_volumeGroupMap.end()) {
		*val = g_volumeGroupMap[area];
		return true;
	}
	else return false;
}
void _declspec(dllexport) h3d::Audio::Settings::setSpeakerChannelMask(char config[]) {
	if (config == "7.1")
		g_speakerMask = SPEAKER_7POINT1;
	if (config == "7.1 suround")
		g_speakerMask = SPEAKER_7POINT1_SURROUND;
	else if (config == "5.1")
		g_speakerMask = SPEAKER_5POINT1;
	else if (config == "5.1 suround")
		g_speakerMask = SPEAKER_5POINT1_SURROUND;
	else if (config == "3.1")
		g_speakerMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
						SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY;
	else if (config == "2.1")
		g_speakerMask = SPEAKER_2POINT1;
	else if (config == "2.0")
		g_speakerMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
}
void _declspec(dllexport) h3d::Audio::Settings::setSpeedOfSound(float val) {
	g_speedOfSound = val;
}
/////////////////////////////////////////////////////////////////
bool _declspec(dllexport) h3d::Audio::Settings::loadFromFile(char path[])
{
	// binary = 0/text = 1
	char mode;

	// Opening and checking File
	std::ifstream file_stream;
	if (strstr(path,".txt") != NULL) {
		file_stream.open(path, std::ios::in);
		mode = 1;
	}
	else {
		file_stream.open(path, std::ios::in | std::ios::binary);
		mode = 0;
	}
	if (file_stream.bad()) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("audio_log.txt");
			h3d::Debugstream << "Failed to open: " << path << "\n";
			h3d::Debugstream.close();
		}
		return false;
	}

	// Reset Current Settings
	g_speakerMask = g_speedOfSound = 0;
	g_volumeGroupMap.clear();

	// Loading
	if (mode == 1) // Textfile
	{
		std::string param;
		while (!file_stream.eof())
		{
			file_stream >> param;
			if (param == "g_speakerMask") {
				file_stream >> g_speakerMask;
			}
			else if (param == "g_speedOfSound") {
				file_stream >> g_speedOfSound;
			}
			else if (param == "g_volumeGroupMap::size()") {
				size_t size;
				float val;
				std::string str;

				file_stream >> size;
				for (int i = 0;i < size;i++) {
					file_stream >> str >> val;
					g_volumeGroupMap[str] = val;
				}
			}
		}
	}
	else if (mode == 0) // Binaryfile
	{
		size_t mapSize;
		float val;
		char *str;
		int  str_length;

		file_stream.read((char*)&g_speakerMask, sizeof(uint32_t));
		file_stream.read((char*)&g_speedOfSound, sizeof(float));
		file_stream.read((char*)&mapSize,sizeof(size_t));
		for (int i = 0;i < mapSize;i++) {
			file_stream.read((char*)&str_length,sizeof(int));
			str = new char[str_length];
			file_stream.read((char*)&str,sizeof(char)*str_length);
			file_stream.read((char*)&val,sizeof(float));
			g_volumeGroupMap[std::string(str)] = val;
		}
	}
	else return false;

	// Closing file_stream and return successful
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
bool _declspec(dllexport) h3d::Audio::Settings::saveToFile(char path[])
{
	// binary = 0/text = 1
	char mode;

	// Opening and checking File
	std::ofstream file_stream;
	if (strstr(path, ".txt") != NULL) {
		file_stream.open(path, std::ios::in);
		mode = 1;
	}
	else {
		file_stream.open(path, std::ios::in | std::ios::binary);
		mode = 0;
	}
	if (file_stream.bad()) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("audio_log.txt");
			h3d::Debugstream << "Failed to open: " << path << "\n";
			h3d::Debugstream.close();
		}
		return false;
	}

	// Writing
	if (mode == 1) // Textfile
	{
		file_stream << "g_speakerMask" << g_speakerMask << std::endl;
		file_stream << "g_speedOfSound" << g_speedOfSound << std::endl;
		file_stream << "g_volumeGroupMap::size()" << g_volumeGroupMap.size() << std::endl;
		for (auto &iter : g_volumeGroupMap)
			file_stream << iter.first << iter.second << std::endl;
	}
	else if (mode == 0) // Binaryfile
	{
		file_stream.write((char*)&g_speakerMask,sizeof(uint32_t));
		file_stream.write((char*)&g_speedOfSound,sizeof(float));
		file_stream.write((char*)g_volumeGroupMap.size(), sizeof(size_t));
		for (auto &iter : g_volumeGroupMap) {
			file_stream.write((char*)iter.first.size(),sizeof(int));
			file_stream.write((char*)iter.first.data(),iter.first.size());
			file_stream.write((char*)&iter.second,sizeof(float));
		}
	}
	else return false;

	// Closing file_stream and return successful
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
// Audio Engine init() and shutdown()
/////////////////////////////////////////////////////////////////
bool h3d::Audio::init()
{
	// Call for COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// Create Engine
	if (FAILED(XAudio2Create(&h3d::Audio::g_engine))) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("audio_log.txt");
			h3d::Debugstream << "Failed to create Engine!\n";
			h3d::Debugstream.close();
		}
		return false;
	}
	
	// Create Mastering Voice
	if (FAILED(g_engine->CreateMasteringVoice(&h3d::Audio::g_master))) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("audio_log.txt");
			h3d::Debugstream << "Failed to create Engine!\n";
			h3d::Debugstream.close();
		}
		return false;
	}
	
	// Initialize X3D
	X3DAudioInitialize(h3d::Audio::Settings::g_speakerMask,
					   h3d::Audio::Settings::g_speedOfSound,
					   (BYTE*)&h3d::Audio::g_x3dAudioHandle);
	
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Audio::shutdown()
{
	// Call for COM
	CoUninitialize();
	return true;
}
/////////////////////////////////////////////////////////////////