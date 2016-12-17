#include "Network.hpp"
#include "Utilities.hpp"
/////////////////////////////////////////////////////////////////
//	Implementations of Network Module
/////////////////////////////////////////////////////////////////
// Startup/Shutdown
/////////////////////////////////////////////////////////////////
bool h3d::Network::Startup(char version[2] = "20")
{
	if (h3d::DebugMode) {
		Log.info("h3d::Network::Startup(version=%s)");
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
	return true;
}
/////////////////////////////////////////////////////////////////
// Package
/////////////////////////////////////////////////////////////////
h3d::Network::Package::Package() { Size = 0; Data.clear(); }
h3d::Network::Package::Package(char *adata, unsigned int asize)
{
	memcpy(Data.data(), adata, asize);
}
/////////////////////////////////////////////////////////////////
//	TCP_Socket Implementations
/////////////////////////////////////////////////////////////////
h3d::Network::TCP_Socket::TCP_Socket(const h3d::Network::TCP_Socket& val)
{
	*this = val;
}
h3d::Network::TCP_Socket::TCP_Socket(int af   = AF_INET, 
									 int type = SOCK_STREAM, 
									 int protocol = 0):
	m_af(af), m_type(type), m_protocol(protocol)
{
	m_socket = socket(af, type, protocol);
	if (m_socket == INVALID_SOCKET)
	{
		if (h3d::DebugMode){
			Log.error("Unable to create socket");
		}
		this->~TCP_Socket();
	}
}
h3d::Network::TCP_Socket::~TCP_Socket() {};
/////////////////////////////////////////////////////////////////
h3d::Network::TCP_Socket& h3d::Network::TCP_Socket::operator=
(const h3d::Network::TCP_Socket& val)
{
	this->m_af      = val.m_af;
	this->m_type    = val.m_type;
	this->m_protocol= val.m_protocol;

	this->m_socket = val.m_socket;
	this->m_socketaddrin = val.m_socketaddrin;

	this->m_outqueue = val.m_outqueue;
	this->m_inqueue = val.m_inqueue;

	return *this;
}
/////////////////////////////////////////////////////////////////
bool h3d::Network::TCP_Socket::connect(const char aIP[], const char aPort[])
{
	int debug;

	memset((void*)&m_socketaddrin, 0, sizeof(SOCKADDR_IN));
	m_socketaddrin.sin_family = m_af;
	m_socketaddrin.sin_port = htons(std::stoi(aPort));
	m_socketaddrin.sin_addr.S_un.S_addr = inet_addr(aIP);

	debug = ::connect(m_socket,(SOCKADDR*)&m_socketaddrin, sizeof(SOCKADDR_IN));
	if (debug == SOCKET_ERROR)
	{
		if (h3d::DebugMode) {
			Log.error("Failed to connect Socket to %s : %s",aIP,aPort);
		}
		return false;
	}

	return true;
}
bool h3d::Network::TCP_Socket::close()
{
	if (::closesocket(m_socket) == SOCKET_ERROR)
	{
		if (h3d::DebugMode) {
			Log.error("Unable to close a socket");
		}
		return false;
	}
	else return true;
}
/////////////////////////////////////////////////////////////////
void h3d::Network::TCP_Socket::Datastreamhandling()
{
	// Buffer
	static Package temp_pkg;
	std::vector<char> chartoi_vec;
	
	static int received_bytes;

	static std::vector<char>buffer;
	static std::vector<char>recv_buffer;
					   
	// Check for outgoing requests
	if (!m_outqueue.empty())
	{
		::send(m_socket, m_outqueue.front().Data.data(),
			   m_outqueue.front().Size, 0);
		m_outqueue.pop();
	}
	// Check for incoming requests
	recv_buffer.clear();
	if ((received_bytes = ::recv(m_socket, &recv_buffer[0], 256, 0) != 0))
		buffer.insert(buffer.end(), recv_buffer.begin(), recv_buffer.end());

	if (buffer.size() >= 4 && temp_pkg.Size == 0)
	{
		chartoi_vec.clear();
		chartoi_vec.insert(chartoi_vec.begin(),buffer.begin(), buffer.begin() + 4);
		buffer.erase(buffer.begin(), buffer.begin() + 4);
		temp_pkg.Size = (unsigned int)&chartoi_vec[0];
	}
	else if (temp_pkg.Size != 0)
	{
		if (temp_pkg.Size <= buffer.size())
		{
			temp_pkg.Data.clear();
			temp_pkg.Data.insert(temp_pkg.Data.begin(), buffer.begin(), buffer.end());
		}
	}
}
/////////////////////////////////////////////////////////////////
void h3d::Network::TCP_Socket::startDataProcessing()
{
	m_datastreamthread = std::thread([this] {this->Datastreamhandling();});
}
void h3d::Network::TCP_Socket::endDataProcessing()
{
	m_datastreamthread.~thread();
}
/////////////////////////////////////////////////////////////////
void h3d::Network::TCP_Socket::send(h3d::Network::Package &pkg)
{
	m_outqueue.push(pkg);
}
bool h3d::Network::TCP_Socket::recv(h3d::Network::Package *pkg)
{
	if (m_inqueue.empty()) {
		pkg = NULL;
		return false;
	} else {
		*pkg = m_inqueue.front();
		m_inqueue.pop();
	}
	return true;
}
/////////////////////////////////////////////////////////////////
//	TCP_Server Implementations
/////////////////////////////////////////////////////////////////
//h3d::Network::TCP_Server::TCP_Server() {}
h3d::Network::TCP_Server::~TCP_Server() {}
/////////////////////////////////////////////////////////////////
bool h3d::Network::TCP_Server::tagTCP_ServerSocket::bind
									(const char aPort[], int af = AF_INET)
{
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = af;
	addr.sin_port = htons(std::stoi(aPort));
	addr.sin_addr.S_un.S_addr = ADDR_ANY;

	int debug = ::bind(m_socket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (debug == SOCKET_ERROR)
	{
		if (h3d::DebugMode) {
			Log.error("TCP_Server failed to bind to a port");
		}
		return false;
	}
	else return true;
}
/////////////////////////////////////////////////////////////////
// Handling incoming Connections
void h3d::Network::TCP_Server::handleIncomingConnections(bool* yn)
{
	int debug;
	TCP_Socket temp_socket;
	SOCKADDR_IN temp_addr;

	while (*yn)
	{
		if ((debug = ::listen(m_ListeningSocket.m_socket, 10)) == SOCKET_ERROR)
		{
			if (h3d::DebugMode) {
				Log.error("Listen error");
			}
		}
		else
		{
			temp_socket.m_socket = ::accept(m_ListeningSocket.m_socket,
											(SOCKADDR*)&temp_addr,NULL);
			if (m_Connections.find(::inet_ntoa(temp_addr.sin_addr)) == m_Connections.end() &&
				std::find(m_bannedIPs.begin(),m_bannedIPs.end(), ::inet_ntoa(temp_addr.sin_addr)) 
						  == m_bannedIPs.end())
			{
				m_Connections_Mutex.lock();
				m_Connections[::inet_ntoa(temp_addr.sin_addr)] = temp_socket;
				m_Connections_Mutex.unlock();
			}
		}
	}
}
/////////////////////////////////////////////////////////////////
// Server Commands
void h3d::Network::TCP_Server::setMaxConnections(int val){
	m_maxConnections = val;
}
void h3d::Network::TCP_Server::kickIP(char IP[]){
	if (m_Connections.find(IP) != m_Connections.end())
	{
		m_Connections[IP].close();
		m_Connections.erase(IP);
	}
}
void h3d::Network::TCP_Server::banIP(char IP[]){
	kickIP(IP);
	std::vector<std::string>::iterator iter;
	iter = std::find(m_bannedIPs.begin(), m_bannedIPs.end(), IP);
	if (iter == m_bannedIPs.end())
	{
		m_bannedIPs.push_back(IP);
	}
}
void h3d::Network::TCP_Server::kickAll()
{
	for (auto &iter : m_Connections)
	{
		iter.second.close();
		m_Connections.erase(iter.first);
	}
}
void h3d::Network::TCP_Server::banAll()
{
	for (auto &iter : m_Connections)
		m_bannedIPs.push_back(iter.first);
	kickAll();
}
/////////////////////////////////////////////////////////////////