#include "Socket.hpp"
#include "Package.hpp"
#include "..\Utilities.hpp"
#include <cstdlib>
#include <sys\types.h>
/////////////////////////////////////////////////////////////////
// Implementation of Socket class
/////////////////////////////////////////////////////////////////
h3d::Network::Socket::Socket() {}
h3d::Network::Socket::Socket(int ai_family,
							 int ai_socktype,
							 int ai_protocol,
							 const char* port, const char* address) {
	this->create(ai_family,
				 ai_socktype,
				 ai_protocol,
				 port,address);
}
h3d::Network::Socket::~Socket() {}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::create(int ai_family,
								  int ai_socktype,
								  int ai_protocol,
								  const char* port, 
								  const char* address)
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	int iResult = getaddrinfo(address, port, &hints, &result);
	if (iResult != 0) {
		h3d::Log::error("Socket: getaddrinfo(..) failed in create(...);");
		return false;
	}
	
	m_thisSocket = INVALID_SOCKET;
	ptr = result;

	m_thisSocket = socket(ptr->ai_family, ptr->ai_socktype,
						  ptr->ai_protocol);
	
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::bind()
{
	if (::bind(m_thisSocket,
			   m_thisAddrInfo->ai_addr,
			   m_thisAddrInfo->ai_addrlen) != 0)
	{
		h3d::Log::error("Unable to bind Port !");
		return false;
	}
	else return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::connect()
{
	// Connect to server.
	int iResult = ::connect(m_thisSocket,ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		h3d::Log::error("Unable to connect socket to destination");
		closesocket(m_thisSocket);
		m_thisSocket = INVALID_SOCKET;
		return false;
	}
	
	freeaddrinfo(result);
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::listen()
{
	Package pkg;
	

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
		h3d::Log::info("Socket wasn´t able to transmit whole Package");
		return false;
	} 
	else return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::recv(const h3d::Network::Package& pkg)
{

	return 0;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::Socket::shutdown(int what)
{
	if (::shutdown(0, what) != 0){
		h3d::Log::error("Unable to shutdown socket !");
		return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////