#include "../../H3D/System/Window.hpp"
#include "../../H3D/System/WindowImpl.hpp"

#include "../../H3D/System/Utilities.hpp"
#include "../../H3D/System/Event.hpp"
#include "../../H3D/OS/WglContext.hpp"

// Windows
#ifdef _WIN32 || _WIN64

#include "../../H3D/OS/Win32WindowImpl.hpp"
typedef h3d::intern::Win32WindowImpl WindowImplType;

// Linux
#elif defined _linux_

#include "../../H3D/OS/X11WindowImpl.hpp"
typedef h3d::intern::X11WindowImpl WindowImplType;

#endif 

/////////////////////////////////////////////////////////////////
h3d::Window::Window(h3d::Vec2<int> p_size, 
					std::string			    p_title,
					h3d::WindowStyle		p_style,
					h3d::ContextSettings contextsettings)
{
	m_opened		= true;
	m_Size			= p_size; 
	m_Title			= p_title; 
	m_WindowStyle	= p_style;
	m_ContextSettings = contextsettings;

	m_impl = std::unique_ptr<WindowImplType>(new WindowImplType());
	if (false == m_impl->create(p_size, p_title, p_style, contextsettings)) {
		h3d::Log::error("Unable to create Window");
	}

	m_context = std::unique_ptr<h3d::intern::WglContext>(new h3d::intern::WglContext());	
	if (false == m_context.get()->createContext(m_impl)){
		h3d::Log::error("Unable to create OpenGL Context");
	}
}
/////////////////////////////////////////////////////////////////
// Message Handling
bool h3d::Window::pollEvent(h3d::Event& event) {
	if (m_impl != nullptr && m_impl->popEvent(event)) {
		return true;
	}
	else
		return false;
}
/////////////////////////////////////////////////////////////////
// OpenGL Operations
std::string h3d::Window::getContextVer() {
	return std::string((char*)glGetString(GL_VERSION));
}
void h3d::Window::clear(unsigned int mask,h3d::Color<float> col={ 0,0,0,1 })
{
	glClearColor(col.r, col.g, col.b, col.a);
	glClear(mask);
}
/////////////////////////////////////////////////////////////////
// Setting
void h3d::Window::setActive(bool val){
	
}
void h3d::Window::close() {
	m_impl->close();
}
void h3d::Window::swapBuffers() {
	m_impl->swapBuffers();
}
void h3d::Window::setVSync(bool val){
	m_impl->setVSync(val);
}
h3d::Window::~Window() {
	
}
/////////////////////////////////////////////////////////////////
// Getting
h3d::Vec2<int>   h3d::Window::getSize() { return m_Size; }
std::string		 h3d::Window::getTitle() { return m_Title; }
h3d::WindowStyle h3d::Window::getStyle() { return m_WindowStyle; }
bool			 h3d::Window::isOpen() { return m_opened = m_impl->isOpen(); }
bool			 h3d::Window::isFullscreen() { return m_isFullscreen; }
/////////////////////////////////////////////////////////////////