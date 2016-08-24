#pragma once

#include "Vector.hpp"
#include "Window.hpp"
namespace h3d{
/////////////////////////////////////////////////////////////////
//	class Mouse
/////////////////////////////////////////////////////////////////
static class Mouse
{	
public:
	_declspec(dllexport) Mouse();
	_declspec(dllexport) ~Mouse();

	enum class _declspec(dllexport) Button
	{Left = WM_LBUTTONDOWN,Middle=WM_MBUTTONDOWN,Right =WM_RBUTTONDOWN};

	template<typename T>
	static Vec2<T>   getPosition(h3d::Window *win);
	static bool      _declspec(dllexport) isButtonPressed(int bud_id);
	static void		 _declspec(dllexport) setCursorHide(bool val);
}Mouse;
/////////////////////////////////////////////////////////////////
}