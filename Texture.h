#ifndef TEXTURE_H
#define TEXTURE_H

#include "cModule.h"
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
        bool init(std::string path, DWORD num); 
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
    private:
        /**
         * \brief 纹理id
         * 
         */
        DWORD _ID; 
};







#endif