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

#include "Vector.hpp"
#include "Color.hpp"
#include "OpenGLContext.hpp"
#include "InputManager.hpp"
#include "Event.hpp"

#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)

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
class Window
{
private:
	// Pimp Idiom
	class WindowImpl;
	std::unique_ptr<WindowImpl> m_pimpl;

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

	// Event Queue
	void  pushEvent(Event);
	Event popEvent();
	std::queue<Event> m_EventQueue;
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
	std::string H3D_API getContextVer();
	void		H3D_API clear(GLbitfield mask,h3d::Color<GLfloat> col);
	bool		H3D_API swapBuffers();
	bool		H3D_API setActive();

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