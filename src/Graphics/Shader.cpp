#include "../../H3D/Graphics/Shader.hpp"
#include <stdlib.h>
#include <sstream>
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/Utilities.hpp"
#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
//	Shader Implementation
/////////////////////////////////////////////////////////////////
static bool __glew_init = false;
h3d::Shader::Shader() :m_created(false),m_type(Type::Geometry)
{
	if (__glew_init == false) {
		glewExperimental = true;
		glewInit();
		__glew_init = true;
	}
}
h3d::Shader::Shader(Type type,GLchar code_path[]) :
	m_created(false),m_type(type),m_sourcecode(0),
	m_sourcecode_length(0)
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
		m_sourcecode_length = strlen(acode);
		m_sourcecode = new char[m_sourcecode_length];
		memcpy(m_sourcecode, acode, m_sourcecode_length);
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

		m_sourcecode = new char[fh.getFileSize()+1];
		fh.read(m_sourcecode, fh.getFileSize());
		m_sourcecode[fh.getFileSize()] = '\0';

		fh.close();
		return true;
	} 
}
void h3d::Shader::setType(Type type) { m_type = type;}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::compile()
{
	int shadertype = 0;
	switch (m_type) {
	case Type::Vertex: shadertype = GL_VERTEX_SHADER; break;
	case Type::Fragment: shadertype = GL_FRAGMENT_SHADER; break;
	case Type::Geometry: shadertype = GL_GEOMETRY_SHADER; break;
	case Type::Compute: shadertype = GL_COMPUTE_SHADER; break;
	case Type::TessControl: shadertype = GL_TESS_CONTROL_SHADER; break;
	case Type::TessEvaluation: shadertype = GL_TESS_EVALUATION_SHADER; break;
	}

	glDeleteShader(this->m_shaderid);
	this->m_shaderid = glCreateShader(shadertype);
	glShaderSource(m_shaderid, 1,(const char**)&m_sourcecode,
				   nullptr);

	glCompileShader(m_shaderid);

	if (h3d::DebugMode) 
	{
		GLint status;
		glGetShaderiv(this->m_shaderid, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) 
		{
			h3d::Log::error("Failed while compiling shader:");

			GLint length;
			glGetShaderiv(this->m_shaderid,
						  GL_INFO_LOG_LENGTH, &length);
			char *log = new char[length];
			glGetShaderInfoLog(this->m_shaderid, length, NULL, log);

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
	glGetShaderiv(m_shaderid, GL_COMPILE_STATUS, &compile_success);
	if (compile_success == GL_FALSE)
	{
		glGetShaderiv(m_shaderid, GL_INFO_LOG_LENGTH,&m_buildlog_length);
		m_buildlog = new GLchar[m_buildlog_length];
		glGetShaderInfoLog(m_shaderid, m_buildlog_length, NULL, m_buildlog);
	}
	else {
		m_buildlog = new GLchar[13];
		m_buildlog = "successfull!";
	}
}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::printBuildLog()
{
	if (m_buildlog == NULL)
		return false;
	else
		h3d::Log::info(m_buildlog);
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Shader::saveBuildLog(char Path[])
{
	if(m_buildlog == NULL)
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
		ss << "buildlog from shader " << m_shaderid << " : \n";
		ss << m_buildlog << "\n";
		
		fh.write((char*)ss.str().c_str(), ss.str().length());

		fh.close();
		return true;
	}
}
/////////////////////////////////////////////////////////////////