#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "../dep_lib_fwd.h"
/////////////////////////////////////////////////////////////////
// Shader class
/////////////////////////////////////////////////////////////////
namespace h3d{
	class Program;
	class Shader
	{
	public:
		enum class Type {
		Vertex, Fragment,
		Geometry, Compute,
		TessControl, TessEvaluation
	};
	private:
		friend Program;

		GLchar* m_sourcecode;
		GLint m_sourcecode_length;
		GLchar* m_buildlog;
		GLint m_buildlog_length;

		bool m_created;
		GLuint m_shaderid;
		Type m_type;
	public:
		// Constructor
		H3D_API Shader();
		H3D_API Shader(Type type,GLchar code_path[]);

		// change Code or Type
		H3D_API bool setCode(GLchar acode[]);
		H3D_API void setType(Type type);

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