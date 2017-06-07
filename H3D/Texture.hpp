#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include <memory>
#include "Vector.hpp"
#include "FileDataStructures.hpp"

#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
//	class Texture
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Texture 
	{	
		bool loadPNG(char[], h3d::Texture&);
		bool loadKTX(char[], h3d::Texture&);
		bool loadBMP(char[], h3d::Texture&);
		bool loadTGA(char[], h3d::Texture&);

		// OpenGL Stuff
		GLuint m_texid;
		GLuint m_colormode;

		// Buffer
		unsigned char *m_buffer;

		// Format of the Image loaded
		int m_format;
		GLenum m_colorFormat;

		// Advanced Intel
		h3d::Vec2<unsigned int> m_measurements;
		unsigned char           m_bits;
		unsigned long           m_bufferSize;
	public:
		// Format Flags
		struct H3D_API Format {
			static const int PNG; 
			static const int KTX;
			static const int BMP;
			static const int TGA;
		};

		// Con/De-structor
		H3D_API Texture();
		H3D_API Texture(char Path[]);
		H3D_API ~Texture();

		// Loading and manipulating
		H3D_API bool loadFromFile(char Path[]);

		// Set up to OpenGL
		H3D_API bool createTexture();
		H3D_API bool destroyTexture();

		// Get information
		H3D_API GLenum                  getColorFormat();
		H3D_API h3d::Vec2<unsigned int> getSize();

		// Handling Texture			
		H3D_API GLuint getTextureIndex();
		H3D_API bool   setActive(bool val);
	};
}
/////////////////////////////////////////////////////////////////