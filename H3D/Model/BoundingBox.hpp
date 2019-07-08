#pragma once
#include "../Math/Math.hpp"
#include "../dep_lib_fwd.h"
#include <memory>
#include <array>
#include <vector>
/////////////////////////////////////////////////////////////////
// Bounding Box
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace ModelConverter{
		bool convert(std::string input, std::string output);
	}

	class Mesh;
	class BoundingBox {
		friend bool h3d::ModelConverter::convert(std::string input, std::string output);
		float x_start;
		float x_end;
		float y_start;
		float y_end;
		float z_start;
		float z_end;

		h3d::Vec3<float> m_lastIntersectPoint;
		std::array<h3d::Math::Triangle,12> m_tris;

		struct impl;
		static std::unique_ptr<impl> m_impl;
	public:
		H3D_API BoundingBox();
		H3D_API BoundingBox(float xstart, float xend,
							float ystart, float yend,
							float zstart, float zend);
		//H3D_API BoundingBox(Mesh mesh);
		H3D_API ~BoundingBox();

		void H3D_API render();

		void H3D_API setValues(float x_s,float x_e,
							   float y_s,float y_e,
							   float z_s,float z_e);

		void H3D_API create();
		void H3D_API createFromMultiple(std::vector<h3d::BoundingBox*>& boxes);
		bool H3D_API intersect(const h3d::Math::Ray& ray);
	};
}