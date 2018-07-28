/////////////////////////////////////////////////////////////////
#include "../../H3D/Graphics/Texture.hpp"
#include "../../H3D/System/FileDataStructures.hpp"
#include <fstream>
#include <type_traits>
#include <string>
#include <algorithm>
#include <GL/glew.h>
#include "../../H3D/System/Utilities.hpp"
/////////////////////////////////////////////////////////////////
//	Texture Function Implementations
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
			h3d::Log::error("%s is not a supported format!",Path);
		}
		return false;
	}

	// Load different formats
	switch (m_format)
	{
		// PNG
		case Format::PNG:
			return loadPNG(Path, *this); break;
		// KTX
		case Format::KTX:
			return loadKTX(Path, *this); break;
		// BMP
		case Format::BMP:
			return loadBMP(Path, *this); break;
		// TGA
		case Format::TGA:
			return loadTGA(Path, *this); break;
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

	int image2dparam_format;
	if (m_format == Format::BMP)
		image2dparam_format = GL_BGR;
	else
		image2dparam_format = GL_RGB;

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
        m_measurements.x,
        m_measurements.y,
        GL_RGB, GL_UNSIGNED_BYTE, m_buffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
				 m_measurements.x, 
				 m_measurements.y, 
				 0, image2dparam_format, 
				 GL_UNSIGNED_BYTE,m_buffer);

	return true;
}
bool h3d::Texture::destroyTexture()
{
	glDeleteTextures(1, &m_texid);
	return true;
}
/////////////////////////////////////////////////////////////////
GLenum h3d::Texture::getColorFormat() { return m_colormode; }
h3d::Vec2<int> h3d::Texture::getSize() { return m_measurements; }
/////////////////////////////////////////////////////////////////