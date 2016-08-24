#include "InputManager.hpp"
/////////////////////////////////////////////////////////////////
//	Implementation of Mouse Class
/////////////////////////////////////////////////////////////////
h3d::tagMouse::tagMouse() : _gch3d_HIDBaseClass(0x0) {}
h3d::tagMouse::~tagMouse() {}
/////////////////////////////////////////////////////////////////
void h3d::tagMouse::setupRID(HWND win)
{
	m_rid.usUsagePage = 1;
	m_rid.usUsage = 4; // Joystick
	m_rid.dwFlags = 0;
	m_rid.hwndTarget = win;
	
	try
	{
		if (!RegisterRawInputDevices(&m_rid, 1, sizeof(RAWINPUTDEVICE)))
			throw "Couldn´t register Mouse";
	}
	catch (std::string str) {
		if (h3d::DebugMode) {
			h3d::Debugstream.open("input_log.txt");
			h3d::Debugstream << str << "\n";
			h3d::Debugstream.close();
		}
	}
}
/////////////////////////////////////////////////////////////////