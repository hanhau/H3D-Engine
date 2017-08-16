#ifdef __linux__

#define pimpl m_pimpl.get()
#include "Window.hpp"
#include <gl\glx.h>
#include <X11.h>

class h3d::Window::WindowImpl {
public:
	Display				 *dpy;
	Window				 root;
	GLint				 *att;
	XVisualInfo			 *vi;
	Colormap			 cmap;
	XSetWindowAttributes swa;
	::Window			 win;
	GLXContext			 glc;
	XWindowAttributes    gwa;
	XEvent				 xev;

	// Functions
	virtual void setSize(h3d::Vec2<int> param);
	virtual void resize();
	virtual void setTitle(std::string param);
	virtual void setFullscreen(bool param);
	virtual void setVSync(bool param);
};

void h3d::Window::setupWin(h3d::Vec2<int>size,
						   std::string title,
						   h3d::WindowStyle ws,
						   h3d::ContextSettings cs)
{
	m_Size = size;
	m_Title = title;
	m_WindowStyle = ws;
	m_ContextSettings = cs;

	pimpl->dpy = XOpenDisplay(NULL);
	if (pimpl->dpy == NULL) {
		if (h3d::DebugMode)
			Log.error("Failed to connect to X Server!");
		return false;
	}

	pimpl->root = DefaultRootWindow(dpy);

	pimpl->vi = glXChooseVisual(pimpl->dpy, 0, 
								pimpl->att);
	if (pimpl->vi == NULL) {
		if (h3d::DebugMode)
			Log.error("Xlib: Not correct visual found");
		return false;
	}

	pimpl->cmap = XCreateColormap(pimpl->dpy, 
								  pimpl->root, 
								  pimpl->vi->visual, 
								  AllocNone);
	pimpl->swa.colormap = cmap;
	pimpl->swa.event_mask = ExposureMask | KeyPressMask;

	pimpl->win = XCreateWindow(dpy, root, 0, 0,
		Size.x, Size.y
		0,
		vi->depth, InputOutput,
		vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(pimpl->dpy, pimpl->win);
	XStoreName(pimpl->dpy, pimpl->win, m_Title.c_str());

	pimpl->glc = glXCreateContext(pimpl->dpy, pimpl->vi, 
								  NULL, GL_TRUE);
	glXMakeCurrent(pimpl->dpy, pimpl->win, pimpl->glc);

	glEnable(GL_DEPTH_TEST);
}
/////////////////////////////////////////////////////////////////
// Virtual Functions
/////////////////////////////////////////////////////////////////
void h3d::Window::WindowImpl::setSize(h3d::Vec2<int> param) {
	
}
void h3d::Window::WindowImpl::resize() {

}
void h3d::Window::WindowImpl::setTitle(std::string param) {
	XChangeWindowAttributes();
}
void h3d::Window::WindowImpl::setFullscreen(bool param) {

}
void h3d::Window::WindowImpl::setVSync(bool param) {

}
/////////////////////////////////////////////////////////////////
#endif 
