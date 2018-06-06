/////////////////////////////////////////////////////////////////
#ifdef _WIN32 || _WIN64

#include "Window.hpp"
#include "Win32WindowImpl.hpp"
#include <wingdi.h>
#include <memory>
#include <string>

LRESULT CALLBACK _H3D_WndProc(HWND, UINT, WPARAM, LPARAM);

/////////////////////////////////////////////////////////////////
// System specific setup function
/////////////////////////////////////////////////////////////////
bool h3d::intern::Win32WindowImpl::create(h3d::Vec2<int>       size,
										  std::string          title,
										  h3d::WindowStyle     ws,
										  h3d::ContextSettings cs)
{
	// Parameter sets
	m_Size				= size;
	m_Title				= title;
	Appname = (wchar_t*)m_Title.c_str();
	m_cs = cs;

	m_isOpen = true;

	m_callback = SetWindowLongPtrW(m_Win, GWLP_WNDPROC, 
		reinterpret_cast<LONG_PTR>(&_H3D_WndProc));

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
			return false;
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
	m_WinClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&m_WinClass))
	{
		MessageBoxA(NULL, "Couldn´t register Window!", "FATAL ERROR",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	else if (h3d::DebugMode)
		h3d::Log::info("Registered Winapi Window class");
	
	// Set Window Content
	std::wstring _windowtitle;
	_windowtitle.assign(title.begin(), title.end());

	m_Win =  CreateWindowEx(m_dwExStyle,
							Appname, 
							_windowtitle.c_str(),
							m_dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
							CW_USEDEFAULT, CW_USEDEFAULT,
							m_Size.x, m_Size.y,
							NULL, NULL,
							m_Instance,
							this);
	if (m_Win == NULL) {
		h3d::Log::error("Unable to CreateWindowEx(..)");
		return false;
	}
	if (h3d::DebugMode)
		h3d::Log::info("Created Window Handle");
	

	// Make ready for use
	ShowWindow(m_Win, SW_SHOW);
	UpdateWindow(m_Win);
	if (h3d::DebugMode)
		h3d::Log::info("Finished creating Window");

	return true;
}
/////////////////////////////////////////////////////////////////
// System specific OpenGL Functions
void h3d::intern::Win32WindowImpl::swapBuffers(){
	::SwapBuffers(GetDC(m_Win));
}
void h3d::intern::Win32WindowImpl::setActive(bool val){

}
void h3d::intern::Win32WindowImpl::setVSync(bool val){
	if (1) {
		wglSwapIntervalEXT((val) ? 1 : 0);
	}
	else
		h3d::Log::error("VSync cant be toggled %d", val);
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
	m_isOpen = false;
}
bool h3d::intern::Win32WindowImpl::isOpen() {
	return m_isOpen;
}
/////////////////////////////////////////////////////////////////
// Message processing functions
void h3d::intern::Win32WindowImpl::processEvents() {
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

        if (msg.message == WM_TIMER) 
            break;

		//! translate and dispatch message to Windows
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
void h3d::intern::Win32WindowImpl::processEvent(UINT msg, 
												WPARAM wparam, 
											    LPARAM lparam) {
	if (m_Win == nullptr)
		return;

	switch (msg)
	{
    case WM_TIMER:

        break;
	case WM_CHAR:
		{
		h3d::Log::info("WM_CHAR");
		}
		break;
	case WM_SETFOCUS:
		{
			h3d::Event e;
			e.type = h3d::EventType::GainedFocus;
			pushEvent(e);
		}
		break;
	case WM_KILLFOCUS:
		{
			h3d::Event e;
			e.type = h3d::EventType::LostFocus;
			pushEvent(e);
		}
		break;
		// Resize Event
	case WM_SIZE:
	{
		// break if winapi message
		if (lparam == 0 || wparam == 0) break;

		h3d::Event e;
		e.type = h3d::EventType::Resized;
		pushEvent(e);
	}
	break;
	// Input Handling
	case WM_INPUT:
		h3d::Log::info("WM_INPUT");

		h3d::Event e;
		e.type = h3d::EventType::Input;
		pushEvent(e);

		/*if (h3d::InputManager::isInputActive(DEVICE_TYPE_KEYBOARD)) {
			h3d::InputManager::updateKeyboard();
		}
		if (h3d::InputManager::isInputActive(DEVICE_TYPE_MOUSE)) {
			h3d::InputManager::updateMouse();
		}
		if (h3d::InputManager::isInputActive(DEVICE_TYPE_JOYSTICK)) {
			h3d::InputManager::updateJoystick();
		}*/
		break;
	case WM_CLOSE:
		{
		h3d::Event e;
		e.type = h3d::EventType::Closed;
		pushEvent(e);
		}
		break;
		// Default Window Procedure
	default:
		break;
	}
	return;
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

	h3d::intern::Win32WindowImpl *window = 
		hwnd ? reinterpret_cast<h3d::intern::Win32WindowImpl*>(
				GetWindowLongPtr(hwnd, GWLP_USERDATA)
		) : nullptr;

	if (window != nullptr) {
		window->processEvent(msg, wparam, lparam);
		
		if(window->m_callback)
			return CallWindowProcW(reinterpret_cast<WNDPROC>(window->m_callback),
								   hwnd, msg, wparam, lparam);
	}

	if (msg == WM_CLOSE)
		return 0;

	if ((msg == WM_SYSCOMMAND) && (wparam == SC_KEYMENU))
		return 0;

	return DefWindowProc(hwnd, msg, wparam, lparam);
}
#endif