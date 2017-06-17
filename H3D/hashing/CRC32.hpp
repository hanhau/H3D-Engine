#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <cstdint>
#include <string>
/////////////////////////////////////////////////////////////////
// CRC32Sum
/////////////////////////////////////////////////////////////////
namespace h3d {
	class CRC32Sum
	{
		static unsigned int m_polynominal;
		static uint8_t* m_crcTable;
		uint8_t m_key;
	public:
		// Con-/Destructor
		H3D_API CRC32Sum();
		H3D_API ~CRC32Sum();

		// Create Checksum 
		uint8_t H3D_API create(std::string path);
		uint8_t H3D_API create(const unsigned char* buffer, uint64_t buffer_size);

		// Key Operations
		uint64_t H3D_API getKey();
		bool     H3D_API operator==(const CRC32Sum& sum);
	};
}
/////////////////////////////////////////////////////////////////