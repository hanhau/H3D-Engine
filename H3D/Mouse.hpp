#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "Vector.hpp"
#include "Window.hpp"
namespace h3d{
/////////////////////////////////////////////////////////////////
//	class Mouse
/////////////////////////////////////////////////////////////////
static class Mouse
{	
public:
	Mouse();
	~Mouse();

	enum class H3D_API Button{
		Left = WM_LBUTTONDOWN,
		Middle=WM_MBUTTONDOWN,
		Right =WM_RBUTTONDOWN
	};

	template<typename T>																																	 
	static Vec2<T>   H3D_API getPosition(h3d::Window *win);
	static bool      H3D_API isButtonPressed(int bud_id);
	static void		 H3D_API setCursorHide(bool val);
}Mouse;
/////////////////////////////////////////////////////////////////
}