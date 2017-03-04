#include "InputManager.hpp"
/////////////////////////////////////////////////////////////////
//	Implementation of InputManager Class
/////////////////////////////////////////////////////////////////
// global Variables
H3D_API h3d::tagKeyboard     h3d::Keyboard;
H3D_API h3d::tagMouse        h3d::Mouse;
H3D_API h3d::tagInputLayout  h3d::InputLayout;
H3D_API h3d::tagInputManager h3d::InputManager;
/////////////////////////////////////////////////////////////////
// Con-/Destructor
h3d::tagInputManager::tagInputManager() : m_InputLayout(InputLayout) {}
h3d::tagInputManager::~tagInputManager() {}
/////////////////////////////////////////////////////////////////
void _gch3d_HIDBaseClass::setupRID(HWND win) {}
_gch3d_HIDBaseClass::_gch3d_HIDBaseClass(USHORT usage) {
	m_rid.usUsage = usage;
}
/////////////////////////////////////////////////////////////////
const bool h3d::tagInputManager::isInputActive(uint8_t devType)
{
	switch (devType) {
		case DEVICE_TYPE_MOUSE: return m_mouseActive; break;
		case DEVICE_TYPE_KEYBOARD: return m_keyboardActive; break;
		case DEVICE_TYPE_JOYSTICK: return m_joystickActive; break;
		default: return false; break;
	}
}
/////////////////////////////////////////////////////////////////
bool h3d::tagInputManager::setupHardware(HWND win)
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
void h3d::tagInputManager::updateMouse()
{
	
}
/////////////////////////////////////////////////////////////////
//	Updating RAW Keyboard Data
/////////////////////////////////////////////////////////////////
void h3d::tagInputManager::updateKeyboard()
{

}
/////////////////////////////////////////////////////////////////
//	Updating RAW Joystick Data
/////////////////////////////////////////////////////////////////
void h3d::tagInputManager::updateJoystick()
{

}
/////////////////////////////////////////////////////////////////