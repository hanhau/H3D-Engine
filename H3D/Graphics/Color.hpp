#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <type_traits>
#include <Windows.h>
/////////////////////////////////////////////////////////////////
//	class Color
/////////////////////////////////////////////////////////////////
namespace h3d {
template<typename T>
class Color 
{
public:
	// red,green,blue,alpha
	T r, g, b, a;
	
	// Constructor
	Color() : r(0),g(0),b(0),a(0){};
	Color(T red, T green, T blue, T alpha) :
		r(red), g(green), b(blue), a(alpha) {};

	// Assigment and if needed, casting to 
	template<typename V, typename U>
	h3d::Color<V>& operator=(const h3d::Color<U>& other)
	{
		if((std::is_floating_point(other.r) && std::is_same(T,other.r)) ||
		    std::is_integral(other.r) && std::is_same(T, other.r))
		{ r = other.r; g = other.g;b = other.b;a = other.a;}
		else if(std::is_floating_point(T)) { 
			r = other.r / 256; g = other.g / 256;
			b = other.b / 256; a = other.a / 256;
		} else {
			r = other.r * 256; g = other.g * 256;
			b = other.b * 256; a = other.a * 256;
		}
		return *this;
	}
};}
/////////////////////////////////////////////////////////////////