#include "../../H3D/LuaScript/LuaScript.hpp"
#include "../../H3D/System/FileSystem.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of LuaScript Class
/////////////////////////////////////////////////////////////////
void lua::Script::init() {
	m_state = luaL_newstate();

	m_lua.open_libraries();
	
	// Load Lua Log functions
	m_lua.set_function("log_error", luaLog_error);
	m_lua.set_function("log_debug", luaLog_debug);
	m_lua.set_function("log_info" , luaLog_info);
	m_lua.set_function("log_alarm", luaLog_alarm);
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
	m_lua.~state();
}
/////////////////////////////////////////////////////////////////
sol::table& lua::Script::getTable(const char* name){
	return m_tableMap.at(name);	
}
sol::state& lua::Script::getState(){
	return m_lua;
}
/////////////////////////////////////////////////////////////////
bool lua::Script::loadFromMemory(char *mem)
{
	m_loadResult = m_lua.load_buffer(mem, sizeof(mem), "script");
	if (m_loadResult.valid()) return true;
	else return false;
}
bool lua::Script::loadFromFile(char path[]) 
{
	h3d::FileHandle fh;
	fh.open(path);

	size_t file_size = fh.getFileSize();
	m_code.reserve(file_size);

	fh.read((char*)m_code.c_str(), file_size);
	fh.close();

	m_Path = path;
	m_loadResult = m_lua.load_file(path);
	if (m_loadResult.valid()) return true;
	else return false;
}
/////////////////////////////////////////////////////////////////
bool lua::Script::execute()
{
	auto err = m_loadResult();
	return true;
}
/////////////////////////////////////////////////////////////////