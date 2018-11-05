#include "../../H3D/Posteffects/SSAO.hpp"
#include "../../H3D/Graphics/Program.hpp"

namespace {
	GLuint _normalBuffer;
	GLuint _zBuffer;

	static h3d::Program _program;
	static const GLchar* _fragCode = "";
}

bool h3d::Posteffects::initSSAO() {
	GLchar* code = R"(
		#version 330 core		

		uniform float ssao_level = 1.0;
		uniform float object_level = 1.0;
		uniform float ssao_radius = 5.0;
		uniform bool  weight_by_angle = true;
		uniform uint  point_count = 8;
		uniform bool  randomize_points = true;

		void main(){

		}
		)";
	return true;
}

void h3d::Posteffects::applySSAO(GLuint framebuffer,
								 SSAO_ControlValues &&vals) {
	
}