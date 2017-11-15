#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
#include <string>
/////////////////////////////////////////////////////////////////
// SHA256 Checksum
/////////////////////////////////////////////////////////////////
namespace h3d {
	class SHA256Sum
	{
	private:
		std::string m_key;
	public:
		// Con-/Destructor
		H3D_API SHA256Sum();
		H3D_API SHA256Sum(char * mem, size_t length);
		H3D_API ~SHA256Sum();
		
		std::string H3D_API createSum(char * mem,size_t length);
		std::string H3D_API getKey();
	};
}
/////////////////////////////////////////////////////////////////