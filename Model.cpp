#include "Model.h"

#include "Mesh.h"
#include "Shader.h"
Model::Model():cModule("Model")
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
	const aiScene* scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		error("ASSIMP读取模型错误:%s", importer.GetErrorString());
		return;
	}

	_directory = path.substr(0, path.find_last_of('/'));
	_processNode(scene->mRootNode, scene);
}

void Model::drawModel(Shader *shader)
{
    for(auto& i : _mesh)
        i.reflcetMesh(shader);   
}

void Model::_processNode(aiNode *node, const aiScene *scene)
{
    // 处理节点所有的网格
    for(DWORD i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        _mesh.emplace_back(_processMesh(mesh, scene));         
    }
    // 递归处理子节点
    for(DWORD i = 0; i < node->mNumChildren; i++)
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
	for (auto i = 0; i < mesh->mNumVertices; ++i)
	{
		vertex vertex;
		glm::vec3 vec(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.position = vec;
        if(mesh->HasNormals())
        {
            vec.x = mesh->mNormals[i].x;
            vec.y = mesh->mNormals[i].y;
            vec.z = mesh->mNormals[i].z;
            vertex.normal = vec;
        }
		if (mesh->mTextureCoords[0])
		{
			vertex.texcoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertex.texcoords = glm::vec2(0);
		}

		vertices.push_back(vertex);
	}

	//处理索引
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (DWORD j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//材质
	if (mesh->mMaterialIndex >= 0)
	{
		auto material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<texture> diffuseMaps = _processMaterialTextures(material,aiTextureType_DIFFUSE, "difftexture", scene);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<texture> specularMaps = _processMaterialTextures(material,aiTextureType_SPECULAR, "spectexture", scene);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, indices, textures);
}

std::vector<texture> Model::_processMaterialTextures(aiMaterial* mat, aiTextureType type, std::string textype, const aiScene* scene)
{
    std::vector<texture> textures;
    for(DWORD i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        //检查纹理是否已加载
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
        {   // if texture hasn't been loaded already, load it
            texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->_directory);
            texture.type = textype;
            texture.path = str.C_Str();
            textures.push_back(texture);
            _textureLoaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
	return textures;
}

