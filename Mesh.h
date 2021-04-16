#ifndef MESH_H
#define MESH_H

#include "cModule.h"
/**
 * \brief 物体顶点结构体
 * 
 */ 
struct vertex 
{
    glm::vec3 position;     //坐标
    glm::vec3 normal;       //法向量
    glm::vec2 texcoords;    //纹理坐标
    glm::vec3 tangent;      //切线
    glm::vec3 bitangent;    //双切线
};
/**
 * \brief 纹理结构体
 * 
 */ 
struct texture 
{
    DWORD id;
    std::string type;
    std::string path;
};
class Shader;
/**
 * \brief 网格类
 * 
 */ 
class Mesh : public cModule
{
    public:
        /**
         * \brief 构造函数 
         * 
         */ 
        Mesh(const std::vector<vertex> &vertex, const std::vector<DWORD> &indices, const std::vector<texture> &texture);
        /**
         * \brief 析构函数 
         * 
         */
        ~Mesh();
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
        /**
         * \brief 初始化网格
         * 
         */
        void init(); 
        /**
         * \brief 绘制网格数据
         * 
         */
        void reflcetMesh(Shader *shader); 
    private:
        /**
         * \brief 顶点数组对象
         * 
         */
        DWORD _vao;
        /**
         * \brief 顶点缓冲对象
         * 
         */
        DWORD _vbo;  
        /**
         * \brief 索引缓冲对象
         * 
         */
        DWORD _ebo; 
        /**
         * \brief 网格数据
         * 
         */ 
        std::vector<vertex> _vertex;
        /**
         * \brief 网格数据
         * 
         */
        std::vector<DWORD> _indices;
        /**
         * \brief 网格数据
         * 
         */
        std::vector<texture> _texture;  
};
#endif