#ifndef LIGHT_H
#define LIGHT_H

#include "cModule.h"

struct Lightcolor
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};
/**
 * \brief 光照
 * 
 */ 
class Light : public cModule
{
    public:
        /**
         * \brief 构造函数
         * 
         */
        Light();
        /**
         * \brief 析构函数
         * 
         */
        ~Light();  
    public:
        /**
         * \brief 初始化
         * 
         */
        void init();
        /**
         * \brief 释放资源
         * 
         */
        void final();  
        /**
         * \brief 序列化资源
         * 
         */
        void serialize(void* out);
        /**
         * \brief 反序列化资源
         * 
         */
        void unserialize();
    private:
        /**
         * \brief 光照
         * 
         */
        Lightcolor _light;     
};

#endif