#include "ResourceManager.hpp"
#include <string>
#include <random>
#include <climits>
#include <algorithm>
/////////////////////////////////////////////////////////////////
// Implementation of Resource Base class
/////////////////////////////////////////////////////////////////
namespace h3d {
	Resource::Resource(std::string name,std::string path) :
		m_name(name) , m_refCount(0) , m_path(path)
	{
		std::string tmp = path;
		tmp.replace(tmp.begin(),tmp.end(),'\\', '/');
		m_filename = std::string(tmp.begin()+tmp.rfind('/')+1,
								 tmp.end());
	}
	Resource::~Resource() {
		
	}
	// Getter
	std::string Resource::getPath()		{ return m_path; }
	std::string Resource::getFilename() { return m_filename; }
	std::string Resource::getName()		{ return m_name; }
	uint64_t Resource::getUniqueID()	{ return m_uniqueID; }
	
	// Reference Counter functions
	void Resource::increaseRefCount() { m_refCount++; }
	void Resource::decreaseRefCount() { if (m_refCount - 1 >= 0) m_refCount--; }
}
/////////////////////////////////////////////////////////////////