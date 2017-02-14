#include "LuaScript.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of LuaScript Class
/////////////////////////////////////////////////////////////////
void lua::Script::init() {
	m_luaState = luaL_newstate();
    luaL_openlibs(m_luaState);

	// Load Lua Log functions
	lua_register(m_luaState, "log_error", luaLog_error);
	lua_register(m_luaState, "log_debug", luaLog_debug);
	lua_register(m_luaState, "log_info", luaLog_info);
	lua_register(m_luaState, "log_alarm", luaLog_alarm);
}
lua::Script::Script(){
	init();
}
lua::Script::Script(char path[]){
	init();
	loadFromFile(path);
}
lua::Script::~Script(){
	lua_close(m_luaState);
}
/////////////////////////////////////////////////////////////////
bool lua::Script::loadFromFile(char path[]) 
{
	m_Path = path;
	if (luaL_loadfile(m_luaState, path)) {
		Log.error("Unable to open Scriptfile located %s",path);
		return false;
	}
	// Return successfully
	return true;
}
/////////////////////////////////////////////////////////////////
bool lua::Script::execute()
{
	if (lua_pcall(m_luaState, 0, LUA_MULTRET, 0)) {
		Log.error("Unable to execute Lua Script %s",m_Path.c_str());
		return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////