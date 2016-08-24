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
		GLuint m_positionGL,
			   m_specularGL,
			   m_normalGL,
			   m_albedoGL;
	public:
		// Con-/Destructor
		H3D_API GeometryBuffer();
		H3D_API ~GeometryBuffer();

		// Speficifier for Stage
		struct Stage
		{
			static const int ALL = 0;
			static const int COLOR = 1;
			static const int NORMAL = 2;
			static const int ALBEDO = 3;
			static const int POSITION = 4;
			static const int SPECULAR = 5;
			static const int ZBUFFER = 6;
		};

		// Operations
		void H3D_API setup(h3d::Vec2<unsigned int> size);
		
		void H3D_API bindBuffer(int stage);
		void H3D_API clear(int stage = 0);
	};
}
/////////////////////////////////////////////////////////////////