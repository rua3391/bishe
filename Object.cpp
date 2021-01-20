#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Engine.h"
#include "Light.h"
#include "GObjManager.h"

Object::Object() : 
    zEntry(),
    cModule("OBJECT"),
    _vao(0),
    _vbo(0),
    _shader(NULL),
    _texture(NULL),
    _model(1.0f),
    _view(1.0f),
    _projection(1.0f)
{

}

Object::~Object()
{

}

void Object::final()
{
    if(_shader)
    {
        _shader->final();
        SAFE_DELETE(_shader);
    }
    if(_texture)
    {
        _texture->final();
        SAFE_DELETE(_texture);    
    }
}

bool Object::init(const std::vector<FLOAT> &buf)
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, buf.size() * sizeof(FLOAT), (void *)buf.begin().base(), GL_STATIC_DRAW);

    if(!_shader)
    {
        _shader = new Shader();
        if(!_shader)
        {
            ERROR("内存空间不足, shader创建失败");
            return false;    
        }
    }
    debug("物件初始化成功");
    this->id = QWORD(_vao) << 32 + QWORD(_vbo);
    if(!GObjManager::getInstance()->add(this))
    {
        error("物体加入失败, id已存在->%lld", this->id);
    }
    else
    {
        debug("物体加入全局物件管理器完毕, id->%lld, vao->%u, vbo->%u", this->id, _vao, _vbo);
    }
    return true;
}

bool Object::initShader(const std::string &vertex_file, const std::string &fragment_file)
{
    if(!_shader->init(vertex_file, fragment_file))
    {
        error("shader初始化失败");
        return false;
    }
    return true;
}

bool Object::initNormalTexture(const std::string &path, DWORD num)
{
    if(!_texture)
    {
        _texture = new Texture();
        if(!_texture)
        {
            error("内存空间不足, Texture创建失败");
            return false;
        }
    }
    if(!_texture->init(path, num))
    {
        error("texture初始化失败");
        return false;
    }
    return true;
}

bool Object::initDiffuseTexture(const std::string &path, DWORD num)
{
    if(!_texture)
    {
        _texture = new Texture();
        if(!_texture)
        {
            error("内存空间不足, Texture创建失败");
            return false;
        }
    }
    if(!_texture->init(path, num, Diffuse))
    {
        error("texture初始化失败");
        return false;
    }
    return true;
}

bool Object::initSpecularTexture(const std::string &path, DWORD num)
{
    if(!_texture)
    {
        _texture = new Texture();
        if(!_texture)
        {
            error("内存空间不足, Texture创建失败");
            return false;
        }
    }
    if(!_texture->init(path, num, Specular))
    {
        error("texture初始化失败");
        return false;
    }
    return true;
}

bool Object::activeTexture()
{
    if(_texture->activeTexture(_shader))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Object::serialize(void* out)
{
    //todo
}

void Object::unserialize()
{
    //todo
}

void Object::bindObject()
{
    _shader->useProgram();
    glBindVertexArray(_vao);
}

void Object::updateModel(const glm::vec3 &translation, FLOAT radians, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    _model = glm::translate(_model, translation);
    if(radians)
        _model = glm::rotate(_model, glm::radians(radians), rotation);
    _model = glm::scale(_model, scale);
}

void Object::translate(const glm::vec3 &translation)
{
    _model = glm::translate(glm::mat4(1.0f), translation);
}

void Object::rotate(FLOAT radians, const glm::vec3 &rotation)
{
    if(radians)
        _model = glm::rotate(_model, glm::radians(radians), rotation);
}

void Object::scaling(const glm::vec3 &scale)
{
    _model = glm::scale(_model, scale);
}

void Object::reflectPosition()
{
    DWORD width = Engine::getInstance()->screenx;
    DWORD height = Engine::getInstance()->screeny;
	_view = Camera::getInstance()->getViewMatrix();
    _projection = glm::perspective(glm::radians(Camera::getInstance()->getCameraZoom()), (FLOAT)width / (FLOAT)height, 0.1f, 100.0f);
    _shader->uniformSetmat4("model", _model);
    _shader->uniformSetmat4("view", _view);
    _shader->uniformSetmat4("projection", _projection);
}

void Object::setMaterial(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, FLOAT shiness)
{
    _material.ambient = ambient;
    _material.diffuse = diffuse;
    _material.specular = specular;
    _material.shiness = shiness;
}

void Object::setAmbient(const glm::vec3 &ambient)
{
    _material.ambient = ambient;
}

void Object::setDiffuse(const glm::vec3 &diffuse)
{
    _material.diffuse = diffuse;
}

void Object::setSpecular(const glm::vec3 &specular)
{
    _material.specular = specular;
}

void Object::setShiness(FLOAT shiness)
{
    _material.shiness = shiness;
}

void Object::refelctLight(Light* light)
{
    // bindObject();
    const auto &color = light->getLight();
    _shader->uniformSetvec3("L.position", color.position);
    _shader->uniformSetvec3("L.ambient", color.ambient);
    _shader->uniformSetvec3("L.diffuse", color.diffuse);
    _shader->uniformSetvec3("L.specular", color.specular);
    _shader->uniformSet1i("L.type", color.type);
    _shader->uniformSet1f("L.constant", color.constant);
    _shader->uniformSet1f("L.linear", color.linear);
    _shader->uniformSet1f("L.quadratic", color.quadratic);
    _shader->uniformSetvec3("L.direction", color.direction);
    _shader->uniformSet1f("L.cutoff", color.cutoff);
    _shader->uniformSet1f("L.outcutoff", color.outcutoff);
    _shader->uniformSetvec3("camerapos", Camera::getInstance()->getCameraPosition());
}

void Object::refelctMaterial()
{
    _shader->uniformSetvec3("M.ambient", _material.ambient);
    _shader->uniformSetvec3("M.diffuse", _material.diffuse);
    _shader->uniformSetvec3("M.specular", _material.specular);
    _shader->uniformSet1f("M.shiness", _material.shiness);
    if(_texture)
    {
        activeTexture();
    }
}

void Object::fill(Proto::Common::ObjectProto &out)
{
    //--------------------测试用
    Proto::Common::ShaderProto &tmp= *(out.mutable_shader());
    tmp.set_x(1);
    Proto::Common::TextureProto &tmp2 = *(out.add_texture());
    tmp2.set_x(2);
    //--------------------
}

Shader* Object::getShader()
{
    return _shader;
}