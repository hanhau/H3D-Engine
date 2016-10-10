#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT
/////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <sstream>
#include "Vector.hpp"
#include "Program.hpp"
#include <gl/glew.h>
#include <assert.h>
/////////////////////////////////////////////////////////////////
#include "GUI\Button.hpp"
#include "GUI\Text.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
/////////////////////////////////////////////////////////////////
// Graphical User Interface
/////////////////////////////////////////////////////////////////
namespace gui {
	// Needed Init function to setup OpenGL stuff
	bool H3D_API init();
	// Global OpenGL/Freetype Stuff
	static h3d::Program g_programOGL;
	static FT_Library g_ft_lib;
	// Initialisation function
	class Element;
	template<typename T> const Element newElement(T data);
	// Base GUI Element class
	class Element
	{
		template<typename T> friend const Element newElement(T data);
	private:
		union _t_{
			Button button;
			Text   text;
		}m_elementUnion;
		int m_elementType;

		h3d::Vec2<GLfloat> m_position;
		h3d::Vec2<GLfloat> m_size;
	public:
		H3D_API Element(const Element &element);
		H3D_API ~Element();
		Element();
		void H3D_API operator=(const Element& element);

		void H3D_API render();
		void H3D_API update();
	};
	// Holds Elements together in groups
	class Panel
	{
	private:
		std::vector<gui::Element> m_elementVec;

		bool m_visible;
	public:
		void H3D_API addElement(const gui::Element element);

		void H3D_API show();
		void H3D_API hide();
		bool H3D_API isVisible();

		void H3D_API prepareRendering();
		void H3D_API render();
		void H3D_API update();
	};
}