#pragma once 
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/Model/3DModel.hpp"
#include <string>
/////////////////////////////////////////////////////////////////
// Converts any Format to H3D internal Format
/////////////////////////////////////////////////////////////////
namespace h3d{
    namespace ModelConverter{
        struct Result{
            bool success;
            
            inline Result(){
                success = false;
            }
        };
        Result H3D_API convertToH3DModel(std::string input_path,
                                         h3d::Model &md_output);
    }
}
/////////////////////////////////////////////////////////////////
