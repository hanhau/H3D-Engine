#pragma once

#include "../../H3D/externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
// Packages to send off in h3d::GL::packet_stream
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace GL {
		// Base class for all packages
		struct base;
		typedef void (PFN_EXECUTE)(const base* __restrict pParams);
		struct base {
			PFN_EXECUTE pfnExecute;
		};

		namespace Packages {
			// glEnable() / glDisable()
			struct gl_ENABLE_DISABLE : public base
			{
				GLenum cap;
				GLboolean value;
				static void execute(const gl_ENABLE_DISABLE* __restrict pParams);
			};
			// glClearColor()
			struct gl_CLEAR_COLOR : public base
			{
				GLfloat red, green, blue, alpha;
				static void execute(const gl_CLEAR_COLOR* __restrict pParams);
			};
			// glClear()
			struct gl_CLEAR : public base
			{
				GLbitfield mask;
				static void execute(const gl_CLEAR* __restrict pParams);
			};
			union ALL_PACKAGES
			{
			public:
				PFN_EXECUTE execute;
			private:
				base	m_Base;
				gl_CLEAR_COLOR m_glClearColor;
				gl_CLEAR	   m_glClear;
			};
		}
	}
}
