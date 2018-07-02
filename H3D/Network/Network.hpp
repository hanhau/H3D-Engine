#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <cstring>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <algorithm>
#include "../../H3D/System/Utilities.hpp"
#include "../../H3D/Network/Package.hpp"
/////////////////////////////////////////////////////////////////
// Network Module
namespace h3d {
	namespace Network {
		/////////////////////////////////////////////////////////
		// Start/shutdown functions
		bool H3D_API Startup(char version[2] = "20");
		bool H3D_API Shutdown();
		/////////////////////////////////////////////////////////
	}
}
/////////////////////////////////////////////////////////////////
