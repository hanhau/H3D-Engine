#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif 

#include "WindowImpl.hpp"
#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
#include STR(GLEW_INCLUDE/gl/wglew.h)
/////////////////////////////////////////////////////////////////
//	Contextsettings
/////////////////////////////////////////////////////////////////
namespace h3d {
	struct H3D_API ContextSettings
	{
		inline ContextSettings() {}
		inline ContextSettings(unsigned char bits_fb,
							   unsigned char bits_db,
							   unsigned char bits_sb,
							   unsigned char c_aux) :
			bits_framebuffer(bits_fb),
			bits_depthbuffer(bits_db),
			bits_stencilbuffer(bits_sb),
			count_auxbuffers(c_aux) 
		{}

		unsigned char bits_framebuffer;
		unsigned char bits_depthbuffer;
		unsigned char bits_stencilbuffer;
		unsigned char count_auxbuffers;
	};
}
/////////////////////////////////////////////////////////////////
// OpenGLContext
/////////////////////////////////////////////////////////////////
#include <any>
namespace h3d {
	class GLContext : Uncopyable{
	public:
		inline virtual ~GLContext() {};
		virtual bool createContext(std::any windowimpl);
	};
}
/////////////////////////////////////////////////////////////////