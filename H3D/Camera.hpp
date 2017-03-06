#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <cmath>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Window.hpp"
#include "Program.hpp"
/////////////////////////////////////////////////////////////////
//	class Camera 
/////////////////////////////////////////////////////////////////
namespace h3d {
class Camera
{
private:
	// Vectors
	h3d::Vec3<float> m_pos;
	h3d::Vec3<float> m_target;
	h3d::Vec3<float> m_up;
	
	// Viewport Setup Values
	h3d::Vec2<unsigned short> m_size;
	bool                      m_needToUpdateViewport;

	// Output Matrices
	h3d::mat4x4 m_view;
	h3d::mat4x4 m_projectionMatrix;
public:
	// Con-/Destructor
	H3D_API	Camera();
	H3D_API ~Camera();

	// Updating the camera
	void H3D_API setTarget(    h3d::Vec3<float> target);
	void H3D_API setPos(       h3d::Vec3<float> position);
	void H3D_API setDirection( h3d::Vec3<float> direction);

	// Set Viewportsize
	void H3D_API setViewportSize(h3d::Vec2<unsigned short> size);

	// Needs to be called for updating:
	// -> lookAt Matrix (if necessary)
	// -> Viewport (if necessary)
	void H3D_API update();

	// Set ProjectionMatrices
	void H3D_API setProjectionMatrix(h3d::mat4x4 &mat);

	// Get Data
	h3d::Vec3<float> H3D_API getPos();
	h3d::Vec3<float> H3D_API getTarget();
	h3d::Vec3<float> H3D_API getDirection();

	// Update Current State into actual Shader
	bool H3D_API setShaderValues(h3d::Program &program,
								 const GLchar* name_proj,
								 const GLchar* name_view);

	// Get View Matrices
	h3d::mat4x4 H3D_API getViewMatrix();
	h3d::mat4x4 H3D_API getProjectionMatrix();
};
}
/////////////////////////////////////////////////////////////////