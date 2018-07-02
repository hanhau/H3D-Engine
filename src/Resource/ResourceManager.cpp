#include "../../H3D/Resource/ResourceManager.hpp"
#include "../../H3D/System/Utilities.hpp"
#include <string>
#include <random>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <functional>
/////////////////////////////////////////////////////////////////
// Implementation of Resource Base class
/////////////////////////////////////////////////////////////////
namespace {
	h3d::mem::Chunk _chunk;
	std::unordered_map<int, h3d::Resource> a;
}

namespace h3d {
	ResourceManager::ResourceManager(){}
	ResourceManager::~ResourceManager(){}

	void ResourceManager::initialize(size_t bytesToAllocate) {
		_chunk.size = bytesToAllocate;
		_chunk.start = h3d::GlobalAllocator::getChunk(bytesToAllocate).start;
		if (_chunk.start == nullptr) {
			if (h3d::DebugMode)
				h3d::Log::error("Unable to init h3d::ResourceManager");
		}
	}
	void ResourceManager::shutdown() {


		h3d::GlobalAllocator::freeChunk(_chunk);
	}

	void ResourceManager::registerResource(Resource &&res) {

	}
	void ResourceManager::detachResource(std::string name, std::string path) {

	}

	Resource& ResourceManager::getResource(std::string name, std::string path) {
		return Resource();
	}
}
/////////////////////////////////////////////////////////////////