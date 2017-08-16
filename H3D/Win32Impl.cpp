/////////////////////////////////////////////////////////////////
#ifdef _WIN32 || _WIN64

#define pimpl m_pimpl.get()
#include "Window.hpp"

// PIMPL CLASS
class h3d::Window::WindowImpl {
public:
	GLContextWinapi m_glcontext;

	DWORD m_dwExStyle;
	DWORD m_dwStyle;

	wchar_t* Appname;

	RECT m_WindowRect;
	HINSTANCE m_Instance;
	HWND m_Win;
	MSG m_Msg;
	WNDCLASSEX m_WinClass;

	void processEvent(UINT msg, WPARAM wparam,
		LPARAM lparam);

	// Functions
	virtual void setSize(h3d::Vec2<int> param);
	virtual void resize();
	virtual void setTitle(std::string param);
	virtual void setFullscreen(bool param);
	virtual void setVSync(bool param);
};
/////////////////////////////////////////////////////////////////
// System specific setup function
/////////////////////////////////////////////////////////////////
void h3d::Window::setupWin(h3d::Vec2<int>size,
						   std::string title,
						   h3d::WindowStyle ws,
						   h3d::ContextSettings cs)
{
	// Parameter sets
	m_Size				= size;
	m_Title				= title;
	m_WindowStyle		= ws;
	m_ContextSettings	= cs;
	pimpl->Appname = (wchar_t*)m_Title.c_str();

	// Window Style Setup
	pimpl->m_dwExStyle = WS_EX_OVERLAPPEDWINDOW;
	pimpl->m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	pimpl->m_Instance = GetModuleHandle(NULL);
	
	pimpl->m_WindowRect.left   = 0;
	pimpl->m_WindowRect.right  = m_Size.x;
	pimpl->m_WindowRect.top    = 0;
	pimpl->m_WindowRect.bottom = m_Size.y;

	if (m_WindowStyle == WindowStyle::Fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize		  = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = m_Size.x;
		dmScreenSettings.dmPelsHeight = m_Size.y;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields     = DM_BITSPERPEL | 
										DM_PELSWIDTH  | 
										DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) 
				!= DISP_CHANGE_SUCCESSFUL)
		{
			// setting display mode failed, switch to windowed
			wchar_t* str = L"Fatal Error: Cannot open window "
							"in fullscreen mode !";
			MessageBox(NULL, str, NULL, MB_OK);
			m_WindowStyle = WindowStyle::Default;
		}
	}

	if (m_WindowStyle == WindowStyle::Fullscreen){
		pimpl->m_dwExStyle = WS_EX_APPWINDOW;
		pimpl->m_dwStyle = WS_POPUP;
	}
	else{
		pimpl->m_dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		pimpl->m_dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&pimpl->m_WindowRect, 
						pimpl->m_dwStyle, FALSE, 
						pimpl->m_dwExStyle);

	// Register Window Class
	pimpl->m_WinClass				= { 0 };
	pimpl->m_WinClass.cbSize		= sizeof(WNDCLASSEX);
	pimpl->m_WinClass.style			= CS_OWNDC;
	pimpl->m_WinClass.lpfnWndProc	= _H3D_WndProc;
	pimpl->m_WinClass.cbClsExtra	= 0;
	pimpl->m_WinClass.cbWndExtra	= 0;
	pimpl->m_WinClass.hInstance		= pimpl->m_Instance;
	pimpl->m_WinClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	pimpl->m_WinClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	pimpl->m_WinClass.hbrBackground	= NULL;
	pimpl->m_WinClass.lpszMenuName	= NULL;
	pimpl->m_WinClass.lpszClassName	= pimpl->Appname;
	pimpl->m_WinClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&pimpl->m_WinClass))
	{
		MessageBoxA(NULL, "Couldn´t register Window!", "FATAL ERROR",
			MB_ICONEXCLAMATION | MB_OK);
		this->~Window();
	}
	else if (h3d::DebugMode)
		Log.info("Registered Winapi Window class");
	
	// Set Window Content
	pimpl->m_Win = CreateWindowEx(pimpl->m_dwExStyle,
								  pimpl->Appname, (LPCWSTR)m_Title.c_str(),
								  pimpl->m_dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
								  CW_USEDEFAULT, CW_USEDEFAULT,
								  m_Size.x, m_Size.y,
								  NULL, NULL,
								  pimpl->m_Instance,this);
	if (pimpl->m_Win == NULL) {
		Log.error("Unable to CreateWindowEx(..)");
		this->~Window();
	}
	if (h3d::DebugMode)
		Log.info("Created Window Handle");

	// Create OpenGL Context
	if (!pimpl->m_glcontext.createContext(pimpl->m_Win,cs))
		Log.error("Unable to create Context in Window");
	
	// Make ready for use
	ShowWindow(pimpl->m_Win, SW_SHOW);
	UpdateWindow(pimpl->m_Win);
	SetFocus(pimpl->m_Win);
	if (h3d::DebugMode)
		Log.info("Finished creating Window");
}
/////////////////////////////////////////////////////////////////
// PIMPL function definitions
/////////////////////////////////////////////////////////////////
void h3d::Window::WindowImpl::processEvent(UINT msg, WPARAM wparam,
											LPARAM lparam)
{
	if (!m_Win)
		return;

	switch (msg)
	{
	case WM_DESTROY:

		break;
	}
}
/////////////////////////////////////////////////////////////////
void h3d::Window::WindowImpl::setSize(h3d::Vec2<int> param) {
	SetWindowPos(m_Win,HWND_TOP,0,0,
				 param.x,param.y,SWP_NOMOVE);
}
void h3d::Window::WindowImpl::setTitle(std::string param) {
	SetWindowText(m_Win,(WCHAR*)param.c_str());
}
void h3d::Window::WindowImpl::setFullscreen(bool param) {

}
void h3d::Window::WindowImpl::setVSync(bool param) {
	wglSwapIntervalEXT(param ? true : false);
}
/////////////////////////////////////////////////////////////////
// Win32 Window Callback func
LRESULT CALLBACK _H3D_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_CREATE) {
		LONG_PTR win = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(
			lparam)->lpCreateParams;

		SetWindowLongPtr(hwnd, GWLP_USERDATA, win);
	}

	h3d::Window* window = hwnd ? reinterpret_cast<h3d::Window*>(
		GetWindowLongPtr(hwnd, GWLP_USERDATA)) : NULL;

	if (window)
	{
		std::cout << "VALID YESS" << std::endl;
	}

	switch (msg)
	{
		// Resize Event
	case WM_SIZE:
	{
		// break if winapi message
		if (lparam == 0 || wparam == 0) break;

		h3d::Vec2<int> *newsize = new h3d::Vec2<int>();
		newsize = (h3d::Vec2<int>*)lparam;

		SetWindowPos(hwnd, 0, 1, 1, newsize->x, newsize->y, SWP_NOMOVE);
	}
	break;
	// Input Handling
	case WM_INPUT:
		if (h3d::InputManager.isInputActive(DEVICE_TYPE_KEYBOARD)) {
			h3d::InputManager.updateKeyboard();
		}
		if (h3d::InputManager.isInputActive(DEVICE_TYPE_MOUSE)) {
			h3d::InputManager.updateMouse();
		}
		if (h3d::InputManager.isInputActive(DEVICE_TYPE_JOYSTICK)) {
			h3d::InputManager.updateJoystick();
		}
		break;
	case WM_PAINT:
		break;
	case WM_CLOSE:
		break;
		// Default Window Procedure
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}
#endif