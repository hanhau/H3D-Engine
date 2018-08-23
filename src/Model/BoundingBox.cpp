#include "../../H3D/Model/BoundingBox.hpp"
#include "../../H3D/Math/Vector.hpp"
#include <GL/glew.h>
#include <array>
#include <unordered_map>

const size_t _saveLocalXTimesBeforeUpload = 12;
/////////////////////////////////////////////////////////////////
// Bounding Box Implementation
/////////////////////////////////////////////////////////////////
h3d::BoundingBox::BoundingBox() :
	x_start(0.0f), x_end(0.0f),
	y_start(0.0f), y_end(0.0f),
	z_start(0.0f), z_end(0.0f) {}
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

void h3d::BoundingBox::setValues(float x_s, float x_e,
								 float y_s, float y_e,
								 float z_s, float z_e) {
	x_start = x_s; x_end = x_e;
	y_start = y_s; y_end = y_e;
	z_start = z_s; z_end = z_e;
}

void h3d::BoundingBox::create() {
	std::array<h3d::Vec3<float>, 8> edges = {
		h3d::Vec3<float>(x_start,y_start,z_start), // 0
		h3d::Vec3<float>(x_start,y_start,z_end),   // 1
		h3d::Vec3<float>(x_end  ,y_start,z_end),   // 2
		h3d::Vec3<float>(x_end  ,y_start,z_start), // 3
		h3d::Vec3<float>(x_start,y_end  ,z_start), // 4
		h3d::Vec3<float>(x_start,y_end  ,z_end),   // 5
		h3d::Vec3<float>(x_end  ,y_end  ,z_end),   // 6
		h3d::Vec3<float>(x_end  ,y_end  ,z_start)  // 7
	};
	m_impl->vertices.clear();
	for (auto &iter : edges) {
		h3d::Vertex vert;
		vert.position = iter;
		m_impl->vertices.push_back(vert);
	}
}
bool h3d::BoundingBox::intersect(const h3d::Math::Ray& ray)
{


	return false;
}
/////////////////////////////////////////////////////////////////
struct h3d::BoundingBox::impl {
	static size_t m_count;
	static size_t m_currentID;
	static const short*m_indices;

	static std::unordered_map<size_t, impl&> m_map;
	static GLuint m_elementBuffer;

	std::vector<h3d::Vertex> vertices;

	size_t m_ID;

	impl() : m_ID(m_currentID) {
		if (m_count == 0) {
			glCreateBuffers(1, &m_elementBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * 36, m_indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		m_currentID++;
		m_count++;
		m_map.emplace(m_ID, this);
	}
	~impl() {
		m_count--;
		m_map.erase(m_ID);

		if (m_count == 0) 
			glDeleteBuffers(1, &m_elementBuffer);
	}
};
size_t h3d::BoundingBox::impl::m_count = 0;
size_t h3d::BoundingBox::impl::m_currentID = 1;
const short* h3d::BoundingBox::impl::m_indices = new short[36]{ 
	0,1,2,1,2,3,
	0,1,4,1,4,5,
	2,3,6,3,6,7,
	0,3,4,3,4,7,
	1,2,5,2,5,6,
	4,5,6,5,6,7
};
/////////////////////////////////////////////////////////////////