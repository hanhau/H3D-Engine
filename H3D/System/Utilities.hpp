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
void H3D_API AssertFailed(const char* file, const char* line, 
						  const char* expr);
void H3D_API VerifyFailed(const char* file, const char* line, 
						  const char* expr);
/////////////////////////////////////////////////////////////////
#include <iosfwd>
#include <iostream>
#include <string>
#include <mutex>
#include <cstdint>
#include "Vector.hpp"
/////////////////////////////////////////////////////////////////
// OS specific printf/scanf
#include "Config.hpp"
#ifdef H3D_SYSTEM_WINDOWS

#elif defined H3D_SYSTEM_LINUX

#endif
/////////////////////////////////////////////////////////////////
// Lua
#include "externals.h"
#include STR(LUA_INCLUDE/lua.hpp)
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
// Numerics
namespace h3d {
	class Window;
	namespace numeric {
		inline size_t kilobytes(size_t t) {
			return t * 1024;
		}
		inline size_t megabytes(size_t t) {
			return t * 1024 * 1024;
		}
		inline size_t gigabytes(size_t t) {
			return t * 1024 * 1024 * 1024;
		}
	}
}
/////////////////////////////////////////////////////////////////
// global Console
namespace h3d {
	class Console
	{
	public:
		struct Color {
			static const unsigned short Black = 0;
			static const unsigned short Red = 1 << 2;
			static const unsigned short Green = 1 << 1;
			static const unsigned short Blue = 1 << 0;

			static const unsigned short White = Red|Green|Blue|1<<3;
			static const unsigned short LightGray = Red|Green|Blue;
			static const unsigned short DarkGray = 1 << 3;

			static const unsigned short Cyan = Green | Blue;
			static const unsigned short Purple = Red | Blue;
			static const unsigned short Yellow = Red | Green;

			static const unsigned short IntenseRed    = Red|1<<3;
			static const unsigned short IntenseGreen  = Green|1<<3;
			static const unsigned short IntenseBlue   = Blue|1<<3;
			static const unsigned short IntenseCyan   = Cyan|1<<3;
			static const unsigned short IntensePurple = Purple|1<<3;
			static const unsigned short IntenseYellow = Yellow|1<<3;
		};

		static void H3D_API setTitle(char title[]);
		static void H3D_API setCurPos(h3d::Vec2<int> pos);
			
		static void H3D_API printInColor(unsigned short text,
									     unsigned short back,
										 const char str[]);

		static void H3D_API setBkgCol(unsigned short col);
		static void H3D_API setTextCol(unsigned short col);

		static void print(const char* str) {
			std::cout << str;
		}

		template<typename... Args, typename T>
		static void print(const char* str, T value, Args... args) {
			for (; *str != '\0'; str++) {
				if (*str == '%') {
					std::cout << value;
					printf(str + 2, args...);
					return;
				}
				std::cout << *str;
			}
		}

		static void H3D_API clear();

		static void H3D_API open();
		static void H3D_API resize(h3d::Vec2<int> size);
		static void H3D_API close();
	};
}
/////////////////////////////////////////////////////////////////
// global Logger
/////////////////////////////////////////////////////////////////
namespace h3d {
	extern bool H3D_API DebugMode;
	enum class LogType {
		CONSOLE,FILE
	};
	class Log
	{
	private:
		static std::mutex m_fileMutex;
		static FILE*      m_logFile;
		static LogType    H3D_API m_currentLogType;

		static H3D_API const std::string getCurrentTime();
	public:
		inline Log() {};
		inline ~Log() {};

		// Set Logger Properties
		static void H3D_API setLogType(h3d::LogType type);

		// Log Functions
		template<typename... Args>
		static void error(char*msg, Args... args);
		template<typename... Args>
		static void debug(char*msg, Args... args);
		template<typename... Args>
		static void info (char*msg, Args... args);
		template<typename... Args>
		static void alarm(char*msg, Args... args);
		template<typename... Args>
		static void opengl(char*msg, Args... args);
		template<typename... Args>
		static void subval(char*msg, Args... args);

