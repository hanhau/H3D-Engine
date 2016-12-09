#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include "Matrix.hpp"
/////////////////////////////////////////////////////////////////
// Quaternion Math
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Quaternion
	{	
	public:
		// Con-/Destructor
		H3D_API Quaternion();
		H3D_API Quaternion(double ax, double ai, double aj, double ak);
		H3D_API ~Quaternion();

		// x real, ijk imaginary
		double x, i, j, k;

		// Transformations
		mat4x4       H3D_API toMat4x4();
		Quaternion   H3D_API fromMat4x4(const mat4x4& mat);

		// Operators
		const Quaternion& operator= (const mat4x4& mat); 
		const Quaternion& operator+ (const Quaternion& quat);
		const Quaternion& operator+=(const Quaternion& quat);
	};
}
/////////////////////////////////////////////////////////////////