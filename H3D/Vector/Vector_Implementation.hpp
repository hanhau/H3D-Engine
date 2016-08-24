#pragma once
#include <cmath>
/////////////////////////////////////////////////////////////////
//	h3d::Vec2 Funcs
/////////////////////////////////////////////////////////////////
// Standartoperators
template<typename T>
bool h3d::Vec2<T>::operator==(Vec2 &obj)
{
	return(this->x == obj.x && this->y == obj.y) ? true : false;
}
/////////////////////////////////////////////////////////////////
//	Mathoperatos
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator=(Vec2<U> &obj)
{
	this->x = (T)obj.x;
	this->y = (T)obj.y;
	return *this;
}
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator+(Vec2<U> &obj)
{
	Vec2<T> temp;
	temp.x = this->x + (T)obj.x;
	temp.y = this->y + (T)obj.y;
	return *temp;
}
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator-(Vec2<U> &obj)
{
	Vec2<T> temp;
	temp.x = this->x - (T)obj.x;
	temp.y = this->y - (T)obj.y;
	return *temp;
}
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator*(Vec2<U> &obj)
{
	Vec2<T> temp;
	temp.x = this->x * (T)obj.x;
	temp.y = this->y * (T)obj.y;
	return *temp;
}
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator/(Vec2<U> &obj)
{
	Vec2<T> temp;
	temp.x = this->x / (T)obj.x;
	temp.y = this->y / (T)obj.y;
	return *temp;
}
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator+=(Vec2<U> &obj)
{
	this->x += (T)obj.x;
	this->y += (T)obj.y;
	return *this;
}
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator-=(Vec2<U> &obj)
{
	this->x -= (T)obj.x;
	this->y -= (T)obj.y;
	return *this;
}
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator*=(Vec2<U> &obj)
{
	this->x *= (T)obj.x;
	this->y *= (T)obj.y;
	return *this;
}
template<typename T> template<typename U>
h3d::Vec2<T>& h3d::Vec2<T>::operator/=(Vec2<U> &obj)
{
	this->x /= (T)obj.x;
	this->y /= (T)obj.y;
	return *this;
}
/////////////////////////////////////////////////////////////////
//	Functions
template<typename T>
T h3d::Vec2<T>::length()
{
	return sqrtf(powf(this->x, 2) + powf(this->y, 2));
}
/////////////////////////////////////////////////////////////////
//	h3d::Vec3 Funcs
/////////////////////////////////////////////////////////////////
// Operators
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator=(Vec3<U> &obj)
{
	this->x = (T)obj.x;
	this->y = (T)obj.y;
	this->z = (T)obj.z;
	return *this;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator+(Vec3<U> &obj)
{
	Vec3<T> temp;
	temp.x = this->x + (T)obj.x;
	temp.y = this->y + (T)obj.y;
	temp.z = this->z + (T)obj.z;
	return temp;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator-(Vec3<U> &obj)
{
	Vec3<T> temp;
	temp.x = this->x - (T)obj.x;
	temp.y = this->y - (T)obj.y;
	temp.z = this->z - (T)obj.z;
	return temp;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator*(Vec3<U> &obj)
{
	Vec3<T> temp;
	temp.x = this->x * (T)obj.x;
	temp.y = this->y * (T)obj.y;
	temp.z = this->z * (T)obj.z;
	return temp;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator/(Vec3<U> &obj)
{
	Vec3<T> temp;
	temp.x = this->x / (T)obj.x;
	temp.y = this->y / (T)obj.y;
	temp.z = this->z / (T)obj.z;
	return temp;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator+=(Vec3<U> &obj)
{
	this->x += (T)obj.x;
	this->y += (T)obj.y;
	this->z += (T)obj.z;
	return *this;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator-=(Vec3<U> &obj)
{
	this->x -= (T)obj.x;
	this->y -= (T)obj.y;
	this->z -= (T)obj.z;
	return *this;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator*=(Vec3<U> &obj)
{
	this->x *= (T)obj.x;
	this->y *= (T)obj.y;
	this->z *= (T)obj.z;
	return *this;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator/=(Vec3<U> &obj)
{
	this->x /= (T)obj.x;
	this->y /= (T)obj.y;
	this->z /= (T)obj.z;
	return *this;
}
/////////////////////////////////////////////////////////////////
//	Functions
template<typename T>
T h3d::Vec3<T>::length()
{
	return sqrtf(powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2));
}
/////////////////////////////////////////////////////////////////
template<typename T> h3d::Vec3<T>& h3d::Vec3<T>::normalize()
{
	T length_temp = length();
	Vec3<T> temp(this->x / length_temp,
				 this->y / length_temp,
				 this->z / length_temp);
	*this = temp;
	return *this;
}	
/////////////////////////////////////////////////////////////////
template<typename T> template<typename U> 
h3d::Vec3<T>& h3d::Vec3<T>::cross(h3d::Vec3<U> &obj)
{
	h3d::Vec3<T> temp;
	temp.x = (this->y*obj.z) - (this->z*obj.y);
	temp.y = (this->z*obj.x) - (this->x*obj.z);
	temp.z = (this->x*obj.y) - (this->y*obj.x);
	return temp;
}
/////////////////////////////////////////////////////////////////
//	Math Implementations 
/////////////////////////////////////////////////////////////////
template<typename T> h3d::Vec3<T> h3d::normalized(h3d::Vec3<T> vec)
{
	return h3d::Vec3<T>(vec.x / vec.length(),
						vec.y / vec.length(),
						vec.z / vec.length());
}
/////////////////////////////////////////////////////////////////
template<typename T> h3d::Vec3<T> h3d::cross(h3d::Vec3<T> vec_a,
										h3d::Vec3<T> vec_b)
{
	return h3d::Vec3<T>(vec_a.y * vec_b.z - vec_b.y * vec_a.z,
						vec_a.z * vec_b.x - vec_b.z * vec_a.x,
						vec_a.x * vec_b.y - vec_b.y * vec_a.x);
}
/////////////////////////////////////////////////////////////////
template<typename T> T h3d::dot(h3d::Vec3<T> vec_a,
								h3d::Vec3<T> vec_b)
{
	return T(vec_a.x*vec_b.x+ vec_a.y*vec_b.y+ vec_a.z*vec_b.z);
}
/////////////////////////////////////////////////////////////////