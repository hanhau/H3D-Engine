#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "memmng\pool_alloc.hpp"
#include "Vector.hpp"
#include "Texture.hpp"
#include "3DModel.hpp"

/////////////////////////////////////////////////////////////////
// Drawable
/////////////////////////////////////////////////////////////////
namespace h3d {
	struct AABB {
		Vec2<GLfloat> x_boundaries;
		Vec2<GLfloat> y_boundaries;
		Vec2<GLfloat> z_boundaries;
	};

	class Drawable
	{
		AABB aabb;

		enum class Type {
			static_, dynamic_
		};
		Type type;

		h3d::Texture &tex;
		h3d::Model3D &model;
	public:
	};
}
