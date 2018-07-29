#version 330 core

in vec2 TexCoords;
in vec3 posout;
out vec4 FragColor;

void main()
{    
    FragColor = vec4(posout.zzz,1.0);
}