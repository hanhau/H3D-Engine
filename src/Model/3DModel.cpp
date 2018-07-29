#include "../../H3D/Model/3DModel.hpp"

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
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
h3d::Model3D::Model3D() {}
h3d::Model3D::Model3D(char Path[])
{
	this->loadFromFile(Path);
}
h3d::Model3D::~Model3D() {}
/////////////////////////////////////////////////////////////////
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

    for (int i = 0; i < scene->mNumMaterials; i++) {
        h3d::Material mat;
        mat.loadFromAssimpMaterial(scene->mMaterials[i]);
        m_materials.push_back(mat);
    }

    for (int i = 0; i < scene->mNumMeshes; i++) {
		m_meshes.push_back(Mesh());
		m_meshes.back().loadFromAiMesh(scene->mMeshes[i]);
		m_meshes.back().loadToOpenGL();
    }

    h3d::Log::info("Finished loading %s",Path);
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