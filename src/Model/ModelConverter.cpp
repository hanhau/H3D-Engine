#include "../../H3D/Model/ModelConverter.hpp"
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/FileDataStructures.hpp"
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/Utilities.hpp"
#include "../../H3D/Model/Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <filesystem>
namespace fs = std::filesystem;
/////////////////////////////////////////////////////////////////
void processNode(aiNode *node, const aiScene *scene,std::vector<h3d::Mesh>& const meshes)
{
	if (scene == nullptr) return;

	// itself
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(h3d::Mesh());
		meshes.back().loadFromAiMesh(mesh);
		meshes.back().loadToOpenGL();
	}

	// children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene,meshes);
	}
}


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
	h3d::FileType::MH3D::ModelData		f_modelData;
	h3d::FileType::MH3D::MaterialInfo	f_materialInfo;
	h3d::FileType::MH3D::AnimationData	f_animationData;

	memcpy(f_header.format, "mh3d_?", 6);
	f_header.size = 0;
	f_header.type = 0;
	h3d::setObjectToFileHandle(f_header, fh);

	// Meshes
	std::vector<h3d::Mesh> meshes;
	processNode(scene->mRootNode, scene, meshes);

	// Bounding Box
	{
		std::vector<h3d::BoundingBox*> boxes;
		for (auto& const iter : meshes) {
			boxes.push_back(&iter.getBoundingBox());
		}
		h3d::BoundingBox totalBoundingBox;
		totalBoundingBox.createFromMultiple(boxes);
		f_boundingBox.x_start = totalBoundingBox.x_start;
		f_boundingBox.x_end = totalBoundingBox.x_end;
		f_boundingBox.y_start = totalBoundingBox.y_start;
		f_boundingBox.y_end = totalBoundingBox.y_end;
		f_boundingBox.z_start = totalBoundingBox.z_start;
		f_boundingBox.z_end = totalBoundingBox.z_end;
	}
	h3d::setObjectToFileHandle(f_boundingBox, fh);

	// Information
	{
		f_information.numMesh = meshes.size();
	}
	h3d::setObjectToFileHandle(f_information, fh);

	// Model Data
	for(auto& const iter: meshes)
	{
		fh.write((char*)((int32_t)iter.getIndicesNum()), sizeof(int32_t));
		fh.write((char*)iter.getIndices().data(), sizeof(unsigned int)*iter.getIndicesNum());
		fh.write((char*)((int32_t)iter.getVertexNum()), sizeof(int32_t));
		fh.write((char*)iter.getVertices().data(), sizeof(h3d::Vertex)*iter.getVertexNum());
	}

	return true;
}

std::string ws2s(const std::wstring wstr)
{
	std::string output = "";
	for (auto& iter : wstr) {
		output += iter;
	}
	return "";
}

bool h3d::ModelConverter::convertFolderContent(std::string folder_in, std::string folder_out)
{
	bool _error_flag = false;
	for (auto& p : fs::directory_iterator(folder_in)) {
		if (!h3d::ModelConverter::convert(ws2s(std::wstring(p.path().c_str())),
										  folder_out + ws2s(std::wstring(p.path().filename().c_str()))));
			_error_flag = true;
	}
	return _error_flag;
}