#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <vector>
#include "../../H3D/Graphics/Vertex.hpp"
#include "../../H3D/Model/BoundingBox.hpp"

typedef unsigned int GLuint;
/////////////////////////////////////////////////////////////////
//	h3d::Mesh
/////////////////////////////////////////////////////////////////
struct aiMesh;
namespace h3d {
	class Mesh
	{
	private:
        GLuint m_vao;
        GLuint m_vbo;
		GLuint m_ebo;

        std::vector<h3d::Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
		size_t m_indicesCount;

		h3d::BoundingBox m_boundingBox;
	public:
        H3D_API Mesh();
        H3D_API ~Mesh();

        void H3D_API render();

        bool H3D_API loadFromAiMesh(const aiMesh *m_ptr);
		H3D_API h3d::BoundingBox& getBoundingBox();

		void H3D_API passVertices(std::vector<h3d::Vertex> &vertices);
		void H3D_API passIndices(std::vector<unsigned int> &indices);
		H3D_API std::vector<h3d::Vertex>& getVertices();
		H3D_API std::vector<unsigned int>& getIndices();

        void H3D_API loadToOpenGL();
        bool H3D_API unloadFromOpenGL();
		void H3D_API clearOfflineData();

        GLuint H3D_API getVertexBufferID();
        GLuint H3D_API getElementBufferID();
        GLuint H3D_API getVbaID();
        size_t H3D_API getVertexNum();
		size_t H3D_API getIndicesNum();
	};
}
/////////////////////////////////////////////////////////////////