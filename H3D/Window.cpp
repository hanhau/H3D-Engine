#include "Window.hpp"
#include <exception>
#include <type_traits>
#include <iostream>

#include "Utilities.hpp"
#include "Event.hpp"
/////////////////////////////////////////////////////////////////
//	Constructor
h3d::Window::Window(h3d::Vec2<int> p_size, 
					std::string			    p_title,
					h3d::WindowStyle		p_style,
					h3d::ContextSettings contextsettings)
{
	m_opened			= true;
	m_Size			= p_size; 
	m_Title			= p_title; 
	m_WindowStyle	= p_style;
	
	setupWin(p_size,p_title,p_style,
			 h3d::ContextSettings(24,8,12,0));

}
/////////////////////////////////////////////////////////////////
//	Get-Methods
h3d::Vec2<int> h3d::Window::getSize()  { return m_Size;  }
std::string				h3d::Window::getTitle() { return m_Title; }
h3d::WindowStyle		h3d::Window::getStyle() { return m_WindowStyle; }
MSG*                    h3d::Window::getMessage(){return &m_Msg;}
HWND*					h3d::Window::getHandle() {return &m_Win;}
bool					h3d::Window::isOpen() {  return m_opened; }
std::string h3d::Window::getContextVer()
{
	return std::string((char*)glGetString(GL_VERSION));
}
/////////////////////////////////////////////////////////////////
//	Framebuffer Operations
void h3d::Window::clear(GLbitfield mask, 
						h3d::Color<GLfloat> col = {0,0,0,1})
{
	glClearColor(col.r,col.g,col.b,col.a);
	glClear(mask);
}
/////////////////////////////////////////////////////////////////
bool h3d::Window::swapBuffers(){
	return static_cast<bool>(SwapBuffers(m_glcontext.m_hdc));
}
/////////////////////////////////////////////////////////////////
h3d::Window::~Window()
{
	close();
	SetWindowLongPtr(m_Win,GWLP_USERDATA, NULL);
	CloseWindow(m_Win);
}
/////////////////////////////////////////////////////////////////
void h3d::Window::close()
{	
	m_opened = false;
	if (m_WindowStyle == WindowStyle::Fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);         
	}
	m_opened = false;
	ShowCursor(TRUE);
	PostQuitMessage(0);
	setActive();
	wglDeleteContext(wglGetCurrentContext());
	PostQuitMessage(0);
	UnregisterClass(Appname, m_Instance);
	m_opened = false;
}
/////////////////////////////////////////////////////////////////
// Editing Window
void h3d::Window::setSize(h3d::Vec2<int> size)
{
	::WindowImpl::setSize(size);
	m_Size = size;
}
void h3d::Window::setTitle(std::string title)
{
	m_Title = title;
}
void h3d::Window::setFullscreen(bool val)
{
		
}
bool h3d::Window::isFullscreen()
{
	return m_isFullscreen;
}
void h3d::Window::resize()
{
	SendMessage(m_Win, WM_SIZE,0,(LPARAM)&m_Size);
}
void h3d::Window::allowResize(bool val)
{
	m_allowResize = val;
}
/////////////////////////////////////////////////////////////////
// Activate OpenGL Context
bool h3d::Window::setActive()
{
	wglMakeCurrent(m_glcontext.m_hdc,m_glcontext.m_hrc);
	return true;
}
/////////////////////////////////////////////////////////////////
//	Updating and receiving Data for Window
bool h3d::Window::pollEvent(h3d::Event &event)
{
#ifdef _WIN32 || _WIN64
	static MSG msg;
	
	if (!PeekMessage(&msg, m_Win, 
		0, 0, PM_NOREMOVE))
		return false;
	
	switch (msg.message)
	{
	case WM_CLOSE:
		event.type = h3d::EventType::Closed;
		break;
	default:
		DefWindowProc(msg.hwnd, msg.message,
					  msg.wParam, msg.lParam);
		break;
	}

	std::cout << "....." << std::endl;
	
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	return true;
#elif defined __linux__

#endif	
}
/////////////////////////////////////////////////////////////////