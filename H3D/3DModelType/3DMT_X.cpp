#include "3DMT_X.hpp"
#include "..\Utilities.hpp"
#include <fstream>
/////////////////////////////////////////////////////////////////
//	Implementation of X Functions
/////////////////////////////////////////////////////////////////
h3d::ModelType::X::X() {}
h3d::ModelType::X::~X() {}
/////////////////////////////////////////////////////////////////
bool h3d::ModelType::X::loadFromFile(char Path[])
{
	// C++ filestream
	std::ifstream file_stream(Path, std::ios::in);
	
	// Check if truly supported
	char* tmp = new char[4];
	file_stream.read(tmp, 4);
	if (tmp != "xof") {
		Log.error("Cannot open %s, probably damaged ?",Path);
		return false;
	}
	file_stream.read(tmp, 4);
	file_stream.read(tmp, 4);
	if (tmp != "txt") {
		Log.error("%s is not a ASCII format !",Path);
		return false;
	}
	file_stream.read(tmp, 4);

	// Temp values
	std::string param;

	// Actual file loading
	while (!file_stream.eof())
	{
		file_stream >> param;
		if (param == "//" || param == "#") {
			char* str;
			file_stream.getline(str, 128);
			m_comments += str;
			m_comments += '\n';
		}
		else if (param == "Header")
		{
				
		}
		// Parse Mesh
		else if (param == "Mesh")
		{
			// Add new Mesh
			m_meshes.push_back(Mesh());

			
		}
	}

	// Clean up successfully
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
void h3d::ModelType::X::render()
{

}
/////////////////////////////////////////////////////////////////
void h3d::ModelType::X::logModelData()
{

}
/////////////////////////////////////////////////////////////////