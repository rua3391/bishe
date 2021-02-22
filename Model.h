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
        void drawModel(Shader *shader); 
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
        std::vector<texture> _processMaterialTextures(aiMaterial* mat, aiTextureType type, std::string textype, const aiScene* scene);
        /**
         * \brief 加载纹理
         * 
         */
        DWORD TextureFromFile(const std::string &path, const std::string &directory); 
        /**
         * \brief 已加载纹理
         * 
         */
        std::vector<texture> _textureLoaded;
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
};
#endif