#include "Texture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

Texture::Texture() : cModule("TEXTURE")
{
}

Texture::~Texture()
{
}

bool Texture::init(const std::string& path, DWORD num)
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
		debug("format:%d", format);
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

bool Texture::activeTexture(DWORD num)
{
	if(!_unit.count(num))
	{
		error("激活纹理单元非法, %d号纹理单元未绑定纹理", num);
		return false;
	}
	glActiveTexture(GL_TEXTURE0 + num);
	return true;
}

SDWORD Texture::getTextureId(DWORD num)
{
	if(!_unit.count(num))
		return -1;
	return _unit[num];
}