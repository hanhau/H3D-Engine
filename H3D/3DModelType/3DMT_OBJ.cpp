#include "3DMT_OBJ.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
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
	std::cout << "entering" << std::endl;
	std::fstream file_stream;
	file_stream.open(Path, std::ios::in);
	if (!file_stream.good()) return false;

	std::cout << "opened" << std::endl;

	std::string			param;
	int					temp_i;
	GLuint				temp_ui;
	GLfloat				temp_f;
	std::string			temp_s;
	std::stringstream   temp_sstream;
	h3d::Vec2<GLfloat>  temp_vec2f;
	h3d::Vec3<GLfloat>  temp_vec3f;
	h3d::Vec3<GLuint>   temp_vec3i;
	Mesh				*temp_mesh = nullptr;

	int face_type = 0;

	std::cout << "before while" << std::endl;

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
		}
		else if (param == "vn")
		{
			std::cout << "vn" << std::endl;
			file_stream >> temp_vec3f.x;
			file_stream >> temp_vec3f.y;
			file_stream >> temp_vec3f.z;
			temp_mesh->m_normals.push_back(temp_vec3f);
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
			// Get rest of line
			temp_sstream.clear();
			for (int i = 0;i < 3;i++) {
				file_stream >> temp_s;
				temp_sstream << " " << temp_s;
			}
			temp_s = temp_sstream.str();
			
			// Get Facetype (how data is organized)
			// 1 = f x x x 
			// 2 = f x/x x/x x/x
			// 3 = f x//x x//x x//x
			// 4 = f x/x/x x/x/x x/x/x
			// 5 = error, check File
			if (std::count(temp_s.begin(), temp_s.end(), '/') == 0)
				face_type = 1;
			else if (std::count(temp_s.begin(), temp_s.end(), '/') == 3)
				face_type = 2;
			else if (std::count(temp_s.begin(), temp_s.end(), '/') == 6)
			{
				if (temp_s.find("//") != std::string::npos)
					face_type = 3;
				else
					face_type = 4;
			}
			else
			{
				if (h3d::DebugMode){
					h3d::Debugstream.open("OBJ_log.txt");
					h3d::Debugstream << "Cant get Faces from " << Path << "\n";
					h3d::Debugstream.close();
				}
				return false;
			}

			// Remove all "/"
			std::replace(temp_s.begin(), temp_s.end(), '/', ' ');
			temp_sstream.clear();
			temp_sstream << temp_s;
			
			// Fill Vectors
			switch (face_type)
			{
				// Facetype 1
			case 1:
				temp_sstream >> temp_vec3i.x >> temp_vec3i.y >> temp_vec3i.z;
				temp_mesh->m_indicesVertices.push_back(temp_vec3i.x);
				temp_mesh->m_indicesVertices.push_back(temp_vec3i.y);
				temp_mesh->m_indicesVertices.push_back(temp_vec3i.z);
				break;
				// Facetype 2
			case 2:
				for (int i = 0;i < 3;i++)
				{
					temp_sstream >> temp_vec3i.x >> temp_vec3i.y;
					temp_mesh->m_indicesVertices.push_back(temp_vec3i.x);
					temp_mesh->m_indicesTexCoords.push_back(temp_vec3i.y);
				}
				break;
				// Facetype 3
			case 3:

				break;
				// Facetype 4
			case 4:
				for (int i = 0;i < 3;i++)
				{
					temp_sstream >> temp_vec3i.x >> temp_vec3i.y >> temp_vec3i.z;
					temp_mesh->m_indicesVertices.push_back(temp_vec3i.x);
					temp_mesh->m_indicesTexCoords.push_back(temp_vec3i.y);
					temp_mesh->m_indicesNormals.push_back(temp_vec3i.z);
				}
				break;
			default: break;
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