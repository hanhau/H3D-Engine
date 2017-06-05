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
#include "opengl\ogl_util.h"
#include <assert.h>
/////////////////////////////////////////////////////////////////
#include "GUI\Button.hpp"
#include "GUI\Text.hpp"
#include "..\dependencies\freetype\ft2build.h"
#include "..\dependencies\freetype\freetype\freetype.h"
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
		union _unionMember{
			Button *button;
			Text   *text;
		}m_elementUnion;
		int m_elementType;

		h3d::Vec2<GLfloat> m_position;
		h3d::Vec2<GLfloat> m_size;
	public:
		H3D_API Element(const Element &element);
		H3D_API ~Element();
		H3D_API Element();
		void H3D_API operator=(const Element& element);

		void H3D_API render();
		void H3D_API update();
	};
	// Holds Elements together in groups
	class Panel
	{
		friend Button;
	private:
		// Managing contained elements
		std::vector<gui::Element> m_elementVec;
		bool					  m_needsUpdate;

		// OpenGL batched data
		std::vector<h3d::Vertex> m_batchedVertices;

		// visibility
		bool m_visible;
	public:
		H3D_API Panel();
		H3D_API ~Panel();

		void H3D_API addElement(const gui::Element element);

		void H3D_API show();
		void H3D_API hide();
		bool H3D_API isVisible();

		void H3D_API prepareRendering();
		void H3D_API render();
		void H3D_API update();
	};
}