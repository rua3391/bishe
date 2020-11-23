#ifndef Z_ENTRY_H
#define Z_ENTRY_H

#include "zSdk.h"

class zEntry
{
    public:
        /**
         * \brief 物件id
         * 
         */ 
        union
        {
            /**
             * \brief 前2字节
             * 
             */ 
            DWORD id1;
            /**
             * \brief 后2字节
             * 
             */
            DWORD id2; 
            /**
             * \brief 物件id
             * 
             */ 
            QWORD id;
        };
        /**
         * \brief 物件名字
         * 
         */
        std::string name;
        /**
         * \brief 默认构造函数
         * 
         */
        zEntry() : id(0), name(""){}  
        /**
         * \brief 构造函数
         * \param id 物件id
         * \param name 物件名称
         * 
         */
        zEntry(QWORD id, const std::string &name) { this->id = id; this->name = name;}
        /**
         * \brief 构造函数
         * \param id1 物件id1
         * \param id2 物件id2
         * \param name 物件名称
         * 
         */
        zEntry(DWORD id1, DWORD id2, std::string &name) { this->id1 = id1; this->id2 = id2; this->name = name;} 
        /**
         * \brief 析构函数
         * 
         */
        ~zEntry() {} 
};

/**
 * \brief 遍历物件管理器规则
 * 
 */
template<typename T>
class zCallback
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        zCallback() {};
        /**
         * \brief 析构函数
         * 
         */ 
        virtual ~zCallback() {};
        /**
         * \brief 规则详细, 如果return false立刻停止遍历
         * 
         */ 
        virtual bool exec(T* ) {}
        /**
         * \brief 规则详细, return true则删除该物件
         * 
         */
        virtual bool isit(T* ) {} 
}; 

/**
 * \brief 物件管理器，用于管理物件
 * 
 */ 
template <typename T>
class zEntryManager
{
    public:
        /**
         * \brief 构造函数
         * 
         */
        zEntryManager() { }
        /**
         * \brief 析构函数
         * 
         */
        ~zEntryManager() {}
        /**
         * \brief 添加一个物件
         * 
         */
        bool add(T* obj)
        {
            if(get(obj->id))
                return false;
            _collection.push_back(obj);
            return true;
        }
        /**
         * \brief 获取一个物件
         * \param id 物件id
         * 
         */ 
        T* get(QWORD id)
        {
            for(DWORD i = 0; i < _collection.size(); ++i)
            {
                if(id == _collection[i]->id)
                    return _collection[i];
            }
            return NULL;
        }
        /**
         * \brief 删除一个物件
         * 
         */
        void remove(T* obj)
        {
            for(DWORD i = 0; i < _collection.size(); ++i)
            {
                if(_collection[i] == obj)
                    QUICK_RELEASE(_collection, i);
            }
        } 
        /**
         * \brief 按规则遍历物件
         * 
         */ 
        void execEvery(zCallback<T> &rule)
        {
            for(DWORD i = 0; i < _collection.size(); ++i)
            {
                if(!rule.exec(_collection[i]))
                    return;
            }
        }
        void deleteEveryif(zCallback<T> &rule)
        {
            for(DWORD i = 0; i < _collection.size(); ++i)
            {
                T* obj = _collection[i];
                if(rule.isit(obj))
                {
                    QUICK_RELEASE(_collection, i);
                    SAFE_DELETE(obj);
                }
            }
        }
    private:
        /**
         * \brief 物体集合
         * 
         */
        typedef std::vector<T* > zEntryVec;
        /**
         * \brief 存放物体的集合 
         * 
         */
        zEntryVec _collection;
};


#endif