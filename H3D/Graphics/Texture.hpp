#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <memory>
#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/System/FileDataStructures.hpp"

#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
//	class Texture
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Texture 
	{	
	public:
		enum class Format;
	private:
		bool loadPNG(char[], h3d::Texture& ref );
		bool loadKTX(char[], h3d::Texture& ref);
		bool loadBMP(char[], h3d::Texture& ref );
		bool loadTGA(char[], h3d::Texture& ref);

		// OpenGL Stuff
		GLuint m_texid;
		GLuint m_colormode;

		// Buffer
		char *m_buffer;

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
		bool H3D_API loadFromFile(char Path[]);
		bool H3D_API loadFromMemory(void * mem);

		// Set up to OpenGL
		bool H3D_API createTexture();
		void H3D_API generateMipMaps();
		bool H3D_API destroyTexture();

		// Get information
		H3D_API GLenum         getColorFormat();
		H3D_API h3d::Vec2<int> getSize();

		// Handling Texture			
		GLuint H3D_API getTextureIndex();
		bool   H3D_API setActive(bool val);
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