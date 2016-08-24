#include "Matrix.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <memory>
/////////////////////////////////////////////////////////////////
//	Implementation of Matrix Functions	
/////////////////////////////////////////////////////////////////
//  Constructor/Destructor
/////////////////////////////////////////////////////////////////
h3d::mat4x4::mat4x4() 
{
	for (int i = 0;i < 4;i++)
		m_column[i] = _mm_set_ps(0.0f,0.0f,0.0f,0.0f);
}
h3d::mat4x4::mat4x4(mat4x4 &mat)
{
	*this = mat;
}
h3d::mat4x4::~mat4x4() {}
/////////////////////////////////////////////////////////////////
//  Access Operators
/////////////////////////////////////////////////////////////////
float& h3d::mat4x4::operator()(int x, int y){
	return m_column[y].m128_f32[x];
}
__m128& h3d::mat4x4::operator()(int y) {
	return m_column[y];
}
float* h3d::mat4x4::getColumnWiseValues()
{
	static float values[16];
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
			values[i*4+j] = m_column[i].m128_f32[j];
	return values;
}
float* h3d::mat4x4::getRowWiseValues()
{
	static float values[16];
	for (int i = 0,col = 0;col < 4;col++)
		for (int row = 0;row < 4;row++)
		{
			values[i] = m_column[col].m128_f32[row];
			i++;
		}
	return values;
}
void h3d::mat4x4::setColumnWiseValues(float *values)
{
	m_column[0] = _mm_set_ps(values[ 3], values[ 2], values[ 1], values[ 0]);
	m_column[1] = _mm_set_ps(values[ 7], values[ 6], values[ 5], values[ 4]);
	m_column[2] = _mm_set_ps(values[11], values[10], values[ 9], values[ 8]);
	m_column[3] = _mm_set_ps(values[15], values[14], values[13], values[12]);
}
void h3d::mat4x4::setRowWiseValues(float *values)
{							
	m_column[0] = _mm_set_ps(values[12], values[ 8], values[4], values[0]);
	m_column[1] = _mm_set_ps(values[13], values[ 9], values[5], values[1]);
	m_column[2] = _mm_set_ps(values[14], values[10], values[6], values[2]);
	m_column[3] = _mm_set_ps(values[15], values[11], values[7], values[3]);
}
/////////////////////////////////////////////////////////////////
// Standart Operators
/////////////////////////////////////////////////////////////////
h3d::mat4x4& h3d::mat4x4::operator=(h3d::mat4x4 &mat)
{
	for (int i = 0;i < 4;i++)
		m_column[i] = mat.m_column[i];	
	return *this;
}
/////////////////////////////////////////////////////////////////
//  Math Operations
/////////////////////////////////////////////////////////////////
h3d::mat4x4& h3d::mat4x4::operator+=(const float val) 
{
	__m128 add_vals = _mm_set_ps(val, val, val, val);
	for (int i = 0;i < 4;i++)
		m_column[i] = _mm_add_ps(m_column[i], add_vals);
	return *this;
}
h3d::mat4x4& h3d::mat4x4::operator+=(const h3d::mat4x4 &mat) 
{
	for (int i = 0;i < 4;i++)
		m_column[i] = _mm_add_ps(m_column[i],mat.m_column[i]);
	return *this;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4& h3d::mat4x4::operator-= (const float val)
{
	__m128 sub_vals = _mm_set_ps(val, val, val, val);
	for (int i = 0;i < 4;i++)
		m_column[i] = _mm_sub_ps(m_column[i], sub_vals);
	return *this;
}
h3d::mat4x4& h3d::mat4x4::operator-= (const h3d::mat4x4 &mat)
{
	for (int i = 0;i < 4;i++)
		m_column[i] = _mm_sub_ps(m_column[i], mat.m_column[i]);
	return *this;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4& h3d::mat4x4::operator*=(const float val)
{
	__m128 mul_vals = _mm_set_ps(val, val, val, val);
	for (int i = 0;i < 4;i++)
		m_column[i] = _mm_mul_ps(m_column[i], mul_vals);
	return *this;
}
h3d::mat4x4& h3d::mat4x4::operator*=(h3d::mat4x4 &mat) 
{
	const float *A = getRowWiseValues();
	const float *B = mat.getRowWiseValues();
	float *C;
	__m128 row1 = _mm_load_ps(&B[0]);
	__m128 row2 = _mm_load_ps(&B[4]);
	__m128 row3 = _mm_load_ps(&B[8]);
	__m128 row4 = _mm_load_ps(&B[12]);
	for (int i = 0;i < 4;i++)
	{
		__m128 brod1 = _mm_set1_ps(A[4 * i + 0]);
		__m128 brod2 = _mm_set1_ps(A[4 * i + 1]);
		__m128 brod3 = _mm_set1_ps(A[4 * i + 2]);
		__m128 brod4 = _mm_set1_ps(A[4 * i + 3]);
		__m128 row = _mm_add_ps(
						_mm_add_ps(_mm_mul_ps(brod1,row1),
								   _mm_mul_ps(brod2,row2)),
						_mm_add_ps(_mm_mul_ps(brod3,row3),
								   _mm_mul_ps(brod4,row4)));
		_mm_store_ps(&C[4*i],row);
	}
	setRowWiseValues(C);
	return *this;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4& h3d::mat4x4::operator+(const float val)
{
	mat4x4 temp_mat;
	
	return temp_mat;
}
h3d::mat4x4& h3d::mat4x4::operator+(const h3d::mat4x4 &mat)
{
	mat4x4 temp_mat;

	return temp_mat;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4& h3d::mat4x4::operator-(const float val)
{
	mat4x4 temp_mat;

	return temp_mat;
}
h3d::mat4x4& h3d::mat4x4::operator-(const h3d::mat4x4 &mat)
{
	mat4x4 temp_mat;

	return temp_mat;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4& h3d::mat4x4::operator*(const float val)
{
	mat4x4 temp_mat;

	return temp_mat;
}
h3d::mat4x4& h3d::mat4x4::operator*(const h3d::mat4x4 &mat)
{
	mat4x4 temp_mat;

	return temp_mat;
}
/////////////////////////////////////////////////////////////////
//	Implementations of Matrix Math Functions
/////////////////////////////////////////////////////////////////
h3d::mat4x4 h3d::Math::rotate(float deg_x = 0.0f, float deg_y = 0.0f, float deg_z = 0.0f)
{
	deg_x *= M_PI / 180.0f;
	deg_y *= M_PI / 180.0f;
	deg_z *= M_PI / 180.0f;
	float values[16] = {cosf(deg_y)*cosf(deg_z),		// 1st row
						cosf(deg_x)*sinf(deg_z)+sinf(deg_x)*sinf(deg_y)*cosf(deg_z),
						sinf(deg_x)*sinf(deg_z)-cosf(deg_x)*sinf(deg_y)*cosf(deg_z),0.0,
						-cosf(deg_y)*sinf(deg_z),		// 2nd row
						cosf(deg_x)*cosf(deg_z)-sinf(deg_x)*sinf(deg_y)*sinf(deg_z),
						sinf(deg_x)*cosf(deg_z)+cosf(deg_x)*sinf(deg_y)*sinf(deg_z),0.0,
						sinf(deg_y),					// 3rd row
						-sinf(deg_x)*cosf(deg_y),
						cosf(deg_x)*cosf(deg_y),0.0,
						0.0f,0.0f,0.0f,1.0};			// 4th row
	mat4x4 mat;
	mat.setRowWiseValues(values);
	return mat;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4 h3d::Math::scale(float scl_x, float scl_y, float scl_z)
{
	float values[16] = {scl_x, 0.0f, 0.0f, 0.0f,
						0.0f, scl_y, 0.0f, 0.0f,
						0.0f, 0.0f, scl_z, 0.0f,
						0.0f, 0.0f,  0.0f, 1.0f};
	mat4x4 mat;
	mat.setRowWiseValues(values);
	return mat;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4 h3d::Math::translate(float trs_x, float trs_y, float trs_z)
{
	float values[16] = {1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f, 
						trs_x,trs_y,trs_z, 1.0f};	
	mat4x4 mat;
	mat.setRowWiseValues(values);
	return mat;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4 h3d::Math::lookAt(h3d::Vec3<float> eye_vec,
					          h3d::Vec3<float> center_vec,
							  h3d::Vec3<float> up_vec)
{
	h3d::mat4x4 look_mat;
	h3d::Vec3<float> distance = center_vec - eye_vec;
	h3d::Vec3<float> side = h3d::cross(center_vec,up_vec);
	h3d::Vec3<float> new_up = h3d::cross(side,distance);
	float values[16] = { side.x, new_up.x, distance.x, -eye_vec.x,
						 side.y, new_up.y, distance.y, -eye_vec.y,
						 side.z, new_up.z, distance.z, -eye_vec.z,
						   0.0f,     0.0f,       0.0f,       1.0f };
	look_mat.setRowWiseValues(values);
	return look_mat;
}
/////////////////////////////////////////////////////////////////
h3d::mat4x4 h3d::Math::projectionMatrix(float fov, float near_c,
										float far_c, float aspectRatio)
{
	mat4x4 proj_mat;
	float S1 = 1 / (aspectRatio*tanf(95.f / 2.f));
	float S2 = 1 / (tanf(95.f / 2.f));
	float values[16] = {  S1 ,0.0f,0.0f,0.0f,
						 0.0f, S2 ,0.0f,0.0f,
						 0.0f,0.0f,((-near_c - far_c) / (near_c - far_c)), 1.0f,
						 0.0f,0.0f,(2 *near_c*far_c / (near_c - far_c)),0.0f };
	proj_mat.setRowWiseValues(values);
	return proj_mat;
}
/////////////////////////////////////////////////////////////////