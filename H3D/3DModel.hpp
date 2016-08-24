#pragma once 
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <string>
#include "3DModelType\3DMT_MD5.hpp"
#include "3DModelType\3DMT_DAE.hpp"
#include "3DModelType\3DMT_OBJ.hpp"
/////////////////////////////////////////////////////////////////
//	Universal 3D Model Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Model3D
	{
	private:
		
	public:
		// Con-/Destructor
		Model3D();
		~Model3D();
	};
}
/////////////////////////////////////////////////////////////////
