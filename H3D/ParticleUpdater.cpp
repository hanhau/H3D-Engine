#include "ParticleEngine.hpp"
#include <cmath>
/////////////////////////////////////////////////////////////////
// Implementation of ParticleUpdater class
/////////////////////////////////////////////////////////////////
h3d::PE::ParticleUpdater::ParticleUpdater()
{
	// Get avaliability of compute shaders
	if (glewIsSupported("ARB_compute_shader"))
	{
		m_computingType = 0x0;
		
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &m_maxWorkerCount.x);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &m_maxWorkerCount.y);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &m_maxWorkerCount.z);

		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &m_maxWorkerSize.x);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &m_maxWorkerSize.y);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &m_maxWorkerSize.z);

		GLchar computeCode[] = {
			"#version 430 compatibility\n"
			"#extension GL_ARB_compute_shader               : enable;"
			"#extension GL_ARB_shader_storage_buffer_object : enable;"
			""
			"layout(local_size_x = 128,  local_size_y = 1, local_size_z = 1)   in;"
			""
			"struct pos{"
			"vec4 pxyzw; // positions"
			"};"
			"struct vel{"
			"vec4 vxyzw;// velocities"
			"};"
			"struct color{"
			"vec4 crgba;// colors"
			"};"
			"layout(std140, binding = 0)  buffer  Pos {"
			"struct pos Positions[];// array of structures"
			"};"
			"layout(std140, binding = 1)  buffer Vel {"
			"struct vel Velocities[];// array of structures"
			"};"
			"layout(std140, binding = 2)  buffer  Col {"
			"struct color Colors[];// array of structures"
			"};"
			""
			"subroutine void ParticleUpdateFunc();"
			""
			"subroutine(ParticleUpdateFunc) updateFunc_PointParticle(){"
			"	"
			"}"
			"subroutine uniform ParticleUpdateFunc ptr_UpdateFunc;"
			""
			"void main(){"
			"	ptr_UpdateFunc();"
			"}"
		};
		m_computeShader.setCode(computeCode);
		m_computeShader.setType(GL_COMPUTE_SHADER);
		m_program.attachShader(m_computeShader);
		m_program.link();
	}
	else
	{
		m_computingType = 0x1;
	}
}
h3d::PE::ParticleUpdater::~ParticleUpdater()
{

}
/////////////////////////////////////////////////////////////////
void h3d::PE::ParticleUpdater::addToQueue(const h3d::PE::Emitter& emitter)
{
	m_EmitterQueue.push(emitter);
}
/////////////////////////////////////////////////////////////////
void h3d::PE::ParticleUpdater::clearQueue()
{
	std::priority_queue<h3d::PE::Emitter>().swap(m_EmitterQueue);
}
/////////////////////////////////////////////////////////////////
void h3d::PE::ParticleUpdater::update()
{
	// Compute Shader Updating
	if (m_computingType == 0x0)
	{
		for (int i = 0;i < m_EmitterQueue.size();i++)
		{

		}
	}
	// CPU Updating
	else if (m_computingType == 0x1)
	{

	}
	else return;
}
/////////////////////////////////////////////////////////////////