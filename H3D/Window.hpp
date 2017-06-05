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
#include "opengl\ogl_util.h"
#include "..\dependencies\glew\gl\wglew.h"
#include "OpenGLContext.hpp"
#include "InputManager.hpp"

#define WM_RESIZE (WM_USER + 0x0001)
/////////////////////////////////////////////////////////////////
//	_H3D_WndProc
LRESULT CALLBACK _H3D_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
namespace h3d{
/////////////////////////////////////////////////////////////////
/// \enum Window styles for creating a window
enum class WindowStyle {
	Default,	/*!< Create a normal window */
	Fullscreen  /*!< Produces a fullscreen window */
};
/////////////////////////////////////////////////////////////////
///	\brief OpenGL Window for rendering
/////////////////////////////////////////////////////////////////
class Window
{
private:
	// Data
	Vec2<unsigned int> Size;
	wchar_t* Title;
	wchar_t* Appname;
	WindowStyle Style;
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
	/////////////////////////////////////////////////////////////
	/// \brief Construct a new window and open it.
	///	This constructor creates the Winapi window and initializes 
	/// it with a OpenGL context
	///
	/// \param p_size  Size of the window
	/// \param p_title Title on the window frame
	/// \param p_style Set a WindowStyle
	/////////////////////////////////////////////////////////////
	H3D_API Window(h3d::Vec2<unsigned int> p_size,wchar_t* p_title,WindowStyle p_style);

	/////////////////////////////////////////////////////////////
	/// \brief Destruct a window and clean up context
	/////////////////////////////////////////////////////////////
	H3D_API ~Window();

	// Getter Methods
	/////////////////////////////////////////////////////////////
	/// \return Size of the window as Vec2
	Vec2<unsigned int> H3D_API getSize();
	/// \return Title of the window as wchar_t*
	H3D_API           wchar_t* getTitle();
	/// \return WindowStyle of the window
	WindowStyle        H3D_API getStyle();
	/// \return Validate OpenGL context version
	std::string		   H3D_API getContextVer();
	/// \return Return current winapi message from window
	H3D_API MSG*               getMessage();
	/// \return Get winapi HWND handle
	H3D_API HWND*			   getHandle();
	/// \return Returns true if window is opened
	bool			   H3D_API isOpen();
	/// \return Returns true if window is in fullscreen
	bool H3D_API               isFullscreen();

	// Framebuffer Operations
	/////////////////////////////////////////////////////////////
	/// \brief Clears the backside framebuffer content
	/// \param mask Decide what gets cleared. Same params as glClear(...)
	void H3D_API clear(GLbitfield mask);
	/// \brief Swap backside and frontend framebuffer
	/// \return True, if successful
	bool H3D_API swapBuffers();

	// Editing Window
	/////////////////////////////////////////////////////////////
	/// \param size New size of the window
	void H3D_API setSize(h3d::Vec2<unsigned int>size);
	/// \param title Defines a new title for the window
	void H3D_API setTitle(std::wstring title);
	/// \param val Change fullscreen state
	void H3D_API setFullscreen(bool val);
	/// \brief Forces the window to resize
	void H3D_API resize();
	/// \param val Allows resize events
	void H3D_API allowResize(bool val);
	/// \param val Shows or hides Cursor
	void H3D_API showCursor(bool val);
	/// \brief Closes the window and destroys OpenGL context
	void  H3D_API close();

	// Set OpenGL Context as current
	/// \brief Sets window as current OpenGL context
	/// 
	/// This must be done before anything gets rendered into the window
	bool H3D_API setActive();

	// Update Window Events
	/// \brief NOT FINAL YET
	void H3D_API update();
};
/////////////////////////////////////////////////////////////////
}