#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <string>
/////////////////////////////////////////////////////////////////
// SHA256
/////////////////////////////////////////////////////////////////
namespace h3d {
	class SHA256Sum
	{
	private:
		std::string m_key;
	public:
		// Con-/Destructor
		H3D_API SHA256Sum();
		H3D_API ~SHA256Sum();

		// Create Checksum
		std::string H3D_API create(std::string path);
		std::string H3D_API create(const unsigned char* buffer,std::size_t buffer_size);

		// Key Operations
		std::string H3D_API getKey();
		bool  H3D_API operator==(const SHA256Sum& sum);
	};
}
/////////////////////////////////////////////////////////////////