#ifndef Z_SINGLETON_H
#define Z_SINGLETON_H

#include <cstdlib>
#include "zNoneCopy.h"
/**
 * \brief 单例模式 懒汉单例模式, 需要自行初始化资源
 * 
 */ 
template <typename T>
class zSingletonBase : private zNoneCopy
{
    public:
        /**
         * \brief 获取实例
         * \return 返回实例对象
         * 
         */ 
        static T* getInstance()
        {
            if(instance == NULL)
            {
                instance = new T();
            }   
            return instance;
        }
        /**
         * \brief 删除实例对象
         * 
         */ 
        static void deleteInstance()
        {
            SAFE_DELETE(instance);
        }
    protected:
        /**
         * \brief 构造函数
         * 
         */ 
        zSingletonBase() {}
        /**
         * \brief 析构函数
         * 
         */ 
        ~zSingletonBase() { SAFE_DELETE(instance);}
    protected:
        /**
         * \brief 实例
         * 
         */
        static T* instance; 
};

template <typename T> T* zSingletonBase<T>::instance = NULL;

#endif