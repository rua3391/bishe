#include "GLightManager.h"
#include "Light.h"

GLightManager::GLightManager()
{

}

GLightManager::~GLightManager()
{

}

void GLightManager::addLight(Light *light)
{
    add(light);
}

void GLightManager::removeLight(Light *light)
{
    remove(light);
}

void GLightManager::save(Proto::Common::EngineData &out)
{
    struct callback : public zCallback<Light>
    {
        Proto::Common::EngineData &_target;
        callback(Proto::Common::EngineData &target) : _target(target) {}
        ~callback(){}
        bool exec(Light* light)
        {
            light->fill(*_target.add_light());
            return true;
        }
    };
    callback call(out);
    this->execEvery(call);
}

void GLightManager::final()
{
    struct callback : public zCallback<Light>
    {
        callback(){}
        ~callback(){}
    };
    callback call;
    this->deleteEveryif(call);
}