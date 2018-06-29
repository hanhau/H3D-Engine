#include "Network.hpp"

#ifdef _WIN32 || _WIN64
#include <WinSock2.h>
#include <Windows.h>
#elif __linux__
#include <sys\types.h>
#include <sys\socket.h>
#include <netdb.h>
#endif
/////////////////////////////////////////////////////////////////
//	Implementations of Network Module
/////////////////////////////////////////////////////////////////
bool h3d::Network::Startup(char version[2])
{
	if (h3d::DebugMode) {
		h3d::Log::info("h3d::Network::Startup(version=%s)",version);
	}
#ifdef _WIN32 || _WIN64
	WSAData wsd;
	int result = WSAStartup(MAKEWORD(version[0],version[1]),&wsd);

	if (result != 0)
	{
		if (h3d::DebugMode)
			h3d::Log::error("h3d::Network::Startup(...) failed !");
		return false;
	}
	else
#endif
	return true;
}
bool h3d::Network::Shutdown()
{
	if (h3d::DebugMode)
		h3d::Log::info("Shutdown Network (WSA Cleanup)");
#ifdef _WIN32 || _WIN64
	return (WSACleanup()) ? true : false;	
#endif
	return true;
}
/////////////////////////////////////////////////////////////////