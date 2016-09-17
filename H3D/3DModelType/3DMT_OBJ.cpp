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
	glGenBuffers(1, &m_vbo_buffer);
	glGenBuffers(1, &m_element_buffer);
	glCreateVertexArrays(1, &m_vba_object);
}
h3d::ModelType::OBJ::Mesh::~Mesh() { clearUp(); }
/////////////////////////////////////////////////////////////////
void h3d::ModelType::OBJ::Mesh::clearUp()
{
	memset(&m_meshname, 0, sizeof(char) * 40);
	m_textureID.clear();

	glDeleteBuffers(1, &m_vbo_buffer);
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
void h3d::ModelType::OBJ::Mesh::prepareRendering()
{
	// Generate required Buffers
	glGenBuffers(1, &m_vbo_buffer);
	glGenBuffers(1, &m_element_buffer);
		
	// Create the VertexArray (VBA)
	glGenVertexArrays(1, &m_vba_object);
	glBindVertexArray(m_vba_object);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size(),
				 m_vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesVertices.size(),
				 m_indicesVertices.data(), GL_STATIC_DRAW);
	
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
	
	glBindBuffer(GL_ARRAY_BUFFER,m_vbo_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);

	glDrawArrays(GL_TRIANGLES, 0, m_indicesVertices.size() / 3);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	GLuint				temp_ui;
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
						temp_mesh->m_indicesNormals.push_back(temp_i);
				}
				else if (std::count(temp_s.begin(), temp_s.end(), '/') == 2)
				{
					
				}
			}

			// Ignore rest of line
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else 
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	m_meshes.push_back(*temp_mesh);
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