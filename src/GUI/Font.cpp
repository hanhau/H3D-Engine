#include "../../H3D/GUI/Font.hpp"
#include "../../H3D/GUI/GUI.hpp"
#include "../../H3D/System/FileSystem.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
/////////////////////////////////////////////////////////////
// Implementation of Font
/////////////////////////////////////////////////////////////
struct gui::Font::impl {
	FT_Face ft_face;
};
gui::Font::Font() {}
gui::Font::Font(char Path[]) {}
gui::Font::~Font() {}
/////////////////////////////////////////////////////////////
bool gui::Font::loadFromFile(char Path[])
{
	h3d::FileHandle fh(Path);
	

	return false;
}
/////////////////////////////////////////////////////////////
bool gui::Font::loadFromMemory(char* data)
{
	assert(data == nullptr);

	return false;
}
/////////////////////////////////////////////////////////////