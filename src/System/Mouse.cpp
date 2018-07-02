//#include "InputManager.hpp"
//#include "InputManager.hpp"
/////////////////////////////////////////////////////////////////
//	Implementation of Mouse Class
/////////////////////////////////////////////////////////////////
/*d::tagMouse::tagMouse() : _gch3d_HIDBaseClass(0x0) {}
h3d::tagMouse::~tagMouse() {}
/////////////////////////////////////////////////////////////////
void h3d::tagMouse::setupRID(HWND win)
{
	m_rid.usUsagePage = 1;
	m_rid.usUsage = 4;
	m_rid.dwFlags = 0;
	m_rid.hwndTarget = win;
	
	if (!RegisterRawInputDevices(&m_rid, 1, sizeof(RAWINPUTDEVICE))){
		if (h3d::DebugMode)		{
			h3d::Log::alarm("Unable to register Mouse");
		}
	}
}
/////////////////////////////////////////////////////////////////
h3d::Vec2<LONG> h3d::tagMouse::getPosition(HWND window)
{
	static LPPOINT lp = new POINT();
	GetCursorPos(lp);
	return h3d::Vec2<LONG>((*lp).x,(*lp).y);
}
h3d::Vec2<LONG> h3d::tagMouse::getOffsetFromLastPos()
{
	return h3d::Vec2<LONG>();
}
///////////////////////////////////////////////////////////////// 
*/