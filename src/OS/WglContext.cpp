#include "../../H3D/System/Config.hpp"
#include <memory>

#ifdef H3D_SYSTEM_WINDOWS
#include "../../H3D/OS/WglContext.hpp"
#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

#undef APIENTRY
#define APIENTRY _stdcall
void APIENTRY __opengl_callback_func(GLenum source, GLenum type,
	GLuint id, GLenum severity,
	GLsizei length, const GLchar* msg, const void* usr)
{
	h3d::Log::opengl("");

	switch (severity) {
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		h3d::Console::setTextCol(h3d::Console::Color::Green);
		break;
	case GL_DEBUG_SEVERITY_LOW:
		h3d::Console::setTextCol(h3d::Console::Color::Blue);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		h3d::Console::setTextCol(h3d::Console::Color::Yellow);
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		h3d::Console::setTextCol(h3d::Console::Color::Red);
		break;
	}
	std::cout << "[#] ";
	h3d::Console::setTextCol(h3d::Console::Color::White);

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		std::cout << "GL_DEBUG_SOURCE_API";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		std::cout << "GL_DEBUG_SOURCE_SHADER_COMPILER";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		std::cout << "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		std::cout << "GL_DEBUG_SOURCE_THIRD_PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		std::cout << "GL_DEBUG_SOURCE_APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		std::cout << "GL_DEBUG_SOURCE_OTHER";
		break;
	default: break;
	}

	std::cout << " ";

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "GL_DEBUG_TYPE_ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "GL_DEBUG_TYPE_PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "GL_TYPE_PORTABILITY";
		break;
	case GL_DEBUG_TYPE_MARKER:
		std::cout << "GL_DEBUG_TYPE_MARKER";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		std::cout << "GL_DEBUG_TYPE_PUSH_GROUP";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "GL_DEBUG_TYPE_OTHER";
		break;
	default: break;
	}

	std::string s = msg;
	std::cout << " " << s << "\n";
}

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
	pfd.cColorBits = 24;
	pfd.cDepthBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	const int nPixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (nPixelFormat == 0)
		return false;

	const BOOL bResult = SetPixelFormat(m_hdc, nPixelFormat, &pfd);
	if (!bResult)
		return false;

	HGLRC tempOGLContext = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, tempOGLContext);

	glewExperimental = GL_TRUE;
	const GLenum error = glewInit();
	if (error != GLEW_OK)
		return false;

	if (ptr->m_cs.is_debug_context) {
		h3d::Log::info("Creating Debug Context");
	}

	const int debug_attributes[9]{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 5,
		WGL_CONTEXT_DEBUG_BIT_ARB,
		WGL_CONTEXT_FLAGS_ARB,
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 1,
		0
	};

	const int attributes[] =
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