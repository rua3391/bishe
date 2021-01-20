#version 330 core
out vec4 FragColor;

in vec3 normalvector;
in vec3 worldpos;
in vec2 textpos;

#define simple 1000
#define directionLight 1001
#define pointLight 1002
#define spotLight 1003

struct material
{
	vec3 ambient;//环境光
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
	vec3 ambient;//环境光强度
	vec3 diffuse;//漫反射光强度
	vec3 specular;//镜面高光强度
	//衰减因子
	float constant;
    float linear;
    float quadratic;
	//切光角 反应聚光的半径
	float cutoff;
	//外切光角 用于平滑操作
	float outcutoff;
	//光照类型
	int type;
};

uniform material M;
uniform Light L;
uniform vec3 camerapos;

vec3 lightdirection;

void calculateLightdirection(int type)
{
	if(type == directionLight)
		lightdirection = normalize(-L.direction);
	else
		lightdirection = normalize(L.position - worldpos);
}

vec3 calculateAmbient(int type)
{
	vec3 ambient;
	if(M.diffuseTexture)
		ambient = L.ambient * texture(M.difftexture, textpos).rgb;
	else
		ambient = L.ambient * M.ambient;
	return ambient;
}

vec3 calculateDiffuse(int type)
{
	vec3 diff;
	vec3 normal = normalize(normalvector);
	float diffusefactor = max(dot(normal, lightdirection), 0.0);
	if(M.diffuseTexture)
		diff = L.diffuse * diffusefactor * texture(M.difftexture, textpos).rgb;
	else
		diff = L.diffuse * diffusefactor * M.diffuse;
	
	return diff;
}

vec3 calculateSpecular(int type)
{
	vec3 specular;
	vec3 viewdirection = normalize(camerapos - worldpos);
	vec3 reflectdirection = reflect(-lightdirection, normalize(normalvector));
	float shininess = pow(max(dot(viewdirection, reflectdirection), 0.0f),M.shiness);
	if(M.specularTexture)
		specular = L.specular * shininess * texture(M.spectexture, textpos).rgb;
	else
		specular = L.specular * shininess * M.specular;
	return specular;
}

float calculateAttenuation(int type)
{
	float attenuation = 1.0f;
	if(type != directionLight)
	{
		float d = length(L.position - worldpos);
		attenuation = 1.0 / (L.constant + L.linear * d + L.quadratic * (d * d));
	}
	return attenuation;
}

void main()
{
	calculateLightdirection(L.type);
	float theta = dot(lightdirection, normalize(-L.direction)); 
	float epsilon   = L.cutoff - L.outcutoff;
	float intensity = clamp((theta - L.outcutoff) / epsilon, 0.0, 1.0);

	vec3 ambient = calculateAmbient(L.type);
	vec3 diffuse = calculateDiffuse(L.type);
	vec3 specular = calculateSpecular(L.type);
	float attenuation = calculateAttenuation(L.type);
	//将衰减叠加到光照上
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	if(L.type == spotLight)
	{
		diffuse *= intensity;
    	specular *= intensity;
	}
	FragColor = vec4((ambient + diffuse + specular), 1.0f);
}
