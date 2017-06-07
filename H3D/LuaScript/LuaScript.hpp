#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
// Lua Headers
#include "..\externals.h"
#include STR(LUA_INCLUDE/lua.hpp)
#include STR(SOL2_INCLUDE/sol/sol.hpp)
// Cpp Headers
#include <fstream>
#include <string>
#include <map>
// additional Stuff
#include "..\Utilities.hpp"
/////////////////////////////////////////////////////////////////
// LuaScript Class
/////////////////////////////////////////////////////////////////
namespace lua {
	class Script final {
	private:
		// Lua
		sol::state       m_lua;
		sol::load_result m_loadResult;
		std::string      m_Path;
		
		// Managing "Namespaces" in Lua
		std::map<const char*,sol::table>  m_tableMap;
		
		// Internal
		void init();
	public:
		// Con-/Destructor
		H3D_API Script();
		H3D_API Script(char path[]);
		H3D_API ~Script();

		// Direct Access to sol2
		H3D_API sol::table& getTable(const char* name);
		H3D_API sol::state& getState();

		// Script Operations
		bool H3D_API loadFromMemory(char* mem);
		bool H3D_API loadFromFile(char path[]);
		bool H3D_API execute();
	};
}
/////////////////////////////////////////////////////////////////
