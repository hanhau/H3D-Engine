#include "../../H3D/Graphics/Program.hpp"
#include "../../H3D/System/Utilities.hpp"

#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
// Program Implementation
/////////////////////////////////////////////////////////////////
h3d::Program::tagUniformOperations::tagUniformOperations(h3d::Program &prgm) : m_programRef(prgm){}
h3d::Program::tagUniformOperations::~tagUniformOperations() {}
/////////////////////////////////////////////////////////////////
h3d::Program::Program() : Uniform(*this), linked(false) {}
h3d::Program::~Program() {}
/////////////////////////////////////////////////////////////////
bool h3d::Program::attachShader(h3d::Shader &ashader)
{
	if (linked)
		return false;
	else
	{
		switch(ashader.m_type)
		{
		case Shader::Type::Vertex:
			vertexshader = std::make_unique<Shader>(ashader);
			break;
		case Shader::Type::Fragment:
			fragmentshader = std::make_unique<Shader>(ashader);
			break;
		case Shader::Type::Geometry:
			geometryshader = std::make_unique<Shader>(ashader);
			break;
		case Shader::Type::Compute:
			computeshader = std::make_unique<Shader>(ashader);
			break;
		case Shader::Type::TessControl:
			tesscontrolshader = std::make_unique<Shader>(ashader);
			break;
		case Shader::Type::TessEvaluation:
			tessevaluationshader = std::make_unique<Shader>(ashader);
			break;
		default: 
			return false; 
		}
	}
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Program::link()
{
	if (linked)
		return false;
	else
	{
		programid = glCreateProgram();
		if (vertexshader) {
			vertexshader->compile();
			glAttachShader(this->programid,vertexshader->m_shaderid);
		}
		if (fragmentshader) {
			fragmentshader->compile();
			glAttachShader(this->programid, fragmentshader->m_shaderid);
		}
		if (geometryshader) {
			geometryshader->compile();
			glAttachShader(this->programid,geometryshader->m_shaderid);
		}
		glLinkProgram(programid);
		GLint status;
		glGetProgramiv(programid, GL_LINK_STATUS, &status);
		if (status == GL_TRUE)
			return true;
		else {
			h3d::Log::error("Failed while linking shaders");

			GLint att_shaders, length;

			glGetProgramiv(this->programid, GL_ATTACHED_SHADERS,
						   &att_shaders);
			glGetProgramiv(this->programid, GL_INFO_LOG_LENGTH,
						   &length);
			std::string log;
			log.reserve(length);

			glGetProgramInfoLog(programid, length, 0,(char*)log.c_str());

			h3d::Log::error("Attached shaders: %d", att_shaders);
			h3d::Log::error("%s", log.c_str());

			return false;
		}
	}
}
/////////////////////////////////////////////////////////////////
void h3d::Program::use(bool yn)
{
	if (yn) glUseProgram(programid);
	else    glUseProgram(0);
}
/////////////////////////////////////////////////////////////////
GLuint h3d::Program::getID_GL()
{
	return this->programid;
}
/////////////////////////////////////////////////////////////////
void h3d::Program::clear()
{
	glDeleteProgram(programid);
	memset((void*)&vertexshader, 0, sizeof(vertexshader));
	linked = false;
}
/////////////////////////////////////////////////////////////////
// Uniform Operations
/////////////////////////////////////////////////////////////////
GLint h3d::Program::tagUniformOperations::getLocation(GLchar* name)
{
	return glGetUniformLocation(m_programRef.programid, name);
}
void h3d::Program::tagUniformOperations::deleteUniformEntry(GLint location)
{

}
/////////////////////////////////////////////////////////////////s
// SET METHODS
namespace h3d{ 
	void Program::tagUniformOperations::setMatrix4x4(h3d::mat4x4& mat, 
													 GLint location)
	{
		m_uniformMap[location] = std::tuple<GLuint, GLuint, void*>
		(_TYPE_MAT4X4_F,sizeof(mat),(void*)&mat);
	}
	void Program::tagUniformOperations::setUniform4f(h3d::Vec4& val, 
													 GLint location)
	{
		m_uniformMap[location] = std::tuple<GLuint, GLuint, void*>
		(_TYPE_VEC4F, sizeof(val),(void*)&val);
	}
	void Program::tagUniformOperations::setUniform3f(h3d::Vec3<float>& val, 
													 GLint location)
	{
		m_uniformMap[location] = std::tuple<GLuint, GLuint, void*>
		(_TYPE_VEC3F, sizeof(val), (void*)&val);
	}
	void Program::tagUniformOperations::setUniform2f(h3d::Vec2<float>& val, 
													 GLint location)
	{
		m_uniformMap[location] = std::tuple<GLuint, GLuint, void*>
		(_TYPE_VEC2F, sizeof(val), (void*)&val);
	}
	void Program::tagUniformOperations::setUniform1f(float val, 
													 GLint location)
	{
		m_uniformMap[location] = std::tuple<GLuint, GLuint, void*>
		(_TYPE_VEC1F, sizeof(val), (void*)&val);
	}
}
/////////////////////////////////////////////////////////////////
// GET METHODS
namespace h3d {
	mat4x4&      Program::tagUniformOperations::getMatrix4x4(GLint location)
	{
		if ((m_uniformMap.find(location) != m_uniformMap.end()) &&
			std::get<0>(m_uniformMap[location]) == _TYPE_MAT4X4_F) {
			std::tuple<GLuint, GLuint, void*> temp_tuple = m_uniformMap[location];
			return mat4x4(reinterpret_cast<mat4x4&>(std::get<2>(temp_tuple)));
		}
		else return mat4x4();
	}
	Vec4&        Program::tagUniformOperations::getUniform4f(GLint location)
	{
		if ((m_uniformMap.find(location) != m_uniformMap.end()) &&
			std::get<0>(m_uniformMap[location]) == _TYPE_VEC4F) {
			std::tuple<GLuint, GLuint, void*> temp_tuple = m_uniformMap[location];
			return Vec4(reinterpret_cast<Vec4&>(std::get<2>(temp_tuple)));
		}
		else return Vec4(0, 0, 0, 0);
	}
	Vec3<float>& Program::tagUniformOperations::getUniform3f(GLint location)
	{
		if ((m_uniformMap.find(location) != m_uniformMap.end()) &&
			std::get<0>(m_uniformMap[location]) == _TYPE_VEC3F) {
			std::tuple<GLuint, GLuint, void*> temp_tuple = m_uniformMap[location];
			return Vec3<float>(reinterpret_cast<Vec3<float>&>(std::get<2>(temp_tuple)));
		}
		else return Vec3<float>(0,0,0);
	}
	Vec2<float>& Program::tagUniformOperations::getUniform2f(GLint location)
	{
		if ((m_uniformMap.find(location) != m_uniformMap.end()) &&
			std::get<0>(m_uniformMap[location]) == _TYPE_VEC2F) {
			std::tuple<GLuint, GLuint, void*> temp_tuple = m_uniformMap[location];
			return Vec2<float>(reinterpret_cast<Vec2<float>&>(std::get<2>(temp_tuple)));
		}
		else return Vec2<float>(0, 0);
	}
	float        Program::tagUniformOperations::getUniform1f(GLint location)
	{
		if ((m_uniformMap.find(location) != m_uniformMap.end()) &&
			std::get<0>(m_uniformMap[location]) == _TYPE_VEC1F) {
			std::tuple<GLuint, GLuint, void*> temp_tuple = m_uniformMap[location];
			return float(reinterpret_cast<float&>(std::get<2>(temp_tuple)));
		}
		else return 0.0f;
	}
}
/////////////////////////////////////////////////////////////////
// Build Log Functions
/////////////////////////////////////////////////////////////////
void h3d::Program::printBuildLogs()
{
	vertexshader->printBuildLog();
	fragmentshader->printBuildLog();
	geometryshader->printBuildLog();
	computeshader->printBuildLog();
	tesscontrolshader->printBuildLog();
	tessevaluationshader->printBuildLog();
}
/////////////////////////////////////////////////////////////////
void h3d::Program::saveBuildLogs(char Path[])
{
	vertexshader->saveBuildLog(Path);
	fragmentshader->saveBuildLog(Path);
	geometryshader->saveBuildLog(Path);
	computeshader->saveBuildLog(Path);
	tesscontrolshader->saveBuildLog(Path);
	tessevaluationshader->saveBuildLog(Path);
}
/////////////////////////////////////////////////////////////////