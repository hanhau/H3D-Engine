#include "../../H3D/System/Utilities.hpp"
#include "../../H3D/System/Config.hpp"
/////////////////////////////////////////////////////////////////
// Console Impls
/////////////////////////////////////////////////////////////////
#ifdef H3D_SYSTEM_WINDOWS

#include <Windows.h>
#include <consoleapi.h>
#include <cstdio>

#undef TRUE
#define TRUE 1
#undef STD_OUTPUT_HANDLE 
#define STD_OUTPUT_HANDLE ((DWORD)-11)

namespace h3d {
	void Console::open() {
		if (!AllocConsole()) {
			MessageBoxA(0, "Unable to open console", "ERROR", 0);
			h3dverify(false);
		}
	}
	void Console::resize(h3d::Vec2<int> size) {
		static COORD coord;
		coord.X = size.x;
		coord.Y = size.y;

		static _SMALL_RECT rect;
		rect.Top = 0;
		rect.Left = 0;
		rect.Bottom = size.y - 1;
		rect.Right = size.x - 1;

		const _SMALL_RECT minimal_rect = { 0,0,1,1 };

		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleWindowInfo(handle, TRUE, &minimal_rect);
		SetConsoleScreenBufferSize(handle, coord);
		SetConsoleWindowInfo(handle, TRUE, &rect);
	}
	void Console::close() {
		if (!FreeConsole()) {
			MessageBoxA(0, "Unable to open console", "ERROR", 0);
			h3dverify(false);
		}
	}
	void Console::setTitle(char title[]) {
		SetConsoleTitleA(title);
	}
	void Console::setCurPos(h3d::Vec2<int> pos) {
		COORD coord;
		coord.X = pos.x;
		coord.Y = pos.y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	namespace {
		static unsigned short __bckg_flags = 0;
		static unsigned short __text_flags = 0;
	}
	void Console::setBkgCol(unsigned short col) {
		__bckg_flags = col << 4;

		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, __bckg_flags | __text_flags);
	}
	void Console::setTextCol(unsigned short col) {
		__text_flags = col;

		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, __bckg_flags | __text_flags);
	}
	void Console::clear() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD target = { 0,0 };
		DWORD written;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
			&csbi);
		FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE),
			' ', csbi.dwSize.X * csbi.dwSize.Y,
			target, &written);
		FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			__bckg_flags | __text_flags,
			csbi.dwSize.X * csbi.dwSize.Y,
			target, &written);
		
		setCurPos({ 0,0 });
	}
	void Console::printInColor(unsigned short back,
							   unsigned short text,
							   const char str[]) {
		setTextCol(text);
		setBkgCol(back);

		printf_s(str);
	}
}
#elif 
#error "no linux"
#endif