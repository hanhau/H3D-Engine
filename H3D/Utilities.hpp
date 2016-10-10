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
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "Color.hpp"
#include "Vector.hpp"
#include "Texture.hpp"
#include "Program.hpp"
#include "Vertex.hpp"
#include <gl/glew.h>
#include <atomic>
#include <mutex>
/////////////////////////////////////////////////////////////////
//	global Log File Names
/////////////////////////////////////////////////////////////////
#define DEBUG_LP_AUDIO  "audiolog.txt"
#define DEBUG_LP_WINDOW "windowlog.txt"
/////////////////////////////////////////////////////////////////
// global Debug-Mode
/////////////////////////////////////////////////////////////////
namespace h3d {
	template<typename T> class Color;

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
			CONSOLE, FILE, BITMAPFONT
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
	/////////////////////////////////////////////////////////////
	// Class for outputíng Bitmapfonts on the screen
	/////////////////////////////////////////////////////////////
	class DebugGraphicalText
	{
	private:
		static h3d::Texture m_fontTexture;
		static std::mutex   m_texMutex;
		static GLuint m_texture3DBuffer;
		static GLuint m_vertexBuffer;

		static h3d::Program m_programOGL;
		static std::mutex   m_programMutex;

		static bool m_programConfigured;
		
		h3d::Color<GLfloat> m_textColor;
		h3d::Vec2<GLfloat>  m_position;
		h3d::Vec2<GLfloat>  m_size;
		h3d::Vec2<GLuint>   m_grid;

		std::string       m_content;
		std::stringstream m_stringStream;
	public:
		// Con-/Destructor
		H3D_API DebugGraphicalText();
		H3D_API ~DebugGraphicalText();

		// Setup Textwindow
		void H3D_API setup(h3d::Vec2<GLfloat> size,
						   h3d::Vec2<GLfloat> pos,
						   h3d::Vec2<GLuint>  grid,
						   h3d::Color<GLfloat> col = h3d::Color<GLfloat>(0.0,0.0,0.0,1.0));

		// Set Content of String
		template<typename T>             
		void operator<<(T data) {
			m_stringStream << data;      
		}								 
		void H3D_API clear();

		// Operations
		void H3D_API setColor(h3d::Color<GLfloat> col_val);
		void H3D_API update();
		void H3D_API render();
		bool H3D_API setBitmapFontTexture(const h3d::Texture& tex);
	};
}
/////////////////////////////////////////////////////////////////