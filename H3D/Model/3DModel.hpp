#pragma once 
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "../../H3D/Graphics/Drawable.hpp"
#include "../../H3D/Graphics/Material.hpp"
#include "../../H3D/Model/Mesh.hpp"
#include "../dep_lib_fwd.h"

#include <vector>
/////////////////////////////////////////////////////////////////
//	Universal 3D Model Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	class BoudingBox {
		float x_start;
		float x_end;
		float y_start;
		float y_end;
		float z_start;
		float z_end;
	};
	class Model3D
	{
		struct impl;
		std::unique_ptr<impl>m_impl;

		std::vector<h3d::Mesh> m_meshes;
		std::vector<h3d::Material> m_materials;

		void processNode(aiNode *node, const aiScene *scene);
	public:
		// Con-/Destructor
		H3D_API Model3D() noexcept;
		H3D_API Model3D(char Path[]);
		H3D_API ~Model3D();

		// Load Model
		bool H3D_API loadFromFile(char Path[]);

		// Rendering
		void H3D_API render();

		// get Intel
		bool H3D_API isAnimated();
		void H3D_API logModelData();

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
