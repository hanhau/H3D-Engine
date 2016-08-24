#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include <WinSock2.h>
#include <cstring>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <algorithm>
/////////////////////////////////////////////////////////////////
// Network Module
namespace h3d {
	namespace Network {
		/////////////////////////////////////////////////////////
		// Start/shutdown functions
		bool _declspec(dllexport) Startup(char version[2]);
		bool _declspec(dllexport) Shutdown();
		/////////////////////////////////////////////////////////
		// Package
		/////////////////////////////////////////////////////////
		struct _declspec(dllexport) Package
		{
			unsigned int Size;
			std::vector<char> Data;

			Package();
			Package(char* adata, unsigned int asize);
		};
		/////////////////////////////////////////////////////////
		// TCP Socket (Client sided)
		/////////////////////////////////////////////////////////
		class TCP_Server;
		class TCP_Socket
		{
			friend TCP_Server;
		private:
			// Winsock Stuff
			int m_af, m_type, m_protocol;
			SOCKET m_socket;
			SOCKADDR_IN m_socketaddrin;

			// Package Transfer
			std::queue<Package> m_outqueue;
			std::queue<Package> m_inqueue;

			// Threads
			std::thread m_datastreamthread;
			void Datastreamhandling();
		public:
			// Constructor
			_declspec(dllexport) TCP_Socket(const TCP_Socket& val);
			_declspec(dllexport) TCP_Socket(int af,int type,int protocol);
			_declspec(dllexport)  ~TCP_Socket();

			// Operator
			_declspec(dllexport) TCP_Socket& operator=(const TCP_Socket &val);

			// Connectionfunctions
			bool _declspec(dllexport) connect(const char aIP[],const char aPort[]);
			bool _declspec(dllexport) close();

			// Threadfunctions
			void _declspec(dllexport) startDataProcessing();
			void _declspec(dllexport) endDataProcessing();

			// Sending & Receiving
			void _declspec(dllexport) send(h3d::Network::Package &pkg);
			bool _declspec(dllexport) recv(h3d::Network::Package *pkg);
		};
		/////////////////////////////////////////////////////////
		// TCP Server (pure Server)
		/////////////////////////////////////////////////////////
		class TCP_Server
		{
		private:
			// Server Socket
			class tagTCP_ServerSocket : public TCP_Socket
			{
			public:
				bool bind(const char aPort[],int af);
			}m_ListeningSocket;

			// Handling incoming Connections
			bool m_ConnectionsOpen;
			void handleIncomingConnections(bool* yn);

			// List of connected Sockets
			std::mutex						 m_Connections_Mutex;
			std::map<std::string,TCP_Socket> m_Connections;

			// Server Configuration
			std::vector<std::string> m_bannedIPs;
			std::vector<std::string> m_Whitelist;
			bool m_WhitelistActive;
			int  m_maxConnections;
			
		public:
			// Constructor
			_declspec(dllexport) TCP_Server();
			_declspec(dllexport) ~TCP_Server();

			// Open/Close Connections
			void _declspec(dllexport) allowConnections(bool val);

			// Data send/recv functions
			bool _declspec(dllexport) sendToAll(Package &pkg);
			bool _declspec(dllexport) sendToSpecific(char IP[],Package &pkg);

			// Server Commands
			void _declspec(dllexport) setMaxConnections(int val);
			void _declspec(dllexport) kickIP(char IP[]);
			void _declspec(dllexport) banIP(char IP[]);
			void _declspec(dllexport) kickAll();
			void _declspec(dllexport) banAll();
		};
		/////////////////////////////////////////////////////////
		// UDP Socket (Client sided)
		/////////////////////////////////////////////////////////
		class UDP_Socket
		{
		private:
			// Winsock Stuff
			int m_af, m_type, m_protocol;
			SOCKET m_socket;
			SOCKADDR_IN m_socketaddrin;

		public:
			// Con-/Destructor
			_declspec(dllexport) UDP_Socket();
			_declspec(dllexport) ~UDP_Socket();

			// Setup Socket
			void _declspec(dllexport) setup();

			// Manual Sending
			int _declspec(dllexport) send(char IP[],char Port[],Package &pkg);
			int _declspec(dllexport) recv(char IP[],char Port[],Package &pkg);

			// Automated Sending
			void _declspec(dllexport) setConnection(char IP[], char Port[]);
			int  _declspec(dllexport) send(Package &pkg);
			int  _declspec(dllexport) recv(Package &pkg);
		};
		/////////////////////////////////////////////////////////
		// UDP Server (pure Server)
		/////////////////////////////////////////////////////////
		class UDP_Server
		{
		private:

		public:

		};
		/////////////////////////////////////////////////////////
	}
}
/////////////////////////////////////////////////////////////////
