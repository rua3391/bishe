#ifndef G_OBJ_MANAGER_H
#define G_OBJ_MANAGER_H

#include "zSdk.h"
#include "zSingleton.h"
#include "zEntry.h"
#include "Common.pb.h"
/**
 * \brief 全局物件管理器
 * 
 */ 
class Object;
class GObjManager : public zSingletonBase<GObjManager>, public zEntryManager<Object>
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        GObjManager();
        /**
         * \brief 析构函数
         * 
         */
        ~GObjManager();
    public:
        /**
         * \brief 添加一个物件 
         * 
         */
        void addObj(Object* obj);
        /**
         * \brief 删除一个物件
         * 
         */
        void removeObj(Object* obj);
        /**
         * \brief 存储所有物件内容
         * 
         */
        void save(Proto::Common::EngineData &out);
        /**
         * \brief 销毁全部obj
         * 
         */
        void final();     
};

#endif