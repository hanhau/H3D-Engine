#include <cassert>
#include <sstream>
#include <stdlib.h>

#include "../../H3D/System/Utilities.hpp"
#include "../../H3D/System/Window.hpp"
#include "../../H3D/System/FileDataStructures.hpp"
#include "../../H3D/System/FileSystem.hpp"

#include "../../H3D/System/Config.hpp"
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
/////////////////////////////////////////////////////////////////
#ifdef H3D_SYSTEM_WINDOWS
const std::string h3d::Log::getCurrentTime()
{
	std::string currTime;
	time_t now = time(0);
	currTime.assign(ctime(&now));
	currTime.erase(std::end(currTime)-1);
	currTime.push_back('\0');
	return currTime;
}
#elif defined H3D_SYSTEM_LINUX
const std::string h3d::Log::getCurrentTime()
{
	return "no time func";
}
#endif
/////////////////////////////////////////////////////////////////
// Assertion 
void AssertFailed(const char* file, const char* line, const char* expr)
{
	std::string str("accured at: " + std::string(line) +
					" in file '" + std::string(file) + 
					"' with the expression: " + std::string(expr));
	h3d::Log::costum("H3D-ASSERT", str.c_str());
}
// Verify
void VerifyFailed(const char* file, const char* line, const char* expr)
{
	std::string str("accured at: " + std::string(line) +
					" in file '" + std::string(file) +
					"' with the expression: " + std::string(expr));
	h3d::Log::costum("H3D-VERIFY", str.c_str());
}
/////////////////////////////////////////////////////////////////
// Implementation of Logger
/////////////////////////////////////////////////////////////////
bool h3d::DebugMode = false;

std::mutex h3d::Log::m_fileMutex;
FILE* h3d::Log:: m_logFile = nullptr;
h3d::LogType h3d::Log::m_currentLogType = h3d::LogType::CONSOLE;
/////////////////////////////////////////////////////////////////
void h3d::Log::setLogType(h3d::LogType type) {
	m_currentLogType = type;
}
/////////////////////////////////////////////////////////////////
// costum tag log
void h3d::Log::costum(const char* tag, const char* str)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);
	logString.append(" [" + std::string(tag) + "]: ");
	logString.append(str);
	logString.append("\n");
	if (m_currentLogType == LogType::CONSOLE)
	{
		printf(logString.c_str());
	}
	else if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str());
	}
}
/////////////////////////////////////////////////////////////////
// Lua implementation of log functions
/////////////////////////////////////////////////////////////////
extern "C" {
	int luaLog_error(lua_State *lua)
	{
		h3d::Log::error((char*)lua_tostring(lua, 1));
		return 0;
	}
	int luaLog_debug(lua_State *lua)
	{
		h3d::Log::debug((char*)lua_tostring(lua, 1));
		return 0;
	}
	int luaLog_info(lua_State *lua)
	{
		h3d::Log::info((char*)lua_tostring(lua, 1));
		return 0;
	}
	int luaLog_alarm(lua_State *lua)
	{
		h3d::Log::alarm((char*)lua_tostring(lua, 1));
		return 0;
	}
}
/////////////////////////////////////////////////////////////////
// Take Screenshot
void h3d::Log::screenshot(char folder[], h3d::Window& win) 
{
	std::string path = std::string(folder) + "shot " + (char*)h3d::Log::getCurrentTime().c_str() + ".bmp";
	std::replace(path.begin(), path.end(), ':', '_');
	if (h3d::DebugMode)
		h3d::Log::info("Saving Screenshot '%s'", path.c_str());

	h3d::Vec2<int> size = win.getSize();
	h3d::FileType::BMP::Header t_header = { 0 };
	h3d::FileType::BMP::Body t_body = { 0 };

	uint8_t * pixels = new uint8_t[size.x*size.y*3];
	glReadPixels(0, 0, size.x, size.y, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	t_header.bfType = 19778;
	t_header.bfReserved = 0;
	t_header.bfOffBits = sizeof(t_header) + sizeof(t_body);
	t_header.bfsize = size.x*size.y * 3 + sizeof(t_header) + sizeof(t_body);

	t_body.biWidth = size.x;
	t_body.biHeight = size.y;
	t_body.biPlanes = 1;
	t_body.biBitCount = 24;
	t_body.biCompression = 0;
	t_body.biSizeImage = 0;
	t_body.biSize = sizeof(t_body);
	t_body.biXPelsPerMeter = 72;
	t_body.biYPelsPerMeter = 72;

	// Check content of header and body
	h3d::Log::debug("bfType    = %s", t_header.bfType);
	h3d::Log::debug("bfOffBits = %d", t_header.bfOffBits);
	h3d::Log::debug("bfsize    = %d", t_header.bfsize);

	h3d::Log::debug("biWidth     = %d",t_body.biWidth);
	h3d::Log::debug("biHeight    = %d",t_body.biHeight);
	h3d::Log::debug("biBitCount  = %d", t_body.biBitCount);
	h3d::Log::debug("biSizeImage = %d", t_body.biSizeImage);
	h3d::Log::debug("biSize      = %d", t_body.biSize);

	h3d::FileHandle fh;
	if (fh.open(path) == false) {
		h3d::Log::error("Unable to save screenshot to %s", path.c_str());
		return;
	}
	
	fh.write((char*)&t_header, sizeof(t_header));
	fh.write((char*)&t_body, sizeof(t_body));
	fh.write((char*)pixels, size.x*size.y * 3);
	
	delete[] pixels;
	fh.close();
}
/////////////////////////////////////////////////////////////////
