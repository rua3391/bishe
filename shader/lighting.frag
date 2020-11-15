#version 330 core
out vec4 FragColor;

in vec3 normalvector;
in vec3 worldpos;

struct material
{
	vec3 ambientcolor;//环境光照下这个物体反射颜色
	vec3 diffuse;//漫反射光照下物体的颜色
	vec3 specular;//镜面光照对物体的颜色影响
	float shiness;//影响镜面高光的散射/半径
};

struct Light
{
	vec3 position;// 光照位置

	vec3 ambientlight;//环境光
	vec3 diffuselight;//漫反射光
	vec3 specularlight;//镜面高光
};

uniform material M;
uniform Light L;
//uniform vec3 ambientcolor;

uniform vec3 camerapos;


void main()
{
	//ambient light
//	float ambientfactor = 0.1f;//ambient factor
	vec3 ambient = L.ambientlight * M.ambientcolor;
	//diffuse light
	vec3 normal = normalize(normalvector);
	vec3 lightdirection = normalize(L.position - worldpos);
	float diffusefactor = max(dot(normal, lightdirection), 0.0);
	vec3 diff = L.diffuselight * (diffusefactor * M.diffuse);
	//specular highlight
//	float SpecularFactor = 0.5f;//the strength of Specular highlight
	vec3 viewdirection = normalize(camerapos - worldpos);
	vec3 reflectdirection = reflect(-lightdirection, normal);
	float shininess = pow(max(dot(viewdirection, reflectdirection), 0.0f),M.shiness);//32是反应了物体的反光度，反光度越高反射能力越强
	vec3 specular = M.specular * shininess * L.specularlight;

	FragColor = vec4((ambient + diff + specular), 1.0f);//环境光漫反射镜面反射叠加得出最终成色
}
