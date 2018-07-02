#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "../../H3D/Network/Network.hpp"
#include <string>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
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
			struct impl;
			std::unique_ptr<impl> m_impl;

			// Winsock stuff
			addrinfo *result = NULL,
					 *ptr = NULL,
					 hints;

			SOCKET    m_thisSocket;
			addrinfo *m_thisAddrInfo;
		public:
			enum class Transport {
				in,out,both
			};

			H3D_API Socket();
			H3D_API Socket(int ai_family,
						   int ai_socktype,
						   int ai_protocol,
						   const char* port, const char* address);
			H3D_API ~Socket();

			bool H3D_API create(int ai_family,
								int ai_socktype,
								int ai_protocol,
								const char* port,const char* address);
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