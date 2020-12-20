#include "GObjManager.h"
#include "Object.h"

GObjManager::GObjManager()
{

}

GObjManager::~GObjManager()
{

}

void GObjManager::addObj(Object *obj)
{
    add(obj);
}

void GObjManager::removeObj(Object *obj)
{
    remove(obj);
}

void GObjManager::save(Proto::Common::EngineData &out)
{
    struct callback : public zCallback<Object>
    {
        Proto::Common::EngineData &_target;
        callback(Proto::Common::EngineData &target) : _target(target) {}
        ~callback(){}
        bool exec(Object* obj)
        {
            obj->fill(*_target.add_object());
            return true;
        }
    };
    callback call(out);
    this->execEvery(call);
}

void GObjManager::final()
{
    struct callback : public zCallback<Object>
    {
        callback(){}
        ~callback(){}
    };
    callback call;
    this->deleteEveryif(call);
}