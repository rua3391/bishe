#ifndef LIGHT_H
#define LIGHT_H

#include "cModule.h"
#include "Common.pb.h"
#include "zEntry.h"

/**
 * \brief 光照类型枚举
 * 
 */ 
enum LightType
{
    Simple = 1000,
    Direction = 1001,
    Point = 1002,

    LightMax = 1003
};
/**
 * \brief 光照结构体
 * 
 */ 
struct Lightcolor
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;
    FLOAT constant;
    FLOAT linear;
    FLOAT quadratic;
    LightType type;
};
/**
 * \brief 光照
 * 
 */ 
class Light : public cModule, public zEntry
{
    public:
        /**
         * \brief 构造函数
         * 
         */
        explicit Light(LightType type = LightType::Simple);
        /**
         * \brief 析构函数
         * 
         */
        Light(QWORD id, const std::string &name);
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
        bool init(const glm::vec3 &pos);
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
         * \brief 返回光照类型
         * 
         */ 
        const SDWORD getType();
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
        /**
         * \brief 设置光照衰减
         * 
         */ 
        void setLightConstant(FLOAT num);
        /**
         * \brief 设置光照衰减
         * 
         */ 
        void setLightLinear(FLOAT num);
        /**
         * \brief 设置光照衰减
         * 
         */ 
        void setLightQuadratic(FLOAT num);
        /**
         * \brief 填充光源信息
         * 
         */
        void fill(Proto::Common::LightProto &out);     
    protected:
        /**
         * \brief 光照
         * 
         */
        Lightcolor _light;     
};

#endif