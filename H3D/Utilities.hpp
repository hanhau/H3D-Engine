#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
// h3dassert(x) only in debug mode
/////////////////////////////////////////////////////////////////
#ifdef H3D_DEBUG
#define h3dassert(x) {if(!!(x)) AssertFailed( __FILE__, std::to_string(__LINE__).c_str(),#x);}
#else
#define h3dassert(x) (x)
#endif
/////////////////////////////////////////////////////////////////
// h3dverify in release and debug mode
/////////////////////////////////////////////////////////////////
#define h3dverify(x) {if(!!(x)) VerifyFailed( __FILE__, std::to_string(__LINE__).c_str(),#x);}
/////////////////////////////////////////////////////////////////
// Functions to show Assert/Verify
/////////////////////////////////////////////////////////////////
void H3D_API AssertFailed(const char* file, const char* line, const char* expr);
void H3D_API VerifyFailed(const char* file, const char* line, const char* expr);
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <cstdio>
#include <mutex>
#include <cstdint>
// Lua
#include "externals.h"
#include STR(LUA_INCLUDE/lua.hpp)
/////////////////////////////////////////////////////////////////
// global Logger
/////////////////////////////////////////////////////////////////
namespace h3d {
	extern bool H3D_API DebugMode;
	enum class LogType {
		CONSOLE,FILE
	};
	class __Logger
	{
	private:
		static __Logger* m_instance;

		std::mutex m_fileMutex;
		FILE*      m_logFile;
		LogType    m_currentLogType;

		std::string H3D_API getCurrentTime();
	public:
		__Logger();
		~__Logger();

		// Set Logger Properties
		void H3D_API setLogType(h3d::LogType type);

		// Log Functions
		template<typename... Args>
		void error(char* msg, Args... args);
		template<typename... Args>
		void debug(char *msg, Args...args);		
		template<typename... Args>
		void info (char *msg, Args...args);
		template<typename... Args>
		void alarm(char *msg, Args...args);

		// costum tag log
		void costum(const char* tag,const char* str);

		// Get global Instance
		static __Logger& GetInstance();
	};
}
#define Log h3d::__Logger::GetInstance()
/////////////////////////////////////////////////////////////////
// Lua Log functions
extern "C" {
	int H3D_API luaLog_error(lua_State *lua);
	int H3D_API luaLog_debug(lua_State *lua);
	int H3D_API luaLog_info(lua_State *lua);
	int H3D_API luaLog_alarm(lua_State *lua);
}
/////////////////////////////////////////////////////////////////
// Log Functions
template<typename... Args>
void h3d::__Logger::error(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);
	logString.append(" [ERROR]: ");
	logString.append(msg);
	logString.append("\n");
	if (m_currentLogType == LogType::CONSOLE)
	{
		printf(logString.c_str(), args...);
	}
	else if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::__Logger::debug(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);
	logString.append(" [DEBUG]: ");
	logString.append(msg);
	logString.append("\n");
	if (m_currentLogType == LogType::CONSOLE)
	{
		printf(logString.c_str(), args...);
	}
	else if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::__Logger::info(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);
	logString.append(" [INFO]: ");
	logString.append(msg);
	logString.append("\n");
	if (m_currentLogType == LogType::CONSOLE)
	{
		printf(logString.c_str(), args...);
	}
	else if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::__Logger::alarm(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString)-1);
	logString.append(" [ALARM]: ");
	logString.append(msg);
	logString.append("\n");
	if (m_currentLogType == LogType::CONSOLE)
	{
		printf(logString.c_str(), args...);
	}
	else if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}