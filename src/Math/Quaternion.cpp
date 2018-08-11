#include "../../H3D/Math/Quaternion.hpp"

h3d::Quaternion::Quaternion() {
	w = 0; x = 0; y = 0; z = 0;
}
h3d::Quaternion::Quaternion(float aw, float ax, float ay, float az) :
	w(aw), x(ax), y(ay), z(az) {}
h3d::Quaternion::~Quaternion() {
	w = 0; x = 0; y = 0; z = 0;
}

/////////////////////////////////////////////////////////////////
// Utils
constexpr float calc_Pi() {
	float p16 = 1, pi = 0, precision = 10;
		for (int k = 0; k <= precision; k++) {
			pi += 1.f / p16 * (4.f / (8.f * k + 1.f) - 2.f /
				(8.f * k + 4.f) - 1.f / (8.f * k + 5) - 1.f /
				(8.f * k + 6.f));
			p16 *= 16.f;
		}
return pi;
}

constexpr float Pi = calc_Pi();
float to_degree(float radian) { return radian * (180.0 / Pi);}
float to_radian(float degree) { return degree * (Pi / 180.0);}
/////////////////////////////////////////////////////////////////
//	Implementation of Quaternions
/////////////////////////////////////////////////////////////////
h3d::mat4x4 h3d::Quaternion::toRotateMat4x4()
{
	h3d::mat4x4 mat;

	float values[] = {1.f-2.f*y*y,2.f*x*y- 2.f*w*z,2.f*x*z+2.f*w*y,0.f,
					  2.f*x*y+2.f*w*z,1.f-2.f*x*-2*z*z,2.f*y*z+2*w*x,0.f,
					  2.f*x*z-2.f*w*y,2.f*y*z-2.f*w*x,1.f-2.f*x*x-2.f*y*y,0.f,
					  0.f,0.f,0.f,1.f};

	mat.setRowWiseValues(values);
	return mat;
}

h3d::Quaternion h3d::Quaternion::fromMat4x4(mat4x4& mat)
{
	return h3d::Quaternion();
}

h3d::Quaternion& h3d::Quaternion::conjugate() {
	x = -x; y = -y; z = -z;
	w = w;
	return *this;
}
h3d::Quaternion& h3d::Quaternion::normalize() 
{
	float n = sqrtf(x*x + y*y + z*z + w*w);
	x /= n;
	y /= n;
	z /= n;
	w /= n;
	return *this;
}

h3d::Quaternion & h3d::Quaternion::operator=(mat4x4 & mat)
{
	fromMat4x4(mat);
	return *this;
}

h3d::Quaternion& h3d::Quaternion::operator+ (Quaternion& q)
{
	return h3d::Quaternion(w + q.w, x + q.x,
						   y + q.y, z + q.z);
}
h3d::Quaternion& h3d::Quaternion::operator+=(Quaternion& q)
{
	w += q.w; x += q.x; 
	y += q.y; z += q.z;
	return *this;
}

h3d::Quaternion& h3d::Quaternion::operator*(Quaternion& q)
{
	float tx =  x * q.w + y * q.z - z * q.y + w * q.x;
	float ty = -x * q.z + y * q.w + z * q.x + w * q.y;
	float tz =  x * q.y - y * q.x + z * q.w + w * q.z;
	float tw = -x * q.x - y * q.y - z * q.z + w * q.w;
	return Quaternion(tw, tx, ty, tz);
}
h3d::Quaternion& h3d::Quaternion::operator*=(Quaternion& q)
{
	float tx =  x * q.w + y * q.z - z * q.y + w * q.x;
	float ty = -x * q.z + y * q.w + z * q.x + w * q.y;
	float tz =  x * q.y - y * q.x + z * q.w + w * q.z;
	float tw = -x * q.x - y * q.y - z * q.z + w * q.w;
	w = tw; x = tx; y = ty; z = tz;
	return *this;
}

h3d::Quaternion& h3d::Quaternion::operator*(float val)
{
	h3d::Quaternion quat(this->w*val,
						 this->x*val, 
						 this->y*val, 
						 this->z*val);
	return quat;
}
h3d::Quaternion& h3d::Quaternion::operator*=(float val)
{
	w *= val;
	x *= val;
	y *= val;
	z *= val;
	return *this;
}
/////////////////////////////////////////////////////////////////
h3d::Quaternion&  h3d::Math::conjugated(Quaternion& q) 
{
	return Quaternion(q.w, -q.x, -q.y, -q.z);
}
h3d::Quaternion&  h3d::Math::toQuaternion(h3d::mat4x4& mat) 
{
	return Quaternion();
}

h3d::mat4x4	h3d::Math::toRotateMat4x4(Quaternion& q) 
{
	h3d::mat4x4 mat;

	float values[] = {
		// 1 2 3 4 
		1.0f - 2.0f*q.y*q.y - 2.0f*q.z*q.z, 2.0f *q.x*q.y - 2.0f*q.z*q.w, 
		2.0f*q.x*q.z + 2.0f*q.y*q.w, 0.0f,
		// 5 6 7 8
		2.0f*q.x*q.y + 2.0*q.z*q.w, 1.0 - 2.0f*q.x*q.x - 2.0f*q.z*q.z, 
		2.0f*q.y*q.z - 2.0*q.x*q.w, 0.0f,
		// 9 10 11 12
		2.0f *q.x*q.z - 2.0f*q.y*q.w, 2.0f*q.y*q.z + 2.0f*q.x*q.w, 
		1.0f - 2.0f*q.x*q.x - 2.0f*q.y*q.y, 0.0f,		
		// 13 14 15 16
		0.0f, 0.0f, 0.0f, 1.0f
	};

	mat.setRowWiseValues(values);
	return mat;
}

h3d::Vec3<float> h3d::Math::toEulerAngles(Quaternion& q)
{
	h3d::Vec3<float> m_temp;

	m_temp.y = atan2f(to_radian(2 * q.y*q.w - 2 * q.x*q.z),
					  to_radian(1 - 2 * q.y * q.y - 2 * q.z * q.z));

	m_temp.z = asinf(to_radian(2 * q.x*q.y + 2 * q.z*q.w));

	m_temp.x = atan2f(to_radian(2 * q.x*q.w - 2 * q.y*q.z),
					  to_radian(1 - 2 * q.x * q.x - 2 * q.z * q.z));
	
	if (q.x*q.y + q.z*q.w == 0.5f) {
		m_temp.y = 2.0 * atan2f(q.x, q.w);
		m_temp.x = 0.0;
	}
	if (q.x*q.y + q.z*q.w == -0.5f) {
		m_temp.y = -2.0 * atan2f(q.x, q.w);
		m_temp.x = 0.0;
	}

	return m_temp;
}

h3d::Quaternion& h3d::Math::toQuaternion(h3d::Vec3<float> euler) 
{	
	float   c1 = cosf(euler.y / 2),
			c2 = cosf(euler.z / 2),
			c3 = cosf(euler.x / 2),
			s1 = sinf(euler.y / 2),
			s2 = sinf(euler.z / 2),
			s3 = sinf(euler.x / 2);

	return h3d::Quaternion(c1 * c2 * c3 - s1 * s2 * s3,
						   s1 * s2 * c3 + c1 * c2 * s3,
						   s1 * c2 * c3 + c1 * s2 * s3,
						   c1 * s2 * c3 - s1 * c2 * s3);
}
/////////////////////////////////////////////////////////////////
