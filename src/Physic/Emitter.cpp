#include "../../H3D/Physic/Physic.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of Emitter
/////////////////////////////////////////////////////////////////
const float _gravity_ms = 9.81;

struct h3d::PE::Emitter::impl {
	GLuint m_bufferids[4];

	int						m_particleCount;
	h3d::Vec3<float>		m_pos;
	h3d::PE::Emitter::Type  m_type;
	bool					m_gravity;
	h3d::Vec3<float>		m_size;
	float					m_strength;
};

h3d::PE::Emitter::Emitter() {
	m_impl = std::make_unique<impl>();
	glCreateBuffers(4,m_impl->m_bufferids);


}
h3d::PE::Emitter::~Emitter() {
	glDeleteBuffers(4, m_impl->m_bufferids);
}

void h3d::PE::Emitter::create(h3d::Vec3<float> pos,
							  int particle_count,
							  Type type, bool gravity,
							  h3d::Vec3<float> size,
							  float strength) 
{

}

void h3d::PE::Emitter::setParticle(h3d::Texture& tex,
								   h3d::Vec3<float> size,
								   float fadetime, FadeType ftype,
								   h3d::Color<GLfloat> col)
{
	
}

void h3d::PE::Emitter::update(float deltaTime) {

}
void h3d::PE::Emitter::render() {

}
/////////////////////////////////////////////////////////////////