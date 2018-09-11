#pragma once 
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <string>
/////////////////////////////////////////////////////////////////
// Converts any Format to H3D internal Format
/////////////////////////////////////////////////////////////////
namespace h3d{
    namespace ModelConverter{
		bool H3D_API convert(std::string input, std::string output);
		bool H3D_API convertFolderContent(std::string folder_in,std::string folder_out);
    }
}
/////////////////////////////////////////////////////////////////
