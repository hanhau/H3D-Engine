#include "../../H3D/GUI/Font.hpp"
#include "../../H3D/GUI/GUI.hpp"

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
	FT_Error error;
	if (error == FT_Err_Unknown_File_Format || error) return false;
	else return true;
}
/////////////////////////////////////////////////////////////
bool gui::Font::loadFromMemory(char* data)
{
	assert(data == nullptr);

	FT_Error error;
	if (error) return false;
	else return true;
}
/////////////////////////////////////////////////////////////