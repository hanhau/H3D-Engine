#include "../../H3D/System/Config.hpp"
#include <memory>

#ifdef H3D_SYSTEM_WINDOWS
#include "../../H3D/OS/WglContext.hpp"
#include <windows.h>

bool h3d::intern::WglContext::createContext(std::unique_ptr<h3d::intern::Win32WindowImpl>& ptr)
{	
	m_hdc = GetDC(ptr->m_Win); //Get device context

	// set Pixelformatdescriptor
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL |
				  PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (nPixelFormat == 0)
		return false;

	BOOL bResult = SetPixelFormat(m_hdc, nPixelFormat, &pfd);
	if (!bResult)
		return false;

	HGLRC tempOGLContext = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, tempOGLContext);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
		return false;

	int * debug_attributes;

	if (ptr->m_cs.is_debug_context) {
		h3d::Log::info("Creating Debug Context");
		debug_attributes = new int[8]();
		int vals[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 5,
			WGL_CONTEXT_DEBUG_BIT_ARB,
			WGL_CONTEXT_FLAGS_ARB,
			WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 1,
			0
		};
		for (int i = 0; i < 9; i++)
			debug_attributes[i] = vals[i];
	}

	int attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 5,
		WGL_CONTEXT_FLAGS_ARB, 
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") != 0)
	{
		if (ptr->m_cs.is_debug_context)
			m_hrc = wglCreateContextAttribsARB(m_hdc, NULL, 
							                   debug_attributes);
		else 
			m_hrc = wglCreateContextAttribsARB(m_hdc, NULL, 
				                               attributes);
		
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempOGLContext);
		wglMakeCurrent(m_hdc, m_hrc);
	}
	else {
		m_hrc = tempOGLContext;
		wglMakeCurrent(GetDC(ptr->m_Win),tempOGLContext);
	}

	int glVersion[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

    if (glVersion[0] == -1 || glVersion[1] == -1) {
        h3d::Log::error("Unable to create OpenGL Context with following settings:\n"
                        "cs.bits_framebuffer = %d\n"
                        "cs.bits_depthbuffer = %d\n"
                        "cs.bits_stencilbuffer = %d\n"
                        "cs.count_auxbuffers = %d\n"
                        "cs.is_debug_context = %b",
                        ptr->m_cs.bits_framebuffer,
                        ptr->m_cs.bits_depthbuffer,
                        ptr->m_cs.bits_stencilbuffer,
                        ptr->m_cs.count_auxbuffers,
                        ptr->m_cs.is_debug_context);
    }

	h3d::Log::info("Created Context with OpenGL Ver %d.%d", 
				   glVersion[0], glVersion[1]);

	if (ptr->m_cs.is_debug_context) {
		glEnable(GL_DEBUG_CALLBACK_FUNCTION);
		glDebugMessageCallback(&__opengl_callback_func, 0);
		glEnable(GL_DEBUG_CALLBACK_FUNCTION);
	}

	ShowWindow(ptr->m_Win, SW_SHOW);
	UpdateWindow(ptr->m_Win);
	SetFocus(ptr->m_Win);

	return true;
}
#endif