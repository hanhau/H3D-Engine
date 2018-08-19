#include "../../H3D/Math/Math.hpp"
#include "../../H3D/Model/3DModel.hpp"

constexpr float _smallnum = 0.00000001f;

bool h3d::Math::intersectRay(const Ray& ray, const Triangle& tri, 
							 h3d::Vec3<float> &res_point)
{
	res_point = h3d::Vec3<float>(0, 0, 0);
	const h3d::Vec3<float> u = h3d::distance(tri.m_pos[0], tri.m_pos[1]);
	const h3d::Vec3<float> v = h3d::distance(tri.m_pos[0], tri.m_pos[2]);
	const h3d::Vec3<float> n = u.cross(v);
	if (n == 0) return false;

	const h3d::Vec3<float> dir = ray.m_target - ray.m_pos;
	const h3d::Vec3<float> w0 = ray.m_pos - tri.m_pos[0];
	const float a = -dot(n,w0);
	const float b = dot(n,dir);
	if (fabs(b) < _smallnum) {
		if (a == 0.0f) return true;
		else return false;
	}

	const float r = a / b;
	if (r < 0.0f)
		return false;

	res_point = ray.m_pos + dir * r;

	const h3d::Vec3<float> w = res_point - tri.m_pos[0];

	const float vv = v.dot(v);
	const float uv = u.dot(v);
	const float wv = w.dot(v);
	const float wu = w.dot(u);
	const float uu = u.dot(u);
	const float D = (uv*uv) - (uu*vv);

	const float s = (uv*wv) - (vv*wu) / D;
	if (s < 0.0f || s > 1.0f)
		return false;
	const float t = (uv*wu) - (uu*wv) / D;
	if (t < 0.0f || (s + t) > 1.0f) 
		return false;
	
	return true;
}

bool h3d::Math::intersectRay(const Ray& ray, h3d::Mesh& const mesh,
							 h3d::Vec3<float> &res_point)
{
	const size_t indicesCount = mesh.getIndices().size();
	const size_t tri_num = indicesCount/3;
	std::vector<h3d::Math::Triangle> tris;
	tris.resize(tri_num);
	return false;
}