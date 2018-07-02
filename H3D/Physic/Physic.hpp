#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "../../H3D/System/Utilities.hpp"
#include "../../H3D/Physic/PhysicObject.hpp"
#include <thread>

/////////////////////////////////////////////////////////////////
// Physic Lib
/////////////////////////////////////////////////////////////////
namespace h3d {
	class PhysicEngine
	{
	public:
		// must be called before anything else
		static bool init();

		// Manip objects
		static void addObject(const PhysicObject& obj);

		// main functions
		static void udpate(float deltaTime);
	};
}
/////////////////////////////////////////////////////////////////