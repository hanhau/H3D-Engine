#include "../../H3D/Model/3DModel.hpp"
#include "../../H3D/System/FileSystem.hpp"

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <experimental/filesystem>
/////////////////////////////////////////////////////////////////
// Impl
struct h3d::Model3D::impl 
{
    aiScene m_scene;
    Assimp::Importer m_importer;
    GLuint m_vba;
    GLuint *m_buffers;
    int m_buffersCount;
};
/////////////////////////////////////////////////////////////////
// Implementation of abstract model class
/////////////////////////////////////////////////////////////////
h3d::Model3D::Model3D() noexcept {}
h3d::Model3D::Model3D(char Path[])
{
	this->loadFromFile(Path);
}
h3d::Model3D::~Model3D() {}
/////////////////////////////////////////////////////////////////
void h3d::Model3D::clearEntireData() {
	this->m_boundingBox = h3d::BoundingBox();
	this->m_materials.clear();
	this->m_meshes.clear();
}
void h3d::Model3D::processNode(aiNode *node, const aiScene *scene)
{
	if (scene == nullptr) return;

	// itself
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(Mesh());
		m_meshes.back().loadFromAiMesh(mesh);
		m_meshes.back().loadToOpenGL();
	}

	// children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

bool h3d::Model3D::loadFromFile(char Path[]) 
{
	clearEntireData();

	std::experimental::filesystem::path path(Path);
	if (path.extension().c_str() != L"mh3d") {
		h3d::Log::error("Convert it to a mh3d file first");
		return false;
	}

	h3d::FileHandle fh;
	fh.open(Path);
	if (!fh.isOpen()) {
		h3d::Log::error("Unable to open %s", Path);
		return false;
	}

	h3d::FileType::MH3D::Header			f_header;
	h3d::FileType::MH3D::BoundingBox	f_boundingBox;
	h3d::FileType::MH3D::Information	f_information;
	h3d::FileType::MH3D::ModelData		f_modelData;
	h3d::FileType::MH3D::MaterialInfo	f_materialInfo;
	h3d::FileType::MH3D::AnimationData	f_animationData;

	h3d::setObjectFromFileHandle(f_header,fh);
	
	h3d::setObjectFromFileHandle(f_boundingBox,fh);
	m_boundingBox.setValues(f_boundingBox.x_start, f_boundingBox.x_end,
							f_boundingBox.y_start, f_boundingBox.y_end,
							f_boundingBox.z_start, f_boundingBox.z_end);
	m_boundingBox.create();

	h3d::setObjectFromFileHandle(f_information, fh);

	int32_t count = 0;
	h3d::Mesh temp_mesh;
	std::vector<h3d::Vertex> temp_vertices;
	std::vector<unsigned int> temp_indices;
	for (int i = 0; i < f_information.numMesh; i++) {
		temp_mesh = h3d::Mesh();
		temp_vertices.clear();
		temp_indices.clear();

		fh.read((char*)&count, sizeof(int32_t));
		temp_indices.resize(count);
		fh.read((char*)temp_indices.data(), sizeof(unsigned int) * count);

		fh.read((char*)&count, sizeof(int32_t));
		temp_vertices.resize(count);
		fh.read((char*)temp_vertices.data(), sizeof(h3d::Vertex) * count);

		temp_mesh.passIndices(temp_indices);
		temp_mesh.passVertices(temp_vertices);

		m_meshes.push_back(temp_mesh);
	}

	// // // //
	return true;
    h3d::Log::info("Loading %s now",Path);

    Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(Path,
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices);
    if (!scene) {
        h3d::Log::error("Unable to load %s", Path);
        return false;
    }

	for (unsigned int i = 0; i < scene->mNumMaterials;i++) {
		
	}

	processNode(scene->mRootNode, scene);
	for (auto &iter : m_meshes)
		iter.clearOfflineData();

	h3d::Log::info("Finished loading %s", Path);
    return true;
}
/////////////////////////////////////////////////////////////////
void h3d::Model3D::render() {
    for (auto &iter : m_meshes) {
        iter.render();
    }
}
void h3d::Model3D::logModelData() {
    h3d::Log::info("+ Data Content of Model3D:");
    h3d::Log::info("| Num Materials: %d",m_materials.size());
    h3d::Log::info("| Num Meshes: %d",m_meshes.size());
    h3d::Log::info("+ Meshes: %d",1);
}
const h3d::BoundingBox& h3d::Model3D::getBoundingBox() {
	return m_boundingBox;
}
/////////////////////////////////////////////////////////////////
// Specialised Loading Functions
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////