#pragma 
#ifdef _linux_
#include "Vector.hpp"
#include "Window.hpp"

namespace h3d {
	namespace intern {
		class X11WindowImpl {
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
		public:
			bool isOpen();
			bool create(h3d::Vec2<int>size, std::string title,
							   h3d::WindowStyle ws, h3d::ContextSettings cs);
		};
	}
}
#endif
