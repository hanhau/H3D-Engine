#include "3DMT_MD5.hpp"
#include "..\Utilities.hpp"
#include <iostream>
#include <cstring>
#include <math.h>
#include <cassert>
#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
//	Implementation of MD5 Functions
/////////////////////////////////////////////////////////////////
h3d::ModelType::MD5::MD5() {}
h3d::ModelType::MD5::~MD5() {}
h3d::ModelType::MD5::Animation::SkeletonJoint::SkeletonJoint() {}
h3d::ModelType::MD5::Animation::SkeletonJoint::SkeletonJoint(const BaseFrame& copy) 
{
	this->m_Pos = copy.m_Pos;
	this->m_Quat_vec3 = copy.m_Quat_vec3;
	this->m_Quat_w = copy.m_Quat_w;
}
/////////////////////////////////////////////////////////////////
bool h3d::ModelType::MD5::prepareMesh(Mesh& mesh)
{
	mesh.position_vec.clear();
	mesh.tex_vec.clear();

	Vec3<float> finalPos;
	Vec3<float> rotPos;

	Vertex temp_vertex;
	Weight temp_weight;
	Joint  temp_joint;

	// Compute Vertices
	for (auto &iter : mesh.vertex_vec)
	{
		finalPos = Vec3<float>(0.0, 0.0, 0.0);		
		temp_vertex = iter;

		temp_vertex.pos = Vec3<float>(0.0, 0.0, 0.0);
		temp_vertex.normal = Vec3<float>(0.0, 0.0, 0.0);

		// Sum position of weights
		for (int j = 0;j < temp_vertex.weightCount;++j)
		{
			temp_weight = mesh.weight_vec[temp_vertex.startWeight + j];
			temp_joint = joint_vec[temp_weight.jointID];

			// Convert weight pos from joint local space to 
			// object space
			rotPos = temp_joint.orientation * temp_weight.pos;

			temp_vertex.pos += (temp_joint.position + rotPos) * temp_weight.pos;
		}
		mesh.position_vec.push_back(temp_vertex.pos);
		mesh.tex_vec.push_back(temp_vertex.texCoord);
	}

	return true;
}
bool h3d::ModelType::MD5::prepareNormals(Mesh& mesh)
{
	mesh.normal_vec.clear();

	Vec3<float> t_v[3];
	Vec3<float> normal;
	Vec3<float> temp_vec3;
	Vertex      temp_vertex;
	Weight      temp_weight;
	Joint       temp_joint;

	// Loop through triangles and calc normals
	for (unsigned int i = 0;i < mesh.triangle_vec.size();++i)
	{
		t_v[0] = mesh.vertex_vec[mesh.triangle_vec[i].x].pos;
		t_v[1] = mesh.vertex_vec[mesh.triangle_vec[i].y].pos;
		t_v[2] = mesh.vertex_vec[mesh.triangle_vec[i].z].pos;

		normal = t_v[2] - t_v[0];
		normal.cross(t_v[1] - t_v[0]);

		mesh.vertex_vec[mesh.triangle_vec[i].x].normal += normal;
		mesh.vertex_vec[mesh.triangle_vec[i].y].normal += normal;
		mesh.vertex_vec[mesh.triangle_vec[i].z].normal += normal;
	}
	// Normalize all normals
	for (unsigned int i = 0;i < mesh.vertex_vec.size();++i)
	{
		temp_vertex = mesh.vertex_vec[i];

		normal = temp_vertex.normal.normalize();
		mesh.normal_vec.push_back(normal);

		// reset normal to calc bin-pose normal in joint space
		temp_vertex.normal = Vec3<float>(0, 0, 0);

		// put bind-pose normal into joint-local space
		// so the animated normal can be computed faster
		for (int j = 0;j < temp_vertex.weightCount;++j)
		{
			temp_weight = mesh.weight_vec[temp_vertex.startWeight + j];
			temp_joint = joint_vec[temp_weight.jointID];
			temp_vec3 = Vec3<float>(temp_weight.bias,0.0f, 0.0f);
				temp_vertex.normal += (normal * temp_joint.orientation) * temp_vec3;
		}
	}

	return true;
}
/////////////////////////////////////////////////////////////////
void h3d::ModelType::MD5::renderMesh(const Mesh &mesh)
{
	glColor3f(1.0f, 1.0f, 1.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindTexture(GL_TEXTURE_2D,1);
	glVertexPointer(3, GL_FLOAT, 0, &(mesh.position_vec[0]));
	glNormalPointer(GL_FLOAT, 0, &(mesh.normal_vec[0]));
	glTexCoordPointer(2, GL_FLOAT, 0, &(mesh.tex_vec[0]));

	glDrawElements(GL_TRIANGLES, mesh.index_vec.size(), GL_UNSIGNED_INT, &(mesh.index_vec[0]));

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);
}
/////////////////////////////////////////////////////////////////
bool h3d::ModelType::MD5::loadFromFile(const char path[])
{
	// Debug purposes
	Debugstream.open("helloo.txt");

	// Opening Filestream
	std::ifstream file_stream;
	file_stream.open(path, std::ios::in);
	if (!file_stream.good()) return false;
	if (h3d::DebugMode)
		Debugstream << "MD5: loadFromFile(" << path << ")\n";// << std::endl;

	// additional temp vals
	std::string			temp_s;
	std::string			temp_sa[10];
	int					temp_i;
	char				temp_ca[200];
	Joint				temp_joint;
	Mesh				temp_mesh;
	Vertex				temp_vertex;
	Weight				temp_weight;
	Vec3<int>			temp_triangle;
	int numVerts, numTris, numWeights;

	// Preparing this instance
	joint_vec.clear();
	mesh_vec.clear();

	// Reading File
	while (!file_stream.eof())
	{
		file_stream >> temp_s;

		if (temp_s == "MD5Version")
		{
			file_stream >> md5_version;
			assert(md5_version == 10);

			if(h3d::DebugMode)
				Debugstream <<  md5_version <<"\n";
		}
		else if (temp_s == "commandline")
		{
			file_stream.getline(temp_ca, 200);
		}
		else if (temp_s == "numJoints")
		{
			file_stream >> temp_i;
			joint_count = temp_i;

			if(h3d::DebugMode)
				Debugstream << temp_i <<"\n";
		}
		else if (temp_s == "numMeshes")
		{
			file_stream >> temp_i;
			mesh_count = temp_i;

			if(h3d::DebugMode)
				Debugstream << temp_i << "\n";
		}
		// Importing JOINTS
		else if (temp_s == "joints")
		{
			file_stream >> temp_s; // '{' char

			// Iterate through all joints
			for (unsigned int i = 0;i < joint_count;i++)
			{
				file_stream >> temp_joint.name >> temp_joint.parentIndex >> temp_s >>
					temp_joint.position.x >> temp_joint.position.y >>
					temp_joint.position.z >> temp_s >> temp_s >>
					temp_joint.orientation.x >> temp_joint.orientation.y >>
					temp_joint.orientation.z >> temp_s;

				if(h3d::DebugMode)
					Debugstream << temp_joint.name << temp_joint.parentIndex <<
						temp_joint.position.x << temp_joint.position.y <<
						temp_joint.position.z << temp_joint.orientation.x <<
						temp_joint.orientation.y << temp_joint.orientation.z << "\n";//<< std::endl;

				temp_joint.name.erase(temp_joint.name.begin());
				temp_joint.name.erase(temp_joint.name.end());

				static float t;
				t = 1.0f - powf(temp_joint.orientation.x, 2) -
					powf(temp_joint.orientation.y, 2) -
					powf(temp_joint.orientation.z, 2);
				if (t < 0.0f)
					temp_joint.orientation_quaternion = 0.0f;
				else
					temp_joint.orientation_quaternion = -sqrtf(t);

				joint_vec.push_back(temp_joint);

				file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			file_stream >> temp_s;
		}
		// Importing MESHES
		else if (temp_s == "mesh")
		{
			file_stream >> temp_s;
			file_stream >> temp_s;

			while (temp_s != "}")
			{
				if (temp_s == "shader")
				{
					file_stream >> temp_s;
					temp_s.erase(temp_s.begin(),temp_s.begin() + temp_s.find_last_of("\\"));

					if (h3d::DebugMode)
						Debugstream << temp_s << "\n";//std::endl;
				}
				else if (temp_s == "numverts")
				{
					file_stream >> numVerts;
					file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					if (h3d::DebugMode)
						Debugstream << numVerts << "\n";//std::endl;

					for (int i = 0;i < numVerts;++i)
					{
						file_stream >> temp_s >> temp_s >> temp_s >>
							temp_vertex.texCoord.x >> temp_vertex.texCoord.y >>
							temp_s >> temp_vertex.startWeight >> temp_vertex.weightCount;

						if (h3d::DebugMode)
							Debugstream << temp_vertex.texCoord.x << temp_vertex.texCoord.y <<
								temp_vertex.startWeight << temp_vertex.weightCount << "\n";//std::endl;

						file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

						temp_mesh.vertex_vec.push_back(temp_vertex);
						temp_mesh.tex_vec.push_back(temp_vertex.texCoord);
					}
				}
				else if (temp_s == "numtris")
				{
					file_stream >> numTris;
					file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					if (h3d::DebugMode)
						Debugstream << numTris << "\n";//std::endl;

					for (int i = 0;i < numTris;i++)
					{
						file_stream >> temp_s >> temp_s >>
							temp_triangle.x >> temp_triangle.y >> temp_triangle.z;

						if (h3d::DebugMode)
							Debugstream << temp_triangle.x << temp_triangle.y << temp_triangle.z << "\n";//std::endl;

						file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

						temp_mesh.triangle_vec.push_back(temp_triangle);
						temp_mesh.index_vec.push_back(temp_triangle.x);
						temp_mesh.index_vec.push_back(temp_triangle.y);
						temp_mesh.index_vec.push_back(temp_triangle.z);
					}
				}
				else if (temp_s == "numweights")
				{
					file_stream >> numWeights;
					file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					for (int i = 0;i < numWeights;i++)
					{
						file_stream >> temp_s >> temp_s >> temp_weight.jointID >>
							temp_weight.bias >> temp_s >> temp_weight.pos.x >>
							temp_weight.pos.y >> temp_weight.pos.z >> temp_s;

						if (h3d::DebugMode)
							Debugstream << temp_weight.jointID << temp_weight.bias <<
							temp_weight.pos.x << temp_weight.pos.y << temp_weight.pos.z << "\n";//std::endl;

						file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						temp_mesh.weight_vec.push_back(temp_weight);
					}
				}
				else
				{
					file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				file_stream >> temp_s;
			}
			prepareMesh(temp_mesh);
			prepareNormals(temp_mesh);

			mesh_vec.push_back(temp_mesh);
		}
	}

	// Closing Filestream and return
	file_stream.close();
	if (h3d::DebugMode)
		Debugstream << "End of: loadfromFile(" << path << ");" << "\n";//std::endl;

	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::ModelType::MD5::Animation::loadFromFile(char Path[])
{
	std::fstream file_stream;
	file_stream.open(Path, std::ios::in);
	if (!file_stream.is_open())
	{
		if (h3d::DebugMode) {
			h3d::Debugstream.open("md5_anim_log.txt");
			h3d::Debugstream << "Error loading " << Path << "\n";
		}
		return false;
	}

	// Temporarly Data
	std::string param, junk;

	// Clean up before new Loading

	// Loading
	file_stream >> param;
	while (!file_stream.eof())
	{
		/////////////////////////////////////////////////////////		
		// .md5anim Header
		if (param == "MD5Version")
		{
			file_stream >> m_MD5Version;
			if (m_MD5Version != 10)
			{
				h3d::Debugstream.open("md5_anim_log.txt");
				h3d::Debugstream << "md5anim: Version not matching" << "\n";
				return false;
			}
		}
		else if (param == "commandline")
		{
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "numFrames")
		{
			file_stream >> m_NumFrames;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "numJoints")
		{
			file_stream >> m_NumJoints;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "frameRate")
		{
			file_stream >> m_Framerate;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "numAnimatedComponents")
		{
			file_stream >> m_NumAnimatedComponents;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		/////////////////////////////////////////////////////////		
		// .md5anim Data
		else if (param == "hierachy")
		{
			file_stream >> junk;
			for (int i = 0;i < m_NumJoints;++i)
			{
				Joint_Info joint;
				file_stream >> joint.m_Name >> joint.m_ParentID >>
					joint.m_Flags >> joint.m_StartIndex;

				m_JointInfos.push_back(joint);

				file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			file_stream >> junk;
		}
		else if (param == "bounds")
		{
			file_stream >> junk;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (int i = 0;i < m_NumFrames;++i)
			{
				Bound bound;
				file_stream >> junk;
				file_stream >> bound.m_Min.x >> bound.m_Min.y >> bound.m_Min.z;
				file_stream >> junk >> junk;
				file_stream >> bound.m_Max.x >> bound.m_Max.y >> bound.m_Max.z;

				m_Bounds.push_back(bound);

				file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			file_stream >> junk;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "baseframe")
		{
			file_stream >> junk;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			for (int i = 0;i < m_NumJoints;++i)
			{
				BaseFrame baseframe;
				file_stream >> baseframe.m_Pos.x >> baseframe.m_Pos.y >> baseframe.m_Pos.z;
				file_stream >> junk >> junk;
				file_stream >> baseframe.m_Quat_vec3.x >> baseframe.m_Quat_vec3.y >> baseframe.m_Quat_vec3.z;
				file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				m_BaseFrames.push_back(baseframe);
			}

			file_stream >> junk;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (param == "frame")
		{
			FrameData frame;
			file_stream >> frame.m_FrameID >> junk;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			for (int i = 0;i < m_NumAnimatedComponents;++i)
			{
				float framedata;
				file_stream >> framedata;
				frame.m_FrameData.push_back(framedata);
			}

			m_Frames.push_back(frame);

			// Build Skeleton for this Frame

			file_stream >> junk;
			file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		/////////////////////////////////////////////////////////		
		file_stream >> junk;
	}

	m_AnimatedSkeleton.m_Joints.assign(m_NumJoints, SkeletonJoint());

	m_FrameDuration = 1.0f / (float)m_Framerate;
	m_AnimDuration = (m_FrameDuration * (float)m_NumFrames);
	m_AnimTime = 0.0f;

	if (h3d::DebugMode)
	{
		if (m_JointInfos.size() != m_NumJoints ||
			m_Bounds.size() != m_NumFrames ||
			m_BaseFrames.size() != m_NumJoints ||
			m_Frames.size() != m_NumFrames ||
			m_Skeletons.size() != m_NumFrames)
		{
			h3d::Debugstream.open("md5_anim_log.txt");
			h3d::Debugstream << "File: " << Path << " has invalid Counts, check it!\n";
		}
	}

	// Close File
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
void h3d::ModelType::MD5::Animation::BuildFrameskeleton(std::vector<FrrameSkeleton>&   skeletons,
														const std::vector<Joint_Info>& jointInfos,
														const std::vector<BaseFrame>&  baseFrames,
														const FrameData&			   frameData)
{
	FrrameSkeleton skeleton;

	for (unsigned int i = 0;i < jointInfos.size(); ++i)
	{
		unsigned int j = 0;

		const Joint_Info& jointInfo = jointInfos[i];
		// Start with the base frame position and orientation.
		SkeletonJoint animatedJoint = baseFrames[i];

		animatedJoint.m_Parent = jointInfo.m_ParentID;

		if (jointInfo.m_Flags & 1) // Pos.x
		{
			animatedJoint.m_Pos.x = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 2) // Pos.y
		{
			animatedJoint.m_Pos.y = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 4) // Pos.x
		{
			animatedJoint.m_Pos.z = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 8) // Orient.x
		{
			animatedJoint.m_Quat_vec3.x = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 16) // Orient.y
		{
			animatedJoint.m_Quat_vec3.y = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 32) // Orient.z
		{
			animatedJoint.m_Quat_vec3.z = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}

		//compute quadw animatedJoint.morient

	}
}
/////////////////////////////////////////////////////////////////