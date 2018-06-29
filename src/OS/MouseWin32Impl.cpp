#include "Config.hpp"
#ifdef H3D_SYSTEM_WINDOWS

#include "Mouse.hpp"
#include <windows.h>

struct h3d::Mouse::impl {
	
};

namespace h3d {
	Vec2<float> Mouse::getPosition(const Window *win)
	{
		if (win == nullptr){
			POINT point;
			GetCursorPos(&point);
			return Vec2<float>(point.x,point.y);
		}
		else {
			return Vec2<float>();
		}
	}

	bool Mouse::isButtonPressed(Mouse::Button bud_id)
	{
		return true;
	}

	void Mouse::setCursorVisible(bool val)
	{
		if (val)
			SetCursor(GetCursor());
		else
			SetCursor(0);
	}
}
#endif