/////////////////////////////////////////////////////////////////
#ifdef _WIN32 || _WIN64

#define pimpl m_pimpl.get() 
#include "Window.hpp"
#include "Win32WindowImpl.hpp"

LRESULT CALLBACK _H3D_WndProc(HWND, UINT, WPARAM, LPARAM);

/////////////////////////////////////////////////////////////////
// System specific setup function
/////////////////////////////////////////////////////////////////
void h3d::intern::Win32WindowImpl::create(h3d::Vec2<int>size,
										  std::string title,
										  h3d::WindowStyle ws,
										  h3d::ContextSettings cs)
{
	// Parameter sets
	m_Size				= size;
	m_Title				= title;
	Appname = (wchar_t*)m_Title.c_str();

	// Window Style Setup
	m_dwExStyle = WS_EX_OVERLAPPEDWINDOW;
	m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	m_Instance = GetModuleHandle(NULL);
	
	m_WindowRect.left   = 0;
	m_WindowRect.right  = m_Size.x;
	m_WindowRect.top    = 0;
	m_WindowRect.bottom = m_Size.y;

	if (ws == WindowStyle::Fullscreen)
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
		}
	}

	if (ws == WindowStyle::Fullscreen){
		m_dwExStyle = WS_EX_APPWINDOW;
		m_dwStyle = WS_POPUP;
	}
	else{
		m_dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		m_dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&m_WindowRect, m_dwStyle, FALSE, m_dwExStyle);

	// Register Window Class
	m_WinClass				= { 0 };
	m_WinClass.cbSize		= sizeof(WNDCLASSEX);
	m_WinClass.style		= CS_OWNDC;
	m_WinClass.lpfnWndProc	= _H3D_WndProc;
	m_WinClass.cbClsExtra	= 0;
	m_WinClass.cbWndExtra	= 0;
	m_WinClass.hInstance	= m_Instance;
	m_WinClass.hIcon		= LoadIcon(NULL, IDI_APPLICATION);
	m_WinClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	m_WinClass.hbrBackground= NULL;
	m_WinClass.lpszMenuName	= NULL;
	m_WinClass.lpszClassName= Appname;
	>m_WinClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&m_WinClass))
	{
		MessageBoxA(NULL, "Couldn´t register Window!", "FATAL ERROR",
			MB_ICONEXCLAMATION | MB_OK);
	}
	else if (h3d::DebugMode)
		Log.info("Registered Winapi Window class");
	
	// Set Window Content
	m_Win =  CreateWindowEx(m_dwExStyle,
							Appname, (LPCWSTR)m_Title.c_str(),
							m_dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
							CW_USEDEFAULT, CW_USEDEFAULT,
							m_Size.x, m_Size.y,
							NULL, NULL,
							m_Instance,this);
	if (m_Win == NULL) {
		Log.error("Unable to CreateWindowEx(..)");
	}
	if (h3d::DebugMode)
		Log.info("Created Window Handle");
	
	// Make ready for use
	ShowWindow(m_Win, SW_SHOW);
	UpdateWindow(m_Win);
	SetFocus(m_Win);
	if (h3d::DebugMode)
		Log.info("Finished creating Window");
}
/////////////////////////////////////////////////////////////////
// System specific OpenGL Functions
void h3d::intern::Win32WindowImpl::swapBuffers(){

}
void h3d::intern::Win32WindowImpl::setActive(bool val){

}
void h3d::intern::Win32WindowImpl::setVSync(bool val){
	
}
// Settings
void h3d::intern::Win32WindowImpl::setSize(h3d::Vec2<int>size) {

}
void h3d::intern::Win32WindowImpl::setTitle(std::string title) {

}
void h3d::intern::Win32WindowImpl::setFullscreen(bool val) {
	m_isFullscreen = val;
}
// Utils
void h3d::intern::Win32WindowImpl::resize()	{
	SendMessage(m_Win, WM_SIZE, 0, 0);
}
void h3d::intern::Win32WindowImpl::allowResize(bool val) {
	m_resizeAllowed = val;
}
void h3d::intern::Win32WindowImpl::showCursor(bool val) {
	ShowCursor((BOOL)val);
}
void h3d::intern::Win32WindowImpl::close() {
	if (m_isFullscreen)
		ChangeDisplaySettings(NULL, 0);

	ShowCursor(TRUE);
	setActive(true);
	wglDeleteContext(wglGetCurrentContext());
	PostQuitMessage(0);
	UnregisterClass(Appname, m_Instance);
}
/////////////////////////////////////////////////////////////////
// Poll Events
bool h3d::Window::pollEvent(h3d::Event &event) {
	return true;
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