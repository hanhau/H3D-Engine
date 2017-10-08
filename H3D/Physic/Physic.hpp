#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "..\Utilities.hpp"
#include "..\PhysicObject.hpp"
#include <thread>

/////////////////////////////////////////////////////////////////
// Physic Lib
/////////////////////////////////////////////////////////////////
namespace h3d {
	class PhysicEngine
	{
	private:
		int m_numOfCores;

		// container of objects
	public:
		// must be called before anything else
		bool init();

		// Manip objects
		void addObject(const PhysicObject& obj);

		// main functions
		void udpate(float deltaTime);
	};
}
/////////////////////////////////////////////////////////////////