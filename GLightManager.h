#ifndef G_LIGHT_MANAGER_H
#define G_LIGHT_MANAGER_H

#include "zSdk.h"
#include "zSingleton.h"
#include "zEntry.h"
#include "Common.pb.h"
/**
 * \brief 全局物件管理器
 * 
 */ 
class Light;
class GLightManager : public zSingletonBase<GLightManager>, public zEntryManager<Light>
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        GLightManager();
        /**
         * \brief 析构函数
         * 
         */
        ~GLightManager();
    public:
        /**
         * \brief 添加一个光源 
         * 
         */
        void addLight(Light* light);
        /**
         * \brief 删除一个光源
         * 
         */
        void removeLight(Light* light);
        /**
         * \brief 存储所有光源内容
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