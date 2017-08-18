#pragma once
#include "OpenGLContext.hpp"
#include "WindowImpl.hpp"

namespace h3d {
	namespace intern {
		class WglContext : GLContext
		{
			HGLRC	m_hrc;	//OpenGL Context
			HDC		m_hdc;	//Win32 Device Context
			HWND	m_hwnd;	//Win32 Window identifier
		public:
			bool createContext(std::any windowimpl);
		};
	}
}
