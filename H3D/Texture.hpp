#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
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
	public:
		enum class Format;
	private:
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
		Format m_format;
		GLenum m_colorFormat;

		// Advanced Intel
		h3d::Vec2<int> m_measurements;
		unsigned char           m_bits;
		unsigned long           m_bufferSize;
	public:
		// Format Flags
		enum class H3D_API Format {
			PNG, KTX, BMP, TGA
		};

		// Con/De-structor
		H3D_API Texture();
		H3D_API Texture(char Path[]);
		H3D_API ~Texture();

		// Loading and manipulating
		H3D_API bool loadFromFile(char Path[]);
		H3D_API bool loadFromMemory(void * mem);

		// Set up to OpenGL
		H3D_API bool createTexture();
		H3D_API void generateMipMaps();
		H3D_API bool destroyTexture();

		// Get information
		H3D_API GLenum         getColorFormat();
		H3D_API h3d::Vec2<int> getSize();

		// Handling Texture			
		H3D_API GLuint getTextureIndex();
		H3D_API bool   setActive(bool val);
	};
}
/////////////////////////////////////////////////////////////////
// Converter
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace converter {
		bool H3D_API PNGToKTX(char input[], char output[]);
		bool H3D_API BMPToKTX(char input[], char output[]);
		bool H3D_API TGAToKTX(char input[], char output[]);
	}
}
/////////////////////////////////////////////////////////////////