#include "InputManager.hpp"
/////////////////////////////////////////////////////////////////
//	Implementation of InputManager Class
/////////////////////////////////////////////////////////////////
// global Variables
H3D_API h3d::tagKeyboard     h3d::Keyboard;
H3D_API h3d::tagMouse        h3d::Mouse;
H3D_API h3d::tagInputLayout  h3d::InputLayout;
/////////////////////////////////////////////////////////////////
void _gch3d_HIDBaseClass::setupRID(HWND win) {}
_gch3d_HIDBaseClass::_gch3d_HIDBaseClass(USHORT usage) {
	m_rid.usUsage = usage;
}
/////////////////////////////////////////////////////////////////
HWND				h3d::InputManager::m_window;
RAWINPUTDEVICELIST *h3d::InputManager::m_rawDeviceListPtr;
uint32_t			h3d::InputManager::m_rawDeviceListSize;
uint32_t			h3d::InputManager::m_numRawDevices;

bool h3d::InputManager::m_mouseActive;
bool h3d::InputManager::m_keyboardActive;
bool h3d::InputManager::m_joystickActive;
/////////////////////////////////////////////////////////////////
bool h3d::InputManager::isInputActive(uint8_t devType)
{
	switch (devType) {
		case DEVICE_TYPE_MOUSE: return m_mouseActive; break;
		case DEVICE_TYPE_KEYBOARD: return m_keyboardActive; break;
		case DEVICE_TYPE_JOYSTICK: return m_joystickActive; break;
		default: return false; break;
	}
}
/////////////////////////////////////////////////////////////////
bool h3d::InputManager::setupHardware(HWND win)
{
	// Enumerate connected RAW Devices
	if ((m_numRawDevices = GetRawInputDeviceList(m_rawDeviceListPtr,
												 &m_numRawDevices,
												 sizeof(RAWINPUTDEVICELIST))
		 ) != (UINT)-1)
	{
		if (h3d::DebugMode) {
			Log.error("Failed to get Device List %d",GetLastError());
		}
		return false;
	}

	// Initialize those devices
	return true;
}
/////////////////////////////////////////////////////////////////
//	Updating RAW Mouse Data
/////////////////////////////////////////////////////////////////
void h3d::InputManager::updateMouse()
{
	
}
/////////////////////////////////////////////////////////////////
//	Updating RAW Keyboard Data
/////////////////////////////////////////////////////////////////
void h3d::InputManager::updateKeyboard()
{

}
/////////////////////////////////////////////////////////////////
//	Updating RAW Joystick Data
/////////////////////////////////////////////////////////////////
void h3d::InputManager::updateJoystick()
{

}
/////////////////////////////////////////////////////////////////