#ifndef TEXTURE_H
#define TEXTURE_H

#include "cModule.h"

/**
 * \brief 纹理类型
 * 
 */ 
enum TextureType
{
    Normal = 1,
    Diffuse = 2,
    Specular = 3,

    TextureMax = 4
};
class Shader;
/**
 * \brief 纹理类
 *
 */
class Texture : public cModule
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        Texture();
        /**
         * \brief 析构函数 
         * 
         */
        ~Texture(); 
    public:
        /**
         * \brief 初始化资源
         * \param path 纹理文件路径
         * \param num 激活第num个纹理单元
         * \return 初始化是否成功
         * 
         */
        bool init(const std::string& path, DWORD num, TextureType type = Normal); 
        /**
         * \brief 序列化
         * 
         */
        void serialize(void *out);
        /**
         * \brief 反序列化
         * 
         */
        void unserialize();
        /**
         * \brief 释放资源
         * 
         */
        void final();
    public:
        /**
         * \brief 激活并绑定纹理单元
         * \param num 第num个纹理单元
         * 
         */
        bool activeTexture(Shader *shader);
        /**
         * \brief 获取num号单元纹理id
         * \param num 第num个纹理单元
         * 
         */
        SDWORD getTextureId(DWORD num);    
    private:
        /**
         * \brief 激活纹理单元与纹理id映射关系
         * 
         */
        std::map<DWORD, DWORD> _unit;
        /**
         * \brief 纹理单元与纹理类型映射
         * 
         */ 
        std::map<DWORD, TextureType> _type;
};

#endif