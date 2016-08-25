#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API	_declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "Light.hpp"
#include "Vector.hpp"
#include <GL/glew.h>
#include <mutex>
#include <map>
/////////////////////////////////////////////////////////////////
//	GBuffer Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	class GeometryBuffer
	{
	private:
		// Pixel Size
		h3d::Vec2<unsigned int> m_size;

		// OGL Buffer IDs
		GLuint m_fbo;
		GLuint m_oglBuffer[6];
		std::map<int, std::tuple<GLuint,bool>> m_BufferOrderMap;
	public:
		// Con-/Destructor
		H3D_API GeometryBuffer();
		H3D_API ~GeometryBuffer();

		// Speficifier for Stage
		struct Stage
		{
			H3D_API static const int DIFFUSE	= 0b0000'0001;
			H3D_API static const int NORMAL		= 0b0000'0010;
			H3D_API static const int ALBEDO		= 0b0000'0100;
			H3D_API static const int POSITION	= 0b0000'1000;
			H3D_API static const int SPECULAR	= 0b0001'0000;
			H3D_API static const int DEPTH	    = 0b0010'0000;
			H3D_API static const int ALL		= 0b0011'1111;

			static const int MaxElementCount = 6;
		};

		// Operations
		void H3D_API setup(h3d::Vec2<unsigned int> size,int bitmask);
		
		void H3D_API bind();
		void H3D_API clear(int bitmask = Stage::ALL);

		GLint H3D_API getColorAttachmentOffset(const int stage);
	};
}
/////////////////////////////////////////////////////////////////