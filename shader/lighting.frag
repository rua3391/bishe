#version 330 core
out vec4 FragColor;

in vec3 normalvector;
in vec3 worldpos;

struct material
{
	vec3 ambientcolor;//����������������巴����ɫ
	vec3 diffuse;//������������������ɫ
	vec3 specular;//������ն��������ɫӰ��
	float shiness;//Ӱ�쾵��߹��ɢ��/�뾶
};

struct Light
{
	vec3 position;// ����λ��

	vec3 ambientlight;//������
	vec3 diffuselight;//�������
	vec3 specularlight;//����߹�
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
	float shininess = pow(max(dot(viewdirection, reflectdirection), 0.0f),M.shiness);//32�Ƿ�Ӧ������ķ���ȣ������Խ�߷�������Խǿ
	vec3 specular = M.specular * shininess * L.specularlight;

	FragColor = vec4((ambient + diff + specular), 1.0f);//�����������侵�淴����ӵó����ճ�ɫ
}