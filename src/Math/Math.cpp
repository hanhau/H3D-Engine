#include "../../H3D/Math/Math.hpp"

bool h3d::Math::intersectRay(const Ray& ray, const Triangle& tri)
{
	h3d::Vec3<float> u = h3d::distance(tri.m_pos[0], tri.m_pos[1]);
	h3d::Vec3<float> v = h3d::distance(tri.m_pos[0], tri.m_pos[2]);
	h3d::Vec3<float> w = ray.m_dir - tri.m_pos[0];

	const float vv = v.cross(v);
	const float uv = u.cross(v);
	const float wv = w.cross(v);
	const float wu = w.cross(u);
	const float uu = u.cross(u);
	const float D = (uv*uv) - (uu*vv);

	const float s = (uv*wv) - (vv*wu) / D;
	const float t = (uv*wu) - (uu*wv) / D;

	if (t < 0.0f || (s + t) > 1.0f) return false;
	else return true;
}