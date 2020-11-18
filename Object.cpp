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
    _projection(1.0f),
    _activenum(0)
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

bool Object::init(FLOAT *buffer, DWORD size, const std::string &vertex_file, const std::string &fragment_file)
{
    if(!buffer)
    {
        error("空指针");
        return false;
    }
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(FLOAT), buffer, GL_STATIC_DRAW);
    if(!_shader)
    {
        _shader = new Shader();
        if(!_shader)
        {
            ERROR("内存空间不足, shader创建失败");
            return false;    
        }
    }
    
    if(!_shader->init(vertex_file, fragment_file))
    {
        error("shader初始化失败");
        return false;
    }
    debug("物件初始化成功");
    this->id = _vao;
    if(!GObjManager::getInstance()->add(this))
    {
        error("物体加入失败, id已存在->%u", _vao);
    }
    else
    {
        debug("物体加入全局物件管理器完毕, id->%u, vbo->%u", _vao, _vbo);
    }
    return true;
}

bool Object::initTexture(std::string path)
{
    if(!_texture)
    {
        _texture = new Texture();
        if(!_texture)
        {
            ERROR("内存空间不足, Texture创建失败");
            return false;
        }
    }
    if(!_texture->init(path, _activenum++))
    {
        error("texture初始化失败");
        return false;
    }
    return true;
}

void Object::avtiveTexture()
{
    for(DWORD i = 0; i < _activenum; ++i)
    {
        _texture->activeTexture(i);
        _shader->uniformSet1i("Texture" + std::to_string(i), i);
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

void Object::updateModel(glm::vec3 translation, FLOAT radians, glm::vec3 rotation, glm::vec3 scale)
{
    _model = glm::translate(_model, translation);
    if(radians)
        _model = glm::rotate(_model, glm::radians(radians), rotation);
    _model = glm::scale(_model, scale);
}

void Object::setPosition()
{
    // bindObject();
    DWORD width = Engine::getInstance()->screenx;
    DWORD height = Engine::getInstance()->screeny;
	_view = Camera::getInstance()->getViewMatrix();
    _projection = glm::perspective(glm::radians(Camera::getInstance()->getCameraZoom()), (FLOAT)width / (FLOAT)height, 0.1f, 100.0f);
    _shader->uniformSetmat4("model", _model);
    _shader->uniformSetmat4("view", _view);
    _shader->uniformSetmat4("projection", _projection);
    glm::mat4 reset(1.0f);
    _model = reset;
}

void Object::setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, FLOAT shiness)
{
    // bindObject();
    _shader->uniformSetvec3("M.ambientcolor", ambient);
    _shader->uniformSetvec3("M.diffuse", diffuse);
    _shader->uniformSetvec3("M.specular", specular);
    _shader->uniformSet1f("M.shiness", shiness);
}

void Object::setColor(const Lightcolor &color)
{
    // bindObject();
    _shader->uniformSetvec3("L.position", color.position);
    _shader->uniformSetvec3("L.ambientlight", color.ambient);
    _shader->uniformSetvec3("L.diffuselight", color.diffuse);
    _shader->uniformSetvec3("L.specularlight", color.specular);
    _shader->uniformSetvec3("camerapos", Camera::getInstance()->getCameraPosition());
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