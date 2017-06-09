#pragma once 
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "3DModelType\3DMT_MD5.hpp"
#include "3DModelType\3DMT_X.hpp"
#include "3DModelType\3DMT_OBJ.hpp"

#include <string>
#include <algorithm>
/////////////////////////////////////////////////////////////////
//	Universal 3D Model Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	enum class Model3DFormat {
		OBJ,MD5,DAE
	};
/////////////////////////////////////////////////////////////////
	class Model3D
	{
	private:
		union {
			ModelType::OBJ *obj;
			ModelType::MD5 *md5;
			ModelType::X   *x;
		}m_rawModels;
		Model3DFormat m_modelTypeEnum;
	public:
		// Con-/Destructor
		H3D_API Model3D();
		H3D_API Model3D(char Path[]);
		H3D_API ~Model3D();

		// Load Model
		bool H3D_API loadFromFile(char Path[]);

		// Rendering
		void H3D_API render();
	};
}
/////////////////////////////////////////////////////////////////
