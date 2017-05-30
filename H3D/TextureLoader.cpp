#include "FileSystem.hpp"
#include "FileDataStructures.hpp"
#include "Utilities.hpp"
#include "Vector.hpp"
#include "Texture.hpp"
#include <gl\glew.h>
/////////////////////////////////////////////////////////////////
// Loading individual formats
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadBMP(char Path[],h3d::Texture& ref)
{
	// Opening filestream
	h3d::FileHandle filehandle;
	filehandle.open(Path);
	if (FALSE == filehandle.isOpen()) {
		if (h3d::DebugMode) Log.error("Unable to load BMP %s",Path);
		return false;
	}

	// Temporarly variables
	h3d::FileType::BMP::Header t_header;
	h3d::FileType::BMP::Body   t_body;

	// Reading 
	// Header (12 bytes)
	h3d::setObjectFromFileHandle(t_header, filehandle);
	if (t_header.bfType != 19778) {
		if (h3d::DebugMode) {
			Log.error("%s is corrupted!", Path);
		}
		return false;
	}

	// Informationblock (40 bytes+t_bfOffBits/8)
	h3d::setObjectFromFileHandle(t_body, filehandle);

	// Set format intel
	ref.m_measurements = h3d::Vec2<unsigned int>(t_body.biWidth, abs(t_body.biHeight));
	ref.m_format = GL_BGR;

	// Picturedatablock
	unsigned long imageSize = t_body.biWidth*t_body.biHeight*t_body.biBitCount / 8;
	ref.m_buffer = new unsigned char[imageSize];
	h3d::setObjectFromFileHandle(ref.m_buffer, filehandle);

	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadPNG(char Path[],h3d::Texture& ref)
{
	// Open File
	h3d::FileHandle filehandle;
	filehandle.open(Path);
	if (FALSE == filehandle.isOpen()) {
		if (h3d::DebugMode) Log.error("Unable to open %s",Path);
		return false;
	}
	

	// Return successfully
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadKTX(char Path[],h3d::Texture& ref)
{
	// Opening unbuffered filestream
	std::ifstream file_stream;
	file_stream.rdbuf()->pubsetbuf(0, 0);
	file_stream.open(Path, std::ios::binary);
	if (file_stream.bad()) {
		if (h3d::DebugMode) {
			Log.error("Unable to open %s", Path);
		}
		return false;
	}
	// Temporarly variables
	h3d::FileType::KTX::Header t_header;

	// Reading
	file_stream.read((char*)&t_header, sizeof(t_header));



	// Return
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadTGA(char Path[],h3d::Texture& ref)
{
	std::ifstream file_stream;
	file_stream.rdbuf()->pubsetbuf(0, 0);
	file_stream.open(Path, std::ios::binary);
	if (file_stream.bad()) {
		if (h3d::DebugMode) {
			Log.error("Unable to open %s", Path);
		}
		return false;
	}
	// Temporary Variables
	h3d::FileType::TGA::Header t_header;

	// Read Header (18 bytes)
	file_stream.read((char*)&t_header, sizeof(t_header));


	// Close and return
	file_stream.close();
	return true;
}