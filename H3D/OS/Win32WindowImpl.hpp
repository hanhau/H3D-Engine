#pragma once
#ifdef _WIN32 || _WIN64

#include "WindowImpl.hpp"
namespace h3d {
	class Event;
	namespace intern {
		class Win32WindowImpl : public WindowImpl
		{
		public:
			DWORD m_dwExStyle;
			DWORD m_dwStyle;

			wchar_t* Appname;
			bool m_isFullscreen;
			bool m_resizeAllowed;
			bool m_isOpen;

			LONG_PTR m_callback;

			RECT m_WindowRect;
			HINSTANCE m_Instance;
			HWND m_Win;
			MSG m_Msg;
			WNDCLASSEX m_WinClass;

			h3d::ContextSettings m_cs;

			void processEvents();

			// Win32 specific
			void processEvent(UINT msg, WPARAM wparam, LPARAM lparam);

			void setSize(h3d::Vec2<int> param);
			void resize();
			void setTitle(std::string param);
			void setFullscreen(bool param);
			void setVSync(bool param);
			void setActive(bool val);
			void swapBuffers();
			void allowResize(bool val);
			void showCursor(bool val);
			void close();
			bool pollEvent(h3d::Event &event);
			bool isOpen();

			bool create(h3d::Vec2<int>size, std::string title,
							   h3d::WindowStyle ws, h3d::ContextSettings cs);
		};
	}
}
#endif
