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
	class Checksum {
	private:
		std::string m_key;
	public:
		// Con-/Destructor
		H3D_API Checksum();
		H3D_API ~Checksum();

		// Create Checksum
		std::string H3D_API create(std::string path);
		std::string H3D_API create(const unsigned char* buffer, uint64_t buffer_size);

		// Key Operations
		std::string H3D_API getKey();
		bool        H3D_API operator==(const Checksum& sum);
	};
}
/////////////////////////////////////////////////////////////////