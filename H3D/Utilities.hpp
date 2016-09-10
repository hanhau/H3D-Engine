#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
/////////////////////////////////////////////////////////////////
//	global Log File Names
/////////////////////////////////////////////////////////////////
#define DEBUG_LP_AUDIO  "audiolog.txt"
#define DEBUG_LP_WINDOW "windowlog.txt"
/////////////////////////////////////////////////////////////////
// global Debug-Mode
/////////////////////////////////////////////////////////////////
namespace h3d {
	class globalLogger
	{
	private:
		int m_currentType;
		std::string m_actualLogPath;
		std::fstream m_dataStream;

	public:
		// Constructor/Destructor
		H3D_API globalLogger();
		H3D_API ~globalLogger();

		// Log function
		struct None {};
		template<typename T>
		struct LogData
		{
			typedef T type;
			type list;
		};
		void H3D_API log(LogData<None>());

		// Setting outputstream
		enum H3D_API Output {
			CONSOLE, FILE
		};											   
		bool H3D_API setOutputMode(const int mode,char* param = NULL);

		// Singleton stuff
		static globalLogger& GetInstance()
		{
			#ifdef DLL_EXPORT
				typedef globalLogger* (*GetGLFn)();
				HMODULE mod = GetModuleHandle(NULL);
				GetGLFn GetGL = (GetGLFn)::GetProcAddress(mod, "GetGL");
				globalLogger* Instance = GetGL();
				return *Instance;
			#else
				static globalLogger Instance;
				return Instance;
			#endif
		}
	};
    #define Logger globalLogger.GetInstance()

	class tagDebugstream
	{
	private:
		std::ofstream file_stream;
	public:
		// << Operator
		template<typename T>
		H3D_API std::ostream& operator<<(T stream);

		// Filehandling
		bool H3D_API open(const char* filename, std::ios_base::openmode mode = std::ios::out);
		void H3D_API close();
	};
	H3D_API extern tagDebugstream Debugstream;
	H3D_API extern bool DebugMode;
}
/////////////////////////////////////////////////////////////////