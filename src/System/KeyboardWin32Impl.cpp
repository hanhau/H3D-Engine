#include "../../H3D/System/Config.hpp"
#ifdef H3D_SYSTEM_WINDOWS

#include "../../H3D/System/Keyboard.hpp"
#include <Windows.h>

namespace {

}

int KeyToVK(h3d::Keyboard::Key key) {
	switch (key) {
	case h3d::Keyboard::Key::A: return 0x41;
	case h3d::Keyboard::Key::B: return 0x42;
	case h3d::Keyboard::Key::C: return 0x43;
	case h3d::Keyboard::Key::D: return 0x44;
	case h3d::Keyboard::Key::E: return 0x45;
	case h3d::Keyboard::Key::F: return 0x46;
	case h3d::Keyboard::Key::G: return 0x47;
	case h3d::Keyboard::Key::H: return 0x48;
	case h3d::Keyboard::Key::I: return 0x49;
	case h3d::Keyboard::Key::J: return 0x4A;
	case h3d::Keyboard::Key::K: return 0x4B;
	case h3d::Keyboard::Key::L: return 0x4C;
	case h3d::Keyboard::Key::M: return 0x4D;
	case h3d::Keyboard::Key::N: return 0x4E;
	case h3d::Keyboard::Key::O: return 0x4F;
	case h3d::Keyboard::Key::P: return 0x50;
	case h3d::Keyboard::Key::Q: return 0x51;
	case h3d::Keyboard::Key::R: return 0x52;
	case h3d::Keyboard::Key::S: return 0x53;
	case h3d::Keyboard::Key::T: return 0x54;
	case h3d::Keyboard::Key::U: return 0x55;
	case h3d::Keyboard::Key::V: return 0x56;
	case h3d::Keyboard::Key::W: return 0x57;
	case h3d::Keyboard::Key::X: return 0x58;
	case h3d::Keyboard::Key::Y: return 0x59;
	case h3d::Keyboard::Key::Z: return 0x5A;

	}
}

namespace h3d {
	bool Keyboard::isKeyPressed(Keyboard::Key key)
	{
		int vk_val = KeyToVK(key);
		if (1 << 15 == GetAsyncKeyState(vk_val))
			return true;
		else
			return false;
	}
}


#endif