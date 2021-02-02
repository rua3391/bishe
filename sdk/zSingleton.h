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
            if(!instance.get())
            {
                instance.reset(new T());
            }   
            return instance.get();
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
        ~zSingletonBase() {}
    protected:
        /**
         * \brief 实例
         * 
         */
        static std::shared_ptr<T> instance; 
};

template<typename T>
std::shared_ptr<T> zSingletonBase<T>::instance = std::shared_ptr<T>(NULL);
#endif