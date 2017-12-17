#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <cmath>
#include <xmmintrin.h>
#pragma warning(disable:4244)
/////////////////////////////////////////////////////////////////
namespace h3d{
	class mat4x4;
/////////////////////////////////////////////////////////////////
//	Vector2<class T> 
/////////////////////////////////////////////////////////////////
template<typename T>
class Vec2
{
public:
	// Values
	T x, y;
	
	// Con-/Destructor
	template<typename T>
	Vec2(T a, T b) :x(a), y(b) {};
	Vec2() {};
	
	// Standartoperators
	bool operator==(Vec2 &obj);

	// Mathoperators
	template<typename U> Vec2<T>& operator= (Vec2<U> &obj);
	template<typename U> Vec2<T>& operator+ (Vec2<U> &obj);
	template<typename U> Vec2<T>& operator- (Vec2<U> &obj);
	template<typename U> Vec2<T>& operator* (Vec2<U> &obj);
	template<typename U> Vec2<T>& operator/ (Vec2<U> &obj);
	template<typename U> Vec2<T>& operator+=(Vec2<U> &obj);
	template<typename U> Vec2<T>& operator-=(Vec2<U> &obj);
	template<typename U> Vec2<T>& operator*=(Vec2<U> &obj);
	template<typename U> Vec2<T>& operator/=(Vec2<U> &obj);

	// Mathfunctions
	T length();
};
/////////////////////////////////////////////////////////////////
//	Vector3<class T> 
/////////////////////////////////////////////////////////////////
template<typename T>
class Vec3
{
public:
	// values
	T x, y, z;

	// constructors
	template<typename T>
	Vec3(T a, T b, T c) :x(a), y(b),z(c) {};
	Vec3() {};

	// operators
	template<typename U> Vec3<T>& operator= (Vec3<U> &obj);
	template<typename U> Vec3<T>& operator+ (Vec3<U> &obj);
	template<typename U> Vec3<T>& operator- (Vec3<U> &obj);
	template<typename U> Vec3<T>& operator* (Vec3<U> &obj);
	template<typename U> Vec3<T>& operator/ (Vec3<U> &obj);
	template<typename U> Vec3<T>& operator+=(Vec3<U> &obj);
	template<typename U> Vec3<T>& operator-=(Vec3<U> &obj);
	template<typename U> Vec3<T>& operator*=(Vec3<U> &obj);
	template<typename U> Vec3<T>& operator/=(Vec3<U> &obj);

	// functions
	T length();
	Vec3<T>& normalize();
	template<typename U> Vec3<T>& cross(h3d::Vec3<U> &obj);
};
/////////////////////////////////////////////////////////////////
//  Vec4 (SIMD supported class)
/////////////////////////////////////////////////////////////////
class H3D_API Vec4
{
public:
	// Con-/Destructor
	Vec4(float _x, float _y, float _z, float _w);
	Vec4(h3d::Vec3<float> vec, float w);
	Vec4();
	~Vec4();

	// direct Access
	float x, y, z, w;

	// operators
	Vec4& operator= (Vec4 &obj);
	Vec4& operator= (float val);
	Vec4& operator+ (Vec4 &obj);
	Vec4& operator+ (float val);
	Vec4& operator- (Vec4 &obj);
	Vec4& operator- (float val);
	Vec4& operator* (Vec4 &obj);
	Vec4& operator* (float val);
	Vec4& operator/ (Vec4 &obj);
	Vec4& operator/ (float val);
	Vec4& operator+=(Vec4 &obj);
	Vec4& operator-=(Vec4 &obj);
	Vec4& operator*=(Vec4 &obj);
	Vec4& operator/=(Vec4 &obj);

	// Mathematical Operations
	virtual h3d::Vec4 asAppliedWith(h3d::mat4x4 &mat);
};
/////////////////////////////////////////////////////////////////
//	Math Operations
/////////////////////////////////////////////////////////////////
template<typename T> h3d::Vec3<T> normalized(h3d::Vec3<T> vec);
template<typename T> h3d::Vec3<T> cross(h3d::Vec3<T> vec_a,
										h3d::Vec3<T> vec_b);
template<typename T>           T  dot(h3d::Vec3<T> vec_a,
									  h3d::Vec3<T> vec_b);
/////////////////////////////////////////////////////////////////
}