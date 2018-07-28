#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT
/////////////////////////////////////////////////////////////
#include <string>
#include "Font.hpp"
#include "../../H3D/Graphics/Color.hpp"

#include <GL/glew.h>
/////////////////////////////////////////////////////////////
// Text class
/////////////////////////////////////////////////////////////
namespace gui {
	class Text
	{
	private:
		gui::Font*          m_fontPtr;
		std::string         m_string;
		unsigned short      m_charSize;
		h3d::Color<GLfloat> m_color;
	public:
		H3D_API Text();
		H3D_API Text(gui::Font &font,
					 std::string string,
					 unsigned short size,
					 h3d::Color<GLfloat> color);
		H3D_API ~Text();

		// Text specific functions
		void H3D_API setFont(gui::Font &font);
		void H3D_API setString(std::string string);
		void H3D_API setSize(unsigned short size);
		void H3D_API setColor(h3d::Color<GLfloat> color);
		
		// Element functions
		void H3D_API render();
		void H3D_API update();
	};
}
/////////////////////////////////////////////////////////////
