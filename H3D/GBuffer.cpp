#include "GBuffer.hpp"
/////////////////////////////////////////////////////////////////
// Implemenation of GeometryBuffer
/////////////////////////////////////////////////////////////////
h3d::GeometryBuffer::GeometryBuffer() {}
h3d::GeometryBuffer::~GeometryBuffer() 
{
	glDeleteBuffers(1, &m_positionGL);
	glDeleteBuffers(1, &m_specularGL);
	glDeleteBuffers(1, &m_normalGL);
	glDeleteBuffers(1, &m_albedoGL);
}
/////////////////////////////////////////////////////////////////
void h3d::GeometryBuffer::setup(h3d::Vec2<unsigned int> size, unsigned int bitmask)
{
	m_size = std::move(size);

	// Setup Position Buffer
	glGenTextures(1, &m_positionGL);
	glBindTexture(GL_TEXTURE_2D, m_positionGL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_size.x, size.y, 0, GL_RGB,
				 GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
						   m_positionGL, 0);

	// Setup Normal Buffer
	glGenTextures(1, &m_normalGL);
	glBindTexture(GL_TEXTURE_2D, m_normalGL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_size.x, size.y, 0, GL_RGB,
				 GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
						   m_normalGL, 0);

	// Setup Color + Specular Buffer
	glGenTextures(1, &m_albedoGL);
	glBindTexture(GL_TEXTURE_2D, m_albedoGL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, size.y, 0, GL_RGBA,
				 GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
						   m_albedoGL, 0);

	// Setup Color Attachment
		GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);
}
/////////////////////////////////////////////////////////////////
void h3d::GeometryBuffer::bindBuffer(int stage)
{
	switch (stage)
	{
	case Stage::ALBEDO:
		glBindBuffer(GL_TEXTURE_2D, m_albedoGL);
		break;
	case Stage::NORMAL:
		glBindBuffer(GL_TEXTURE_2D, m_normalGL);
		break;
	case Stage::SPECULAR:
		glBindBuffer(GL_TEXTURE_2D, m_specularGL);
		break;
	case Stage::POSITION:
		glBindBuffer(GL_TEXTURE_2D, m_positionGL);
		break;
	default:
		glBindBuffer(GL_TEXTURE_2D, 0);
	}
}
/////////////////////////////////////////////////////////////////
void h3d::GeometryBuffer::clear(int stage)
{
	switch (stage)
	{
	case Stage::COLOR:
		
		break;
	case Stage::NORMAL:

		break;
	case Stage::ALBEDO:

		break;
	case Stage::ALL:

		break;
	default: break;
	}
}
/////////////////////////////////////////////////////////////////