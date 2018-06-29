#include "Font.hpp"
#include "../GUI.hpp"
/////////////////////////////////////////////////////////////
// Implementation of Font
/////////////////////////////////////////////////////////////
gui::Font::Font() {}
gui::Font::Font(char Path[]) {}
gui::Font::~Font() {}
/////////////////////////////////////////////////////////////
bool gui::Font::loadFromFile(char Path[])
{
	FT_Error error;
	//error = FT_New_Face(h3d::intern::gui::g_ft_lib, Path, 0, &m_face);
	if (error == FT_Err_Unknown_File_Format || error) return false;
	else return true;
}
/////////////////////////////////////////////////////////////
bool gui::Font::loadFromMemory(char* data)
{
	assert(data == nullptr);

	FT_Error error;
	//error = FT_New_Memory_Face(h3d::intern::gui::g_ft_lib,(const FT_Byte*)data, sizeof(*data), 0, &m_face);
	if (error) return false;
	else return true;
}
/////////////////////////////////////////////////////////////