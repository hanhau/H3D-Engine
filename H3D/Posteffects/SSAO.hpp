#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
// SSAO Post Effect
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace Posteffects {
		// Contains variables for SSAO
		struct SSAO_ControlValues
		{
			float ssao_level         = 0;
			float object_level       = 0;
			float ssao_radius        = 0;
			bool  weight_by_angle    = 0;
			unsigned int point_count = 0;
			bool  randomize_points   = 0;

			inline SSAO_ControlValues() :
				ssao_level(),
				object_level(),
				ssao_radius(),
				weight_by_angle(),
				point_count(),
				randomize_points()
			{}
		};

		void H3D_API applySSAO(GLuint framebuffer,
							   SSAO_ControlValues &&vals);
	}
}
/////////////////////////////////////////////////////////////////