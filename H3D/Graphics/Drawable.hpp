#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "../../H3D/MemoryMng/pool_alloc.hpp"
#include "../../H3D/Math/Vector.hpp"
#include "Texture.hpp"
#include "../../H3D/Model/3DModel.hpp"
#include "../../H3D/System/Window.hpp"

/////////////////////////////////////////////////////////////////
// Drawable
/////////////////////////////////////////////////////////////////
namespace h3d {
	typedef h3d::Vec3<h3d::Vec2<GLfloat>> AABB;

	class Drawable
	{
		AABB aabb;

		enum class Type {
			static_, dynamic_
		};
		Type type;

		//h3d::Texture tex;
		//h3d::Model3D model;
	public:
		Drawable();
		~Drawable();

		virtual void draw(h3d::Window &win) = 0;
	};
}
