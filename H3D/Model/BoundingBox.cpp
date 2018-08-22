#include "../../H3D/Model/BoundingBox.hpp"
#include "../../H3D/Math/Vector.hpp"
#include <GL/glew.h>
#include <array>
#include <unordered_map>
/////////////////////////////////////////////////////////////////
// Bounding Box Implementation
/////////////////////////////////////////////////////////////////
h3d::BoundingBox::BoundingBox() {}
h3d::BoundingBox::BoundingBox(float xstart, float xend,
	float ystart, float yend,
	float zstart, float zend) :
	x_start(xstart), x_end(xend),
	y_start(ystart), y_end(yend),
	z_start(zstart), z_end(zend)
{
	this->create();
}
h3d::BoundingBox::~BoundingBox() {
	
}

void h3d::BoundingBox::create() {
	std::array<h3d::Vec3<float>, 8> m_edges = {
		h3d::Vec3<float>(x_start,y_start,z_start),
		h3d::Vec3<float>(x_start,y_start,z_end),
		h3d::Vec3<float>(x_end,y_start,z_end),
		h3d::Vec3<float>(x_end,y_start,z_start),
		h3d::Vec3<float>(x_start,y_end,z_start),
		h3d::Vec3<float>(x_start,y_end,z_end),
		h3d::Vec3<float>(x_end,y_end,z_end),
		h3d::Vec3<float>(x_end,y_end,z_start)
	};
}
bool h3d::BoundingBox::intersect(const h3d::Math::Ray& ray)
{
	

	return false;
}
/////////////////////////////////////////////////////////////////
struct h3d::BoundingBox::impl {
	size_t m_ID;
	static size_t m_count;
	static size_t m_currentID;
	static std::unordered_map<size_t,impl&> m_map;

	impl() : m_ID(m_currentID) {
		m_currentID++;
		m_map.emplace(m_ID, this);
	}
	~impl() {
		m_map.erase(m_ID);
	}
};
size_t h3d::BoundingBox::impl::m_count = 0;
size_t h3d::BoundingBox::impl::m_currentID = 1;
/////////////////////////////////////////////////////////////////