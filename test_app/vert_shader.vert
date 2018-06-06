#version 330 core

out vec2 uv;

layout(location=0) in vec3 vert_in;
layout(location=1) in vec3 uv_in;
layout(location=2) in vec3 normal_in;

void main()
{
	gl_Position = vec4(vert_in,1.0);
	uv = uv_in.xy;
}