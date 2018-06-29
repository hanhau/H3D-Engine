#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <map>
#include <vector>
#include <Windows.h>
#include <Mmsystem.h>
#include <fstream>
#include <hidsdi.h>

#include "Utilities.hpp"
#include "Vector.hpp"
/////////////////////////////////////////////////////////////////
//	Enumerations
/////////////////////////////////////////////////////////////////
namespace h3d {
	enum class DeviceType {
		Keyboard, Mouse, Joystick
	};
	enum class InputType {
		State, Action, Range
	};
}
#define DEVICE_TYPE_KEYBOARD   0b0000'0001
#define DEVICE_TYPE_MOUSE      0b0000'0010
#define DEVICE_TYPE_JOYSTICK   0b0000'0100

#define INPUT_TYPE_STATE       0b0001'0000
#define INPUT_TYPE_ACTION      0b0010'0000	   
#define INPUT_TYPE_RANGE	   0b0100'0000
/////////////////////////////////////////////////////////////////
//	Base Classes for HID Raw Devices
/////////////////////////////////////////////////////////////////
class _gch3d_HIDBaseClass
{
public:
	// Winapi Stuff
	RAWINPUTDEVICE m_rid;
	virtual void H3D_API setupRID(HWND win);
public:
	// Constructor
	_gch3d_HIDBaseClass(USHORT usage);
};
/////////////////////////////////////////////////////////////////
//	Input Devices
/////////////////////////////////////////////////////////////////
namespace h3d {
	class InputManager; // Forward Declaration
/////////////////////////////////////////////////////////////////	
//	Joystick/Gamepad
/////////////////////////////////////////////////////////////////
	class Joystick : private _gch3d_HIDBaseClass
	{
	private:
		// OS Information
		JOYCAPS        m_joycaps;
		JOYINFOEX      m_joyinfoex;
		char           m_ID;

		// Button struct
		class tagButton {
			bool m_pressed;
			int  m_id;
		public:
			bool isPressed();
		};

		// Axis struct
		struct tagAxis {
			float m_value;
			char  m_axisName;
		public:
			float getValue();
		};

		// Container 
		std::map<uint32_t, tagButton> m_buttonMap;
		std::map<char, tagAxis>       m_axisMap;
	public:
		// Constructors 
		H3D_API Joystick();
		H3D_API ~Joystick();

		// Setup 
		bool H3D_API setupJoystick();

		// get Information
		WORD  H3D_API getManufacturerID();
		WORD  H3D_API getProductIdentifier();
		WCHAR H3D_API getProductName();
		WCHAR H3D_API getRegistryKey();
		WCHAR H3D_API getDriverOEM();

		// get Boundaries/Nums
		UINT H3D_API getNumButtons();
		UINT H3D_API getNumAxes();
		
		// Check directly Buttons and Axis
		bool  H3D_API getButtonValue(int button_id);
		float H3D_API getAxisValue(int axis_id);

		// Update States 
		void update(PRAWINPUT rawdata);
	};
/////////////////////////////////////////////////////////////////
//	Class InputActions
/////////////////////////////////////////////////////////////////
class InputAction
	{
	private:
		// Name 
		std::string m_actionName;

		// Value and Type
		void	  *m_value;
		uint8_t    m_valueType;
		uint8_t    m_actionType;

		// Inputs
		std::vector<bool> m_joystickAxes;
		std::vector<bool> m_joystickButtons;
		std::vector<bool> m_mouseButtons;
		std::vector<bool> m_keyboardKeys;
		std::vector<std::string> m_bindingNames;

	public:
		// bind Keys etc to the Action
		void addInput();

		// update the Action
		void update();
	};
/////////////////////////////////////////////////////////////////
//	Class InputLayout
/////////////////////////////////////////////////////////////////
	class InputLayout
	{
	private:
		
	public:
		// Save and load from File
		static bool H3D_API loadFromFile(char Path[]);
		static bool H3D_API saveToFile  (char Path[]);
	};
/////////////////////////////////////////////////////////////////
//	Class InputManager
/////////////////////////////////////////////////////////////////
	class InputManager
	{
	private:
		// InputActionVector
		static std::vector<InputAction> m_inputActionVec;

		// RAW Input Device Setup Data
		static HWND				m_window;
		static RAWINPUTDEVICELIST *m_rawDeviceListPtr;
		static uint32_t			m_rawDeviceListSize;
		static uint32_t			m_numRawDevices;

		// Input Activation
		static bool m_mouseActive;
		static bool m_keyboardActive;
		static bool m_joystickActive;

		// Joystick/Gamepad Handling
		static std::map<unsigned char, Joystick> m_JoystickMap;
	public:		
		// Add bounded Actions
		static void H3D_API addInputAction(h3d::InputAction &action);

		// Activate/Deactivate Inputs
		static void H3D_API activateInput(uint8_t devType,bool val);
		static bool H3D_API isInputActive(uint8_t devType);
		
		// Processing Inputs
		static void H3D_API updateMouse();
		static void H3D_API updateKeyboard();
		static void H3D_API updateJoystick();

		// Setup Hardware
		static bool H3D_API setupHardware(HWND win);
	};
}
/////////////////////////////////////////////////////////////////