#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
// define Type values for shader <=> h3d_api
#define _TYPE_MAT4X4_F 0b0000'0001 
#define _TYPE_VEC4F    0b0000'0010
#define _TYPE_VEC3F    0b0000'0011
#define _TYPE_VEC2F    0b0000'0100
#define _TYPE_VEC1F    0b0000'0101 
/////////////////////////////////////////////////////////////////
#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/Math/Matrix.hpp"
#include "Shader.hpp"
#include <vector>
#include <map>
#include <tuple>
#include <memory>

#include "../dep_lib_fwd.h"
/////////////////////////////////////////////////////////////////
//	Program class
/////////////////////////////////////////////////////////////////
namespace h3d{
	class Program
	{
	private:
		// OpenGL stuff
		bool linked;
		GLuint programid;

		std::unique_ptr<Shader> vertexshader;
		std::unique_ptr<Shader> fragmentshader;
		std::unique_ptr<Shader> geometryshader;
		std::unique_ptr<Shader> computeshader;
		std::unique_ptr<Shader> tesscontrolshader;
		std::unique_ptr<Shader> tessevaluationshader;
		
		// Provides Interface for Uniform Manipulation
		struct tagUniformOperations
		{
			friend Program;
		private:
			// Reference to the Program object
			const h3d::Program& m_programRef;

			// Maps to hold our values [key=location][val_type/val_size/val]
			std::map<GLint,std::tuple<GLuint,GLuint,void*>>m_uniformMap;

			// Helper Functions to store/load variables
			void storeObject(int type);
		public:
			// Con-/Destructor
			H3D_API tagUniformOperations(h3d::Program &prgm);

			// Basic Uniform Operations
			GLint H3D_API getLocation(GLchar* name);
			void  H3D_API deleteUniformEntry(GLint location);

			// set Uniform Variables
			void H3D_API setMatrix4x4(const h3d::mat4x4&		mat, GLchar* name);
			void H3D_API setMatrix4x4(const h3d::mat4x4&      mat, GLint location);
			void H3D_API setUniform4f(const h3d::Vec4&        val, GLchar* name);
			void H3D_API setUniform4f(const h3d::Vec4&        val, GLint location);
			void H3D_API setUniform3f(const h3d::Vec3<float>& val, GLchar* name);
			void H3D_API setUniform3f(const h3d::Vec3<float>& val, GLint location);
			void H3D_API setUniform2f(const h3d::Vec2<float>& val, GLchar* name);
			void H3D_API setUniform2f(const h3d::Vec2<float>& val, GLint location);
			void H3D_API setUniform1f(const float             val, GLchar* name);
			void H3D_API setUniform1f(const float             val, GLint location);

			void H3D_API setMatrix4x4v(const h3d::mat4x4* mats     , GLchar* name);
			void H3D_API setMatrix4x4v(const h3d::mat4x4* mats     , GLint location);
			void H3D_API setUniform4fv(const h3d::Vec4* vals       , GLchar* name);
			void H3D_API setUniform4fv(const h3d::Vec4* vals	   , GLint location);
			void H3D_API setUniform3fv(const h3d::Vec3<float>* vals, GLchar* name);
			void H3D_API setUniform3fv(const h3d::Vec3<float>* vals, GLint location);
			void H3D_API setUniform2fv(const h3d::Vec2<float>* vals, GLchar* name);
			void H3D_API setUniform2fv(const h3d::Vec2<float>* vals, GLint location);
			void H3D_API setUniform1fv(const float* vals, GLchar* name);
			void H3D_API setUniform1fv(const float* vals, GLint location);

			// get Uniform Variables
			H3D_API h3d::mat4x4&      getMatrix4x4(GLint location);
			H3D_API h3d::Vec4&        getUniform4f(GLint location);
			H3D_API h3d::Vec3<float>& getUniform3f(GLint location);
			H3D_API h3d::Vec2<float>& getUniform2f(GLint location);
			float             H3D_API getUniform1f(GLint location);
		};
	public:
		// Con-/Destructor
		H3D_API Program();

		// Resets the Program to be linked again
		H3D_API void clear();

		// Handy functions
		H3D_API bool attachShader(h3d::Shader &ashader);
		H3D_API bool link();
		H3D_API void use(bool yn = true);
		H3D_API GLuint getID_GL();

		// Uniform Operations
		tagUniformOperations Uniform;

		// Debug stuff
		H3D_API void printBuildLogs();
		H3D_API void saveBuildLogs(char Path[]);
	};
}
/////////////////////////////////////////////////////////////////