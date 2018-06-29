#include "../../H3D/Graphics/GBuffer.hpp"
/////////////////////////////////////////////////////////////////
// Implemenation of GeometryBuffer
/////////////////////////////////////////////////////////////////
h3d::GeometryBuffer::GeometryBuffer() {}
h3d::GeometryBuffer::~GeometryBuffer() 
{

}
/////////////////////////////////////////////////////////////////
void h3d::GeometryBuffer::setup(h3d::Vec2<int> size,int bitmask)
{
	// Check for valid bitmask
	if (bitmask > Stage::ALL) return;

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
			glBindTexture(GL_TEXTURE_2D, m_oglBuffer[6]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_oglBuffer[5], 0);
			bitmask -= Stage::DEPTH;
		}
		else
		{
			if (bitmask & Stage::DIFFUSE)
				bitmask -= (actualState = Stage::DIFFUSE);
			if (bitmask & Stage::NORMAL)
				bitmask -= (actualState = Stage::NORMAL);
			if (bitmask & Stage::ALBEDO)
				bitmask -= (actualState = Stage::ALBEDO);
			if (bitmask & Stage::POSITION)
				bitmask -= (actualState = Stage::POSITION);
			if (bitmask & Stage::SPECULAR)
				bitmask -= (actualState = Stage::SPECULAR);

			glBindTexture(GL_TEXTURE_2D,m_oglBuffer[actualPos]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 
						 size.x, size.y, 0, 
						 GL_RGB, GL_FLOAT, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, 
								   GL_COLOR_ATTACHMENT0 + actualPos,
								   GL_TEXTURE_2D,
								   m_oglBuffer[actualPos], 0);
		 
			actualPos++;
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
	return 0;
}
/////////////////////////////////////////////////////////////////