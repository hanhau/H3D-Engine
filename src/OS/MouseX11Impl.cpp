#include "Config.hpp"
#ifdef H3D_SYSTEM_LINUX

#include "Mouse.hpp"

struct h3d::Mouse::impl {

};

namespace h3d {
	Vec2<float> Mouse::getPosition(const Window *win)
	{
		return Vec2<float>();
	}

	bool Mouse::isButtonPressed(Mouse::Button bud_id)
	{
		return true;
	}

	void Mouse::setCursorVisible(bool val)
	{

	}
}

#endif