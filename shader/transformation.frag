#version 330 core
out vec4 FragColor;
in vec3 ourcolor;
in vec2 text_cord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;
//uniform float alpha;

void main(){
	FragColor = mix(texture(Texture1, text_cord), texture(Texture2, vec2(1.0 - text_cord.x, text_cord.y)), 0.2);
}
