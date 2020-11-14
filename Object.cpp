#include "Common.pb.h"

#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Engine.h"

Object::Object() : 
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
    SAFE_DELETE(_shader);
    SAFE_DELETE(_texture);
}

bool Object::init(FLOAT *buffer, const std::string &vertex_file, const std::string &fragment_file)
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    _shader->init(vertex_file, fragment_file);
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

void Object::setPosition()
{
    bindObject();
    DWORD width = Engine::getInstance()->screenx;
    DWORD height = Engine::getInstance()->screeny;
	_view = Camera::getInstance()->getViewMatrix();
    _projection = glm::perspective(glm::radians(Camera::getInstance()->getCameraZoom()), (FLOAT)width / (FLOAT)height, 0.1f, 100.0f);
    _shader->uniformSetmat4("model", _model);
    _shader->uniformSetmat4("view", _view);
    _shader->uniformSetmat4("projection", _projection);
}