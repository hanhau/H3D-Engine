#include "Text.hpp"
/////////////////////////////////////////////////////////////
// Implementations of the Text class
/////////////////////////////////////////////////////////////
gui::Text::Text() {}
gui::Text::Text(gui::Font &font,
				std::string string,
				unsigned short size,
				h3d::Color<GLfloat> color)
{
	setFont(font); setString(string);
	setSize(size); setColor(color);
}
gui::Text::~Text() {}
/////////////////////////////////////////////////////////////
void gui::Text::setFont(gui::Font &font) { m_fontPtr = &font; }
void gui::Text::setString(std::string string) { m_string = std::move(string); }
void gui::Text::setSize(unsigned short size) { m_charSize = size; }
void gui::Text::setColor(h3d::Color<GLfloat> color) { m_color = color; }
/////////////////////////////////////////////////////////////
void gui::Text::render()
{

}
/////////////////////////////////////////////////////////////
void gui::Text::update()
{

}
/////////////////////////////////////////////////////////////