#version 330 core
out vec4 FragColor;

in vec3 normalvector;
in vec3 worldpos;
in vec2 textpos;

#define simple 1000
#define directionLight 1001
#define pointLight 1002

struct material
{
	vec3 ambientcolor;//环境光
	vec3 diffuse;//漫反射光
	vec3 specular;//镜面高光
	sampler2D difftexture;//漫反射贴图
	sampler2D spectexture;//镜面光贴图
	float shiness;//光照系数

	bool diffuseTexture;
	bool specularTexture;
};

struct Light
{
	vec3 direction;//光照方向 [从光源出发] 
	vec3 position;//光照位置 定向光不需要位置
	vec3 ambientlight;//环境光强度
	vec3 diffuselight;//漫反射光强度
	vec3 specularlight;//镜面高光强度
	//衰减因子
	float constant;
    float linear;
    float quadratic;
	//光照类型
	int type;
};

uniform material M;
uniform Light L;
uniform vec3 camerapos;


void main()
{
	//环境光
	vec3 ambient;
	if(M.diffuseTexture)
		ambient = L.ambientlight * texture(M.difftexture, textpos).rgb;
	else
		ambient = L.ambientlight * M.ambientcolor;

	//漫反射光
	vec3 normal = normalize(normalvector);
	vec3 lightdirection;
	if(L.type == directionLight)
		lightdirection = normalize(-L.direction);
	else
		lightdirection = normalize(L.position - worldpos);
	float diffusefactor = max(dot(normal, lightdirection), 0.0);
	vec3 diff;
	if(M.diffuseTexture)
		diff = L.diffuselight * diffusefactor * texture(M.difftexture, textpos).rgb;
	else
		diff = L.diffuselight * diffusefactor * M.diffuse;
	//镜面高光
	vec3 viewdirection = normalize(camerapos - worldpos);
	vec3 reflectdirection = reflect(-lightdirection, normal);
	float shininess = pow(max(dot(viewdirection, reflectdirection), 0.0f),M.shiness);
	vec3 specular;
	if(M.specularTexture)
		specular = L.specularlight * shininess * texture(M.spectexture, textpos).rgb;
	else
		specular = L.specularlight * shininess * M.specular;

	//计算衰减
	float attenuation;
	if(L.type != directionLight)
	{
		float d = length(L.position - worldpos);
		attenuation = 1.0 / (L.constant + L.linear * d + L.quadratic * (d * d));
	}
	else
	{
		attenuation = 1.0;
	}
	//将衰减叠加到光照上
	ambient *= attenuation;
	diff *= attenuation;
	specular *= attenuation;

	FragColor = vec4((ambient + diff + specular), 1.0f);
}
