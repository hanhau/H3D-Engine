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
	class Mesh;
	namespace Math {
		struct Triangle;
		struct Ray {
			h3d::Vec3<float> m_pos;
			h3d::Vec3<float> m_target;
			bool H3D_API intersect(Triangle& tri);
		};
		struct Triangle{
			h3d::Vec3<float> m_pos[3];
		};
		bool H3D_API intersectRay(const Ray& ray,const Triangle& tri,h3d::Vec3<float> &res_point);
		bool H3D_API intersectRay(const Ray& ray, h3d::Mesh& const mesh, h3d::Vec3<float> &res_point);
	}
}
/////////////////////////////////////////////////////////////////