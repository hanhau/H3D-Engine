#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/Math/Quaternion.hpp"
#include <vector>

namespace h3d {
	struct AABBCube {
		h3d::Vec2<float> m_zRange;
		h3d::Vec2<float> m_yRange;
		h3d::Vec2<float> m_xRange;
	};

	struct Force {
		float            m_strength;
		h3d::Quaternion  m_rot;

		void H3D_API mix(Force& const force);
	};
	static const Force mix(Force& const force_a,
				           Force& const force_b);

	class PhysicObject
	{
	private:
		AABBCube m_aabbCube;

		float m_mass;
		std::vector<h3d::Vec3<float>> m_points;
	public:
		enum class Type {
			_static,_dynamic
		};

		void H3D_API loadHullMesh(char obj_path[]);
		void H3D_API applyRayCastedForce(h3d::Vec3<float> pos,
										 h3d::Vec3<float> vec);

		void H3D_API update(float deltaTimeSec);
	};
}