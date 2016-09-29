#include "3DMT_OBJ.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <iostream>

#undef max
/////////////////////////////////////////////////////////////////
//	Implementation of OBJ Functions
/////////////////////////////////////////////////////////////////
h3d::ModelType::OBJ::Mesh::Mesh() 
{
	clearUp();

	glGenBuffers(1, &m_element_buffer);
	glCreateVertexArrays(1, &m_vba_object);
}
h3d::ModelType::OBJ::Mesh::~Mesh() { clearUp(); }
/////////////////////////////////////////////////////////////////
void h3d::ModelType::OBJ::Mesh::clearUp()
{
	memset(&m_meshname, 0, sizeof(char) * 40);
	m_textureID.clear();

	glDeleteBuffers(1, &m_element_buffer);
	glDeleteVertexArrays(1, &m_vba_object);

	m_texCoords.clear();
	m_vertices.clear();
	m_normals.clear();
	m_indicesVertices.clear();
	m_indicesNormals.clear();
	m_indicesTexCoords.clear();
}
/////////////////////////////////////////////////////////////////
void h3d::ModelType::OBJ::Mesh::correctIndices()
{
	if (m_indicesVertices.size() != 0)
		for (auto &iter : m_indicesVertices)
			iter--;
	if (m_indicesNormals.size() != 0)
		for (auto &iter : m_indicesNormals)
			iter--;
	if (m_indicesTexCoords.size() != 0)
		for (auto &iter : m_indicesTexCoords)
			iter--;
}
/////////////////////////////////////////////////////////////////
void h3d::ModelType::OBJ::Mesh::prepareRendering()
{
	std::cout << "before correct: " << m_indicesVertices.size() << std::endl;

	// Correct the Indices
	correctIndices();

	std::cout << "after correct: " << m_indicesVertices.size() << std::endl;

	// Setup Vertices in the Vec
	m_verticesVec.clear();
	for (unsigned int i = 0;i < m_vertices.size();i++)
	{
		h3d::Vertex vert;

		if(m_vertices.size() != 0)
			vert.position = m_vertices[i];
		else vert.position = h3d::Vec3<GLfloat>(0.0, 0.0, 0.0);

		if(m_normals.size() != 0)
			vert.normal   = m_normals[i];
		else vert.normal = h3d::Vec3<GLfloat>(1.0,0.0,0.0);

		if(m_texCoords.size() != 0)
			vert.texCoord = m_texCoords[i];
		else vert.texCoord = h3d::Vec2<GLfloat>(0.0,0.0);
		
		m_verticesVec.push_back(vert);
	}

	std::cout << "after vert setup: " << m_indicesVertices.size() << std::endl;

	// Generate required Buffers
	glGenBuffers(1, &m_element_buffer);
	glGenBuffers(1 ,&m_verticesBufferOGL);

	// Create the VertexArray (VBA)
	glGenVertexArrays(1, &m_vba_object);
	glBindVertexArray(m_vba_object);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesVertices.size()*sizeof(GLuint),
				 m_indicesVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_verticesBufferOGL);
	glBufferData(GL_ARRAY_BUFFER, m_verticesVec.size() * sizeof(h3d::Vertex),
				 m_verticesVec.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(h3d::Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0); // position

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(h3d::Vertex), (GLvoid*)(sizeof(h3d::Vec3<GLfloat>)));
	glEnableVertexAttribArray(1); // texCoords

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(h3d::Vertex), (GLvoid*)(sizeof(h3d::Vec3<GLfloat>)+sizeof(h3d::Vec2<GLfloat>)));
	glEnableVertexAttribArray(2); // normals

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
/////////////////////////////////////////////////////////////////
// Con-/Destructor
h3d::ModelType::OBJ::OBJ() {}
h3d::ModelType::OBJ::~OBJ() {}
/////////////////////////////////////////////////////////////////
void h3d::ModelType::OBJ::Mesh::render()
{
	glBindVertexArray(m_vba_object);
	
	glBindBuffer(GL_ARRAY_BUFFER,m_verticesBufferOGL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);

	glDrawElements(GL_TRIANGLES, m_indicesVertices.size(), GL_UNSIGNED_INT, 0);

	std::cout << "Vertex  Count   : " << m_verticesVec.size() << std::endl;
	std::cout << "Indices Vertices: " << m_indicesVertices.size() << std::endl;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
/////////////////////////////////////////////////////////////////
bool h3d::ModelType::OBJ::loadFromFile(char Path[])
{
	std::fstream file_stream;
	file_stream.open(Path, std::ios::in);
	if (!file_stream.good()) return false;

	std::string			param;
	int					temp_i;
	GLfloat				temp_f;
	std::string			temp_s;
	h3d::Vec2<GLfloat>  temp_vec2f;
	h3d::Vec3<GLfloat>  temp_vec3f;
	h3d::Vec3<GLuint>   temp_vec3i;
	Mesh				*temp_mesh = nullptr;
	int face_type = 0;

	while(!file_stream.eof())
	{
		file_stream >> param;
		if (param == "#")
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else if (param == "g")
		{	
			std::cout << "g" << std::endl;
			if (temp_mesh == nullptr)
				temp_mesh = new Mesh;
			if (temp_mesh != nullptr)
				m_meshes.push_back(*temp_mesh);
			temp_mesh->clearUp();

			file_stream >> temp_mesh->m_meshname;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "usemtl")
		{
			std::cout << "usemtl" << std::endl;
			file_stream >> temp_mesh->m_textureID;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "v")
		{
			std::cout << "v" << std::endl;
			file_stream >> temp_vec3f.x;
			file_stream >> temp_vec3f.y;
			file_stream >> temp_vec3f.z;
			temp_mesh->m_vertices.push_back(temp_vec3f);
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "vn")
		{
			std::cout << "vn" << std::endl;
			file_stream >> temp_vec3f.x;
			file_stream >> temp_vec3f.y;
			file_stream >> temp_vec3f.z;
			temp_mesh->m_normals.push_back(temp_vec3f);
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "vt")
		{
			std::cout << "vt" << std::endl;
			file_stream >> temp_f; temp_vec2f.x = temp_f;
			file_stream >> temp_f; temp_vec2f.y = temp_f;
			temp_mesh->m_texCoords.push_back(temp_vec2f);
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "f")
		{
			for (int i = 0;i < 3;i++)
			{
				file_stream >> temp_s;
				std::stringstream temp_sstream(temp_s);

				if (std::count(temp_s.begin(), temp_s.end(), '/') == 0)
				{
					file_stream >> temp_i;
					temp_mesh->m_indicesVertices.push_back(temp_i);
				}
				else if (std::count(temp_s.begin(), temp_s.end(), '/') == 1)
				{
					std::replace(temp_s.begin(), temp_s.end(), '/', ' ');
					temp_sstream.clear();
					temp_sstream << temp_s;

					temp_sstream >> temp_i; 
						temp_mesh->m_indicesVertices.push_back(temp_i);
					temp_sstream >> temp_i;
						temp_mesh->m_indicesTexCoords.push_back(temp_i);
				}
				else if (std::count(temp_s.begin(), temp_s.end(), '/') == 2)
				{
					if (temp_s.find("//") != std::string::npos)
					{
						std::replace(temp_s.begin(), temp_s.end(), '/', ' ');
						temp_sstream.clear();
						temp_sstream << temp_s;

						temp_sstream >> temp_i;
							temp_mesh->m_indicesVertices.push_back(temp_i);
						temp_sstream >> temp_i;
							temp_mesh->m_indicesNormals.push_back(temp_i);
					}
					else
					{
						std::replace(temp_s.begin(), temp_s.end(), '/', ' ');
						temp_sstream.clear();
						temp_sstream << temp_s;

						temp_sstream >> temp_i;
							temp_mesh->m_indicesVertices.push_back(temp_i);
						temp_sstream >> temp_i;
							temp_mesh->m_indicesTexCoords.push_back(temp_i);
						temp_sstream >> temp_i;
							temp_mesh->m_indicesNormals.push_back(temp_i);
					}
				}
			}

			// Ignore rest of line
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else 
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	m_meshes.push_back(*temp_mesh);
	m_meshes.erase(m_meshes.begin());
	delete temp_mesh;

	for (auto &iter : m_meshes)
		iter.prepareRendering();

	return true;
}
/////////////////////////////////////////////////////////////////
void h3d::ModelType::OBJ::render()
{
	for (auto &iter : m_meshes)
	{
		iter.render();
	}
}
/////////////////////////////////////////////////////////////////