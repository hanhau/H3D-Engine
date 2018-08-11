#include "../../H3D/Model/ModelConverter.hpp"
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/FileDataStructures.hpp"
#include "../../H3D/System/Utilities.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
/////////////////////////////////////////////////////////////////
bool h3d::ModelConverter::convert(std::string input, std::string output) {
	h3d::Log::info("Converting %s now", input.c_str());

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(input.c_str(),
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices);
	if (!scene) {
		h3d::Log::error("Unable to open %s", input.c_str());
		return false;
	}

	h3d::FileType::MH3D::Header f_header;
	
}