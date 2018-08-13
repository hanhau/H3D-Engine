#include "../../H3D/Network/Network.hpp"
#include "../../H3D/System/Config.hpp"
#ifdef H3D_SYSTEM_WINDOWS
#include <WinSock2.h>
#include <Windows.h>
#elif H3D_SYSTEM_LINUX
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
#ifdef H3D_SYSTEM_WINDOWS
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
#ifdef H3D_SYSTEM_WINDOWS
	return (WSACleanup()) ? true : false;	
#endif
	return true;
}
/////////////////////////////////////////////////////////////////