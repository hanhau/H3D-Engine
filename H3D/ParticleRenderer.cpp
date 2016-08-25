#include "ParticleEngine.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of the ParticleRenderer class
/////////////////////////////////////////////////////////////////
h3d::PE::ParticleRenderer::ParticleRenderer()
{
	GLchar vertexCode[] = {
		"#version 330 core\n"
		""
		""
		""
		"void main(){"
		""
		"}"
	};

	GLchar fragmentCode[] = {
		"#version 330 core\n"
		""
		"uniform int mode;"
		""
		"in  vec4 color_in;"
		"out vec4 color_out;"
		""
		"void main(){"
		"	color_out = dynamicFunction();"
		"}"
	};

	m_vertexShader.setCode(vertexCode);
	m_vertexShader.setType(GL_VERTEX_SHADER);
	m_fragmentShader.setCode(fragmentCode);
	m_fragmentShader.setType(GL_FRAGMENT_SHADER);

	m_program.attachShader(m_vertexShader);
	m_program.attachShader(m_fragmentShader);
	m_program.link();
}
h3d::PE::ParticleRenderer::~ParticleRenderer()
{
	
}
/////////////////////////////////////////////////////////////////
void h3d::PE::ParticleRenderer::render()
{
	m_program.use();
	
	

	m_program.use(false);
}
/////////////////////////////////////////////////////////////////