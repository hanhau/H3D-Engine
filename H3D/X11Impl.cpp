#ifdef __linux__
#include "Window.hpp"

void h3d::Window::setupWin(h3d::Vec2<int>size,
						   std::string title,
						   h3d::WindowStyle ws,
						   h3d::ContextSettings cs)
{
	m_Size = size;
	m_Title = title;
	m_WindowStyle = ws;
	m_ContextSettings = cs;

	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		if (h3d::DebugMode)
			Log.error("Failed to connect to X Server!");
		return false;
	}

	root = DefaultRootWindow(dpy);

	vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		if (h3d::DebugMode)
			Log.error("Xlib: Not correct visual found");
		return false;
	}

	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(dpy, root, 0, 0,
		Size.x, Size.y
		0,
		vi->depth, InputOutput,
		vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(dpy, win);
	XStoreName(dpy, win, m_Title.c_str());

	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

	glEnable(GL_DEPTH_TEST);
}

#endif 
