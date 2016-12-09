#include "Quaternion.hpp"
/////////////////////////////////////////////////////////////////
//	Implementation of Quaternions
/////////////////////////////////////////////////////////////////
h3d::Quaternion::Quaternion() {}
h3d::Quaternion::Quaternion(double ax, double ai, double aj, double ak) :
							x(ax),i(ai),j(aj),k(ak){}
h3d::Quaternion::~Quaternion() {}
/////////////////////////////////////////////////////////////////
h3d::mat4x4 h3d::Quaternion::toMat4x4()
{
	return h3d::mat4x4();
}
/////////////////////////////////////////////////////////////////
h3d::Quaternion h3d::Quaternion::fromMat4x4(const mat4x4& mat)
{
	return h3d::Quaternion();
}
/////////////////////////////////////////////////////////////////
const h3d::Quaternion & h3d::Quaternion::operator=(const mat4x4 & mat)
{
	fromMat4x4(mat);
	return *this;
}
const h3d::Quaternion & h3d::Quaternion::operator+(const h3d::Quaternion & quat)
{
	return h3d::Quaternion();
}
const h3d::Quaternion & h3d::Quaternion::operator+=(const h3d::Quaternion & quat)
{
	return h3d::Quaternion();
}
/////////////////////////////////////////////////////////////////
