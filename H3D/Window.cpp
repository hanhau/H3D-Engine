#include "Window.hpp"
#include "WindowImpl.hpp"

#include "Utilities.hpp"
#include "Event.hpp"

#ifdef _WIN32 || _WIN64
#include "Win32WindowImpl.hpp"
#elif defined _linux_
#include "X11WindowImpl.hpp"
#endif 
#define pimpl m_impl.get()
#define glcontext m_context.get()

/////////////////////////////////////////////////////////////////
h3d::Window::Window(h3d::Vec2<int> p_size, 
					std::string			    p_title,
					h3d::WindowStyle		p_style,
					h3d::ContextSettings contextsettings)
{
#ifdef _WIN32 || _WIN64
	m_impl = std::unique_ptr<h3d::intern::Win32WindowImpl>();
#elif defined _linux_
	m_impl = std::unique_ptr<h3d::intern::X11WindowImpl>();
#endif 

	m_opened		= true;
	m_Size			= p_size; 
	m_Title			= p_title; 
	m_WindowStyle	= p_style;
	
	h3d::Vec2<int> i = {1,2};

	pimpl->create(p_size, p_title, p_style,
				  h3d::ContextSettings(24, 8, 12, 0));
	glcontext->createContext(pimpl);
}
/////////////////////////////////////////////////////////////////
// OpenGL Operations
std::string h3d::Window::getContextVer() {
	return std::string((char*)glGetString(GL_VERSION));
}
void h3d::Window::clear(GLbitfield mask,h3d::Color<GLfloat> col={ 0,0,0,1 })
{
	glClearColor(col.r, col.g, col.b, col.a);
	glClear(mask);
}
/////////////////////////////////////////////////////////////////
// Getting
h3d::Vec2<int>          h3d::Window::getSize() { return m_Size; }
std::string				h3d::Window::getTitle() { return m_Title; }
h3d::WindowStyle		h3d::Window::getStyle() { return m_WindowStyle; }
bool					h3d::Window::isOpen() { return m_opened; }
bool					h3d::Window::isFullscreen() { return m_isFullscreen; }
/////////////////////////////////////////////////////////////////