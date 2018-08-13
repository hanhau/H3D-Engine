#pragma once

#include "../System/Config.hpp"
#ifdef H3D_SYSTEM_WINDOWS

#include "../../H3D/System/WindowImpl.hpp"
#include <Windows.h>

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

			void setSize(h3d::Vec2<int> param) override;
			void resize() override;
			void setTitle(std::string param) override;
			void setFullscreen(bool param) override;
			void setVSync(bool param) override;
			void setActive(bool val) override;
			void swapBuffers() override;
			void allowResize(bool val) override;
			void showCursor(bool val) override;
			void close() override;
			bool pollEvent(h3d::Event &event);
			bool isOpen() override;

			bool create(h3d::Vec2<int>size, std::string title,
							   h3d::WindowStyle ws, h3d::ContextSettings cs) override;
		};
	}
}
#endif
