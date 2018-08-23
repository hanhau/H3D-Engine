#include "../../H3D/Model/ModelConverter.hpp"
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/FileDataStructures.hpp"
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/Utilities.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <filesystem>
namespace fs = std::filesystem;
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

	h3d::FileHandle fh;
	fh.open(output);
	if (!fh.isOpen()) {
		h3d::Log::error("Unable to open output file %s", output);
		return false;
	}
	
	h3d::FileType::MH3D::Header			f_header;
	h3d::FileType::MH3D::BoundingBox	f_boundingBox;
	h3d::FileType::MH3D::Information	f_information;
	h3d::FileType::MH3D::AnimationData	f_animationData;
	h3d::FileType::MH3D::MaterialInfo	f_materialInfo;
	h3d::FileType::MH3D::ModelData		f_modelData;

	memcpy(f_header.format, "mh3d_?", 6);
	f_header.size = 0;
	f_header.type = 0;

	

	return true;
}

bool h3d::ModelConverter::convertFolderContent(std::string folder_in, std::string folder_out)
{
	bool _error_flag = false;
	for (auto& p : fs::directory_iterator(folder_in)) {
		if (!convert(p.path, folder_out + p.path.filename()))
			_error_flag = true;
	}
	return _error_flag;
}