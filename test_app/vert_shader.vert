#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 posout;

void main()
{
	TexCoords = aTexCoords;    
	posout = aPos;
	gl_Position = vec4(aPos*0.5,1.0);
}