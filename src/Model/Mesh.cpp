#include "Mesh.hpp"
#include <assimp/mesh.h>
#include <algorithm>
#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
// Implementation of Mesh
/////////////////////////////////////////////////////////////////
namespace h3d {
    Mesh::Mesh() {
    }
    Mesh::~Mesh() {
        unloadFromOpenGL();
    }

    void Mesh::render() {
        glBindVertexArray(m_vba);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);

        glDrawArrays(GL_TRIANGLES, 3, GL_UNSIGNED_INT);
    }
    
    bool Mesh::loadFromAiMesh(aiMesh *m_ptr) {
        for (int i = 0; i < m_ptr->mNumVertices; i++) {
            h3d::Vertex temp_vert;
            temp_vert.position = h3d::Vec3<float>(
                m_ptr->mVertices[i].x,
                m_ptr->mVertices[i].y,
                m_ptr->mVertices[i].z);
            m_vertices.push_back(temp_vert);
        }
        m_indices.clear();
        auto iter = m_indices.begin();
        m_indices.insert(iter, &m_ptr->mFaces->mIndices[0],
                         m_ptr->mFaces->mIndices+sizeof(m_ptr->mFaces->mIndices));
        return true;
    }
    GLuint Mesh::loadToOpenGL() {
        glCreateBuffers(1, &m_bufferID);
        glCreateBuffers(1, &m_elementBuffer);
        glCreateVertexArrays(1, &m_vba);

        glBindVertexArray(m_vba);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
        
        glBufferStorage(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
        glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

        glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(Vertex), m_vertices.data(),GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(h3d::Vertex), (void*)offsetof(h3d::Vertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(h3d::Vertex), (void*)offsetof(h3d::Vertex, texCoord));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(h3d::Vertex), (void*)offsetof(h3d::Vertex, normal));
        glEnableVertexAttribArray(2);

        return 1;
    }
    bool Mesh::unloadFromOpenGL() {
        glDeleteBuffers(1, &m_bufferID);
        glDeleteBuffers(1, &m_elementBuffer);
        return true;
    }

    GLuint Mesh::getVertexBufferID()  { return m_bufferID;}
    GLuint Mesh::getElementBufferID() { return m_elementBuffer; }
    GLuint Mesh::getVbaID()           { return m_vba; }
    size_t Mesh::getVertexNum() { return m_vertices.size();}
    
}
/////////////////////////////////////////////////////////////////