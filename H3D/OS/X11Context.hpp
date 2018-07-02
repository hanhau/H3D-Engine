#pragma once
#include "../../H3D/System/Config.hpp"
#ifdef H3D_SYSTEM_LINUX

#include "OpenGLContext.hpp"
namespace h3d {
	namespace intern {
		class X11Context : GLContext
		{
						
		public:
			bool create();
		};
	}
}
#endif