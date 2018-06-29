#include "../../H3D/Graphics/Shader.hpp"
#include <stdlib.h>
#include <sstream>
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/Utilities.hpp"
/////////////////////////////////////////////////////////////////
//	Shader Implementation
/////////////////////////////////////////////////////////////////
static bool __glew_init = false;
h3d::Shader::Shader() :created(false),shadertype(0)
{
	if (__glew_init == false) {
		glewExperimental = true;
		glewInit();
		__glew_init = true;
	}
}
h3d::Shader::Shader(GLenum type,GLchar code_path[]) :
	created(false),shadertype(0)
{
	setType(type); setCode(code_path);
}
h3d::Shader::~Shader()
{
	//glDeleteShader(shaderid);
}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::setCode(GLchar acode[])
{
	h3dassert(sizeof(*acode) == 0);
	if (acode[0] == '#')
	{
		sourcecode_length = strlen(acode);
		sourcecode = new char[sourcecode_length];
		memcpy(sourcecode, acode, sourcecode_length);
		return true;
	}
	else
	{
		h3d::Log::debug("Loading shader from: %s",acode);

		h3d::FileHandle fh;
		if (!fh.open(acode)) {
			if (h3d::DebugMode)
				Log::error("");
			return false;
		}

		sourcecode = new char[fh.getFileSize()+1];
		fh.read(sourcecode, fh.getFileSize());
		sourcecode[fh.getFileSize()] = '\0';

		fh.close();
		return true;
	} 
}
void h3d::Shader::setType(GLenum atype) 
{ 
	h3dverify(atype != GL_VERTEX_SHADER &&
			  atype != GL_FRAGMENT_SHADER &&
			  atype != GL_GEOMETRY_SHADER &&
			  atype != GL_COMPUTE_SHADER &&
			  atype != GL_TESS_CONTROL_SHADER &&
			  atype != GL_TESS_EVALUATION_SHADER);
	shadertype = atype; 
}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::compile()
{
	if (shadertype == 0)
		return false;
	glDeleteShader(this->shaderid);
	this->shaderid = glCreateShader(shadertype);
	glShaderSource(shaderid, 1,(const char**)&sourcecode,
				   nullptr);

	glCompileShader(shaderid);

	if (h3d::DebugMode) 
	{
		GLint status;
		glGetShaderiv(this->shaderid, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) 
		{
			h3d::Log::error("Failed while compiling shader:");

			GLint length;
			glGetShaderiv(this->shaderid,
						  GL_INFO_LOG_LENGTH, &length);
			char *log = new char[length];
			glGetShaderInfoLog(this->shaderid, length, NULL, log);

			h3d::Log::error("%s",log);

			return false;
		}
	}
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
		h3d::Log::info(buildlog);
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::saveBuildLog(char Path[])
{
	if(buildlog == NULL)
		return false;
	else
	{
		h3d::FileHandle fh;
		if (!fh.open(Path)) {
			if (h3d::DebugMode)
				h3d::Log::error("Unable to open %s", Path);
			return false;
		}
		if (h3d::DebugMode)
			h3d::Log::debug("Saving shader log %s", Path);

		std::stringstream ss;
		ss << "buildlog from shader " << shaderid << " : \n";
		ss << buildlog << "\n";
		
		fh.write((char*)ss.str().c_str(), ss.str().length());

		fh.close();
		return true;
	}
}
/////////////////////////////////////////////////////////////////