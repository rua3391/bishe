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
    Simple = 1000,      //简易光源
    Direction = 1001,   //平行光    特点在无关光源位置，且强度不会衰减
    Point = 1002,       //点光源    特点在于光源位置参与计算漫反射光，且强度会衰减
    Spot = 1003,   //聚光      特点在于切光角决定了聚光的半径，在半径之外的不应显示颜色或应显示暗色

    LightMax = 1004
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
    glm::vec3 direction;
    FLOAT constant;
    FLOAT linear;
    FLOAT quadratic;
    FLOAT cutoff;
    FLOAT outcutoff;
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
         * \brief 设置光照衰减 常量系数
         * 
         */ 
        void setLightConstant(FLOAT num);
        /**
         * \brief 设置光照衰减 线性系数
         * 
         */ 
        void setLightLinear(FLOAT num);
        /**
         * \brief 设置光照衰减 平方系数
         * 
         */ 
        void setLightQuadratic(FLOAT num);
        /**
         * \brief 设置光照方向
         * 
         */ 
        void setLightDirection(const glm::vec3 &dir);
        /**
         * \brief 设置切光角
         * 
         */ 
        void setLightCutoff(FLOAT num);
        /**
         * \brief 设置外圆锥切光角
         * 
         */
        void setLightOutCutoff(FLOAT num); 
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