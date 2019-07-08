#include "../../H3D/Model/BoundingBox.hpp"
#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/Graphics/Vertex.hpp"
#include <GL/glew.h>
#include <array>
#include <unordered_map>

/////////////////////////////////////////////////////////////////
struct h3d::BoundingBox::impl {
	static size_t m_count;
	static size_t m_currentID;
	static const short*m_indices;

	static std::unordered_map<size_t, impl&> m_map;
	static GLuint m_elementBuffer;
	static GLuint m_vao;
	static GLuint m_vertexBuffer;

	static std::vector<h3d::Vertex> vertices;

	size_t m_ID;

	impl() : m_ID(m_currentID) {
		if (m_count == 0) {
			glCreateVertexArrays(1, &m_vao);

			glCreateBuffers(1, &m_elementBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * 36, m_indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		m_currentID++;
		m_count++;
		m_map.emplace(m_ID, *this);
	}
	~impl() {
		m_count--;
		m_map.erase(m_ID);

		if (m_count == 0) {
			glDeleteBuffers(1, &m_elementBuffer);
			glDeleteVertexArrays(1, &m_vao);
		}
	}

	static void updateVertices() {
		static int lastVertNum = 0;
		if (vertices.size() != lastVertNum) {
			
		}
	}
};
std::unordered_map<size_t, h3d::BoundingBox::impl&> h3d::BoundingBox::impl::m_map;
size_t h3d::BoundingBox::impl::m_count = 0;
size_t h3d::BoundingBox::impl::m_currentID = 1;
GLuint h3d::BoundingBox::impl::m_vao = 0;
std::vector<h3d::Vertex> h3d::BoundingBox::impl::vertices;
const short* h3d::BoundingBox::impl::m_indices = new short[36]{
	0,1,2,1,2,3,
	0,1,4,1,4,5,
	2,3,6,3,6,7,
	0,3,4,3,4,7,
	1,2,5,2,5,6,
	4,5,6,5,6,7
};

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
	for (int i = 0, j = 0; i < sizeof(m_impl->m_indices); i++, j += 3) {
		m_tris[i].m_pos[0] = m_impl->vertices[m_impl->m_indices[j + 0]].position;
		m_tris[i].m_pos[1] = m_impl->vertices[m_impl->m_indices[j + 1]].position;
		m_tris[i].m_pos[2] = m_impl->vertices[m_impl->m_indices[j + 2]].position;
	}
}
void h3d::BoundingBox::createFromMultiple(std::vector<h3d::BoundingBox*>& boxes) {
	if (boxes.size() == 0) return;
	//*this = boxes[0];
	for (const auto& iter : boxes) {
		if (iter->x_start < x_start) x_start = iter->x_start;
		if (iter->x_end < x_end) x_end = iter->x_end;
		if (iter->y_start < y_start) y_start = iter->y_start;
		if (iter->y_end < y_end) y_end = iter->y_end;
		if (iter->z_start < z_start) z_start = iter->z_start;
		if (iter->z_end < z_end) z_end = iter->z_end;
	} 
}
bool h3d::BoundingBox::intersect(const h3d::Math::Ray& ray)
{
	std::vector<h3d::Vec3<float>> points;
	h3d::Vec3<float> temp;
	for (const auto& iter : m_tris) {
		h3d::Math::intersectRay(ray, iter, temp);
		if (!(temp == 0)) {
			points.push_back(temp);
		}
	}
	if(points.size() == 0)
		return false;
	else {
		std::vector<h3d::Vec3<float>> distance_vecs;
		for (auto &iter : points) {
			distance_vecs.push_back(ray.m_pos - iter);
		}
		int finalIndex = 0;
		for (int i = 0; i < distance_vecs.size(); i++) {
			if (distance_vecs[i].length() < distance_vecs[finalIndex].length())
				finalIndex = i;
		}
		m_lastIntersectPoint = points[finalIndex];
		return true;
	}
}
void h3d::BoundingBox::render() {
	glBindVertexArray(m_impl->m_vao);
	glDrawElements(GL_VERTEX_ARRAY, 12, GL_STATIC_DRAW, 0);
}
/////////////////////////////////////////////////////////////////
