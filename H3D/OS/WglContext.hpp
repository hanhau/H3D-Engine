#pragma once
#include "../../H3D/System/Config.hpp"
#ifdef H3D_SYSTEM_WINDOWS

#include "../../H3D/Graphics/OpenGLContext.hpp"
#include "../../H3D/OS/Win32WindowImpl.hpp"
namespace h3d {
	namespace intern {
		class WglContext : GLContext
		{
		friend h3d::Window;
			HGLRC	m_hrc;	//OpenGL Context
			HDC		m_hdc;	//Win32 Device Context
			HWND	m_hwnd;	//Win32 Window identifier
		public:
			bool createContext(std::unique_ptr<h3d::intern::Win32WindowImpl>& ptr);
		};
	}
}
#endif
