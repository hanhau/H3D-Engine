#pragma once 
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "3DModelType\3DMT_MD5.hpp"
#include "3DModelType\3DMT_X.hpp"
#include "3DModelType\3DMT_OBJ.hpp"
#include "3DModelType\3DMT_H3D.hpp"
#include "Drawable.hpp"

#include <string>
#include <algorithm>
/////////////////////////////////////////////////////////////////
//	Universal 3D Model Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	enum class Model3DFormat {
		OBJ,MD5,DAE
	};
	enum class Model3DTechnique {
		NormalMap, Animated
	};
/////////////////////////////////////////////////////////////////
// Convert Models
/////////////////////////////////////////////////////////////////
	namespace converter {
		bool H3D_API MD5ToH3D(char input[], char ouput[]);
		bool H3D_API OBJToH3D(char input[], char ouput[]);
		bool H3D_API XToH3D  (char input[], char ouput[]);
	}
/////////////////////////////////////////////////////////////////
class Model3D
	{
	private:
		union {
			ModelType::OBJ *obj;
			ModelType::MD5 *md5;
			ModelType::X   *x;
			ModelType::H3D *h3d;
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

		// get Intel
		bool H3D_API isAnimated();

		// Animation Controls
		void H3D_API play();
		void H3D_API pause();
		void H3D_API stop();

		void H3D_API setLooped(bool val);

		void  H3D_API setTimeStamp(float val);
		float H3D_API getTimeStamp();

		void H3D_API changeAnimation(char* name);
	};
}
/////////////////////////////////////////////////////////////////
