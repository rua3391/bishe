#version 330 core
out vec4 Fragcolor;
in vec4 vertexcolor;
uniform vec4 mycolor;
void main(){
	Fragcolor = vertexcolor;
}