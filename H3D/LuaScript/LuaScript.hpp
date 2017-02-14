#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
// Lua Headers
#include <lua.hpp>
// Cpp Headers
#include <fstream>
#include <string>
// additional Stuff
#include "..\Utilities.hpp"
using h3d::__Logger;
/////////////////////////////////////////////////////////////////
// LuaScript Class
/////////////////////////////////////////////////////////////////
namespace lua {
	class Script final {
	private:
		lua_State   *m_luaState;
		std::string  m_Path;

		void init();
	public:
		H3D_API Script();
		H3D_API Script(char path[]);
		H3D_API ~Script();

		bool H3D_API loadFromFile(char path[]);
		bool H3D_API execute();
	};
}
/////////////////////////////////////////////////////////////////
