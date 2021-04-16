#include "Model.h"

#include "Mesh.h"
#include "Shader.h"
#include "Engine.h"
#include "Camera.h"
#include "GLightManager.h"

Model::Model():
    cModule("Model"),
    _model(1.0f),
    _view(1.0f),
    _projection(1.0f),
    _shader(NULL)
{
}

Model::~Model()
{

}

void Model::serialize(void *out)
{

}

void Model::unserialize()
{

}

void Model::final()
{

}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		error("ASSIMP读取模型错误:%s", importer.GetErrorString());
		return;
	}

	_directory = path.substr(0, path.find_last_of('/'));
	_processNode(scene->mRootNode, scene);
    _shader = new Shader();
    if(!_shader)
    {
        error("初始化模型Shader失败，内存不足");
        return;
    }
    _shader->init("shader/model.vert","shader/model.frag");
    debug("载入模型%s成功", path.c_str());
}

void Model::drawModel()
{
    _shader->useProgram();
    reflectPosition();
    // reflectLight();
    for(auto& i : _mesh)
    {
        i.reflcetMesh(_shader);   
    }
}

void Model::_processNode(aiNode *node, const aiScene *scene)
{
    // 处理节点所有的网格
    for(DWORD i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        _mesh.push_back(_processMesh(mesh, scene));         
    }
    // 递归处理子节点
    for(DWORD i = 0; i < node->mNumChildren; ++i)
    {
        _processNode(node->mChildren[i], scene);
    }
}

Mesh Model::_processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<vertex> vertices;
	std::vector<DWORD> indices;
	std::vector<texture> textures;
	//处理位置
	for (DWORD i = 0; i < mesh->mNumVertices; ++i)
	{
		vertex _vertex;
        glm::vec3 vector;
        // 位置
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        _vertex.position = vector;
        // 法向量
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            _vertex.normal = vector;
        }
        // 纹理坐标
        if(mesh->mTextureCoords[0]) 
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            _vertex.texcoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            _vertex.tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            _vertex.bitangent = vector;
        }
        else
            _vertex.texcoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(_vertex);
	}
	//处理索引
	for (DWORD i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (DWORD j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	//材质

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<texture> diffuseMaps = _processMaterialTextures(material, aiTextureType_DIFFUSE, "difftexture");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<texture> specularMaps = _processMaterialTextures(material, aiTextureType_SPECULAR, "spectexture");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<texture> normalMaps = _processMaterialTextures(material, aiTextureType_HEIGHT, "normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<texture> heightMaps = _processMaterialTextures(material, aiTextureType_AMBIENT, "height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return Mesh(vertices, indices, textures);
}

std::vector<texture> Model::_processMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string &textype)
{
    std::vector<texture> textures;
    for(DWORD i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // 检查当前路径纹理是否已加载
        bool skip = false;
        for(DWORD j = 0; j < _textureLoaded.size(); j++)
        {
            if(std::strcmp(_textureLoaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(_textureLoaded[j]);
                skip = true; 
                break;
            }
        }
        if(!skip)
        {   
            texture _texture;
            _texture.id = _textureFromFile(str.C_Str(), this->_directory);
            _texture.type = textype;
            _texture.path = str.C_Str();
            textures.push_back(_texture);
            _textureLoaded.push_back(_texture);  
        }
    }
    return textures;
}

void Model::translate(const glm::vec3 &translation)
{
    _model = glm::translate(glm::mat4(1.0f), translation);
}

void Model::rotate(FLOAT radians, const glm::vec3 &rotation)
{
    if(radians)
        _model = glm::rotate(_model, glm::radians(radians), rotation);
}

void Model::scaling(const glm::vec3 &scale)
{
    _model = glm::scale(_model, scale);
}

void Model::reflectPosition()
{
    _shader->useProgram();
    DWORD width = Engine::getInstance()->screenx;
    DWORD height = Engine::getInstance()->screeny;
	_view = Camera::getInstance()->getViewMatrix();
    _projection = glm::perspective(glm::radians(Camera::getInstance()->getCameraZoom()), (FLOAT)width / (FLOAT)height, 0.1f, 100.0f);
    _shader->uniformSetmat4("model", _model);
    _shader->uniformSetmat4("view", _view);
    _shader->uniformSetmat4("projection", _projection);
}

void Model::reflectLight()
{
    // bindObject();
    DWORD size = GLightManager::getInstance()->size();
    _shader->uniformSet1i("size", size);
    _shader->uniformSetvec3("camerapos", Camera::getInstance()->getCameraPosition());
    struct LightCallback : public zCallback<Light>
    {
        LightCallback(Model *model) : _model(model){}
        ~LightCallback(){};
        bool exec(Light *light)
        {
            const auto &color = light->getLight();
            std::string tmp = "[" + std::to_string(cnt) + "]";
            _model->_shader->uniformSetvec3("L" + tmp + ".position", color.position);
            _model->_shader->uniformSetvec3("L" + tmp + ".ambient", color.ambient);
            _model->_shader->uniformSetvec3("L" + tmp + ".diffuse", color.diffuse);
            _model->_shader->uniformSetvec3("L" + tmp + ".specular", color.specular);
            _model->_shader->uniformSet1i("L" + tmp + ".type", color.type);
            _model->_shader->uniformSet1f("L" + tmp + ".constant", color.constant);
            _model->_shader->uniformSet1f("L" + tmp + ".linear", color.linear);
            _model->_shader->uniformSet1f("L" + tmp + ".quadratic", color.quadratic);
            _model->_shader->uniformSetvec3("L" + tmp + ".direction", color.direction);
            _model->_shader->uniformSet1f("L" + tmp + ".cutoff", color.cutoff);
            _model->_shader->uniformSet1f("L" + tmp + ".outcutoff", color.outcutoff);
            ++cnt;
            return true;
        }
        Model *_model;
        DWORD cnt;
    };
    LightCallback lightcallback(this);
    GLightManager::getInstance()->execEveryN(lightcallback);
}
