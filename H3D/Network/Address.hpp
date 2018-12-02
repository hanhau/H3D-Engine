#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <string>
#include <WinSock2.h>
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace Network {
		enum class Protocol {
			UDP,TCP
		};

		class Address
		{
		public:
			std::string m_ip;
			std::string m_port;
			std::string m_subnetmask;
			std::string m_macAddress;
		};
	}
}
/////////////////////////////////////////////////////////////////