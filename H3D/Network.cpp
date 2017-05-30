#include "Network.hpp"
#include <WinSock2.h>
#include <Windows.h>
/////////////////////////////////////////////////////////////////
//	Implementations of Network Module
/////////////////////////////////////////////////////////////////
// Startup/Shutdown
/////////////////////////////////////////////////////////////////
bool h3d::Network::Startup(char version[2])
{
	if (h3d::DebugMode) {
		Log.info("h3d::Network::Startup(version=%s)",version);
	}

	WSAData wsd;
	int result = WSAStartup(MAKEWORD(version[0],version[1]),&wsd);

	if (result != 0)
	{
		if (h3d::DebugMode)
			Log.error("h3d::Network::Startup(...) failed !");
		return false;
	}
	else
		return true;
}
bool h3d::Network::Shutdown()
{
	if (h3d::DebugMode)
		Log.info("Shutdown Network (WSA Cleanup)");
	return (WSACleanup()) ? true : false;	
}
/////////////////////////////////////////////////////////////////