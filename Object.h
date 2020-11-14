#ifndef OBJECT_H
#define OBJECT_H

#include "cModule.h"

struct material
{
    glm::vec3   ambient;
    glm::vec3   diffuse;
    glm::vec3   specular;
    FLOAT       shiness;
};

class Shader;
class Texture;
class Object : public cModule
{
    public:
        /**
         * \brief 构造函数
         * 
         */
        Object();
        /**
         * \brief 析构函数
         * 
         */
        ~Object();  
    public:
        /**
         * \brief 初始化
         * 
         */
        bool init(FLOAT *buffer, const std::string &vertex_file, const std::string &fragment_file);
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
         * \brief 绑定此物件
         * 
         */
        void bindObject(); 
        /**
         * \brief 设置材质
         * 
         */
        void setMaterial();
        /**
         * \brief 设置物件位置
         * 
         */
        void setPosition();  
    private:
        /**
         * \brief 顶点属性数组对象
         * 
         */
        DWORD _vao;
        /**
         * \brief 顶点缓冲对象
         * 
         */
        DWORD _vbo;  
        /**
         * \brief 着色器
         * 
         */
        Shader *_shader;
        /**
         * \brief 纹理
         * 
         */
        Texture *_texture;
        /**
         * \brief model矩阵 将局部坐标转世界坐标
         * 
         */
        glm::mat4 _model;
        /**
         * \brief view矩阵 将世界坐标转视觉空间坐标
         * 
         */
        glm::mat4 _view;   
        /**
         * \brief projection矩阵 将视觉坐标转为投影坐标
         * 
         */
        glm::mat4 _projection;
        /**
         * \brief 材质 
         * 
         */
        material _material;
        /**
         * \brief 摄像机位置
         * 
         */
        glm::vec3 _position; 
};

#endif