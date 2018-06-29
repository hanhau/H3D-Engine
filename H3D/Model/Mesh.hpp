#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <vector>
#include "Vertex.hpp"
#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
//	h3d::Mesh
/////////////////////////////////////////////////////////////////
struct aiMesh;
namespace h3d {
	class Mesh
	{
	private:
        GLuint m_vba;
        GLuint m_bufferID;
        GLuint m_elementBuffer;
        std::vector<h3d::Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
	public:
        H3D_API Mesh();
        H3D_API ~Mesh();

        void H3D_API render();

        bool H3D_API loadFromAiMesh(aiMesh *m_ptr);
        GLuint H3D_API loadToOpenGL();
        bool H3D_API unloadFromOpenGL();

        GLuint H3D_API getVertexBufferID();
        GLuint H3D_API getElementBufferID();
        GLuint H3D_API getVbaID();
        size_t H3D_API getVertexNum();
	};
}
/////////////////////////////////////////////////////////////////