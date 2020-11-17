#ifndef OBJECT_H
#define OBJECT_H

#include "cModule.h"
#include "zEntry.h"

struct material
{
    glm::vec3   ambient;
    glm::vec3   diffuse;
    glm::vec3   specular;
    FLOAT       shiness;
};

struct Lightcolor;
class Shader;
class Texture;
class Object : public cModule, public zEntry
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
         * \param buffer 顶点属性数组
         * \param size 数组大小
         * \param vertex_file v着色器文件路径
         * \param fragment_file f着色器文件路径
         * 
         */
        bool init(FLOAT *buffer, DWORD size, const std::string &vertex_file, const std::string &fragment_file);
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
        /**
         * \brief 填充消息 
         * 
         */
        void fill(Proto::Common::ObjectProto &out); 
    public:
        /**
         * \brief 初始化纹理
         * \param path 纹理图片路径
         * 
         */ 
        bool initTexture(std::string path);
        /**
         * \brief 应用纹理
         * 
         */
        void avtiveTexture(); 
        /**
         * \brief 绑定此物件
         * 
         */
        void bindObject(); 
        /**
         * \brief 设置材质
         * \param ambient 环境光
         * \param diffuse 漫反射光
         * \param specular 镜面反射光
         * \param shiness 反光度
         * 
         */
        void setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, FLOAT shiness);
        /**
         * \brief 设置物件位置
         * 
         */
        void setPosition();
        /**
         * \brief 更新model矩阵
         * \param translation 位移向量
         * \param radians 旋转角度
         * \param rotation 旋转轴向量
         * \param scale 缩放向量
         * 
         */
        void updateModel(glm::vec3 translation, FLOAT radians, glm::vec3 rotation, glm::vec3 scale);
        /**
         * \brief 根据冯模型算出物体颜色 
         * 
         */
        void setColor(const Lightcolor &color); 
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
        /**
         * \brief 已激活纹理单元个数
         * 
         */
        DWORD _activenum;  
};

#endif