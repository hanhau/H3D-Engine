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
		union {
			ModelType::OBJ *obj;
			ModelType::MD5 *md5;
			ModelType::DAE *dae;
		}m_rawModels;
	public:
		// Con-/Destructor
		Model3D();
		Model3D(char Path[]);
		~Model3D();

		// Load Model
		bool loadFromFile(char Path[]);

		// Rendering
		void render();
	};
}
/////////////////////////////////////////////////////////////////
