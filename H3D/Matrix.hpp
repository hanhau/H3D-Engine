#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <stdlib.h>
#include "Vector.hpp"
/////////////////////////////////////////////////////////////////
//	Matrix Classes (row wise)
/////////////////////////////////////////////////////////////////
namespace h3d {
	class mat4x4	
	{
	private:
		__m128 m_column[4];

		void* operator new(size_t size){ return _mm_malloc(size, 16); }
		void operator delete(void * mem) { _mm_free(mem); }
	public:
		//  Constructor/Deconstructor
		H3D_API mat4x4();
		H3D_API mat4x4(mat4x4 &mat);
		H3D_API ~mat4x4();

		//	Access operators
		H3D_API float&       operator()(int x, int y); // 2D
		H3D_API __m128&      operator()(int y);		   // 1D
		H3D_API float* getColumnWiseValues();
		H3D_API float* getRowWiseValues();
		H3D_API void setColumnWiseValues(float *values);
		H3D_API void setRowWiseValues   (float *values);

		// Standart Operators
		H3D_API mat4x4& operator=(mat4x4& mat);
		
		// Math Operatiors
		H3D_API mat4x4& operator+= (const float val);
		H3D_API mat4x4& operator+= (const h3d::mat4x4 &mat);
		H3D_API mat4x4& operator-= (const float val);
		H3D_API mat4x4& operator-= (const h3d::mat4x4 &mat);
		H3D_API mat4x4& operator*= (const float val);
	    H3D_API mat4x4& operator*=       (h3d::mat4x4 &mat);

		H3D_API mat4x4& operator+(const float val);
		H3D_API mat4x4& operator+(const h3d::mat4x4 &mat);
		H3D_API mat4x4& operator-(const float val);
		H3D_API mat4x4& operator-(const h3d::mat4x4 &mat);
		H3D_API mat4x4& operator*(const float val);
		H3D_API mat4x4& operator*(const h3d::mat4x4 &mat);
	};
	/////////////////////////////////////////////////////////////
	//	Matrix Math Functions
	/////////////////////////////////////////////////////////////
	namespace Math {
		// Create Transformation Matrices
		H3D_API mat4x4 rotate(	 float deg_x,float deg_y,float deg_z);
		H3D_API mat4x4 scale(    float scl_x,float scl_y,float scl_z);
		H3D_API mat4x4 translate(float trs_x,float trs_y,float trs_z);
		// Viewport Matrix Operations
		H3D_API mat4x4 lookAt(h3d::Vec3<float> eye_vec,
							  h3d::Vec3<float> center_vec,
							  h3d::Vec3<float> up_vec);
		H3D_API mat4x4 projectionMatrix(float fov,float near_c,
									    float far_c, float aspectRatio);
	}
}
/////////////////////////////////////////////////////////////////