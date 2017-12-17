#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "Vector.hpp"
#include "Quaternion.hpp"

namespace h3d {
	struct AABBCube {
		h3d::Vec2<float> m_zRange;
		h3d::Vec2<float> m_yRange;
		h3d::Vec2<float> m_xRange;
	};

	class PhysicObject
	{
	private:
		AABBCube m_aabbCube;

		float m_mass;

		h3d::Vec3<float> m_pos;
		h3d::Vec3<float> m_velocity;
		h3d::Quaternion  m_rotation;

	public:
		enum class Type {
			_static,_dynamic
		};

		void H3D_API update(float deltaTimeSec);
	};
}