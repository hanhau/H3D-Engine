#pragma once
#ifdef _WIN32 ||_WIN64

#include <Windows.h>
#include "OpenGLContext.hpp"
#include "Vector.hpp"

#include "externals.h"
#include STR(GLEW_INCLUDE/gl/wglew.h) 

LRESULT CALLBACK _H3D_WndProc(HWND, UINT, WPARAM, LPARAM);

namespace h3d {
	namespace WindowImpls {
		// Data for Winapi Window
		class Winapi {
		protected:
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
		public:
			// Functions
			virtual void setSize(h3d::Vec2<int> param);
			virtual void setTitle(std::string param);
			virtual void setFullscreen(bool param);
			virtual void setVSync(bool param);
		};
	}
}
#endif 