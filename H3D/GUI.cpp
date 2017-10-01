#include "GUI.hpp"
#include "Utilities.hpp"
/////////////////////////////////////////////////////////////////
#define VAR_TYPE_BUTTON 0b0000'0001
#define VAR_TYPE_TEXT   0b0000'0010
namespace h3d {
	namespace intern { 
		namespace gui {
			static h3d::Program g_programOGL;
			static FT_Library g_ft_lib;
		}
	}
}
/////////////////////////////////////////////////////////////////
// Initialization
/////////////////////////////////////////////////////////////////
bool gui::init()
{
	bool status = true;

	GLchar vertexCode[] = {
		"#version 330 core\n"
		"void main() {"
		"}"
	};
	h3d::Shader vertexShader(GL_VERTEX_SHADER, vertexCode);
	GLchar fragmentCode[] = {
		"#version 330 core\n"
		"void main() {"
		"}"
	};
	h3d::Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentCode);
	h3d::intern::gui::g_programOGL.attachShader(vertexShader);
	h3d::intern::gui::g_programOGL.attachShader(fragmentShader);
	
	status = h3d::intern::gui::g_programOGL.link();
	FT_Error error = FT_Init_FreeType(&h3d::intern::gui::g_ft_lib);
	if (error) status = false;

	return status;
}
/////////////////////////////////////////////////////////////////
// Implementations of Element
/////////////////////////////////////////////////////////////////
gui::Element::Element() {}
gui::Element::~Element() {}
gui::Element::Element(const gui::Element& element) 
{
	*this = element;
}
void gui::Element::operator=(const gui::Element& element)
{
	this->m_elementUnion = element.m_elementUnion;
	this->m_elementType = element.m_elementType;
	this->m_position = element.m_position;
	this->m_size = element.m_size;
}
/////////////////////////////////////////////////////////////////
void gui::Element::render()
{
	switch (m_elementType)
	{
	case VAR_TYPE_BUTTON:
		m_elementUnion.button->render();
	default:
		break;
	}
}
void gui::Element::update()
{
	switch (m_elementType)
	{
	case VAR_TYPE_BUTTON:
		m_elementUnion.button->update();
	default:
		break;
	}
}
/////////////////////////////////////////////////////////////////
// Creation of an Element
/////////////////////////////////////////////////////////////////
template<typename T> const gui::Element gui::newElement(T data) 
{
/*	// Check if Template is used with correct classes
	h3dassert(!std::is_same<T, Button>::value );

	// Create temporary element
	static gui::Element temp_element;

	// Switch through all cases and setup Union in element
	if (std::is_same<T, gui::Button>::value)
	{
		temp_element.m_elementUnion.button = new gui::Button();
		*temp_element.m_elementUnion.button = data;
		temp_element.m_elementType = 0b0000'0001;
	}
	else
		temp_element.m_elementType = 0;
	return temp_element;
	*/
	return gui::Element();
}
template H3D_API const gui::Element gui::newElement(gui::Button);
/////////////////////////////////////////////////////////////////
// Implementations of Panel
/////////////////////////////////////////////////////////////////
gui::Panel::Panel() { m_needsUpdate = true; }
gui::Panel::~Panel() {}
/////////////////////////////////////////////////////////////////
void gui::Panel::addElement(const gui::Element element)
{
	m_elementVec.push_back(element);
}
/////////////////////////////////////////////////////////////////
void gui::Panel::show() { m_visible = true;  }
void gui::Panel::hide() { m_visible = false; }
bool gui::Panel::isVisible() { return m_visible; }
/////////////////////////////////////////////////////////////////
void gui::Panel::prepareRendering()
{
	
}
/////////////////////////////////////////////////////////////////
void gui::Panel::update()
{
	for (auto &iter : m_elementVec)
		iter.update();
}
void gui::Panel::render()
{
	for (auto &iter : m_elementVec)
		iter.render();
}
/////////////////////////////////////////////////////////////////