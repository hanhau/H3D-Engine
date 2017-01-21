#include "Socket.hpp"
#include "Package.hpp"
#include "..\Utilities.hpp"
#include <cstdlib>
#include <sys\types.h>
#include <WS2tcpip.h>
/////////////////////////////////////////////////////////////////
// Implementation of Socket class
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::create(const char *node,
								  const char *service,
								  const char* socket_type)
{
	
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::bind()
{
	if (::bind(m_thisSocket,
			   m_thisAddrInfo->ai_addr,
			   m_thisAddrInfo->ai_addrlen) != 0)
	{
		Log.error("Unable to bind Port !");
		return false;
	}
	else return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::connect()
{

}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::listen()
{
	Package pkg;
	pkg = "Hello mothafukkaz";
	pkg.size<uint32_t>();
	pkg.checksum<h3d::CRC32Sum>();
	
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::accept()
{


	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::send(const h3d::Network::Package& pkg)
{
	auto total = 0;
	auto n = 0;

	auto totallen = pkg.size<uint64_t>();
	auto byteleft = totallen;

	while (total < totallen)
	{
		n = ::send(m_thisSocket,(char*)pkg.data()+total, byteleft, 0);
		if (n == -1) break;
		total += n;
		byteleft -= n;
	}
	if (n == -1) {
		Log.info("Socket wasn´t able to transmit whole Package");
		return false;
	} 
	else return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::recv(const h3d::Network::Package& pkg)
{
	
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::shutdown(int what)
{
	if (::shutdown(0, what) != 0){
		Log.error("Unable to shutdown socket !");
		return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////