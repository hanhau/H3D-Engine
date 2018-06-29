#include "Resource.hpp"
#include <algorithm>

/////////////////////////////////////////////////////////////////
// Resource Implementations
/////////////////////////////////////////////////////////////////
namespace h3d {
	Resource::Resource(){}
	Resource::~Resource() {}
	Resource::Resource(const Resource&& res) {
		this->m_filename = res.m_filename;
		this->m_name = res.m_name;
		this->m_path = res.m_path;
		this->m_refCount = res.m_refCount;
	}

	// Getter
	std::string Resource::getPath() { return m_path; }
	std::string Resource::getFilename() { return m_filename; }
	std::string Resource::getName() { return m_name; }

	// Reference Counter functions
	void Resource::increaseRefCount() { m_refCount++; }
	void Resource::decreaseRefCount() { if (m_refCount - 1 >= 0) m_refCount--; }
	bool Resource::isReferenced() { return(m_refCount) ? true : false; }
	
	// Apply the new State
	void Resource::updateState(State state) {
		if (state == State::cold) {

		}
		if (state == State::hot) {

		}
		if (state == State::loaded) {

		}
	}

	// Create a new Resource
	Resource createResource(std::string name, std::string path) {
		Resource temp;
		
		temp.m_path = path;
		temp.m_refCount = 0;
		temp.m_name = name;
		temp.m_state = Resource::State::cold;

		// get filename
		temp.m_filename = std::string(std::find(path.end(),path.begin(),'/'),path.end());

		return temp;
	}
}
/////////////////////////////////////////////////////////////////