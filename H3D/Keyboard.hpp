#pragma once

#include "Vector.hpp"
#include <Windows.h>
namespace h3d{
/////////////////////////////////////////////////////////////////
//	class Keyboard
/////////////////////////////////////////////////////////////////
static class  Keyboard
{
public:
	// Key enumerations
	// l = left,r = right
	static enum class Key
	{
		A = 0x41,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
		Num0 = 0x30,Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8,Num9,
		Arrow_Left = 0x25, Arrow_Up, Arrow_Right, Arrow_Down,
		Backspace = 0x08,TAB,Clear = 0x0C,Enter,Shift = 0x10,Ctrl,
		Alt,Pause,Capslock,ESC = 0x1B,
		Space = 0x20,Page_Up,Page_Down,End,Home,
		Select = 0x29,Print,Execute,Print_Screen,
		Delete = 0x2F,Help,
		Pad0=0x60,Pad1,Pad2,Pad3,Pad4,Pad5,Pad6,Pad7,Pad8,Pad9,
		F1=0x70,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
		lShift=0xA0,rShift,lControl,rControl,lMenu,rMenu,
	}Key;
	// Key pressing Check
	static bool isKeyPressed(int key_id);
}Keyboard;
/////////////////////////////////////////////////////////////////
}