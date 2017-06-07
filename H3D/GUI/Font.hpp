#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT
/////////////////////////////////////////////////////////////
#include "../Texture.hpp"
#include "../Vector.hpp"
#include "../externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
#include STR(FREETYPE_INCLUDE/ft2build.h)
#include STR(FREETYPE_INCLUDE/freetype/freetype.h)
/////////////////////////////////////////////////////////////
// Font class basing of freetype (wrapper class)
/////////////////////////////////////////////////////////////
namespace gui {
	class Font
	{
		FT_Face m_face;
		h3d::Texture m_texture;
	public:
		H3D_API Font();
		H3D_API ~Font();
		H3D_API Font(char Path[]);

		bool H3D_API loadFromFile(char Path[]);
		bool H3D_API loadFromMemory(char* data);
	};
}
/////////////////////////////////////////////////////////////