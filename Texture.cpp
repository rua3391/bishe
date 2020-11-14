#include "Texture.h"
#include "stb_image.h"

Texture::Texture() : cModule("TEXTURE")
{
}

Texture::~Texture()
{
}

bool Texture::init(std::string path, DWORD num)
{
    if(num >= 16)
    {
        error("纹理单元超出上限");//实际上最新glew支持32个
        return false;
    }
    DWORD Texture;
	glGenTextures(1, &Texture);
    glActiveTexture(GL_TEXTURE0 + num);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// 加载并生成纹理
    SDWORD width, height, nrchannels;
	stbi_set_flip_vertically_on_load(true);
    BYTE* data;
	data = stbi_load(path.c_str(), &width, &height, &nrchannels, 0);
	if (data) 
    {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
    {
		error("加载%u号纹理失败", num);
        return false;
	}
	stbi_image_free(data);
	_unit[num] = Texture;
	debug("%u号纹理初始化成功", num);
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

void Texture::activeTexture(DWORD num)
{
	glActiveTexture(GL_TEXTURE0 + num);
	glBindTexture(GL_TEXTURE_2D, _unit[num]);
}