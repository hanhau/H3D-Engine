#include "Utilities.hpp"
#include <time.h>
#include <cassert>
/////////////////////////////////////////////////////////////////
// Implementation of Logger
/////////////////////////////////////////////////////////////////
bool h3d::DebugMode;
/////////////////////////////////////////////////////////////////
h3d::__Logger::__Logger() :m_currentLogType(1) {}
h3d::__Logger::~__Logger() {}
/////////////////////////////////////////////////////////////////
void h3d::__Logger::setLogType(int type) {
	m_currentLogType = type;
}
/////////////////////////////////////////////////////////////////
std::string h3d::__Logger::getCurrentTime()
{
	std::string currTime;
	time_t now = time(0);
	currTime.assign(ctime(&now));
	currTime.erase(std::end(currTime));
	return currTime;
}
/////////////////////////////////////////////////////////////////
// Static global Instance
h3d::__Logger& h3d::__Logger::GetInstance()
{
	static __Logger instance;
	return instance;
}
/////////////////////////////////////////////////////////////////
// Lua implementation of log functions
/////////////////////////////////////////////////////////////////
int luaLog_error(lua_State *lua)
{
	h3d::__Logger::GetInstance().error((char*)lua_tostring(lua,1));
	return 0;
}
int luaLog_debug(lua_State *lua)
{
	h3d::__Logger::GetInstance().debug((char*)lua_tostring(lua, 1));
	return 0;
}
int luaLog_info(lua_State *lua)
{
	h3d::__Logger::GetInstance().info((char*)lua_tostring(lua, 1));
	return 0;
}
int luaLog_alarm(lua_State *lua)
{
	h3d::__Logger::GetInstance().alarm((char*)lua_tostring(lua, 1));
	return 0;
}
/////////////////////////////////////////////////////////////////