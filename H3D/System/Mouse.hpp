#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/System/Window.hpp"
namespace h3d{
/////////////////////////////////////////////////////////////////
// Mouse
/////////////////////////////////////////////////////////////////
class Mouse
{	
	struct impl;
	std::unique_ptr<impl> m_impl;
public:
	enum class H3D_API Button{
		Left = WM_LBUTTONDOWN,
		Middle=WM_MBUTTONDOWN,
		Right =WM_RBUTTONDOWN
	};

	static Vec2<float> H3D_API getPosition(const h3d::Window *win =
										   nullptr);
	static bool        H3D_API isButtonPressed(Button bud_id);
	static void		   H3D_API setCursorVisible(bool val);
};
/////////////////////////////////////////////////////////////////
}