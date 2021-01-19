#version 330 core
out vec4 FragColor;

in vec3 normalvector;
in vec3 worldpos;
in vec2 textpos;

struct material
{
	// vec3 ambientcolor;//环境光
	// vec3 diffuse;//漫反射光
	sampler2D texture;//可用纹理去计算环境光和漫反射光
	sampler2D specular;//用纹理去计算镜面高光
	float shiness;//光照系数
};

struct Light
{
	vec3 position;//光照位置
	vec3 ambientlight;//环境光强度
	vec3 diffuselight;//漫反射光强度
	vec3 specularlight;//镜面高光强度
};

uniform material M;
uniform Light L;
//uniform vec3 ambientcolor;

uniform vec3 camerapos;


void main()
{
	//环境光
	vec3 ambient = L.ambientlight * texture(M.texture, textpos).rgb;
	//漫反射光
	vec3 normal = normalize(normalvector);
	vec3 lightdirection = normalize(L.position - worldpos);
	float diffusefactor = max(dot(normal, lightdirection), 0.0);
	vec3 diff = L.diffuselight * diffusefactor * texture(M.texture, textpos).rgb;
	//镜面高光
	vec3 viewdirection = normalize(camerapos - worldpos);
	vec3 reflectdirection = reflect(-lightdirection, normal);
	float shininess = pow(max(dot(viewdirection, reflectdirection), 0.0f),M.shiness);//32?????????????????????????????????
	vec3 specular = L.specularlight * shininess * texture(M.specular, textpos).rgb;

	FragColor = vec4((ambient + diff + specular), 1.0f);//???????????��?�X?????��???????
}
