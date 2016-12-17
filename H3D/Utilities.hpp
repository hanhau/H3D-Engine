#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <cstdio>
#include <mutex>
/////////////////////////////////////////////////////////////////
// global Logger
/////////////////////////////////////////////////////////////////
namespace h3d {
	static bool DebugMode;
	class __Logger
	{
	private:
		static __Logger* m_instance;

		std::mutex m_fileMutex;
		FILE*      m_logFile;
		int        m_currentLogType;

		std::string getCurrentTime();
	public:
		__Logger();
		~__Logger();
		
		// Log Types
		typedef enum LOG_TYPES
		{
			CONSOLE = 1,
			FILE    = 2
		}LogTypes;

		// Set Logger Properties
		void H3D_API setLogType();

		// Log Functions
		template<typename... Args>
		void error(char* msg, Args... args);
		template<typename... Args>
		void debug(char *msg, Args...args);		
		template<typename... Args>
		void info (char *msg, Args...args);
		template<typename... Args>
		void alarm(char *msg, Args...args);

		// Get global Instance
		static __Logger& GetInstance();
	};
#define Log __Logger::GetInstance()
#define LOG_ERROR(x) __Logger::GetInstance().error(x)
}
/////////////////////////////////////////////////////////////////
// Log Functions
template<typename... Args>
void h3d::__Logger::error(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.append(" [ERROR]: ");
	logString.append(msg);
	logString.append("\n");
	if (m_currentLogType == LogTypes::CONSOLE)
	{
		printf(logString.c_str(), args...);
	}
	else if (m_currentLogType == LogTypes::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::__Logger::debug(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.append(" [DEBUG]: ");
	logString.append(msg);
	logString.append("\n");
	if (m_currentLogType == LogTypes::CONSOLE)
	{
		printf(logString.c_str(), args...);
	}
	else if (m_currentLogType == LogTypes::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::__Logger::info(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.append(" [INFO]: ");
	logString.append(msg);
	logString.append("\n");
	if (m_currentLogType == LogTypes::CONSOLE)
	{
		printf(logString.c_str(), args...);
	}
	else if (m_currentLogType == LogTypes::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}
template<typename... Args>
void h3d::__Logger::alarm(char* msg, Args... args)
{
	std::string logString(getCurrentTime());
	logString.append(" [ALARM]: ");
	logString.append(msg);
	logString.append("\n");
	if (m_currentLogType == LogTypes::CONSOLE)
	{
		printf(logString.c_str(), args...);
	}
	else if (m_currentLogType == LogTypes::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str(), args...);
	}
}