#pragma once
#include "Mesh.hpp"
#include "../Math/Math.hpp"
#include "../dep_lib_fwd.h"
/////////////////////////////////////////////////////////////////
// Bounding Box
/////////////////////////////////////////////////////////////////
namespace h3d {
	class BoundingBox {
		float x_start;
		float x_end;
		float y_start;
		float y_end;
		float z_start;
		float z_end;

		h3d::Mesh m_mesh;
		h3d::Vec3<float> m_lastIntersectPoint;

		struct impl;
		static std::unique_ptr<impl> m_impl;
	public:
		H3D_API BoundingBox();
		H3D_API BoundingBox(float xstart, float xend,
			float ystart, float yend,
			float zstart, float zend);
		H3D_API ~BoundingBox();

		void H3D_API render();

		void H3D_API setValues(float x_s,float x_e,
							   float y_s,float y_e,
							   float z_s,float z_e);

		void H3D_API create();
		bool H3D_API intersect(const h3d::Math::Ray& ray);
	};
}