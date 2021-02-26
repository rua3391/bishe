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
             * \brief 前4字节
             * 
             */ 
            DWORD id1;
            /**
             * \brief 后4字节
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
        virtual bool exec(T* obj) {return false;}
        /**
         * \brief 规则详细, return true则删除该物件
         * 
         */
        virtual bool isit(T* obj) {return true;} 
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
        void remove(DWORD id)
        {
            for(DWORD i = 0; i < _collection.size(); ++i)
            {
                if(_collection[i]->id == id)
                    QUICK_RELEASE(_collection, i);
            }
        }
        /**
         * \brief 遍历物件 返回false时立刻停止
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
        /**
         * \brief 遍历物件, 但不满足时不停止
         * 
         */ 
        void execEveryN(zCallback<T> &rule)
        {
            std::function<void(T*)> isit= [&](T* obj)->void
            {
                rule.exec(obj);
            };
            std::for_each(_collection.begin(), _collection.end(), isit);
        }
        /**
         * \brief 按规则删除物件
         * 
         */ 
        void deleteEveryif(zCallback<T> &rule)
        {
            for(DWORD i = 0; i < _collection.size();)
            {
                T* obj = _collection[i];
                if(rule.isit(obj))
                {
                    QUICK_RELEASE(_collection, i);
                    SAFE_DELETE(obj);
                }
                else
                {
                    ++i;
                }
            }
        }
        /**
         * \brief 获取所有物件
         * 
         */
        void getEveryId(std::vector<QWORD > &idvec)
        {
            std::function<void(T*)> fun = [&](T* obj)
            {
                idvec.push_back(obj->id);
            };
            std::for_each(_collection.begin(), _collection.end(), fun);
        } 
        /**
         * \brief 返回物件管理器size
         * 
         */
        DWORD size()
        {
            return _collection.size();
        } 
    public:
        /**
         * \brief 随机访问 debug用
         * 
         */
        T* operator[](DWORD i)
        {
            if(i < size())
                return _collection[i];
            else
                return NULL;
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