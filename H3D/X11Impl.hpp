#pragma once
#ifdef __linux__

// UNIX specific
#include <gl\glx.h>
#include <X11.h>

namespace h3d {
	namespace WindowImpls {
		// Data for UNIX
		class UNIX {
		protected:
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
		};
	}
}

#endif
