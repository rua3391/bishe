#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Engine.h"
#include "Light.h"
#include "GObjManager.h"
#include "GLightManager.h"

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
	glBufferData(GL_ARRAY_BUFFER, buf.size() * sizeof(FLOAT), &buf[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(FLOAT), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(FLOAT), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(FLOAT), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

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

void Object::reflectLight()
{
    // bindObject();
    DWORD size = GLightManager::getInstance()->size();
    _shader->uniformSet1i("size", size);
    _shader->uniformSetvec3("camerapos", Camera::getInstance()->getCameraPosition());
    struct LightCallback : public zCallback<Light>
    {
        LightCallback(Object *o) : obj(o){}
        ~LightCallback(){};
        bool exec(Light *light)
        {
            const auto &color = light->getLight();
            std::string tmp = "[" + std::to_string(cnt) + "]";
            obj->_shader->uniformSetvec3("L" + tmp + ".position", color.position);
            obj->_shader->uniformSetvec3("L" + tmp + ".ambient", color.ambient);
            obj->_shader->uniformSetvec3("L" + tmp + ".diffuse", color.diffuse);
            obj->_shader->uniformSetvec3("L" + tmp + ".specular", color.specular);
            obj->_shader->uniformSet1i("L" + tmp + ".type", color.type);
            obj->_shader->uniformSet1f("L" + tmp + ".constant", color.constant);
            obj->_shader->uniformSet1f("L" + tmp + ".linear", color.linear);
            obj->_shader->uniformSet1f("L" + tmp + ".quadratic", color.quadratic);
            obj->_shader->uniformSetvec3("L" + tmp + ".direction", color.direction);
            obj->_shader->uniformSet1f("L" + tmp + ".cutoff", color.cutoff);
            obj->_shader->uniformSet1f("L" + tmp + ".outcutoff", color.outcutoff);
            ++cnt;
            return true;
        }
        Object *obj;
        DWORD cnt;
    };
    LightCallback lightcallback(this);
    GLightManager::getInstance()->execEveryN(lightcallback);
}

void Object::reflectMaterial()
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

void Object::draw()
{
    bindObject();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}