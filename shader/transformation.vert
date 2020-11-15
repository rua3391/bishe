#version 330 core
layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 acolor;
layout(location = 2) in vec2 atex;
out vec3 ourcolor;
out vec2 text_cord;
uniform mat4 transform;

void main(){
	gl_Position = transform * vec4(apos,1.0);
	ourcolor = acolor;
	text_cord = atex;
}