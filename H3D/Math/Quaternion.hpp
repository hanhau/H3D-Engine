#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
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
		H3D_API Quaternion(float aw, float ax, float ay, float az);
		H3D_API ~Quaternion();

		// x real, ijk imaginary
		float w, x, y, z;

		// Transformations
		mat4x4       H3D_API toRotateMat4x4();
		Quaternion   H3D_API fromMat4x4(mat4x4& mat);

		H3D_API Quaternion& conjugate();
		H3D_API Quaternion& normalize();

		// Operators
		H3D_API Quaternion& operator= (mat4x4& mat);

		H3D_API Quaternion& operator+ (Quaternion& q);
		H3D_API Quaternion& operator+=(Quaternion& q);

		H3D_API Quaternion& operator*(Quaternion& q);
		H3D_API Quaternion& operator*=(Quaternion& q);

		H3D_API Quaternion& operator*(float val);
		H3D_API Quaternion& operator*=(float val);
	};

	namespace Math {
		H3D_API Quaternion&  conjugated(Quaternion& q);
		H3D_API Quaternion&  conjugate(Quaternion& q);

		H3D_API Quaternion&  toQuaternion(h3d::mat4x4& mat);
		mat4x4	H3D_API      toRotateMat4x4(Quaternion& q);

		Vec3<float> H3D_API  toEulerAngles(Quaternion& q);
		H3D_API Quaternion&  toQuaternion(h3d::Vec3<float> euler);
	}
}
/////////////////////////////////////////////////////////////////