#include "../../H3D/Model/Mesh.hpp"
#include <algorithm>
#include <GL/glew.h>
#include <assimp/mesh.h>
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
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    }
    
    bool Mesh::loadFromAiMesh(aiMesh *m_ptr) { 
        for (int i = 0; i < m_ptr->mNumVertices; i++) {
            h3d::Vertex temp_vert;
            temp_vert.position = h3d::Vec3<float>(
                m_ptr->mVertices[i].x,
                m_ptr->mVertices[i].y,
                m_ptr->mVertices[i].z);
			temp_vert.normal = h3d::Vec3<float>(
				m_ptr->mNormals[i].x,
				m_ptr->mNormals[i].y,
				m_ptr->mNormals[i].z);
            m_vertices.push_back(temp_vert);
			temp_vert.texCoord = Vec2<float>(0, 0);

			m_vertices.push_back(temp_vert);
        }

        m_indices.clear();
		for (unsigned int i = 0; i < m_ptr->mNumFaces; i++)
		{
			aiFace face = m_ptr->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				m_indices.push_back(face.mIndices[j]);
		}
        return true;
    }
    void Mesh::loadToOpenGL() {
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
			&m_indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

		glBindVertexArray(0);
    }
    bool Mesh::unloadFromOpenGL() {
        //glDeleteBuffers(1, &m_vbo);
        //glDeleteBuffers(1, &m_ebo);
		//glDeleteVertexArrays(1,&m_vao);
        return true;
    }

    GLuint Mesh::getVertexBufferID()  { return m_vbo;}
    GLuint Mesh::getElementBufferID() { return m_ebo; }
    GLuint Mesh::getVbaID()           { return m_vao; }
    size_t Mesh::getVertexNum() { return m_vertices.size();}
    
}
/////////////////////////////////////////////////////////////////