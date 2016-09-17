#include "Vector/Vector_Declaration.hpp"
/////////////////////////////////////////////////////////////////
//	Vec4 Implementations
/////////////////////////////////////////////////////////////////
// De-/Constructor
h3d::Vec4::Vec4(float _x, float _y, float _z, float _w) :
	x(m_vec.m128_f32[0]),
	y(m_vec.m128_f32[1]),
	z(m_vec.m128_f32[2]),
	w(m_vec.m128_f32[3])
{
	this->m_vec = _mm_set_ps(x,y,z,w);
}
h3d::Vec4::Vec4() :
	x(m_vec.m128_f32[0]),
	y(m_vec.m128_f32[1]),
	z(m_vec.m128_f32[2]),
	w(m_vec.m128_f32[3])
{
	this->m_vec = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
}
h3d::Vec4::~Vec4() {}
/////////////////////////////////////////////////////////////////
// Operators
h3d::Vec4& h3d::Vec4::operator= (Vec4 &obj) {
	this->m_vec = obj.m_vec;
	return *this;
}
h3d::Vec4& h3d::Vec4::operator= (float val) {
	_mm_set_ps(val, val, val, val);
	return *this;
}
h3d::Vec4& h3d::Vec4::operator+ (Vec4 &obj) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator+ (float val) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator- (Vec4 &obj) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator- (float val) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator* (Vec4 &obj) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator* (float val) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator/ (Vec4 &obj) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator/ (float val) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator+=(Vec4 &obj) {
	this->m_vec = _mm_add_ps(this->m_vec, obj.m_vec);
	return *this;
}
h3d::Vec4& h3d::Vec4::operator-=(Vec4 &obj) {
	this->m_vec = _mm_sub_ps(this->m_vec, obj.m_vec);
	return *this;
}
h3d::Vec4& h3d::Vec4::operator*=(Vec4 &obj) {
	this->m_vec = _mm_mul_ps(this->m_vec, obj.m_vec);
	return *this;
}
h3d::Vec4& h3d::Vec4::operator/=(Vec4 &obj) {
	this->m_vec = _mm_div_ps(this->m_vec, obj.m_vec);
	return *this;
}
/////////////////////////////////////////////////////////////////
// Mathematical Operations
h3d::Vec4 h3d::Vec4::asAppliedWith(h3d::mat4x4 &mat)
{

	return Vec4();
}
/////////////////////////////////////////////////////////////////