#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
/////////////////////////////////////////////////////////////////
#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
// Shader class
/////////////////////////////////////////////////////////////////
namespace h3d{
	class Program;
	class Shader
	{
		friend Program;
	private:
		// Stuff for Building
		GLchar* sourcecode;
		GLint sourcecode_length;
		GLchar* buildlog;
		GLint buildlog_length;

		// OpenGL stuff
		bool created;
		GLenum shadertype;
		GLuint shaderid;
	public:
		// Constructor
		H3D_API Shader();
		H3D_API Shader(GLenum type,GLchar code_path[]);

		// change Code or Type
		H3D_API bool setCode(GLchar acode[]);
		H3D_API void setType(GLenum atype);

		// Compile
		H3D_API bool compile();

		// Compile Error Listing
		H3D_API void createBuildLog();
		H3D_API bool printBuildLog();
		H3D_API bool saveBuildLog(char Path[]);

		// Deconstructor
		H3D_API ~Shader();
	};
}
/////////////////////////////////////////////////////////////////