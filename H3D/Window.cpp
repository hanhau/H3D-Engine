#include "Window.hpp"
#include <exception>
#include <type_traits>
#include <iostream>

#include "Utilities.hpp"
/////////////////////////////////////////////////////////////////
//	Window Handling Func
LRESULT CALLBACK _H3D_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	// Resize Event
	case WM_RESIZE:
		
		break;
	// Input Handling
	case WM_INPUT:
		if (h3d::InputManager.isInputActive(DEVICE_TYPE_KEYBOARD)){
			h3d::InputManager.updateKeyboard();
		}
		if (h3d::InputManager.isInputActive(DEVICE_TYPE_MOUSE)){
			h3d::InputManager.updateMouse();
		}
		if (h3d::InputManager.isInputActive(DEVICE_TYPE_JOYSTICK)){
			h3d::InputManager.updateJoystick();
		}
		break;
	// Window Creation
	case WM_CREATE:
		// Input Setup for this Window
		h3d::InputManager.setupHardware(hwnd);
		break;
	case WM_PAINT:		
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	// Default Window Procedure
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}
/////////////////////////////////////////////////////////////////
//	ContextSettings
h3d::ContextSettings::ContextSettings(BYTE bits_fb, BYTE bits_db,
									  BYTE bits_sb, BYTE c_aux):
	bits_framebuffer(bits_fb),bits_depthbuffer(bits_db),
	bits_stencilbuffer(bits_sb),count_auxbuffers(c_aux){}
/////////////////////////////////////////////////////////////////
//	Constructor
h3d::Window::Window(h3d::Vec2<unsigned int> p_size, wchar_t* p_title,char p_style)
{
	opened = true;
	Size = p_size; Title = p_title; Style = p_style;
	Appname = Title;
	h_Instance = GetModuleHandle(NULL);
	/////////////////////////////////////////////////////////////
	//	Window Creation			
	h_WinClass = { 0 };
	h_WinClass.cbSize = sizeof(WNDCLASSEX);
	h_WinClass.style = CS_OWNDC;
	h_WinClass.lpfnWndProc = _H3D_WndProc;
	h_WinClass.cbClsExtra = 0;
	h_WinClass.cbWndExtra = 0;
	h_WinClass.hInstance = h_Instance;
	h_WinClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	h_WinClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	h_WinClass.hbrBackground = NULL;
	h_WinClass.lpszMenuName = NULL;
	h_WinClass.lpszClassName = Appname;
	h_WinClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&h_WinClass))
	{
		std::cout << GetLastError() << std::endl;
		MessageBoxA(NULL, "Couldn´t register Window!", "FATAL ERROR",
					MB_ICONEXCLAMATION | MB_OK);
		this->~Window();
	}
	if (h3d::DebugMode)
	{
		h3d::Debugstream.open("Window_Log.txt");
		h3d::Debugstream << "Registered WindowClass\n";
	}
	// Create h_Win
	DWORD dwExStyle = m_dwExStyle = WS_EX_OVERLAPPEDWINDOW;
	DWORD dwStyle = m_dwStyle = WS_OVERLAPPEDWINDOW |WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	h_Win = CreateWindowEx(
		dwExStyle,
		Appname, Title,
		dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		Size.x, Size.y,
		NULL, NULL,
		h_Instance,
		NULL);
	if (h_Win == NULL) std::cout << GetLastError() << std::endl;
	if (h3d::DebugMode)
		h3d::Debugstream << "Created Window\n";

	// create Context
	if (!GLContext.createContext(h_Win) && h3d::DebugMode)
		h3d::Debugstream << "Failed to create OGL Context\n";

	// Update Window
	ShowWindow(h_Win, SW_SHOW);
	UpdateWindow(h_Win);
	SetFocus(h_Win);
	if (h3d::DebugMode)
		h3d::Debugstream << "Finished creating window\n";
}
/////////////////////////////////////////////////////////////////
//	Get-Methods
h3d::Vec2<unsigned int> h3d::Window::getSize()  { return Size;  }
wchar_t*				h3d::Window::getTitle() { return Title; }
char					h3d::Window::getStyle() { return Style; }
MSG*                    h3d::Window::getMessage(){return &h_Msg;}
HWND*					h3d::Window::getHandle() {return &h_Win;}
bool					h3d::Window::isOpen() {  return opened; }
/////////////////////////////////////////////////////////////////
std::string h3d::Window::getContextVer()
{
	return std::string((char*)glGetString(GL_VERSION));
}
/////////////////////////////////////////////////////////////////
//	Framebuffer Operations
void h3d::Window::clear(GLbitfield mask)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(mask);
}
/////////////////////////////////////////////////////////////////
bool h3d::Window::swapBuffers(){
	return SwapBuffers(GLContext.m_hdc);
}
/////////////////////////////////////////////////////////////////
h3d::Window::~Window()
{
	close();
	SetWindowLongPtr(h_Win,GWLP_USERDATA, NULL);
	CloseWindow(h_Win);
}
/////////////////////////////////////////////////////////////////
void h3d::Window::close()
{		   
	ShowCursor(TRUE);
	setActive();
	opened = false;
	wglDeleteContext(wglGetCurrentContext());
	UnregisterClass(Appname, h_Instance);
	PostQuitMessage(0);
}
/////////////////////////////////////////////////////////////////
// Editing Window
void h3d::Window::setSize(h3d::Vec2<unsigned int> size)
{
	
}
void h3d::Window::setTitle(std::wstring title)
{
	Title = const_cast<wchar_t*>(title.c_str());
}
void h3d::Window::setFullscreen(bool val)
{
	
}
bool h3d::Window::isFullscreen()
{
	return is_fullscreen;
}
void h3d::Window::resize()
{
	SendMessage(h_Win, WM_RESIZE,0,*reinterpret_cast<LONG*>(this));
	if(m_allowResize)
	{
		RECT rect;
		rect.left = 0;
		rect.right = Size.x;
		rect.top = 0;
		rect.bottom = Size.y;

		AdjustWindowRectEx(
			(LPRECT)&rect,
			m_dwStyle,
			FALSE,
			m_dwExStyle);
	}

}
void h3d::Window::allowResize(bool val)
{
	m_allowResize = val;
}
/////////////////////////////////////////////////////////////////
// Activate OpenGL Context
bool h3d::Window::setActive()
{
	wglMakeCurrent(GLContext.m_hdc, GLContext.m_hrc);
	return true;
}
/////////////////////////////////////////////////////////////////
//	Updating and receiving Data for Window
void h3d::Window::update()
{
	while (PeekMessage(&h_Msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&h_Msg);
		DispatchMessage(&h_Msg);
	}
}
/////////////////////////////////////////////////////////////////