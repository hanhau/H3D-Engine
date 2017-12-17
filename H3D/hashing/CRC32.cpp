#include "CRC32.hpp"
#include <fstream>
#include "..\Utilities.hpp"
/////////////////////////////////////////////////////////////////
#define WIDTH  (8 * sizeof(uint8_t))
#define TOPBIT (1 << (WIDTH -1))
#define POLYNOMIAL 0x04C11DB7
/////////////////////////////////////////////////////////////////
// CRC32 table generation
namespace {
	bool is_created = false;
}
uint8_t* initTable() {
	static uint8_t table[256];
	
	uint8_t remainder;

	// Compute remainder of dividend
	for (uint32_t dividend = 0;dividend < 256; ++dividend)
	{
		remainder = dividend << (WIDTH - 8);

		for (uint8_t bit = 8; bit > 0; --bit)
		{
			if (remainder & TOPBIT)
				remainder = (remainder << 1) ^ POLYNOMIAL;
			else
				remainder = (remainder << 1);
		}

		table[dividend] = remainder;
	}

	return table;
}
/////////////////////////////////////////////////////////////////
// Implementation of CRC32 Hashing
/////////////////////////////////////////////////////////////////
int h3d::CRC32Sum::m_polynominal;
uint8_t*     h3d::CRC32Sum::m_crcTable;
/////////////////////////////////////////////////////////////////
h3d::CRC32Sum::CRC32Sum() 
{
	if (!is_created)
	{
		this->m_crcTable = initTable();
		is_created = true;
	}
}
h3d::CRC32Sum::~CRC32Sum() {}
/////////////////////////////////////////////////////////////////
uint8_t h3d::CRC32Sum::create(std::string path)
{
	static std::fstream file_stream;
	file_stream.open(path, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file_stream.is_open())
		return 0;

	// Get file size
	unsigned fileSize = file_stream.tellg();
	file_stream.seekg(0);

	// Calc CRC32 Checksum from buffer
	unsigned char* buf = new unsigned char[fileSize];
	file_stream.read((char*)buf, fileSize);
	file_stream.close();

	return m_key = create(buf, fileSize);
}
uint8_t h3d::CRC32Sum::create(const unsigned char *buffer,uint64_t buffer_size)
{
	uint8_t data, remainder = 0;

	for (int byte = 0;byte < buffer_size; ++byte)
	{
		data = buffer[byte] ^ (remainder >> (WIDTH - 8));
		remainder = m_crcTable[data] ^ (remainder << 8);
	}

	return m_key = remainder;
}
/////////////////////////////////////////////////////////////////
uint64_t h3d::CRC32Sum::getKey() { return m_key; }
bool     h3d::CRC32Sum::operator==(const CRC32Sum& sum) { return (m_key == sum.m_key); };
/////////////////////////////////////////////////////////////////