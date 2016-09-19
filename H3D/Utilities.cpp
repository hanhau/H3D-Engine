#include "Utilities.hpp"
#include <string>
/////////////////////////////////////////////////////////////////
// Implementation of Logger
/////////////////////////////////////////////////////////////////
h3d::globalLogger::globalLogger() {}
h3d::globalLogger::~globalLogger() {}
/////////////////////////////////////////////////////////////////
bool h3d::globalLogger::setOutputMode(const int mode, char* param)
{
	if ((m_currentType = mode) == Output::FILE)
		m_dataStream.open(param);
	if (!m_dataStream.is_open()) return false;
	else return true;
}
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
H3D_API h3d::tagDebugstream h3d::Debugstream;
H3D_API bool h3d::DebugMode;
/////////////////////////////////////////////////////////////////
//	Writing in the file with "<<" operator
template<typename T>
std::ostream& h3d::tagDebugstream::operator<<(T stream)
{
	file_stream << stream;
	return (std::ostream)0;
}
/////////////////////////////////////////////////////////////////
//	Instances of Operator
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(int);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(unsigned int);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(float);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(double);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(char*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(const char*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(char const*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(const char[]);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(std::string);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(void*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(std::streambuf*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<< (std::ostream& (*pf)(std::ostream&));
template H3D_API std::ostream& h3d::tagDebugstream::operator<< (std::ios& (*pf)(std::ios&));
template H3D_API std::ostream& h3d::tagDebugstream::operator<< (std::ios_base& (*pf)(std::ios_base&));
/////////////////////////////////////////////////////////////////
//	Closing/Opening file
bool h3d::tagDebugstream::open(const char* filename, std::ios_base::openmode mode)
{
	if (file_stream.is_open()) file_stream.close();
	file_stream.open(filename, mode | std::ios::ate);
	if (!file_stream.good()) return false;
	file_stream.rdbuf()->pubsetbuf(0, 0);
	return true;
}
void h3d::tagDebugstream::close()
{
	file_stream.close();
}
/////////////////////////////////////////////////////////////////
// DebugGraphicalText
/////////////////////////////////////////////////////////////////
// Static variables
h3d::Texture    h3d::DebugGraphicalText::m_fontTexture;
std::mutex      h3d::DebugGraphicalText::m_texMutex;
h3d::Program    h3d::DebugGraphicalText::m_programOGL;
std::mutex      h3d::DebugGraphicalText::m_programMutex;
bool			h3d::DebugGraphicalText::m_programConfigured = false;
/////////////////////////////////////////////////////////////////
h3d::DebugGraphicalText::DebugGraphicalText()
{
	std::lock_guard<std::mutex> lock(m_programMutex);
	if (!m_programConfigured)
	{
		GLchar vertexCode[] =
			"#version 330 core			\n"
			""
			""
			""
			"void main(){				\n"
			""
			""
			"}";

		GLchar fragmentCode[] =
			"#version 330 core\n"
			""
			"";

		h3d::Shader vertexShader  (GL_VERTEX_SHADER  , vertexCode), 
					fragmentShader(GL_FRAGMENT_SHADER, fragmentCode);

		m_programOGL.attachShader(vertexShader);
		m_programOGL.attachShader(fragmentShader);
		m_programOGL.link();
	}
}
h3d::DebugGraphicalText::~DebugGraphicalText() {}
/////////////////////////////////////////////////////////////////
void h3d::DebugGraphicalText::render()
{
	std::lock_guard<std::mutex> lock(m_texMutex);
	m_fontTexture.setActive(true);

	
}
/////////////////////////////////////////////////////////////////
void h3d::DebugGraphicalText::setBitmapFontTexture(const h3d::Texture& tex)
{
	std::lock_guard<std::mutex> lock(m_texMutex);
	m_fontTexture = tex;
}
/////////////////////////////////////////////////////////////////
