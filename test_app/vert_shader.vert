#version 450 core

layout (location=0) in vec4 cord;
uniform mat4 proj_mat;
uniform mat4 view_mat;
out vec4 pos;
out vec4 col_a;

void main()
{
	col_a = cord;
	pos = cord;
}