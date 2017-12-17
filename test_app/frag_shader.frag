#version 450 core

out vec4 color;
in vec4 col_a;

void main(){
	color = col_a;
}