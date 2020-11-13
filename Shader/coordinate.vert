#version 330 core
layout(location = 0) in vec3 apos;
layout(location = 1) in vec2 atex;
out vec3 ourcolor;
out vec2 text_cord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(apos,1.0);
	text_cord = atex;
}