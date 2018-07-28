#include "../../H3D/Scene/Camera.hpp"
#include "../../H3D/System/Utilities.hpp"

#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
// Camera Implementations
/////////////////////////////////////////////////////////////////
h3d::Camera::Camera() : m_pos(0.0f, 0.0f, 0.0f),
						m_target(0.0f, 0.0f, 0.0f),
						m_up(0.0f, 0.0f, 0.0f),
						m_view(),m_projectionMatrix() {}
h3d::Camera::~Camera() {}
/////////////////////////////////////////////////////////////////
//	updating Camera	
void h3d::Camera::update()
{
	m_view = h3d::Math::lookAt(m_pos, m_target, m_up);
	
	if (m_needToUpdateViewport){
		glViewport(0,0,m_size.x,m_size.y);
	}
}
/////////////////////////////////////////////////////////////////
//	Set-Methods
void h3d::Camera::setTarget(   h3d::Vec3<float> target)   { 
	m_target = target;
}
void h3d::Camera::setPos(h3d::Vec3<float> position) {
	m_pos = position;
}
void h3d::Camera::setDirection(h3d::Vec3<float> direction){ 
	m_up = direction;
}
void h3d::Camera::setRotation(h3d::Quaternion total){
	m_rotation = total;
}
void h3d::Camera::applyRotation(h3d::Quaternion local_rot){
	m_rotation *= local_rot;
}
/////////////////////////////////////////////////////////////////
// Viewport/Projection Setup
void h3d::Camera::setViewportSize(h3d::Vec2<unsigned short> size)
{
	if (m_size == size)
		m_needToUpdateViewport = false;
	else 
		m_needToUpdateViewport = true;
}
void h3d::Camera::setProjectionMatrix(h3d::mat4x4 &mat) {
	m_projectionMatrix = mat;
}
/////////////////////////////////////////////////////////////////
//	Get-Methods
h3d::Vec3<float> h3d::Camera::getPos()       { return m_pos; }
h3d::Vec3<float> h3d::Camera::getTarget()    { return m_target; };
h3d::Vec3<float> h3d::Camera::getDirection() { return m_target - m_pos; }
/////////////////////////////////////////////////////////////////
// Set Shader Values for the Camera
bool h3d::Camera::setShaderValues(h3d::Program &program,
								  const GLchar* name_proj, const GLchar* name_view)
{
	program.use(true);
	GLint location_proj,location_view;
	location_proj = glGetUniformLocation(program.getID_GL(), name_proj);
	location_view = glGetUniformLocation(program.getID_GL(), name_view);
	if (location_proj == -1 || location_view == -1) {
		h3d::Log::error("h3d::Camera Instance: Error setting variables in shader");
		return false;
	}
	glUniformMatrix4fv(location_proj, 1, GL_TRUE, m_projectionMatrix.getRowWiseValues());
	glUniformMatrix4fv(location_view, 1, GL_TRUE, m_view.getRowWiseValues());	
	return true;
}
/////////////////////////////////////////////////////////////////
// Return View-/Projectionmatrix
h3d::mat4x4 h3d::Camera::getViewMatrix() { return m_view; }
h3d::mat4x4 h3d::Camera::getProjectionMatrix() { return m_projectionMatrix; }
/////////////////////////////////////////////////////////////////
