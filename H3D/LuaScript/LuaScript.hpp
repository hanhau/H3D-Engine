#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <ft2build.h>
#include FT_FREETYPE_H
#include <sol/sol.hpp>
#include <fstream>
#include <string>
#include <map>

#include "../../H3D/System/Utilities.hpp"
/////////////////////////////////////////////////////////////////
// LuaScript Class
/////////////////////////////////////////////////////////////////
namespace lua {
	class Script final {
	private:
		// Lua
		lua_State *m_state;
		sol::state       m_lua;
		sol::load_result m_loadResult;
		std::string      m_Path;
		std::string      m_code;
		
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
