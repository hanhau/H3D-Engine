#include "../../H3D/Model/3DModel.hpp"
#include "../../H3D/externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
#include STR(ASSIMP_INCLUDE/assimp/Importer.hpp)
#include STR(ASSIMP_INCLUDE/assimp/scene.hpp)
#include STR(ASSIMP_INCLUDE/assimp/postprocess.hpp)
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
    h3d::Log::info("Loading %s now");

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(Path, aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);
    
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
        Mesh temp_mesh;
        temp_mesh.loadFromAiMesh(scene->mMeshes[i]);
        temp_mesh.loadToOpenGL();
        m_meshes.push_back(temp_mesh);
    }

    h3d::Log::info("Finished loading %s");
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
    h3d::Log::info("| Num Materials: %d",1);
    h3d::Log::info("| Num Meshes: %d",1);
    h3d::Log::info("+ Meshes: %d",1);
}