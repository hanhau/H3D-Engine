#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif 

#ifdef _WIN32 || _WIN64
#include <Windows.h>
#elif defined __linux__

#endif 

#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
#include STR(GLEW_INCLUDE/gl/wglew.h)
/////////////////////////////////////////////////////////////////
//	Contextsettings
/////////////////////////////////////////////////////////////////
namespace h3d {
	struct H3D_API ContextSettings
	{
		inline ContextSettings() {}
		inline ContextSettings(unsigned char bits_fb,
							   unsigned char bits_db,
							   unsigned char bits_sb,
							   unsigned char c_aux) :
			bits_framebuffer(bits_fb),
			bits_depthbuffer(bits_db),
			bits_stencilbuffer(bits_sb),
			count_auxbuffers(c_aux) 
		{}

		unsigned char bits_framebuffer;
		unsigned char bits_depthbuffer;
		unsigned char bits_stencilbuffer;
		unsigned char count_auxbuffers;
	};
}
/////////////////////////////////////////////////////////////////
// OpenGLContext
/////////////////////////////////////////////////////////////////
namespace h3d {
#ifdef _WIN32 || _WIN64
	struct GLContextWinapi
	{
		bool createContext(HWND hwnd,ContextSettings cs);
	
		HGLRC	m_hrc;	//OpenGL Context
		HDC		m_hdc;	//Win32 Device Context
		HWND	m_hwnd;	//Win32 Window identifier
	};
#elif defined __linux__
	struct GLContextUNIX
	{
		bool createContext();

		// etc ....
	};
#endif
}
/////////////////////////////////////////////////////////////////