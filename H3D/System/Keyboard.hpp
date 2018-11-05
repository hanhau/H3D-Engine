#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

namespace h3d{
/////////////////////////////////////////////////////////////////
//	class Keyboard
/////////////////////////////////////////////////////////////////
class Keyboard
{
public:
	enum class Key
	{
		A,B,C,D,E,F,G,
		H,I,J,K,L,M,N,
		O,P,Q,R,S,T,U,
		V,W,X,Y,Z,

		Num0,Num1,Num2,
		Num3,Num4,Num5,
		Num6,Num7,Num8,
		Num9,

		Arrow_Left, Arrow_Up, Arrow_Right, Arrow_Down,

		Backspace,TAB,Clear,Enter,Shift,Ctrl,

		Alt,Pause,Capslock,ESC,

		Space,Page_Up,Page_Down,End,Home,

		Select,Print,Execute,Print_Screen,
		Delete,Help,

		Pad0,Pad1,Pad2,
		Pad3,Pad4,Pad5,
		Pad6,Pad7,Pad8,
		Pad9,
		
		F1,F2,F3,F4,
		F5,F6,F7,F8,
		F9,F10,F11,F12,

		lShift,rShift,
		lControl,rControl,
		lMenu,rMenu,
	};
	
	static bool isKeyPressed(Key key);
};
/////////////////////////////////////////////////////////////////
}