#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "..\Network.hpp"
#include <string>
#include <winsock.h>
#include <WinSock2.h>
/////////////////////////////////////////////////////////////////
// Network Socket
/////////////////////////////////////////////////////////////////
#define SOCKET_TRANSPORT_IN    0
#define SOCKET_TRANSPORT_OUT   1
#define SOCKET_TRANSPORT_INOUT 2
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace Network {
		class Socket final
		{
		private:
			// Winsock stuff
			SOCKET    m_thisSocket;
			addrinfo *m_thisAddrInfo;
		public:
			H3D_API Socket();
			H3D_API ~Socket();

			bool H3D_API create(const char* node,
								const char *service,
								const char* socket_type);
			bool H3D_API bind();

			bool H3D_API connect();

			bool H3D_API listen();
			bool H3D_API accept();

			bool H3D_API send(const h3d::Network::Package& pkg);
			bool H3D_API recv(const h3d::Network::Package& pkg);
			
			bool H3D_API sendTo();
			bool H3D_API recvFrom();

			bool H3D_API shutdown(int what);
		};
	}
}
/////////////////////////////////////////////////////////////////