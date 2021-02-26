#include "Texture.h"
#include "Shader.h"
#include "Model.h"

#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
	#include "stb_image.h"
#endif

Texture::Texture() : cModule("TEXTURE")
{
}

Texture::~Texture()
{
}

bool Texture::init(const std::string& path, DWORD num, TextureType type)
{
    if(num >= 16)
    {
        error("纹理单元超出上限");//实际上最新glew支持32个
        return false;
    }
	if(_unit.count(num))
	{
		error("第%d纹理单元已绑定纹理", num);
		return false;
	}
    DWORD Texture;
	glGenTextures(1, &Texture);

	// 加载并生成纹理
    SDWORD width, height, nrchannels;
	stbi_set_flip_vertically_on_load(true);
    BYTE* data = stbi_load(path.c_str(), &width, &height, &nrchannels, 0);
	if (data) 
    {
		GLenum format;
		switch (nrchannels)
		{
			case 1:
				format = GL_RED; break;
			case 3:
				format = GL_RGB; break;
			case 4:
				format = GL_RGBA; break;
			default:
				break;
		}
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else 
    {
		error("加载%u号纹理失败", num);
        return false;
	}
	stbi_image_free(data);
	_unit[num] = Texture;
	_type[num] = type;
	debug("%u号纹理初始化成功, 纹理id%d", num, Texture);
    return true;
}

void Texture::serialize(void* out)
{
    //todo
}

void Texture::unserialize()
{
    //todo
}

void Texture::final()
{
    
}

bool Texture::activeTexture(Shader *shader)
{
	for(const auto &i : _unit)
	{
		DWORD num = i.first;
		SDWORD tid = i.second;
		TextureType type = _type[num];
		if(type >= TextureMax || type < 0)
		{
			error("纹理类型不符, 激活失败");
			return false;
		}
		if(tid == -1)
		{
			error("获取%u号纹理id失败, 激活失败", num);
			return false;
		}
		glActiveTexture(GL_TEXTURE0 + num);
		glBindTexture(GL_TEXTURE_2D, tid);
		std::string name, s;
		switch(type)
		{
			case Diffuse:
				name = "M.difftexture"; s = "M.diffuseTexture"; break;
			case Specular:
				name = "M.specspecular"; s = "M.specularTexture"; break;
			default:
				break;
		}
		if(!name.empty())
		{
			shader->uniformSet1i(name, num);
			shader->uniformSetBool(s, true);
		}
	}
	return true;
}

SDWORD Texture::getTextureId(DWORD num)
{
	if(!_unit.count(num))
		return -1;
	return _unit[num];
}

DWORD Model::_textureFromFile(const std::string &path, const std::string &directory)
{
    std::string filename = path;
    filename = directory + '/' + filename;
    DWORD textureID;
    glGenTextures(1, &textureID);

    SDWORD width, height, nrchannels;
	// stbi_set_flip_vertically_on_load(true);
    BYTE* data = stbi_load(filename.c_str(), &width, &height, &nrchannels, 0);
	if (data) 
    {
		GLenum format;
		switch (nrchannels)
		{
			case 1:
				format = GL_RED; break;
			case 3:
				format = GL_RGB; break;
			case 4:
				format = GL_RGBA; break;
			default:
				break;
		}
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//s轴
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//t轴
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);		//缩小图像时过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//放大图像时过滤方式
	}
   else 
    {
		error("模型加载纹理失败");
        return -1;
	}

    return textureID;
}