#include "GBuffer.hpp"
/////////////////////////////////////////////////////////////////
// Implemenation of GeometryBuffer
/////////////////////////////////////////////////////////////////
h3d::GeometryBuffer::GeometryBuffer() {}
h3d::GeometryBuffer::~GeometryBuffer() 
{

}
/////////////////////////////////////////////////////////////////
void h3d::GeometryBuffer::setup(h3d::Vec2<unsigned int> size,int bitmask)
{
	m_size = std::move(size);

	// Clear old contents
	m_BufferOrderMap.clear();
	glDeleteFramebuffers(1, &m_fbo);

	// Generating FBO
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	// Append Stages
	int actualState = 0, actualPos = 0;

	while (bitmask != 0)
	{
		if (bitmask & Stage::DEPTH)
		{

			bitmask -= Stage::DEPTH;
		}
		else
		{
			if (bitmask & Stage::DIFFUSE)
			{

				bitmask -= Stage::DIFFUSE;
			}
			if (bitmask & Stage::NORMAL)
			{
				bitmask -= Stage::NORMAL;
			}
			if (bitmask & Stage::ALBEDO)
			{
				bitmask -= Stage::ALBEDO;
			}
			if (bitmask & Stage::POSITION)
			{
				bitmask -= Stage::POSITION;
			}
			if (bitmask & Stage::SPECULAR)
			{
				bitmask -= Stage::SPECULAR;
			}

			glBindTexture(GL_TEXTURE_2D,);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
		}
	}
}
/////////////////////////////////////////////////////////////////
void h3d::GeometryBuffer::bind()
{
	
}
/////////////////////////////////////////////////////////////////
void h3d::GeometryBuffer::clear(int bitmask)
{
	
}
/////////////////////////////////////////////////////////////////
GLint h3d::GeometryBuffer::getColorAttachmentOffset(const int stage)
{

}
/////////////////////////////////////////////////////////////////