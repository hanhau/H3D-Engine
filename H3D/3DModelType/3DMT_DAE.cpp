#include "3DMT_DAE.hpp"
#include "..\Utilities.hpp"
/////////////////////////////////////////////////////////////////
//	Implementation of DAE Functions
/////////////////////////////////////////////////////////////////
bool h3d::ModelType::DAE::loadFromFile(char Path[])
{
	std::fstream file_stream;
	file_stream.open(Path, std::ios::in);
	if (1)
	{
		if (h3d::DebugMode){
			h3d::Debugstream.open("dae_log.txt");
			h3d::Debugstream << "Error opening " << Path << "\n";
		}
		return false;
	}



	return true;
}
/////////////////////////////////////////////////////////////////