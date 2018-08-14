#include "../../H3D/Hashing/UniChecksum.hpp"
#include <algorithm>
#include <fstream>
/////////////////////////////////////////////////////////////////
// Inplementation of UniChecksum
/////////////////////////////////////////////////////////////////
constexpr int MAX_KEY_LENGTH = 24;
constexpr char* START_STRING = "h3denginechecksumstartseed";
/////////////////////////////////////////////////////////////////
h3d::Checksum::Checksum() {}
h3d::Checksum::~Checksum() {}
/////////////////////////////////////////////////////////////////
std::string h3d::Checksum::create(std::string path)
{
	static std::fstream file_stream;
	file_stream.open(path, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file_stream.is_open())
		return "";

	// Get file size
	unsigned fileSize = file_stream.tellg();
	file_stream.seekg(0);

	// Calc CRC32 Checksum from buffer
	unsigned char* buf = new unsigned char[fileSize];
	file_stream.read((char*)buf, fileSize);
	file_stream.close();

	return m_key = create(buf, fileSize);
}
std::string h3d::Checksum::create(const unsigned char* buffer, uint64_t buffer_size)
{
	std::string tempSum = START_STRING;
	tempSum.resize(MAX_KEY_LENGTH);

	unsigned char currBuffer;
	unsigned char prevBuffer;
	int tempVal;

	for (int i=0;i<buffer_size;i++)
	{
		prevBuffer = buffer[(int)(i-1)];
		currBuffer = buffer[i];
		tempVal = currBuffer * prevBuffer;

		for (int j=0;j<MAX_KEY_LENGTH;j++)
		{
			tempSum[j] ^= buffer[i] & tempVal << 1;
		}
	}

	return m_key = tempSum;
}
/////////////////////////////////////////////////////////////////
std::string h3d::Checksum::getKey() { return m_key; }
bool h3d::Checksum::operator==(const Checksum& sum) { return (m_key == sum.m_key); }
/////////////////////////////////////////////////////////////////