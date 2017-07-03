#include "Window.hpp"
#include <exception>
#include <type_traits>
#include <iostream>

#include "Utilities.hpp"

#ifdef _WIN32 || _WIN64
/////////////////////////////////////////////////////////////////
//	Window Handling Func
LRESULT CALLBACK _H3D_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	// Resize Event
	case WM_SIZE:
	{
		// break if winapi message
		if (lparam == 0 || wparam == 0) break;

		h3d::Vec2<unsigned int> *newsize = new h3d::Vec2<unsigned int>();
			newsize = (h3d::Vec2<unsigned int>*)lparam;

		SetWindowPos(hwnd, 0, 1, 1, newsize->x, newsize->y, SWP_NOMOVE);
	}
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
#endif
/////////////////////////////////////////////////////////////////
//	ContextSettings
h3d::ContextSettings::ContextSettings(BYTE bits_fb, BYTE bits_db,
									  BYTE bits_sb, BYTE c_aux):
	bits_framebuffer(bits_fb),bits_depthbuffer(bits_db),
	bits_stencilbuffer(bits_sb),count_auxbuffers(c_aux){}
/////////////////////////////////////////////////////////////////
//	Constructor
h3d::Window::Window(h3d::Vec2<unsigned int> p_size, wchar_t* p_title,h3d::WindowStyle p_style)
{
	opened = true;
	Size = p_size; Title = p_title; Style = p_style;
	Appname = Title;
	
#ifdef __linux__
	/////////////////////////////////////////////////////////////
	// Linux Window Creation
	/////////////////////////////////////////////////////////////
	
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		if (h3d::DebugMode) 
			Log.error("Failed to connect to X Server!");
		return false;
	}

	root = DefaultRootWindow(dpy);

	vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		if (h3d::DebugMode)
			Log.error("Xlib: Not correct visual found");
		return false;
	}

	cmap = XCreateColormap(dpy,root,vi->visual,AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(dpy, root, 0, 0, 
						Size.x,Size.y
						0, 
						vi->depth, InputOutput, 
						vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(dpy, win);
	XStoreName(dpy, win, (char*)Title);

	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

	glEnable(GL_DEPTH_TEST);

#elif defined _WIN32 ||_WIN64
	/////////////////////////////////////////////////////////////
	// Windows Window Creation
	/////////////////////////////////////////////////////////////

	// Check for Window Style
	m_dwExStyle = WS_EX_OVERLAPPEDWINDOW;
	m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	h_Instance = GetModuleHandle(NULL);

	WindowRect.left = 0;
	WindowRect.right = Size.x;
	WindowRect.top = 0;
	WindowRect.bottom = Size.y;

	if (Style == WindowStyle::Fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = Size.x;
		dmScreenSettings.dmPelsHeight = Size.y;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// setting display mode failed, switch to windowed
			MessageBox(NULL, L"Fatal Error: Cannot open window in fullscreen mode !", NULL, MB_OK);
			Style = WindowStyle::Default;
		}
	}
	if (Style == WindowStyle::Fullscreen)
	{
		m_dwExStyle = WS_EX_APPWINDOW;                  // Window Extended Style
		m_dwStyle = WS_POPUP;                       // Windows Style
	}
	else
	{
		m_dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
		m_dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, m_dwStyle, FALSE, m_dwExStyle);

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
		Log.info("Registered WindowClass");
	}
	// Create h_Win
	h_Win = CreateWindowEx(
		m_dwExStyle,
		Appname, Title,
		m_dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT, CW_USEDEFAULT,
		Size.x, Size.y,
		NULL, NULL,
		h_Instance,
		NULL);
	if (h_Win == NULL)
		if (h3d::DebugMode)
			Log.info("Created Window");

	// create Context
	if (!GLContext.createContext(h_Win) && h3d::DebugMode)
		Log.error("Failed to create OpenGL context");

	// Update Window
	ShowWindow(h_Win, SW_SHOW);
	UpdateWindow(h_Win);
	SetFocus(h_Win);
	if (h3d::DebugMode)
		Log.info("Finished createing Window");
#endif	
}
/////////////////////////////////////////////////////////////////
//	Get-Methods
h3d::Vec2<unsigned int> h3d::Window::getSize()  { return Size;  }
wchar_t*				h3d::Window::getTitle() { return Title; }
h3d::WindowStyle		h3d::Window::getStyle() { return Style; }
MSG*                    h3d::Window::getMessage(){return &h_Msg;}
HWND*					h3d::Window::getHandle() {return &h_Win;}
bool					h3d::Window::isOpen() {  return opened; }
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
	return static_cast<bool>(SwapBuffers(GLContext.m_hdc));
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
	if (Style == WindowStyle::Fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);          // If So Switch Back To The Desktop
	}
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
	Size = size;
	this->resize();
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
	SendMessage(h_Win, WM_SIZE,0,(LPARAM)&Size);
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