		// costum tag log
		static void H3D_API costum(const char* tag,const char* str);

		// take Screenshot
		static void H3D_API screenshot(char folder[],h3d::Window& win);
	};
}
/////////////////////////////////////////////////////////////////
// Lua Log functions
extern "C"{
int H3D_API luaLog_error(lua_State *lua);
int H3D_API luaLog_debug(lua_State *lua);
int H3D_API luaLog_info(lua_State *lua);
int H3D_API luaLog_alarm(lua_State *lua);
}
/////////////////////////////////////////////////////////////////
class Uncopyable {
public:
	inline Uncopyable() {}
private:
	inline Uncopyable(const Uncopyable&) = delete;
	inline Uncopyable& operator=(const Uncopyable&) = delete;
};
/////////////////////////////////////////////////////////////////
// Log Functions
template<typename... Args>
void h3d::Log::error(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);

	if (m_currentLogType == LogType::CONSOLE) {
		Console::printInColor(Console::Color::DarkGray,
			Console::Color::White,
			logString.c_str());
		Console::printInColor(Console::Color::Black,
			Console::Color::IntenseRed,
			" [ERROR]: ");
		Console::setTextCol(Console::Color::Red);
		Console::print(msg, args...);
		Console::print("\n");
	}
	return;

	logString.append(" [ERROR]: ");
	logString.append(msg);
	logString.append("\n");

	if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::Log::debug(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);

	if (m_currentLogType == LogType::CONSOLE) {
		Console::printInColor(Console::Color::DarkGray,
			Console::Color::White,
			logString.c_str());
		Console::printInColor(Console::Color::Black,
			Console::Color::Yellow,
			" [DEBUG]: ");
		Console::setTextCol(Console::Color::White);
		Console::print(msg, args...);
		Console::print("\n");
	}
	return;

	logString.append(" [DEBUG]: ");
	logString.append(msg);
	logString.append("\n");

	if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::Log::info(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);

	if (m_currentLogType == LogType::CONSOLE) {
		Console::printInColor(Console::Color::DarkGray,
			Console::Color::White,
			logString.c_str());
		Console::printInColor(Console::Color::Black,
			Console::Color::IntenseGreen,
			" [!INFO]: ");
		Console::setTextCol(Console::Color::White);
		Console::print(msg, args...);
		Console::print("\n");
	}
	return;

	logString.append(" [!INFO]: ");
	logString.append(msg);
	logString.append("\n");

	if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::Log::alarm(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);

	if (m_currentLogType == LogType::CONSOLE) {
		Console::printInColor(Console::Color::DarkGray,
			Console::Color::White,
			logString.c_str());
		Console::printInColor(Console::Color::Black,
			Console::Color::IntensePurple,
			" [ALARM]: ");
		Console::setTextCol(Console::Color::IntensePurple);
		Console::print(msg, args...);
		Console::print("\n");
	}
	return;

	logString.append(" [ALARM]: ");
	logString.append(msg);
	logString.append("\n");

	if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::Log::opengl(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);

	if (m_currentLogType == LogType::CONSOLE) {
		Console::printInColor(Console::Color::DarkGray,
			Console::Color::White,
			logString.c_str());
		Console::printInColor(Console::Color::Black,
			Console::Color::IntenseBlue,
			" [OpenGL]: ");
		Console::setTextCol(Console::Color::White);
		Console::print(msg, args...);
	}
	return;

	logString.append(" [OpenGL]: ");
	logString.append(msg);
	logString.append("\n");

	if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
/////////////////////////////////////////////////////////////////
#undef APENTRY
#define APIENTRY _stdcall
void APIENTRY __opengl_callback_func(GLenum source, GLenum type,
	GLuint id, GLenum severity,
	GLsizei length, const GLchar* msg, const void* usr);