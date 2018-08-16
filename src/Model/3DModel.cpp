#include "../../H3D/Model/3DModel.hpp"

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
/////////////////////////////////////////////////////////////////
// Bounding Box
h3d::BoundingBox::BoundingBox() {}
h3d::BoundingBox::BoundingBox(float xstart, float xend,
							  float ystart, float yend,
							  float zstart, float zend) :
	x_start(xstart),x_end(xend),
	y_start(ystart),y_end(yend),
	z_start(zstart),z_end(zend)
{
	this->create();
}

void h3d::BoundingBox::create() {
	std::array<h3d::Vec3<float>, 8> m_edges = {
		h3d::Vec3<float>(x_start,y_start,z_start),
		h3d::Vec3<float>(x_start,y_start,z_end),
		h3d::Vec3<float>(x_end,y_start,z_end),
		h3d::Vec3<float>(x_end,y_start,z_start),
		h3d::Vec3<float>(x_start,y_end,z_start),
		h3d::Vec3<float>(x_start,y_end,z_end),
		h3d::Vec3<float>(x_end,y_end,z_end),
		h3d::Vec3<float>(x_end,y_end,z_start)
	};

}
bool h3d::BoundingBox::intersect(const h3d::Math::Ray& ray)
{
	for(auto &iter : m_tris)
		if()
}
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