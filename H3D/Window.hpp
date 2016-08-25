#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include <Windows.h>
#include <string>
#include <vector>
#include <thread>
#include "Vector.hpp"
#include "Color.hpp"
#include <GL\glew.h>
#include <GL\wglew.h>
#include "OpenGLContext.hpp"
#include "InputManager.hpp"

#define WM_RESIZE (WM_USER + 0x0001)
/////////////////////////////////////////////////////////////////
//	_H3D_WndProc
LRESULT CALLBACK _H3D_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
namespace h3d{
/////////////////////////////////////////////////////////////////
// Window Styles
namespace Style{
	static const char Default = 'd';
	static const char Fullscreen = 'f';
}
/////////////////////////////////////////////////////////////////
//	class Window
/////////////////////////////////////////////////////////////////
class Window
{
private:
	// Data
	Vec2<unsigned int> Size;
	wchar_t* Title;
	wchar_t* Appname;
	char Style;
	bool opened;
	bool is_fullscreen;
	bool m_allowResize;

	// OpenGL Context 
	h3d::GLContext GLContext;
	int minorOpenGL;
	int majorOpenGL;
	
	// Winapi Styles
	DWORD m_dwExStyle;
	DWORD m_dwStyle;

	// WinAPI stuff
	RECT WindowRect;
	HINSTANCE h_Instance;
	HWND h_Win;
	MSG h_Msg;
	WNDCLASSEX h_WinClass;

	// Eventhandling
	bool startUpdateThread();
	bool stopUpdateThread();
	std::vector<MSG> m_msgQueue;
	void m_UpdateThread();
public:

	// Window Creation and Destruction
	 _declspec(dllexport) Window(h3d::Vec2<unsigned int> p_size,wchar_t* p_title,char p_style);
	 _declspec(dllexport) ~Window();
	void  _declspec(dllexport) close();

	// Get-Methods
	Vec2<unsigned int> _declspec(dllexport) getSize();
	_declspec(dllexport)           wchar_t* getTitle();
	char               _declspec(dllexport) getStyle();
	std::string		   _declspec(dllexport) getContextVer();
	_declspec(dllexport) MSG*               getMessage();
	_declspec(dllexport) HWND*			    getHandle();
	bool			   _declspec(dllexport) isOpen();

	// Framebuffer Operations
	void H3D_API clear(GLbitfield mask);
	bool H3D_API swapBuffers();

	// Editing Window
	void H3D_API setSize(h3d::Vec2<unsigned int>size);
	void H3D_API setTitle(std::wstring title);
	void H3D_API setFullscreen(bool val);
	bool H3D_API isFullscreen();
	void H3D_API resize();
	void H3D_API allowResize(bool val);

	// Set OpenGL Context as current
	bool _declspec(dllexport) setActive();

	// Update Window Events
	void _declspec(dllexport) update();
};
/////////////////////////////////////////////////////////////////
}