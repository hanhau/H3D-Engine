#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
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

	public:
		globalLogger();
		~globalLogger();

		enum Output {
			CONSOLE, FILE
		};
		void setOutputMode(const int mode,char* param = NULL);

		const globalLogger& operator=(const globalLogger&) = delete;
	};

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