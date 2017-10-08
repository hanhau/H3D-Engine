#include "Physic\Physic.hpp"

#include <thread>

namespace h3d {
	bool PhysicEngine::init() {
		m_numOfCores = std::thread::hardware_concurrency();
		return true;
	}

	// Manip objects
	void PhysicEngine::addObject(const PhysicObject& obj) {

	}

	// main functions
	void PhysicEngine::udpate(float deltaTime) {

	}
}