#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdio>
#include <mutex>
/////////////////////////////////////////////////////////////////
// global Logger
/////////////////////////////////////////////////////////////////
namespace h3d {
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
}
/////////////////////////////////////////////////////////////////