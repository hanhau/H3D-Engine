#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT
/////////////////////////////////////////////////////////////
#include "../Texture.hpp"
#include "../Vector.hpp"
#include <gl/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#define  FT_STATIC
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