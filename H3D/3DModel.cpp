#include "3DModel.hpp"
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
	// Get file extension
	std::string temp_path = Path;
	auto iter = temp_path.find_last_of('.');

	// Define this models 3d model format type
	temp_path.erase(0,iter);
	if (temp_path == "md5mesh") m_modelTypeEnum = 
									h3d::Model3DFormat::MD5;
	else if (temp_path == "dae") m_modelTypeEnum = 
									h3d::Model3DFormat::DAE;
	else if (temp_path == "obj") m_modelTypeEnum = 
									h3d::Model3DFormat::OBJ;
	else return false;

	// Allocate Memory for it
	bool success_load = false;
	switch (m_modelTypeEnum)
	{
	case h3d::Model3DFormat::OBJ:
		m_rawModels.obj = new h3d::ModelType::OBJ();
		success_load = m_rawModels.obj->loadFromFile(Path);
		break;
	case h3d::Model3DFormat::DAE:

		break;
	case h3d::Model3DFormat::MD5:
		m_rawModels.md5 = new h3d::ModelType::MD5();
		success_load = m_rawModels.md5->loadFromFile(Path);
		break;
	}
	// Return state
	return success_load;
}
/////////////////////////////////////////////////////////////////
void h3d::Model3D::render()
{
	switch (m_modelTypeEnum)
	{
	case h3d::Model3DFormat::OBJ:
		m_rawModels.obj->render();
		break;
	case h3d::Model3DFormat::DAE:

		break;
	case h3d::Model3DFormat::MD5:

		break;
	}
	return;
}
/////////////////////////////////////////////////////////////////