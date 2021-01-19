#version 330 core
layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 text;

out vec3 normalvector;
out vec3 worldpos;
out vec2 textpos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	worldpos = vec3(model * vec4(apos, 1.0));
	normalvector = mat3(transpose(inverse(model))) * normal;
	textpos = text;
	
	gl_Position = projection * view * model * vec4(apos,1.0);
}