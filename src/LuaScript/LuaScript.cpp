#include "../../H3D/LuaScript/LuaScript.hpp"
#include "../../H3D/System/FileSystem.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <sol/sol.hpp>
/////////////////////////////////////////////////////////////////
// Implementation of LuaScript Class
/////////////////////////////////////////////////////////////////
struct lua::Script::impl {
	lua_State		 *m_state;
	sol::state       m_lua;
	sol::load_result m_loadResult;
	std::string      m_Path;
	std::string      m_code;
	std::map<const char*, sol::table>  m_tableMap;
};
/////////////////////////////////////////////////////////////////
void lua::Script::init() {
	m_impl->m_state = luaL_newstate();
	m_impl->m_lua.open_libraries();
	
	// Load Lua Log functions
	m_impl->m_lua.set_function("log_error", luaLog_error);
	m_impl->m_lua.set_function("log_debug", luaLog_debug);
	m_impl->m_lua.set_function("log_info" , luaLog_info);
	m_impl->m_lua.set_function("log_alarm", luaLog_alarm);
}
/////////////////////////////////////////////////////////////////
lua::Script::Script(){
	init();
}
lua::Script::Script(char path[]){
	init();
	loadFromFile(path);
}
lua::Script::~Script(){
	m_impl->m_lua.~state();
}
/////////////////////////////////////////////////////////////////
/*
sol::table& lua::Script::getTable(const char* name){
	return m_impl->m_tableMap.at(name);
}
sol::state& lua::Script::getState(){
	return m_impl->m_lua;
}
*/
/////////////////////////////////////////////////////////////////
bool lua::Script::loadFromMemory(char *mem)
{
	m_impl->m_loadResult = m_impl->m_lua.load_buffer(mem, sizeof(mem), "script");
	if (m_impl->m_loadResult.valid()) return true;
	else return false;
}
bool lua::Script::loadFromFile(char path[]) 
{
	h3d::FileHandle fh;
	fh.open(path);

	size_t file_size = fh.getFileSize();
	m_impl->m_code.reserve(file_size);

	fh.read((char*)m_impl->m_code.c_str(), file_size);
	fh.close();

	m_impl->m_Path = path;
	m_impl->m_loadResult = m_impl->m_lua.load_file(path);
	if (m_impl->m_loadResult.valid()) return true;
	else return false;
}
/////////////////////////////////////////////////////////////////
bool lua::Script::execute()
{
	auto err = m_impl->m_loadResult();
	return true;
}
/////////////////////////////////////////////////////////////////