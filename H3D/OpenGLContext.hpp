#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT

#include <Windows.h>
#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
#include STR(GLEW_INCLUDE/gl/wglew.h)
/////////////////////////////////////////////////////////////////
//	Contextsettings
/////////////////////////////////////////////////////////////////
namespace h3d {
	struct H3D_API ContextSettings
	{
		ContextSettings(BYTE, BYTE, BYTE, BYTE);

		BYTE bits_framebuffer;
		BYTE bits_depthbuffer;
		BYTE bits_stencilbuffer;
		BYTE count_auxbuffers;
	};
}
/////////////////////////////////////////////////////////////////
// ÓpenGLContext
/////////////////////////////////////////////////////////////////
namespace h3d {
	class GLContext
	{
	public:
		GLContext();
		~GLContext();
		bool createContext(HWND hwnd);
	
		HGLRC	m_hrc;	//OpenGL Context
		HDC		m_hdc;	//Win32 Device Context
		HWND	m_hwnd;	//Win32 Window identifier
	};
}
/////////////////////////////////////////////////////////////////