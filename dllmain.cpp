// dllmain.cpp : Defines the entry point for the DLL application.
#include "H3D.hpp"
#include "H3D\externals.h"

#ifdef _WIN32 || _WIN64

#define GLEW_STATIC
#pragma comment(lib, STR(LUA_PATH/lib/lua 5.3.4.lib)) 
#pragma comment(lib, STR(OPENAL_PATH/libs/Win32/OpenAL32.lib)) 
#pragma comment(lib, STR(OGG_PATH/win32/VS2010/Win32/Debug/libogg_static.lib))
#pragma comment(lib, STR(LIBVORBIS_PATH/win32/VS2010/Win32/Release/libvorbis_static.lib))
#pragma comment(lib, STR(LIBVORBIS_PATH/win32/VS2010/Win32/Release/libvorbisfile_static.lib))
#pragma comment(lib, STR(GLEW_PATH/lib/Release/Win32/glew32.lib)) 
#pragma comment(lib, STR(FREETYPE_PATH/objs/vc2010/Win32/freetype27ST.lib))

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{	
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
};
#endif