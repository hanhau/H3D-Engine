#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
#include "Vector.hpp"
/////////////////////////////////////////////////////////////////
// Math Functions
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace Math {
		struct Triangle;
		struct Ray {
			h3d::Vec3<float> m_pos;
			h3d::Vec3<float> m_dir;
			bool H3D_API intersect(Triangle& tri);
		};
		struct Triangle{
			h3d::Vec3<float> m_pos[3];
		};
		bool H3D_API intersectRay(const Ray& ray,const Triangle& tri);
	}
}
/////////////////////////////////////////////////////////////////