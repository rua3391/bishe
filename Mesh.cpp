#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh(const std::vector<vertex> &vertex, const std::vector<DWORD> &indices, const std::vector<texture> &texture) :
    cModule("Mesh"),
    _vertex(vertex),
    _indices(indices),
    _texture(texture)
{
}

Mesh::~Mesh()
{

}

void Mesh::serialize(void *out)
{

}

void Mesh::unserialize()
{

}

void Mesh::final()
{
}

void Mesh::init()
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertex.size() * sizeof(vertex), &_vertex[0], GL_STATIC_DRAW);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(DWORD), &_indices[0], GL_STATIC_DRAW);

    // 顶点位置
    glEnableVertexAttribArray(0);   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    // 顶点法线
    glEnableVertexAttribArray(1);   
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);   
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texcoords));

    glBindVertexArray(0);
}

void Mesh::reflcetMesh(Shader *shader)
{
    DWORD diffuseNr = 1;
    DWORD specularNr = 1;
    for(DWORD i = 0; i < _texture.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
        // 获取纹理序号（diffuse_textureN 中的 N）
        std::string number;
        std::string type = _texture[i].type;
        if(type == "difftexture")
            number = std::to_string(diffuseNr++);
        else if(type == "spectexture")
            number = std::to_string(specularNr++);

        shader->uniformSet1i(("M." + type + "[" + number + "]"), i);
        glBindTexture(GL_TEXTURE_2D, _texture[i].id);
    }

    // 绘制网格
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}