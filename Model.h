#ifndef MODEL_H
#define MODEL_H

#include "cModule.h"
#include "Mesh.h"
class Shader;
class Model : public cModule
{
    public:
        /**
         * \brief 构造函数
         * 
         */
        Model(); 
        /**
         * \brief 析构函数 
         * 
         */
        ~Model(); 
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
         * \brief 加载模型
         * 
         */
        void loadModel(const std::string& path); 
        /**
         * \brief 画出模型
         * 
         */
        void drawModel(); 
        /**
         * \brief 位移物体
         * \param translation 位移向量
         * 
         */
        void translate(const glm::vec3 &translation);
        /**
         * \brief 旋转物体
         * \param radians 旋转角度
         * \param rotation 旋转轴
         * 
         */  
        void rotate(FLOAT radians, const glm::vec3 &rotation);
        /**
         * \brief 缩放物体
         * \param scale 缩放向量(x,y,z轴方向缩放)
         * 
         */
        void scaling(const glm::vec3 &scale);
        /**
         * \brief 反应物件在摄像机中展示位置
         * 
         */
        void reflectPosition();
        /**
         * \brief 根据冯模型算出模型颜色 
         * 
         */
        void reflectLight();
    private:
        /**
         * \brief 模型网格数据
         * 
         */ 
        std::vector<Mesh> _mesh;
        /**
         * \brief 处理assimp每个结点 
         * 
         */
        void _processNode(aiNode *node, const aiScene *scene);
        /**
         * \brief 处理每个结点的网格数据
         * 
         */
        Mesh _processMesh(aiMesh *mesh, const aiScene *scene); 
        /**
         * \brief 处理每个网格的纹理
         * 
         */
        std::vector<texture> _processMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string &textype);
        /**
         * \brief 加载纹理
         * 
         */
        DWORD _textureFromFile(const std::string &path, const std::string &directory); 
        // /**
        //  * \brief 已加载纹理
        //  * 
        //  */
        std::vector<texture> _textureLoaded;
        /**
         * \brief 已加载纹理
         * 
         */
        // std::unordered_map<const char*, texture> _textureLoaded; 
        /**
         * \brief 文件夹路径
         * 
         */
        std::string _directory; 
        /**
         * \brief shader
         * 
         */ 
        Shader *_shader;
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
};
#endif