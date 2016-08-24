#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>;
/////////////////////////////////////////////////////////////////
// Shader class
/////////////////////////////////////////////////////////////////
namespace h3d{
	class Shader
	{
	private:
		// Sourcecode
		unsigned char* sourcecode;

		// Shadertype
		GLenum shadertype;
	public:
		// Constructor
		Shader();
		Shader(unsigned char* code);

		// change Code or Type
		void setCode();
		void setType();

		// Compile and use
		bool compile();
		bool use();

		// Compile Error Listing
		void printCompileLog();
		void saveCompileLog(char Path[]);

		// Deconstructor
		~Shader();
	};
}
/////////////////////////////////////////////////////////////////