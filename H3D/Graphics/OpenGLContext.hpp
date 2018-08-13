#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif 

#include "../../H3D/System/Utilities.hpp"
#include "../../H3D/System/Config.hpp"
/////////////////////////////////////////////////////////////////
//	Contextsettings
/////////////////////////////////////////////////////////////////
namespace h3d {
	struct H3D_API ContextSettings
	{
		inline ContextSettings() noexcept :
			bits_framebuffer(24),
			bits_depthbuffer(8),
			count_auxbuffers(1),
			bits_stencilbuffer(1),
			is_debug_context(false)
		{}
		inline ContextSettings(unsigned char bits_fb,
							   unsigned char bits_db,
							   unsigned char bits_sb,
							   unsigned char c_aux,bool v=false) noexcept :
			bits_framebuffer(bits_fb),
			bits_depthbuffer(bits_db),
			bits_stencilbuffer(bits_sb),
			count_auxbuffers(c_aux),
			is_debug_context(v)
		{}

		unsigned char bits_framebuffer;
		unsigned char bits_depthbuffer;
		unsigned char bits_stencilbuffer;
		unsigned char count_auxbuffers;
		bool          is_debug_context;
	};
	class Window;
}
/////////////////////////////////////////////////////////////////
// OpenGLContext
/////////////////////////////////////////////////////////////////
#ifdef H3D_SYSTEM_WINDOWS
#define WGL_CONTEXT
#elif defined H3D_SYSTEM_LINUX
#define X11_CONTEXT
#endif
namespace h3d {
	class GLContext : Uncopyable{
	public:
		inline virtual ~GLContext() {};
	};
}
/////////////////////////////////////////////////////////////////