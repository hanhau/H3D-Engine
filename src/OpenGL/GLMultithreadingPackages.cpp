#include "../../H3D/OpenGL/GLMultithreadingPackages.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of packages
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace GL {
		namespace Packages {
			// glEnable() / glDisable()
			void gl_ENABLE_DISABLE::execute(const gl_ENABLE_DISABLE* __restrict pParams)
			{

			}
			// glClearColor()
			void gl_CLEAR_COLOR::execute(const gl_CLEAR_COLOR* __restrict pParams)
			{
				glClearColor(
					pParams->red, pParams->green,
					pParams->blue, pParams->alpha
				);
			}
		}
	}
}
/////////////////////////////////////////////////////////////////