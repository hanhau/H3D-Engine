#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT
/////////////////////////////////////////////////////////////
#include "../../H3D/Graphics/Texture.hpp"
#include "../../H3D/Math/Vector.hpp"
/////////////////////////////////////////////////////////////
// Font class basing of freetype (wrapper class)
/////////////////////////////////////////////////////////////
namespace gui {
	class Font
	{
		struct impl;
		std::unique_ptr<impl> m_impl;
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