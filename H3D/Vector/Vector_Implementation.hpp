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
	this->x = T(obj.x);
	this->y = T(obj.y);
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
h3d::Vec3<T>& h3d::Vec3<T>::operator=(const Vec3<U> &obj)
{
	this->x = static_cast<T>(obj.x);
	this->y = static_cast<T>(obj.y);
	this->z = static_cast<T>(obj.z);
	return *this;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator+(const Vec3<U> &obj) const
{
	Vec3<T> temp;
	temp.x = this->x + static_cast<T>(obj.x);
	temp.y = this->y + static_cast<T>(obj.y);
	temp.z = this->z + static_cast<T>(obj.z);
	return temp;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator-(const Vec3<U> &obj) const
{
	Vec3<T> temp;
	temp.x = this->x + static_cast<T>(obj.x*-1);
	temp.y = this->y + static_cast<T>(obj.y*-1);
	temp.z = this->z + static_cast<T>(obj.z*-1);
	return temp;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator*(const Vec3<U> &obj) const
{
	Vec3<T> temp;
	temp.x = this->x * static_cast<T>(obj.x);
	temp.y = this->y * static_cast<T>(obj.y);
	temp.z = this->z * static_cast<T>(obj.z);
	return temp;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator/(const Vec3<U> &obj) const
{
	Vec3<T> temp;
	temp.x = this->x / static_cast<T>(obj.x);
	temp.y = this->y / static_cast<T>(obj.y);
	temp.z = this->z / static_cast<T>(obj.z);
	return temp;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator+=(const Vec3<U> &obj)
{
	this->x += static_cast<T>(obj.x);
	this->y += static_cast<T>(obj.y);
	this->z += static_cast<T>(obj.z);
	return *this;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator-=(const Vec3<U> &obj)
{
	this->x -= static_cast<T>(obj.x);
	this->y -= static_cast<T>(obj.y);
	this->z -= static_cast<T>(obj.z);
	return *this;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator*=(const Vec3<U> &obj)
{
	this->x *= static_cast<T>(obj.x);
	this->y *= static_cast<T>(obj.y);
	this->z *= static_cast<T>(obj.z);
	return *this;
}
template<typename T> template<typename U>
h3d::Vec3<T>& h3d::Vec3<T>::operator/=(const Vec3<U> &obj)
{
	this->x /= static_cast<T>(obj.x);
	this->y /= static_cast<T>(obj.y);
	this->z /= static_cast<T>(obj.z);
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
T h3d::Vec3<T>::cross(h3d::Vec3<U> &obj)
{
	return x * obj.x + y * obj.y + z * obj.z;
}
/////////////////////////////////////////////////////////////////
//	Math Implementations 
/////////////////////////////////////////////////////////////////
template<typename T> h3d::Vec3<T> h3d::negative(const h3d::Vec3<T>& vec) 
{
	return h3d::Vec3<T>(vec.x*-1, vec.y*-1, vec.z*-1);
}
/////////////////////////////////////////////////////////////////
template<typename T> h3d::Vec3<T> h3d::distance(const h3d::Vec3<T>& from,
												const h3d::Vec3<T>& to)
{
	return h3d::Vec3<T>(to.x-from.x,to.y-from.y,to.z-from.z);
}
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