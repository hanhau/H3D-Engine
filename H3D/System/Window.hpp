#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <type_traits>

#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/Graphics/Color.hpp"
#include "../../H3D/Graphics/OpenGLContext.hpp"
#include "../../H3D/System/InputManager.hpp"
#include "../../H3D/System/Event.hpp"
#include "../../H3D/System/WindowImpl.hpp"

#include "../../H3D/System/Config.hpp"
#ifdef H3D_SYSTEM_WINDOWS
#include "../../H3D/OS/WglContext.hpp"
#elif defined H3D_SYSTEM_LINUX
#include "../../H3D/OS/X11Context.hpp"
#endif

class h3d::Event;
namespace h3d{
/////////////////////////////////////////////////////////////////
enum class WindowStyle {
	Default,	
	Fullscreen  
};
/////////////////////////////////////////////////////////////////
// Portable Window Class for rendering OpenGL
/////////////////////////////////////////////////////////////////
class Window : Uncopyable 
{
#ifdef H3D_SYSTEM_WINDOWS
	
	friend h3d::intern::WglContext;
	std::unique_ptr<h3d::intern::WglContext> m_context;
	std::unique_ptr<h3d::intern::Win32WindowImpl> m_impl;

#elif defined H3D_SYSTEM_LINUX

	friend h3d::intern::X11Context;
	std::unique_ptr<h3d::intern::X11Context> m_context;
	std::unique_ptr<h3d::intern::X11WindowImpl> m_impl;

#endif
	// Defined different
	void setupWin(h3d::Vec2<int>size,
				  std::string title,
				  h3d::WindowStyle ws,
				  h3d::ContextSettings cs);

	// Data
	Vec2<int>		   m_Size;
	std::string        m_Title;
	WindowStyle		   m_WindowStyle;
	ContextSettings    m_ContextSettings;

	bool m_opened;
	bool m_isFullscreen;
	bool m_allowResize;

	// OpenGL ContextVersion
	int minorOpenGL;
	int majorOpenGL;

	// To make ptrs
	Window() = default;
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
	H3D_API Window(h3d::Vec2<int> p_size,
				   std::string			   p_title,
				   WindowStyle			   p_style,
				   ContextSettings contextsettings);
	H3D_API ~Window();

	// OpenGL Operations
	enum BufferBit {
		Color = 0x00004000,
		Accum = 0x00000400,
		Depth = 0x00000200,
		Stencil = 0x0000100
	};
	std::string H3D_API getContextVer();
	void		H3D_API clear(unsigned int mask,h3d::Color<float> col);
	
	// system specific
	void		H3D_API swapBuffers();
	void		H3D_API setActive(bool val);
	void		H3D_API setVSync(bool val);

	// Getting
	Vec2<int>		   H3D_API getSize();
	std::string        H3D_API getTitle();
	WindowStyle        H3D_API getStyle();
	bool			   H3D_API isOpen();
	bool			   H3D_API isFullscreen();

	// Setting
	void H3D_API setSize(h3d::Vec2<int>size);	
	void H3D_API setTitle(std::string title);	
	void H3D_API setFullscreen(bool val);	

	// Utils
	void H3D_API resize();	
	void H3D_API allowResize(bool val);	
	void H3D_API showCursor(bool val);	
	void H3D_API close();

	// Poll Events
	bool H3D_API pollEvent(h3d::Event &event);
};
/////////////////////////////////////////////////////////////////
}