#version 330 core
layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 normal;

out vec3 normalvector;
out vec3 worldpos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(apos,1.0);
	worldpos = vec3(model * vec4(apos, 1.0));
	normalvector = mat3(transpose(inverse(model))) * normal;
}