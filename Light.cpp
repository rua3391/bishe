#include "Light.h"

Light::Light() : cModule("LIGHT")
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

void Light::final()
{

}

const Lightcolor& Light::getLight()
{
    return _light;
}