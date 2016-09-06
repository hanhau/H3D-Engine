/////////////////////////////////////////////////////////////////
#include "Texture.hpp"
#include "FileDataStructures.hpp"
#include <type_traits>
#include <string>
#include <algorithm>
#include "Utilities.hpp"
/////////////////////////////////////////////////////////////////
//	Texture Function Implementations
/////////////////////////////////////////////////////////////////
const int h3d::Texture::Format::PNG = 0;
const int h3d::Texture::Format::KTX = 1;
const int h3d::Texture::Format::BMP = 2;
const int h3d::Texture::Format::TGA = 3;
/////////////////////////////////////////////////////////////////
h3d::Texture::Texture(){}
h3d::Texture::Texture(char Path[]){
	loadFromFile(Path);
	createTexture();
}
h3d::Texture::~Texture(){}
/////////////////////////////////////////////////////////////////
// Loading and manipulating
bool h3d::Texture::loadFromFile(char Path[])
{
	// Get substring with file extension
	std::string file_extension(Path);
	file_extension.erase(file_extension.begin(), file_extension.begin() + file_extension.find('.')+1);

	// Set Memberflag m_format
	if (file_extension == "png") m_format = Format::PNG;
	else if (file_extension == "ktx") m_format = Format::KTX;
	else if (file_extension == "bmp") m_format = Format::BMP;
	else if (file_extension == "tga") m_format = Format::TGA;
	else {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("TextureLog.txt");
			h3d::Debugstream << "Error: " << Path << " is a not supported format!\n";
			h3d::Debugstream.close();
		}
		return false;
	}

	// Load different formats
	switch (m_format)
	{
		// PNG
		case Format::PNG:
			return loadPNG(Path); break;
		// KTX
		case Format::KTX:
			return loadKTX(Path); break;
		// BMP
		case Format::BMP:
			return loadBMP(Path); break;
		// TGA
		case Format::TGA:
			return loadTGA(Path); break;
		default: return false; break;
	}

	// Exit successful
	return true;
}
/////////////////////////////////////////////////////////////////
GLuint h3d::Texture::getTextureIndex() { return m_texid; }
/////////////////////////////////////////////////////////////////
bool h3d::Texture::setActive(bool val)
{
	if (val)
		glBindTexture(GL_TEXTURE_2D, m_texid);
	else
		glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}
/////////////////////////////////////////////////////////////////
// Loading individual formats
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadBMP(char Path[])
{
	// Opening unbuffered filestream
	std::ifstream file_stream;
	file_stream.open(Path,std::ios::in | std::ios::binary);
	if (!file_stream.good()) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("TextureLog.txt");
			h3d::Debugstream << "Unable to open " << Path << " \n";
			h3d::Debugstream.close();
		}
		return false;
	}
	
	// Temporarly variables
	h3d::FileType::BMP::Header t_header;
	h3d::FileType::BMP::Body   t_body;

	// Reading ////////////////////////////////////////////////////
	// Header (12 bytes)
	file_stream.read((char*)&t_header,sizeof(t_header));
	if (t_header.bfType != 19778) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("TextureLog.txt");
			h3d::Debugstream << "Error:" << Path << "is corrupted! \n";
			h3d::Debugstream.close();
		}
		return false;
	}
	
	// Informationblock (40 bytes+t_bfOffBits/8)
	file_stream.read((char*)&t_body,sizeof(t_body));
	
	// Set format intel
	m_measurements = h3d::Vec2<unsigned int>(t_body.biWidth,abs(t_body.biHeight));
	m_format = GL_BGR;

	// Picturedatablock
	unsigned long imageSize = t_body.biWidth*t_body.biHeight*t_body.biBitCount / 8;
	m_buffer = new unsigned char[imageSize];
	file_stream.read((char*)m_buffer, imageSize);
	
	// Return successful
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadPNG(char Path[])
{
	std::ifstream file_stream;
	file_stream.rdbuf()->pubsetbuf(0, 0);
	file_stream.open(Path, std::ios::binary);
	if (file_stream.bad()) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("TextureLog.txt");
			h3d::Debugstream << "Unable to open " << Path << " \n";
			h3d::Debugstream.close();
		}
		return false;
	}

	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadKTX(char Path[])
{
	// Opening unbuffered filestream
	std::ifstream file_stream;
	file_stream.rdbuf()->pubsetbuf(0, 0);
	file_stream.open(Path, std::ios::binary);
	if (file_stream.bad()) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("TextureLog.txt");
			h3d::Debugstream << "Unable to open " << Path << " \n";
			h3d::Debugstream.close();
		}
		return false;
	}
	// Temporarly variables
	h3d::FileType::KTX::Header t_header;
	
	// Reading
	file_stream.read((char*)&t_header,sizeof(t_header));



	// Return
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadTGA(char Path[])
{
	std::ifstream file_stream;
	file_stream.rdbuf()->pubsetbuf(0, 0);
	file_stream.open(Path, std::ios::binary);
	if (file_stream.bad()) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("TextureLog.txt");
			h3d::Debugstream << "Unable to open " << Path << " \n";
			h3d::Debugstream.close();
		}
		return false;
	}
	// Temporary Variables
	h3d::FileType::TGA::Header t_header;
	
	// Read Header (18 bytes)
	file_stream.read((char*)&t_header,sizeof(t_header));


	// Close and return
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
//  Set up to OpenGL
/////////////////////////////////////////////////////////////////
bool h3d::Texture::createTexture()
{
	glGenTextures(1, &m_texid);
	glBindTexture(GL_TEXTURE_2D, m_texid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
					m_measurements.x, 
					m_measurements.y, 
					GL_RGB, GL_UNSIGNED_BYTE, m_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
				 m_measurements.x, 
				 m_measurements.y, 
				 0, m_format, GL_UNSIGNED_BYTE, m_buffer);

	delete []m_buffer;
	m_buffer = nullptr;
	return true;
}
bool h3d::Texture::destroyTexture()
{
	glDeleteTextures(1, &m_texid);
	return true;
}
/////////////////////////////////////////////////////////////////