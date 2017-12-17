#include "SSAO.hpp"

#include "../Program.hpp"

void h3d::Posteffects::applySSAO(GLuint framebuffer,
								 SSAO_ControlValues &&vals) {
	static h3d::Program gl_program;

	static GLchar frag_code[] = (R"(#version 450 core
	
	// input sampler color, normal, depth
	layout (binding = 0) uniform sampler2D sColor;
	layout (binding = 1) uniform sampler2D sNormalDepth;
	
	// final output
	layout (location = 0) out vec4 color;
	
	// control variables
	uniform float ssao_level         = 1.0;
	uniform float object_level       = 1.0;
	uniform float ssao_radius        = 5.0;
	uniform bool  weight_by_angle    = true;
	uniform uint  point_count		 = 8;
	uniform bool  randomize_points   = true;
	)");
}