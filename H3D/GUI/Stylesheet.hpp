#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT
/////////////////////////////////////////////////////////////////
#include <fstream>
#include "../../H3D/Graphics/Color.hpp"
#include "..\externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
// Class providing a universal design over all GUI elements
/////////////////////////////////////////////////////////////////
namespace gui {
	namespace StylesheetModule
	{
		struct H3D_API Button {
			h3d::Color<GLfloat> m_normalColor;
		};
	}
	class Stylesheet
	{
	private:
		// Modules containing Styles
		StylesheetModule::Button m_buttonStyle;
	public:
		H3D_API Stylesheet();
		H3D_API ~Stylesheet();

		// loading from a xml File
		void H3D_API loadFromFile(char Path[]);

	};
}
/////////////////////////////////////////////////////////////////