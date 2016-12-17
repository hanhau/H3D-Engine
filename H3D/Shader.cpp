#include "Shader.hpp"
#include <iostream>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////
//	Shader Implementation
/////////////////////////////////////////////////////////////////
h3d::Shader::Shader() :created(false),shadertype(0){}
h3d::Shader::Shader(GLenum type,GLchar code_path[])
{
	setType(type); setCode(code_path);
}
h3d::Shader::~Shader()
{
	glDeleteShader(shaderid);
}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::setCode(GLchar acode[])
{
	if (sizeof(*acode) == 0) return false;
	if (acode[0] == '#')
	{
		sourcecode_length = strlen(acode);
		sourcecode = new char[sourcecode_length];
		memcpy(sourcecode, acode, sourcecode_length);
		return true;
	}
	else
	{
		std::ifstream file;
		int file_size;
		file.open(acode,std::ios::in|std::ios::ate);
		if (!file.is_open()) return false;

		file_size = (int)file.tellg();
		sourcecode_length = file_size;
		sourcecode = new char[sourcecode_length];

		file.seekg(std::ios::beg, 0);
		file.read((char*)&sourcecode,sourcecode_length);

		file.close();
		return true;
	} 
}
void h3d::Shader::setType(GLenum atype) { shadertype = atype; }
/////////////////////////////////////////////////////////////////
bool h3d::Shader::compile()
{
	if (shadertype == 0)
		return false;
	glDeleteShader(this->shaderid);
	this->shaderid = glCreateShader(shadertype);
	glShaderSource(shaderid, 1,(const char**)&sourcecode,&sourcecode_length);

	glCompileShader(shaderid);
	return true;
}
/////////////////////////////////////////////////////////////////
void h3d::Shader::createBuildLog()
{
	GLint compile_success = 0;
	glGetShaderiv(shaderid, GL_COMPILE_STATUS, &compile_success);
	if (compile_success == GL_FALSE)
	{
		glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH,&buildlog_length);
		buildlog = new GLchar[buildlog_length];
		glGetShaderInfoLog(shaderid, buildlog_length, NULL, buildlog);
	}
	else {
		buildlog = new GLchar[13];
		buildlog = "successfull!";
	}
}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::printBuildLog()
{
	if (buildlog == NULL)
		return false;
	else
		std::cout << buildlog << std::endl;
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::saveBuildLog(char Path[])
{
	if(buildlog == NULL)
		return false;
	else
	{
		std::ofstream file;
		file.open(Path, std::ios::out | std::ios::app);
		if (!file.is_open()) return false;
		
		file << "BuildLog from Shader: " << shaderid << " : " << std::endl;
		file << buildlog << std::endl;

		file.close();
		return true;
	}
}
/////////////////////////////////////////////////////////////////