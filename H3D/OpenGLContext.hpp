#pragma once
#include <Windows.h>
#include <GL\glew.h>
#include <GL\wglew.h>
/////////////////////////////////////////////////////////////////
//	Contextsettings
/////////////////////////////////////////////////////////////////
namespace h3d {
	struct _declspec(dllexport) ContextSettings
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