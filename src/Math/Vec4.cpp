#include "../../H3D/Vector/Vector_Declaration.hpp"
#include "../../H3D/Math/Matrix.hpp"
#include <utility>
/////////////////////////////////////////////////////////////////
//	Vec4 Implementations
/////////////////////////////////////////////////////////////////
// De-/Constructor
h3d::Vec4::Vec4(float _x, float _y, float _z, float _w) :
	x(_x),y(_y),z(_z),w(_w)
{}
h3d::Vec4::Vec4(h3d::Vec3<float> vec, float w) :
	x(vec.x), y(vec.y), z(vec.z), w(w)
{}
h3d::Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
h3d::Vec4::~Vec4() {}
/////////////////////////////////////////////////////////////////
// Operators
h3d::Vec4& h3d::Vec4::operator= (Vec4 &obj) {
	return *this = std::move(obj);
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
	return Vec4(x*val,y*val,z*val,w*val);
}
h3d::Vec4& h3d::Vec4::operator/ (Vec4 &obj) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator/ (float val) {
	return Vec4();
}
h3d::Vec4& h3d::Vec4::operator+=(Vec4 &obj) {
	
	return *this;
}
h3d::Vec4& h3d::Vec4::operator-=(Vec4 &obj) {
	x -= obj.x;
	y -= obj.y;
	z -= obj.y;
	w -= obj.w;
	return *this;
}
h3d::Vec4& h3d::Vec4::operator*=(Vec4 &obj) {
	
	return *this;
}
h3d::Vec4& h3d::Vec4::operator/=(Vec4 &obj) {
	
	return *this;
}
/////////////////////////////////////////////////////////////////
// Mathematical Operations
h3d::Vec4 h3d::Vec4::asAppliedWith(h3d::mat4x4 &mat)
{
	Vec4 temp(*this);
	temp = mat * temp;
	return temp;
}
/////////////////////////////////////////////////////////////////