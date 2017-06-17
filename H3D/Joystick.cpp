#include "InputManager.hpp"
#include "Utilities.hpp"
/////////////////////////////////////////////////////////////////
//	Joystick Implementations
/////////////////////////////////////////////////////////////////
h3d::Joystick::Joystick()  : _gch3d_HIDBaseClass(0x04) {}
h3d::Joystick::~Joystick() {}
/////////////////////////////////////////////////////////////////
bool __declspec(dllexport) h3d::Joystick::setupJoystick()
{
	m_joyinfoex.dwSize = sizeof(JOYINFOEX);
	m_joyinfoex.dwFlags = JOY_RETURNALL;

	if (joyGetDevCaps(m_ID, &m_joycaps, sizeof(JOYCAPS)) != JOYERR_NOERROR) {
		if (h3d::DebugMode) {
			Log.error("Failed to detect Joystick ID");
		}
		return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////
WORD  h3d::Joystick::getManufacturerID() {
	return m_joycaps.wMid;
}
WORD  h3d::Joystick::getProductIdentifier() {
	return m_joycaps.wPid;
}
WCHAR h3d::Joystick::getProductName() {
	return *m_joycaps.szPname;
}
WCHAR h3d::Joystick::getRegistryKey() {
	return *m_joycaps.szRegKey;
}
WCHAR h3d::Joystick::getDriverOEM() {
	return *m_joycaps.szOEMVxD;
}
/////////////////////////////////////////////////////////////////
UINT h3d::Joystick::getNumButtons() { return m_joycaps.wNumButtons; }
UINT h3d::Joystick::getNumAxes() { return m_joycaps.wNumAxes; }
/////////////////////////////////////////////////////////////////
bool h3d::Joystick::getButtonValue(int button_id) {
	return true;
}	
/////////////////////////////////////////////////////////////////
void h3d::Joystick::update(PRAWINPUT rawdata)
{
	joyGetPosEx(m_ID, &m_joyinfoex); 
}
/////////////////////////////////////////////////////////////////