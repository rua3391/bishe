#ifndef G_OBJ_MANAGER_H
#define G_OBJ_MANAGER_H

#include "zSdk.h"
#include "zSingleton.h"
#include "zEntry.h"
/**
 * \brief 全局物件管理器
 * 
 */ 
class Object;
class GobjManager : public zSingletonBase<GobjManager>, public zEntryManager<Object>
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        GobjManager();
        /**
         * \brief 析构函数
         * 
         */
        ~GobjManager(); 
};

#endif