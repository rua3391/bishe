#ifndef LIGHT_H
#define LIGHT_H

#include "cModule.h"
#include "Common.pb.h"

/**
 * \brief 光照强度
 * 
 */ 
struct Lightcolor
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;
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
        Light(const glm::vec3 &pos);
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
    public:
        /**
         * \brief 返回光照结构体
         * 
         */
        const Lightcolor& getLight();
        /**
         * \brief 返回光照位置
         * 
         */
        const glm::vec3& getPosition();
        /**
         * \brief 设置环境光照
         * 
         */
        void setAmbientLight(const glm::vec3 &ambient);
        /**
         * \brief 设置漫反射光照
         * 
         */
        void setDiffuseLight(const glm::vec3 &diffuse);
        /**
         * \brief 设置镜面高光
         * 
         */
        void setSpecularLight(const glm::vec3 &specular); 
        /**
         * \brief 设置全部光照值
         * 
         */
        void setLightColor(const Lightcolor &lightcolor);
        /**
         * \brief 设置光照位置
         * 
         */
        void setLightPosition(const glm::vec3 &position);    
    private:
        /**
         * \brief 光照
         * 
         */
        Lightcolor _light;     
};

#endif