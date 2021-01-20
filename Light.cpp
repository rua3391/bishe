#include "Light.h"
#include "zSnowFlake.h"
#include "GLightManager.h"

Light::Light(LightType type) : zEntry(id, name), cModule("LIGHT")
{
    this->id = generateId();
    this->_light.type = type;
}

Light::Light(QWORD id, const std::string &name) : zEntry(id, name), cModule("LIGHT")
{

}

Light::~Light()
{

}

void Light::serialize(void* out)
{

}

void Light::unserialize()
{

}

void Light::fill(Proto::Common::LightProto &out)
{
    out.set_x(_light.position.x);
    out.set_y(_light.position.y);
    out.set_z(_light.position.z);
}

bool Light::init(const glm::vec3 &pos)
{
    _light.position = pos;
    GLightManager::getInstance()->add(this);
}

void Light::final()
{

}

const Lightcolor& Light::getLight()
{
    return _light;
}

const glm::vec3& Light::getPosition()
{
    return _light.position;
}

const SDWORD Light::getType()
{
    return _light.type;
}

void Light::setAmbientLight(const glm::vec3& ambient)
{
    _light.ambient = ambient;
}

void Light::setDiffuseLight(const glm::vec3& diffuse)
{
    _light.diffuse = diffuse;
}

void Light::setSpecularLight(const glm::vec3& specular)
{
    _light.specular = specular;
}

void Light::setLightConstant(FLOAT num)
{
    _light.constant = num;
}

void Light::setLightLinear(FLOAT num)
{
    _light.linear = num;
}

void Light::setLightQuadratic(FLOAT num)
{
    _light.quadratic = num;
}

void Light::setLightDirection(const glm::vec3& dir)
{
    _light.direction = dir;
}

void Light::setLightCutoff(FLOAT num)
{
    _light.cutoff = num;
}

void Light::setLightOutCutoff(FLOAT num)
{
    _light.outcutoff = num;
}

void Light::setLightColor(const Lightcolor& lightcolor)
{
    _light.ambient = lightcolor.ambient;
    _light.diffuse = lightcolor.diffuse;
    _light.specular = lightcolor.specular;
    _light.position = lightcolor.position;
}

void Light::setLightPosition(const glm::vec3 &position)
{
    _light.position = position;
}