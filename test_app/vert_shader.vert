#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 posout;
out vec3 Normal;
out vec3 FragPos;  

uniform mat4x4 mat_scale;
uniform mat4x4 mat_rotate;
uniform mat4x4 mat_proj;

void main()
{
	TexCoords = aTexCoords;    
	posout = aPos;
	gl_Position = mat_proj * mat_scale * mat_rotate* vec4(aPos,1.0);
	Normal = aNormal;
}